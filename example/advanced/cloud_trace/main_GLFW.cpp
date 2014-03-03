/**
 *  @example advanced/cloud_trace/main_GLFW.cpp
 *  @brief GLFW-based implementation of the main function.
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "main_common.hpp"
#include "render_data.hpp"
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

void render_loop(RenderData& data)
{
	Context gl;
	ResourceAllocator alloc;
	Raytracer raytracer(data, alloc);
	Renderer renderer(data, alloc);
	Saver saver(data);

	unsigned face = 0;
	double done = 0;

	while(true)
	{
		if(done == 0)
		{
			raytracer.Use(data);
			raytracer.InitFrame(data, face);
		}

		if(done < 1)
		{
			raytracer.Use(data);
			done = raytracer.Raytrace(data);
			raytracer.SwapBuffers(data);

			gl.Disable(Capability::ScissorTest);
			renderer.Use(data);
			renderer.Render(data, raytracer.FrontTexUnit());
			gl.Enable(Capability::ScissorTest);
			glfwSwapBuffers();
		}
		else if(face < 6)
		{
			glfwSwapBuffers();
			saver.SaveFrame(data, face);
			if(face < 5)
			{
				done = 0;
				face++;
			}
		}
		glfwPollEvents();

		int new_x, new_y;
		glfwGetWindowSize(&new_x, &new_y);
		if(new_x > 0)
		{
			data.render_width = unsigned(new_x);
		}
		if(new_y > 0)
		{
			data.render_height = unsigned(new_y);
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

int main_GLFW(RenderData& data)
{
	GLFWInitializer glfw_initializer;

	if(!glfwOpenWindow(
		data.render_width,
		data.render_height,
		8, 8, 8, 8,
		32, 8,
		GLFW_WINDOW
	)) throw std::runtime_error("Error creating GLFW window");
	else
	{
		glfwSetWindowTitle("CloudTrace: OGLplus cloud ray-tracer");
		glfwPollEvents();

		GLAPIInitializer api_init;

		render_loop(data);
	}
	return 0;
}

} // namespace cloud_trace
} // namespace oglplus

int main (int argc, char ** argv)
{
	using oglplus::cloud_trace::main_GLFW;
	using oglplus::cloud_trace::RenderData;

	RenderData data(argc, argv);
	return do_run_main(main_GLFW, data);
}

