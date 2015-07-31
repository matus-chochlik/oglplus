/**
 *  @example oglplus/001_triangle.cpp
 *  @brief Shows the basic usage of OGLplus by drawing a simple red triangle.
 *
 *  @oglplus_screenshot{001_triangle}
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_gl{GL_VERSION_3_0}
 */
#include <oglplus/gl.hpp>

#include <iostream>

#include <oglplus/texgen/swizzle_node.hpp>
#include <oglplus/texgen/newton_node.hpp>
#include <oglplus/texgen/mandelbrot_node.hpp>
#include <oglplus/texgen/normal_map_node.hpp>
#include <oglplus/texgen/blur_node.hpp>
#include <oglplus/texgen/checker_node.hpp>
#include <oglplus/texgen/mix_node.hpp>
#include <oglplus/texgen/global_node.hpp>
#include <oglplus/texgen/render_node.hpp>

#include <oglplus/all.hpp>

#include "example.hpp"

namespace oglplus {
namespace texgen {

} // namespace texgen

class TriangleExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	texgen::NewtonNode nt;
	texgen::MandelbrotNode mb;
	texgen::CheckerNode c0;
	texgen::MixNode m1;
	texgen::SwizzleNode s1, s2;
	texgen::Blur2DNode b1, b2, b3;
	texgen::NormalMapNode nm;
	texgen::RenderNode rn;
public:
	TriangleExample(void)
	 : gl()
	 , s1("rrra")
	 , s2("g")
	{
		//m1.SetZero(0.0f);
		//m1.SetOne(1.0f);
		Connect(nt.Output(0), m1.Input(2));
		Connect(m1.Output(0), s1.Input(0));
		//Connect(sw.Output(0), nm.Input(0));

std::cout << s1.Output(0).Definitions(150) << std::endl;
std::cout << s1.Output(0).Expression(150) << std::endl;

		Connect(s1.Output(0), rn.Input(0));

		rn.Update();

		gl.Disable(Capability::DepthTest);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
		rn.Render();
	}

	bool Continue(double duration)
	{
		return duration < 30;
	}
};

void setupExample(ExampleParams& /*params*/){ }

std::unique_ptr<ExampleThread> makeExampleThread(
	Example& /*example*/,
	unsigned /*thread_id*/,
	const ExampleParams& /*params*/
){ return std::unique_ptr<ExampleThread>(); }

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new TriangleExample);
}

} // namespace oglplus
