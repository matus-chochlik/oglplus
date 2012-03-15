/*
 *  .file example/glx_main.cpp
 *  Implements GLX-based program main function for running examples
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>

#include <oglplus/glx/context.hpp>
#include <oglplus/glx/fb_configs.hpp>
#include <oglplus/glx/version.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/x11/color_map.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/display.hpp>
#include <oglplus/os/semaphore.hpp>

#include <oglplus/config.hpp>
#include <oglplus/compile_error.hpp>
#include <oglplus/application.hpp>

#include <oglplus/ext/ARB_debug_output.hpp>

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <cstring>
#include <cassert>

#include "example.hpp"

namespace oglplus {

void run_loop(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	size_t width,
	size_t height
)
{
#if GL_ARB_debug_output
	ARB_debug_output dbg;
	auto sink = dbg.Install(
		[](
			DebugOutputSource source,
			DebugOutputType type,
			GLuint id,
			DebugOutputSeverity severity,
			GLsizei length,
			const GLchar* message
		) -> void
		{
			std::cout <<
				message <<
				std::endl;
		}
	);

	dbg.InsertMessage(
		DebugOutputSource::Application,
		DebugOutputType::Other,
		0,
		DebugOutputSeverity::Low,
		"Starting main loop"
	);
#endif // GL_ARB_debug_output

	win.SelectInput(
		example->UsesMouseMotion()?
		PointerMotionMask:
		0
	);
	XEvent event;
	double period =
		double(std::chrono::system_clock::period::num)/
		double(std::chrono::system_clock::period::den);
	auto start = std::chrono::system_clock::now();
	while(1)
	{
		while(display.NextEvent(event))
		{
			switch(event.type)
			{
				case MotionNotify:
					example->MouseMove(
						event.xmotion.x,
						height-
						event.xmotion.y,
						width,
						height
					);
					break;
				default:;
			}
		}
		auto now = std::chrono::system_clock::now();
		double t = (now - start).count() * period;
		if(!example->Continue(t)) break;
		example->Render(t);
		ctx.SwapBuffers(win);
	}
}

void make_screenshot(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	size_t width,
	size_t height,
	const char* screenshot_path
)
{
	XEvent event;

	double s = example->HeatUpTime();
	double t = example->ScreenshotTime();
	double dt = example->FrameTime();

	// heat-up
	while(s < t)
	{
		while(display.NextEvent(event));
		example->Render(s);
		s += dt;
		ctx.SwapBuffers(win);
	}
	while(display.NextEvent(event));
	// render the frame
	example->Render(t);
	glFinish();
	//save it to a file
	std::vector<char> pixels(width * height * 3);
	glReadPixels(
		0, 0,
		width,
		height,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		pixels.data()
	);
	std::ofstream output(screenshot_path);
	output.write(pixels.data(), pixels.size());
	ctx.SwapBuffers(win);
}

void run(const x11::Display& display, const char* screenshot_path)
{
	static int visual_attribs[] =
	{
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
	};
	glx::Version version(display);
	version.AssertAtLeast(1, 3);

	glx::FBConfig fbc = glx::FBConfigs(
		display,
		visual_attribs
	).FindBest(display);

	x11::VisualInfo vi(display, fbc);

	const size_t width = 800, height = 600;

	x11::Window win(
		display,
		vi,
		x11::ColorMap(display, vi),
		"oglplus example window",
		width, height
	);
	glx::Context ctx(display, fbc, 3, 3);


	ctx.MakeCurrent(win);
	{
		ExampleParams params;
		std::unique_ptr<Example> example(makeExample(params));

		example->Reshape(width, height);
		example->MouseMove(width/2, height/2, width, height);

		if(screenshot_path)
			make_screenshot(
				display,
				win,
				ctx,
				example,
				width,
				height,
				screenshot_path
			);
		else run_loop(display, win, ctx, example, width, height);
	}
	ctx.Release(display);
}

} // namespace oglplus

int main (int argc, char ** argv)
{
	try
	{
		// this won't let running multiple examples at the same time
		oglplus::os::CriticalSection cs(0x091);
		// look at the options and extract useful things
		oglplus::Application::ParseCommandLineOptions(argc, argv);
		// check if we want to do a screenshot
		const char* screenshot_path = 0;
		if((argc == 3) && (std::strcmp(argv[1], "--screenshot") == 0))
			screenshot_path = argv[2];
		// run the main loop
		oglplus::run(oglplus::x11::Display(), screenshot_path);
		std::cout << "Done" << std::endl;
	}
	catch(oglplus::ProgramBuildError& pbe)
	{
		std::cerr <<
			"Error (in gl" << pbe.GLSymbol() << ", " <<
			pbe.ClassName() << ": '" <<
			pbe.ObjectDescription() << "'): " <<
			pbe.what() << ": " <<
			pbe.Log() <<
			std::endl;
		pbe.Cleanup();
	}
	catch(oglplus::LimitError& le)
	{
		std::cerr <<
			"Limit error: ("<< le.Value() << ") exceeds (" <<
			le.GLSymbol() << " == " << le.Limit() << ") " <<
			" [" << le.File() << ":" << le.Line() << "] " <<
			std::endl;
		le.Cleanup();
	}
	catch(oglplus::Error& err)
	{
		std::cerr <<
			"Error (in gl" << err.GLSymbol() << ", " <<
			err.ClassName() << ": '" <<
			err.ObjectDescription() << "' bound to '" <<
			err.BindTarget() << "'): " <<
			err.what() <<
			" [" << err.File() << ":" << err.Line() << "] ";
		auto i = err.Properties().begin(), e = err.Properties().end();
		while(i != e)
		{
			std::cerr << "<" << i->first << "='" << i->second << "'>";
			++i;
		}
		std::cerr <<std::endl;
		err.Cleanup();
	}
	catch(std::exception& se)
	{
		std::cerr << "Error: " << se.what() << std::endl;
		return 1;
	}
	return 0;
}

