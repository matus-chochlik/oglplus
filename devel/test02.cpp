/**
 *  .file devel/test02.cpp
 *  This source file is here for development/testing purposes
 *  and its contents may change without any prior notice.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>

#include <oglplus/gl.hpp>
#include <oglplus/matrix.hpp>
#include <oglplus/all.hpp>
//
#include <oglplus/glx/context.hpp>
#include <oglplus/glx/fb_configs.hpp>
#include <oglplus/glx/version.hpp>
#include <oglplus/x11/window.hpp>
#include <oglplus/x11/color_map.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/display.hpp>
//
#include <string>
#include <stdexcept>
#include <cassert>

namespace oglplus {
namespace build {

class Cube
{
public:
	template <typename T>
	static GLsizei Vertices(
		std::vector<T>& dest,
		T x = T(1), 
		T y = T(1), 
		T z = T(1)
	)
	{
		const T c[8][3] = {
			{-T(x)/T(2), -T(y)/T(2), +T(z)/T(2)},
			{-T(x)/T(2), -T(y)/T(2), -T(z)/T(2)},
			{-T(x)/T(2), +T(y)/T(2), -T(z)/T(2)},
			{-T(x)/T(2), +T(y)/T(2), +T(z)/T(2)},
			{+T(x)/T(2), -T(y)/T(2), +T(z)/T(2)},
			{+T(x)/T(2), -T(y)/T(2), -T(z)/T(2)},
			{+T(x)/T(2), +T(y)/T(2), -T(z)/T(2)},
			{+T(x)/T(2), +T(y)/T(2), +T(z)/T(2)}
		};
		dest = {
			c[0][0], c[0][1], c[0][2],
			c[2][0], c[2][1], c[2][2],
			c[1][0], c[1][1], c[1][2],
			c[0][0], c[0][1], c[0][2],
			c[3][0], c[3][1], c[3][2],
			c[2][0], c[2][1], c[2][2],

			c[0][0], c[0][1], c[0][2],
			c[1][0], c[1][1], c[1][2],
			c[4][0], c[4][1], c[4][2],
			c[1][0], c[1][1], c[1][2],
			c[5][0], c[5][1], c[5][2],
			c[4][0], c[4][1], c[4][2],

			c[1][0], c[1][1], c[1][2],
			c[2][0], c[2][1], c[2][2],
			c[5][0], c[5][1], c[5][2],
			c[2][0], c[2][1], c[2][2],
			c[6][0], c[6][1], c[6][2],
			c[5][0], c[5][1], c[5][2],

			c[4][0], c[4][1], c[4][2],
			c[5][0], c[5][1], c[5][2],
			c[6][0], c[6][1], c[6][2],
			c[4][0], c[4][1], c[4][2],
			c[6][0], c[6][1], c[6][2],
			c[7][0], c[7][1], c[7][2],

			c[2][0], c[2][1], c[2][2],
			c[3][0], c[3][1], c[3][2],
			c[7][0], c[7][1], c[7][2],
			c[2][0], c[2][1], c[2][2],
			c[7][0], c[7][1], c[7][2],
			c[6][0], c[6][1], c[6][2],

			c[0][0], c[0][1], c[0][2],
			c[4][0], c[4][1], c[4][2],
			c[3][0], c[3][1], c[3][2],
			c[3][0], c[3][1], c[3][2],
			c[4][0], c[4][1], c[4][2],
			c[7][0], c[7][1], c[7][2]
		};
		return 3;
	}

	template <typename T>
	static GLsizei Normals(std::vector<T>& dest)
	{
		const T n[6][3] = {
			{-T(1),  T(0),  T(0)},
			{ T(0), -T(1),  T(0)},
			{ T(0),  T(0), -T(1)},
			{+T(1),  T(0),  T(0)},
			{ T(0), +T(1),  T(0)},
			{ T(0),  T(0),  +(1)}
		};
		dest = {
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],

			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],

			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],

			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],

			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],

			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2]
		};
		return 3;
	}

	template <typename T>
	static GLsizei Indices(std::vector<T>& dest)
	{
		dest = {
		 	 T(0),  T(1),  T(2),  T(3),  T(4),  T(5),
		 	 T(6),  T(7),  T(8),  T(9), T(10), T(11),
		 	T(12), T(13), T(14), T(15), T(16), T(17),
			T(18), T(19), T(20), T(21), T(22), T(23),
			T(24), T(25), T(26), T(27), T(28), T(29),
			T(30), T(31), T(32), T(33), T(34), T(35)
		};
		return 6 * 2 * 3;
	}
};

} // namespace build

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
		"OpenGL 3.0 window"
	);
	glx::Context ctx(display, fbc, 3, 0);
	ctx.MakeCurrent(win);

	//
	{
		using namespace oglplus;

		VertexShader vs;
		vs.Source(" \
			#version 330\n \
			in vec4 vertex; \
			in vec3 normal; \
			uniform mat4 projectionMatrix; \
			uniform mat4 cameraMatrix; \
			out vec4 outColor; \
			void main(void) \
			{ \
				gl_Position = projectionMatrix * cameraMatrix * vertex; \
				outColor = vec4(abs(normal), 1.0); \
			} \
		");
		vs.Compile();
		FragmentShader fs;
		fs.Source(" \
			#version 330\n \
			in vec4 outColor; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = outColor; \
			} \
		");
		fs.Compile();
		Program prog;
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		prog.Link();
		prog.Use();
		//
		//
		VertexArray vao;
		vao.Bind();
		//
		Buffer vertices;
		vertices.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLsizei n_per_vertex = build::Cube::Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray vaa(prog, "vertex");
			vaa.Setup(n_per_vertex, DataType::Float);
			vaa.Enable();
		}
		Buffer normals;
		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLsizei n_per_vertex = build::Cube::Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray vaa(prog, "normal");
			vaa.Setup(n_per_vertex, DataType::Float);
			vaa.Enable();
		}
		Buffer indices;
		GLsizei nindices;
		indices.Bind(Buffer::Target::ElementArray);
		{
			std::vector<GLuint> data;
			nindices = build::Cube::Indices(data);
			Buffer::Data(Buffer::Target::ElementArray, data);
		}
		//
		Uniform(prog, "projectionMatrix").SetMatrix(
			Matrix4f(
				1.5, 0.0, 0.0, 0.0,
				0.0, 2.0, 0.0, 0.0,
				0.0, 0.0, 0.1,-1.0,
				0.0, 0.0, 0.0, 1.0
			)
		);
		Uniform(prog, "cameraMatrix").SetMatrix(
			Matrix4f::RotationZ(M_PI*0.1)*
			Matrix4f::RotationY(M_PI*0.1)*
			Matrix4f::RotationX(M_PI*0.1)
		);
		//
		Context gl;
		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		gl.DrawElements(PrimitiveType::Triangles, nindices, DataType::UnsignedInt);
		ctx.SwapBuffers(win);
		::sleep(2);
	}
	//
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
	catch(std::runtime_error& rte)
	{
		std::cerr << "Error: " << rte.what() << std::endl;
		return 1;
	}
	return 0;
}

