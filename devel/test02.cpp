/**
 *  .file devel/test02.cpp
 *  Development / testing file.
 *  NOTE. this file is here for feature development / testing purposes only
 *  and its source code, input, output can change witout prior notice.
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>

#include <cmath>

#include "test.hpp"

namespace oglplus {

class Test02 : public Test
{
private:
	typedef shapes::Cube Shape;
	//
	Shape shape;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Geometry shader
	GeometryShader gs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBOs for the shape's vertices
	Buffer verts;
public:
	Test02(void)
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

		// Set the geometry shader source
		gs.Source(
			"#version 330\n"
			"layout(triangles) in;"
			"layout(triangle_strip, max_vertices = 108) out;"
			"uniform mat4 projectionMatrix, cameraMatrix;"
			"out vec3 color;"
			"void main(void)"
			"{"
			"	for(int c=0; c!=36; ++c)"
			"	{"
			"		float angle = c * 10 * 2 * 3.14159 / 360.0;"
			"		float cx = cos(angle);"
			"		float sx = sin(angle);"
			"		mat4 modelMatrix = mat4("
			"			 cx, 0.0,  sx, 0.0,"
			"			0.0, 1.0, 0.0, 0.0,"
			"			-sx, 0.0,  cx, 0.0,"
			"			0.0, 0.0, 0.0, 1.0 "
			"		) * mat4("
			"			 1.0, 0.0, 0.0, 0.0,"
			"			 0.0, 1.0, 0.0, 0.0,"
			"			 0.0, 0.0, 1.0, 0.0,"
			"			12.0, 0.0, 0.0, 1.0 "
			"		);"
			"		for(int v=0; v!=gl_in.length(); ++v)"
			"		{"
			"			vec4 vert = gl_in[v].gl_Position;"
			"			gl_Position = "
			"				projectionMatrix *"
			"				cameraMatrix *"
			"				modelMatrix *"
			"				vert;"
			"			color = abs(normalize(modelMatrix*vert)).xzy;"
			"			EmitVertex();"
			"		}"
			"		EndPrimitive();"
			"	}"
			"}"
		);
		// compile it
		gs.Compile();


		// set the fragment shader source
		// (uses the absolute value of normal as color)
		fs.Source(
			"#version 330\n"
			"in vec3 color;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(color, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(gs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the shape
		vao.Bind();

		// bind the VBO for the shape vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> vertices;
			GLuint n_per_vertex = shape.Vertices(vertices);
			// upload the data
			Buffer::Data(Buffer::Target::Array, vertices);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			Matrix4f::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.03f, 0.03f, 0.03f, 0.0f);
		gl.ClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		//
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			Matrix4f::Orbiting(
				Vec3f(),
				13.0,
				Degrees(time * 135),
				Degrees(std::sin(time * 0.3) * 30)
			)
		);

		vao.Bind();
		// This is not very effective
		shape.Instructions().Draw(shape.Indices());
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Test> makeTest(void)
{
	return std::unique_ptr<Test>(new Test02);
}

} // namespace oglplus
