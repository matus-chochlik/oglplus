/**
 *  @example oglplus/013_striped_cubes.cpp
 *  @brief Shows how to draw rotating striped cubes using the Cube builder
 *
 *  @image html 013_striped_cubes.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CubeExample : public Example
{
private:
	// helper object building cube vertex attributes
	shapes::Cube make_cube;
	// helper object encapsulating cube drawing instructions
	shapes::DrawingInstructions cube_instr;
	// indices pointing to cube primitive elements
	shapes::Cube::IndexArray cube_indices;

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

	// VBOs for the cube's vertices and uv-coordinates
	Buffer verts;
	Buffer uvcoords;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"in vec4 vertex;"
			"in vec2 uvcoord;"
			"out vec2 uv;"
			"void main(void)"
			"{"
			"	uv = uvcoord;"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec2 uv;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float i = int((uv.x+uv.y)*8) % 2;"
			"	fragColor = mix("
			"		vec4(0, 0, 0, 1),"
			"		vec4(1, 1, 0, 1),"
			"		i"
			"	);"
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

		// bind the VBO for the cube vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the cube UV-coordinates
		uvcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.UVCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "uvcoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
		//
		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.5,
				Degrees(time * 15),
				Degrees(std::sin(time) * 45)
			)
		);
		cube.Bind();
		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::Translation(-1.0, 0.0, 0.0) *
			ModelMatrixf::RotationZ(Degrees(time * 180))
		);
		cube_instr.Draw(cube_indices);
		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::Translation(+1.0, 0.0, 0.0) *
			ModelMatrixf::RotationY(Degrees(time * 90))
		);
		cube_instr.Draw(cube_indices);
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
