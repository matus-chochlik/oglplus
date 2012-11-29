/*
 *  .file example/frame_dump_main.cpp
 *  Implements GLX-based main function for saving rendered frames in raw RGBA
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/curve.hpp>

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

#if OGLPLUS_LINK_LIBRARY
# include <oglplus/lib.hpp>
#endif

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

	const GLuint width = 852, height = 480;

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

		example->Reshape(width, height);

		const std::size_t mouse_path_pts = 7;
		std::vector<Vec2f> mouse_path_pos(mouse_path_pts);
		std::vector<Vec2f> mouse_path_dir(mouse_path_pts);

		for(std::size_t p=0; p!= mouse_path_pts; ++p)
		{
			mouse_path_pos[p] = Vec2f(
				std::rand() % width,
				std::rand() % height
			);
			mouse_path_dir[p] = Vec2f(
				(std::rand()%2?1.0:-1.0)*10.0f*
				(0.2+float(std::rand())/float(RAND_MAX)*0.8),
				(std::rand()%2?1.0:-1.0)*10.0f*
				(0.2+float(std::rand())/float(RAND_MAX)*0.8)
			);
		}

		typedef CubicBezierLoop<Vec2f, double> Loop;

		double t = 0.0;
		double period = 1.0 / 25.0;
		GLuint frame_no = 0;
		std::vector<char> pixels(width * height * 4);
		ExampleClock clock;

		GLuint border = 32;

		while(1)
		{
			Vec2f mouse_pos = Loop(mouse_path_pos).Position(t*0.2);

			for(std::size_t p=0; p!= mouse_path_pts; ++p)
			{
				Vec2f dir = mouse_path_dir[p];
				Vec2f pos = mouse_path_pos[p];

				if((pos.x() < border) && (dir.x() < 0.0))
					dir = Vec2f(-dir.x(), dir.y());
				if((pos.y() < border) && (dir.y() < 0.0))
					dir = Vec2f( dir.x(),-dir.y());
				if((pos.x() > width-border) && (dir.x() > 0.0))
					dir = Vec2f(-dir.x(), dir.y());
				if((pos.y() >height-border) && (dir.y() > 0.0))
					dir = Vec2f( dir.x(),-dir.y());

				mouse_path_dir[p] = dir;
				mouse_path_pos[p] = pos + dir;
			}

			float mouse_x = mouse_pos.x();
			float mouse_y = mouse_pos.y();

			if(mouse_x < 0.0f) mouse_x = 0.0f;
			if(mouse_y < 0.0f) mouse_y = 0.0f;
			if(mouse_x > width) mouse_x = width;
			if(mouse_y > height) mouse_y = height;

			example->MouseMove(
				GLuint(mouse_x),
				GLuint(mouse_y),
				width,
				height
			);

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

