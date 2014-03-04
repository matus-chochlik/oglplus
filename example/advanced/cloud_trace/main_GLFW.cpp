/**
 *  @example advanced/cloud_trace/main_GLFW.cpp
 *  @brief GLFW-based implementation of the main function.
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "main_common.hpp"
#include "app_data.hpp"
#include "resources.hpp"
#include "renderer.hpp"
#include "raytracer.hpp"
#include "saver.hpp"

#include <oglplus/gl.hpp>
#include <oglplus/fix_gl_version.hpp>

#include <GL/glfw.h>

#include <oglplus/config.hpp>

#include <stdexcept>
#include <iostream>

namespace oglplus {
namespace cloud_trace {

class GLFWInitializer
{
public:
	GLFWInitializer(void)
	{
		if(!glfwInit())
		{
			throw std::runtime_error("GLFW initialization error");
		}
	}

	~GLFWInitializer(void)
	{
		glfwTerminate();
	}
};

void render_loop(AppData& app_data)
{
	Context gl;
	ResourceAllocator alloc;

	RaytracerResources raytrace_res(app_data, alloc);
	Raytracer raytracer(app_data, raytrace_res);

	Renderer renderer(app_data, raytrace_res.dest_tex_unit);
	Saver saver(app_data);

	unsigned face = 0;
	unsigned tile = 0;
	const unsigned tiles = app_data.tiles();

	while(true)
	{
		raytracer.Use(app_data);

		if(tile == 0)
		{
			raytracer.ClearDest(app_data);
			raytracer.InitFrame(app_data, face);
		}

		if(tile < tiles)
		{
			raytracer.Raytrace(app_data, face, tile);

			gl.Disable(Capability::ScissorTest);
			raytracer.BlitBuffers(app_data, tile);

			renderer.Use(app_data);
			renderer.Render(app_data);

			gl.Enable(Capability::ScissorTest);
			glfwSwapBuffers();

			tile++;
		}
		else if(face < 6)
		{
			glfwSwapBuffers();
			saver.SaveFrame(app_data, face);
			if(face < 5)
			{
				tile = 0;
				face++;
			}
			else break;
		}
		glfwPollEvents();

		int new_x, new_y;
		glfwGetWindowSize(&new_x, &new_y);
		if(new_x > 0)
		{
			app_data.render_width = unsigned(new_x);
		}
		if(new_y > 0)
		{
			app_data.render_height = unsigned(new_y);
		}

		if(glfwGetKey(GLFW_KEY_ESC))
		{
			glfwCloseWindow();
			break;
		}
		if(!glfwGetWindowParam(GLFW_OPENED))
		{
			break;
		}
	}
}

int main_GLFW(AppData& app_data)
{
	GLFWInitializer glfw_initializer;

	if(!glfwOpenWindow(
		app_data.render_width,
		app_data.render_height,
		8, 8, 8, 8,
		32, 8,
		GLFW_WINDOW
	)) throw std::runtime_error("Error creating GLFW window");
	else
	{
		glfwSetWindowTitle("CloudTrace: OGLplus cloud ray-tracer");
		glfwPollEvents();

		GLAPIInitializer api_init;

		render_loop(app_data);
	}
	return 0;
}

} // namespace cloud_trace
} // namespace oglplus

int main (int argc, char ** argv)
{
	using oglplus::cloud_trace::main_GLFW;
	using oglplus::cloud_trace::AppData;

	AppData app_data(argc, argv);
	return do_run_main(main_GLFW, app_data);
}

