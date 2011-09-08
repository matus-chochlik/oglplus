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

#include <oglplus/compile_error.hpp>
#include <oglplus/application.hpp>

#include <stdexcept>
#include <iostream>
#include <chrono>
#include <cassert>

#include "test.hpp"

namespace oglplus {

void run(const x11::Display& display)
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
	x11::Window win(
		display,
		vi,
		x11::ColorMap(display, vi),
		"oglplus test window",
		800, 600
	);
	glx::Context ctx(display, fbc, 3, 0);
	ctx.MakeCurrent(win);
	{
		size_t frames = 0;
		std::unique_ptr<Test> example(makeTest());
		double period =
			double(std::chrono::system_clock::period::num)/
			double(std::chrono::system_clock::period::den);
		auto start = std::chrono::system_clock::now();
		while(1)
		{
			auto now = std::chrono::system_clock::now();
			double t = (now - start).count() * period;
			if(!example->Continue(t)) break;
			example->Render(t);
			ctx.SwapBuffers(win);
			++frames;
		}
		auto end = std::chrono::system_clock::now();
		double seconds = (end - start).count() * period;
		std::cout <<
			frames << " frames rendered in " <<
			seconds <<" seconds = " <<
			frames / seconds << " fps." <<
			std::endl;
	}
	ctx.Release(display);
}

} // namespace oglplus

int main (int argc, char ** argv)
{
	try
	{
		oglplus::Application::ParseCommandLineOptions(argc, argv);
		oglplus::run(oglplus::x11::Display());
	}
	catch(oglplus::ProgramBuildError& pbe)
	{
		std::cerr <<
			"Error [in gl" << pbe.GLSymbol() << "]: " <<
			pbe.what() << ": " <<
			pbe.Log() <<
			std::endl;
	}
	catch(oglplus::LimitError& le)
	{
		std::cerr <<
			"Limit error: ("<< le.Value() << ") exceeds (" <<
			le.GLSymbol() << " == " << le.Limit() << ") " <<
			" [" << le.File() << ":" << le.Line() << "] " <<
			std::endl;
	}
	catch(oglplus::Error& err)
	{
		std::cerr <<
			"Error (in gl" << err.GLSymbol() << "): " <<
			err.what() <<
			" [" << err.File() << ":" << err.Line() << "] ";
		auto i = err.Properties().begin(), e = err.Properties().end();
		while(i != e)
		{
			std::cerr << "<" << i->first << "='" << i->second << "'>";
			++i;
		}
		std::cerr <<std::endl;
	}
	catch(std::exception& se)
	{
		std::cerr << "Error: " << se.what() << std::endl;
		return 1;
	}
	return 0;
}

