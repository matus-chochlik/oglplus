/*
 *  .file example/glx_main.cpp
 *  Implements GLX-based program main function for running examples
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>

#if OGLPLUS_LINK_LIBRARY
# include <oglplus/lib.hpp>
#endif

#include <oglplus/glx/context.hpp>
#include <oglplus/glx/fb_configs.hpp>
#include <oglplus/glx/version.hpp>
#include <oglplus/glx/pixmap.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/x11/color_map.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/display.hpp>

#include <oglplus/os/semaphore.hpp>
#include <oglplus/os/steady_clock.hpp>

#include <oglplus/config.hpp>

#include <oglplus/ext/ARB_debug_output.hpp>

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cassert>

#include "example.hpp"
#include "example_main.hpp"

namespace oglplus {

void run_example_loop(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	GLuint width,
	GLuint height
)
{
	std::cout << "-+-[Begin]" << std::endl;
#if GL_ARB_debug_output && !OGLPLUS_NO_LAMBDAS
	ARB_debug_output dbg;
	ARB_debug_output::LogSink sink(
		[](const ARB_debug_output::CallbackData& data) -> void
		{
			std::cout << " |" << std::endl;
			std::cout << " +-+-[" << data.id << "] '" <<
				data.message << "'" << std::endl;
			std::cout << " | +---[source]   '" <<
				EnumValueName(data.source).c_str()  << "'" << std::endl;
			std::cout << " | +---[type]     '" <<
				EnumValueName(data.type).c_str()  << "'" << std::endl;
			std::cout << " | `---[severity] '" <<
				EnumValueName(data.severity).c_str()  << "'" << std::endl;
		}
	);

	dbg.Control(
		DebugOutputARBSource::DontCare,
		DebugOutputARBType::DontCare,
		DebugOutputARBSeverity::Low,
		true
	);

	dbg.InsertMessage(
		DebugOutputARBSource::Application,
		DebugOutputARBType::Other,
		0,
		DebugOutputARBSeverity::Low,
		"Starting main loop"
	);
#endif // GL_ARB_debug_output

	win.SelectInput(
		StructureNotifyMask|
		PointerMotionMask|
		KeyPressMask
	);
	::Atom wmDelete = ::XInternAtom(display, "WM_DELETE_WINDOW", True);
	::XSetWMProtocols(display, win, &wmDelete, 1);

	XEvent event;
	os::steady_clock os_clock;
	ExampleClock clock;
	bool done = false;
	while(!done)
	{
		while(display.NextEvent(event))
		{
			switch(event.type)
			{
				case ClientMessage:
				case DestroyNotify:
					done = true;
					break;
				case MotionNotify:
					example->MouseMove(
						event.xmotion.x,
						height-
						event.xmotion.y,
						width,
						height
					);
					break;
				case KeyPress:
					if(::XLookupKeysym(
						&event.xkey,
						0
					) == XK_Escape) done = true;
					break;
				default:;
			}
		}
		clock.Update(os_clock.seconds());
		if(!example->Continue(clock)) break;
		example->Render(clock);
		ctx.SwapBuffers(win);
	}
	std::cout << " `-[Done]" << std::endl;
}

void make_screenshot(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	GLuint width,
	GLuint height,
	const char* screenshot_path
)
{
	XEvent event;

	double s = example->HeatUpTime();
	double t = example->ScreenshotTime();
	double dt = example->FrameTime();

	ExampleClock clock(s);

	// heat-up
	while(true)
	{
		while(display.NextEvent(event));
		s += dt;
		clock.Update(s);
		example->Render(clock);
		if(s < t) ctx.SwapBuffers(win);
		else break;
	}
	while(display.NextEvent(event));
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

void run_example(const x11::Display& display, const char* screenshot_path)
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

	const GLuint width = 800, height = 600;

	x11::Window win(
		display,
		vi,
		x11::Colormap(display, vi),
		"OGLplus example",
		width, height
	);

	ExampleParams params;
	setupExample(params);
	params.Check();

	glx::Context ctx(display, fbc, 3, 3);

	ctx.MakeCurrent(win);

	{
		oglplus::GLAPIInitializer api_init;
		std::unique_ptr<Example> example(makeExample(params));

		example->Reshape(width, height);
		example->MouseMove(width/2, height/2, width, height);

		if(screenshot_path)
		{
			make_screenshot(
				display,
				win,
				ctx,
				example,
				width,
				height,
				screenshot_path
			);
		}
		else
		{
			run_example_loop(
				display,
				win,
				ctx,
				example,
				width,
				height
			);
		}
	}
	ctx.Release(display);
}

} // namespace oglplus

int glx_example_main(int argc, char ** argv)
{
	// check if we want to do a screenshot
	const char* screenshot_path = 0;
	if((argc == 3) && (std::strcmp(argv[1], "--screenshot") == 0))
		screenshot_path = argv[2];
	// run the main loop
	oglplus::run_example(oglplus::x11::Display(), screenshot_path);
	std::cout << "Done" << std::endl;
	return 0;
}

int main (int argc, char ** argv)
{
	return oglplus::example_main(glx_example_main, argc, argv);
}

