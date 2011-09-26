/**
 *  @example oglplus/007_cubic_bezier.cpp
 *  @brief Shows how to render line approximating a cubic bezier curve
 *
 *  @image html 007_cubic_bezier.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/curve.hpp>
#include <oglplus/bound/buffer.hpp>

#include "example.hpp"

#include <cmath>

namespace oglplus {

class RectangleExample : public Example
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

	// VAO and VBO for the curve approximation points
	VertexArray curve;
	Buffer curve_verts;
	// The count of curve points
	size_t curve_n;

	// VAO and VBO for the curve control points
	VertexArray control;
	Buffer ctrl_verts;
	// The count of control points
	size_t ctrl_n;
public:
	RectangleExample(void)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"in vec4 Position;"
			"void main(void)"
			"{"
			"	gl_Position = Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"uniform vec3 Color;"
			"void main(void)"
			"{"
			"	fragColor = vec4(Color, 1.0);"
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

		// the series of cubic bezier curves
		BezierCurves<Vec2f, double, 3> bezier({
			Vec2f(-0.9f, -0.9f),
			Vec2f(-0.9f, +0.9f),
			Vec2f(+0.9f, +0.9f),
			Vec2f(+0.9f,  0.0f),
			Vec2f(+0.9f, -0.9f),
			Vec2f( 0.0f, -0.9f),
			Vec2f( 0.0f, +0.5f),
			Vec2f(+0.5f, +0.5f),
			Vec2f(+0.7f, +0.5f),
			Vec2f(+0.7f, +0.0f),
			Vec2f(-0.7f, -0.2f),
			Vec2f(-0.8f, +0.8f),
			Vec2f(+0.9f, +0.9f),
		});

		curve.Bind();
		{
			auto data = bezier.Approximate(25);
			curve_n = data.size();
			Bind(curve_verts, Buffer::Target::Array).Data(data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(2, DataType::Float);
			attr.Enable();
		}

		control.Bind();
		{
			auto data = bezier.ControlPoints();
			ctrl_n = data.size();
			Bind(ctrl_verts, Buffer::Target::Array).Data(data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(2, DataType::Float);
			attr.Enable();
		}
		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer();
		// draw the lines between control points
		Uniform(prog, "Color").Set(Vec3f(0.9f, 0.9f, 0.2f));
		control.Bind();
		gl.DrawArrays(PrimitiveType::LineStrip, 0, ctrl_n);
		// draw the curve
		Uniform(prog, "Color").Set(Vec3f(0.1f, 0.1f, 0.1f));
		curve.Bind();
		gl.DrawArrays(PrimitiveType::LineStrip, 0, curve_n);
		// draw the control points
		Uniform(prog, "Color").Set(Vec3f(0.9f, 0.0f, 0.0f));
		control.Bind();
		gl.PointSize(8.0);
		gl.DrawArrays(PrimitiveType::Points, 0, ctrl_n);
		gl.PointSize(1.0);
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus
