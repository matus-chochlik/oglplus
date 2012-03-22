/**
 *  @example oglplus/014_multi_cube.cpp
 *  @brief Shows how to transform and draw multiple instances of a cube
 *
 *  @image html 014_multi_cube.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
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

	// VBOs for the cube's vertices
	Buffer verts;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"in vec4 Position;"
			"out vec3 vertColor;"
			"void main(void)"
			"{"
			"	float angle = gl_InstanceID * 10 * 2 * 3.14159 / 360.0;"
			"	float cx = cos(angle);"
			"	float sx = sin(angle);"
			"	mat4 ModelMatrix = mat4("
			"		 cx, 0.0,  sx, 0.0,"
			"		0.0, 1.0, 0.0, 0.0,"
			"		-sx, 0.0,  cx, 0.0,"
			"		0.0, 0.0, 0.0, 1.0 "
			"	) * mat4("
			"		 1.0, 0.0, 0.0, 0.0,"
			"		 0.0, 1.0, 0.0, 0.0,"
			"		 0.0, 0.0, 1.0, 0.0,"
			"		12.0, 0.0, 0.0, 1.0 "
			"	);"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"	vertColor = abs(normalize((ModelMatrix*Position).xyz));"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec3 vertColor;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(vertColor, 1.0);"
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
			GLuint n_per_vertex = make_cube.Positions(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		//
		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform<Mat4f>(prog, "ProjectionMatrix").Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
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
		Uniform<Mat4f>(prog, "CameraMatrix").Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				14.5,
				Degrees(time * 135),
				Degrees(SineWave(time / 20.0) * 30)
			)
		);

		// draw 36 instances of the cube
		// the vertex shader will take care of their placement
		cube_instr.Draw(cube_indices, 36);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params)
{
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus
