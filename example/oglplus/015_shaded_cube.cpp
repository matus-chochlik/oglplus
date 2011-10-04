/**
 *  @example oglplus/015_shaded_cube.cpp
 *  @brief Shows how to draw a shaded cube
 *
 *  @image html 015_shaded_cube.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CubeExample : public Example
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

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertices and normals
	Buffer verts;
	Buffer normals;
public:
	CubeExample(void)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertColor;"
			"out vec3 vertNormal;"
			"void main(void)"
			"{"
			"	vertNormal = ("
			"		CameraMatrix * vec4("
			"			normalize("
			"				Position.xyz -"
			"				0.01 * Normal"
			"			), 0.0"
			"		)"
			"	).xyz;"
			"	vertColor = Normal;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec3 vertColor;"
			"in vec3 vertNormal;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float intensity = pow("
			"		dot("
			"			vertNormal,"
			"			vec3(0.0, 0.0, 1.0)"
			"		), 3.0"
			"	);"
			"	fragColor = vec4(abs(vertColor),1.0)*intensity;"
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

		// bind the VAO for the cube
		cube.Bind();

		const GLfloat c[8][3] = {
			{-0.5f, -0.5f, +0.5f},
			{-0.5f, -0.5f, -0.5f},
			{-0.5f, +0.5f, -0.5f},
			{-0.5f, +0.5f, +0.5f},
			{+0.5f, -0.5f, +0.5f},
			{+0.5f, -0.5f, -0.5f},
			{+0.5f, +0.5f, -0.5f},
			{+0.5f, +0.5f, +0.5f}
		};
		const size_t vertex_count = 6 * 2 * 3;
		const GLfloat cube_vertices[vertex_count * 3] = {
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
		// bind the VBO for the cube vertices
		verts.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(
			Buffer::Target::Array,
			vertex_count * 3,
			cube_vertices
		);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(3, DataType::Float);
		vert_attr.Enable();

		const GLfloat n[6][3] = {
			{-1.0f,  0.0f,  0.0f},
			{ 0.0f, -1.0f,  0.0f},
			{ 0.0f,  0.0f, -1.0f},
			{ 1.0f,  0.0f,  0.0f},
			{ 0.0f,  1.0f,  0.0f},
			{ 0.0f,  0.0f,  1.0f}
		};
		GLfloat cube_normals[vertex_count * 3];
		for(size_t f=0;f!=6;++f)
			for(size_t v=0;v!=6;++v)
				for(size_t c=0;c!=3;++c)
					cube_normals[(f*6+v)*3+c] = n[f][c];
		// bind the VBO for the cube normals
		normals.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(
			Buffer::Target::Array,
			vertex_count * 3,
			cube_normals
		);
		// setup the vertex attribs array for the vertices
		VertexAttribArray normal_attr(prog, "Normal");
		normal_attr.Setup(3, DataType::Float);
		normal_attr.Enable();
		//
		gl.ClearColor(0.03f, 0.03f, 0.03f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform(prog, "ProjectionMatrix").SetMatrix(
			CamMatrixf::Perspective(
				Degrees(24),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "CameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				1.5,
				Degrees(time * 135),
				Degrees(SineWave(time / 20.0) * 90)
			)
		);

		gl.DrawArrays(PrimitiveType::Triangles, 0, 6 * 2 * 3);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus
