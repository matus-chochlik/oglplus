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
private:
public:
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
			in vec3 vertex; \
			in vec3 inColor; \
			uniform mat4 tmpMatrix; \
			out vec4 outColor; \
			void main(void) \
			{ \
				gl_Position = tmpMatrix * vec4(vertex, 1.0); \
				outColor = vec4(inColor, 1.0); \
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
		Array<Buffer> vbo(2);
		//
		GLfloat triangle_data[9] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};
		vbo[0].Bind(Buffer::Target::Array);
		Buffer::Data(Buffer::Target::Array, triangle_data, 9);
		VertexAttribArray vaa1(prog, "vertex");
		vaa1.Setup(3, DataType::Float);
		vaa1.Enable();
		//
		GLfloat triangle_color[9] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
		vbo[1].Bind(Buffer::Target::Array);
		Buffer::Data(Buffer::Target::Array, triangle_color, 9);
		VertexAttribArray vaa2(prog, "inColor");
		vaa2.Setup(3, DataType::Float);
		vaa2.Enable();
		//
		{
			auto map = Buffer::Map(Buffer::Target::Array, Buffer::Map::Access::Read);
			for(int i=0;i!=9;++i)
				assert(map.At<GLfloat>(i) == triangle_color[i]);
		}
		//
		{
			Vec3 i(1, 0, 0);
			Vec3 j(0, 1, 0);
			Vec3 k(0, 0, 1);
			//
			assert(Cross(i, j) == k);
			assert(Cross(j, k) == i);
			assert(Cross(k, i) == j);
			//
			Vec4 x(i, 1);
			Vec4 y(j, 1);
			Vec4 z(k, 1);
			//
			assert(x.xyz() == i);
			assert(y.xyz() == j);
			assert(z.xyz() == k);

			assert(i + j + k == (x + y + z).xyz());
			assert(Vec4(i + j + k, 3) == (x + y + z));
			//
			assert(i.xxx() == j.yyy());
			assert(i.xxx() == k.zzz());
			assert((i+j+k).x__() == i);
			assert((i+j+k)._x_() == j);
			assert((i+j+k).__x() == k);
			assert((i+j+k).y__() == i);
			assert((i+j+k)._y_() == j);
			assert((i+j+k).__y() == k);
			assert((i+j+k).z__() == i);
			assert((i+j+k)._z_() == j);
			assert((i+j+k).__z() == k);

			Matrix<GLfloat, 4, 4> e;
			assert(e == e);
			assert(e * e == e);
			assert(e + e == e*2);
			assert(e + e + e  == 3.0*e);
			assert(e + e  == 3.0*e - e);
			assert(-e - e == -2.0*e);
			assert(e - e  == 0.0*e);
			//
			(
				//Matrix4d::Translation(-1.0, -1.0, 0.0) *
				//Matrix4d::Scale(2.0, 2.0, 1.0) *
				//Matrix4d::RotationZ(M_PI*0.5) *
				//Matrix4d::RotationY(M_PI*0.5) *
				Matrix4d::RotationA(Vec3d(0.0, 1.0, 1.0), M_PI*0.5) *
				Vec4d(1.0, 0.0, 0.0, 1.0)
			).xyz()._print(std::cout);
		}
		//
		Uniform(prog, "tmpMatrix").SetMatrix(
			Matrix4f::RotationZ(M_PI*0.5) *
			Matrix4f::Translation(-1.0, -1.0, 0.0) *
			Matrix4f::Scale(2.0, 2.0, 1.0) *
			Matrix4f()
		);
		//
		Context gl;
		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		VertexArray::Draw(PrimitiveType::Triangles, 0, 3);
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

