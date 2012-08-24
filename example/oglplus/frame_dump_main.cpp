/*
 *  .file example/frame_dump_main.cpp
 *  Implements GLX-based main function for saving rendered frames in raw RGBA
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
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

#include <oglplus/config.hpp>
#include <oglplus/compile_error.hpp>
#include <oglplus/application.hpp>

#include <stdexcept>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cassert>

#include "example.hpp"

namespace oglplus {

void run(const x11::Display& display, const char* prefix)
{
	if(!prefix) prefix = "/tmp/oglplus-frame-";

	std::vector<char> txtbuf(1024);
	std::cin.getline(txtbuf.data(), txtbuf.size());
	if(std::strcmp(prefix, txtbuf.data()) != 0) return;

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

	const size_t width = 852, height = 480;

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
		params.quality = 1.0f;
		std::unique_ptr<Example> example(makeExample(params));

		win.SelectInput(0);
		XEvent event;

		example->Reshape(width, height);
		example->MouseMove(width/2, height/2, width, height);
		double t = 0.0;
		double period = 1.0 / 25.0;
		size_t frame_no = 0;
		std::vector<char> pixels(width * height * 4);

		ExampleClock clock;
		while(1)
		{
			t += period;
			clock.Update(t);
			if(!example->Continue(clock)) break;
			example->Render(clock);
			glFinish();
			glReadPixels(
				0, 0,
				width,
				height,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				pixels.data()
			);
			glFinish();
			ctx.SwapBuffers(win);
			std::stringstream filename;
			filename <<
				prefix <<
				std::setfill('0') << std::setw(6) <<
				frame_no << ".rgba";
			{
				std::ofstream file(filename.str());
				file.write(pixels.data(), pixels.size());
				file.flush();
			}
			std::cout << filename.str() << std::endl;
			++frame_no;

			txtbuf.resize(filename.str().size()+1);
			std::cin.getline(txtbuf.data(), txtbuf.size());

			if(std::strncmp(
				filename.str().c_str(),
				txtbuf.data(),
				txtbuf.size()
			) != 0) break;
		}
	}
	ctx.Release(display);
}

} // namespace oglplus

int main (int argc, char ** argv)
{
	try
	{
		oglplus::Application::ParseCommandLineOptions(argc, argv);
		oglplus::run(oglplus::x11::Display(), argc>1?argv[1]:0);
	}
	catch(...) { return 1; }
	return 0;
}

