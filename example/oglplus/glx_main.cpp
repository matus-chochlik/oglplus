/**
 *  .file example/glx_main.cpp
 *  Implements GLX-based program main function for running examples
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/glx/context.hpp>
#include <oglplus/glx/fb_configs.hpp>
#include <oglplus/glx/version.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/x11/color_map.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/display.hpp>

#include <oglplus/shader.hpp>

#include <stdexcept>
#include <iostream>
#include <ctime>
#include <cassert>

#include "example.hpp"

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
		//GLX_SAMPLE_BUFFERS  , 1,
		//GLX_SAMPLES         , 4,
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
		"oglplus example window"
	);
	glx::Context ctx(display, fbc, 3, 0);
	ctx.MakeCurrent(win);
	{
		std::unique_ptr<Example> example(makeExample());
		std::time_t start = std::time(0);
		while(example->Continue(std::time(0) - start))
		{
			example->Render();
			ctx.SwapBuffers(win);
		}
	}
	ctx.Release(display);
}

} // namespace oglplus

int main (int argc, char ** argv)
{
	try
	{
		oglplus::run(oglplus::x11::Display());
		std::cout << "Done" << std::endl;
	}
	catch(oglplus::CompileOrLinkError& cle)
	{
		std::cerr << cle.what() << ": " << cle.Log() << std::endl;
	}
	catch(oglplus::Error& e)
	{
		std::cerr << e.what() << " [" << e.File() << ":" << e.Line() << "]" << std::endl;
	}
	catch(std::exception& se)
	{
		std::cerr << "Error: " << se.what() << std::endl;
		return 1;
	}
	return 0;
}

