/**
 *  .file devel/test04.cpp
 *  Development / testing file.
 *  NOTE. this file is here for feature development / testing purposes only
 *  and its source code, input, output can change witout prior notice.
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>

#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/curve.hpp>
#include <oglplus/bound/buffer.hpp>

#include <cmath>

#include "test.hpp"

namespace oglplus {
namespace images {

} // namespace images


class Test04 : public Test
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	VertexArray vao;
	Buffer verts;
	size_t n;
public:
	Test04(void)
	 : n(0)
	 , prog("test_prog")
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"void main(void)"
			"{"
			"	gl_Position = vertex;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(0.0, 0.0, 0.0, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		vao.Bind();
		{
			auto data = CubicBezierLoop<Vec2f, double>({
				Vec2f( 0.0f, -0.8f),
				Vec2f(-0.8f, -0.1f),
				Vec2f( 0.0f, +0.8f),
				Vec2f(-0.1f,  0.1f)
			}).Approximate(15);
			n = data.size();
			Bind(verts, Buffer::Target::Array).Data(data);
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(2, DataType::Float);
			attr.Enable();
		}

		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.PointSize(4.0);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		gl.DrawArrays(PrimitiveType::LineStrip, 0, n);
		gl.DrawArrays(PrimitiveType::Points, 0, n);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Test> makeTest(void)
{
	return std::unique_ptr<Test>(new Test04);
}

} // namespace oglplus
