/**
 *  @example oglplus/014_multi_cube_gs.cpp
 *  @brief Shows how to draw multiple instances of a cube using geometry shader
 *
 *  @image html 014_multi_cube_gs.png
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

	// Geometry shader
	GeometryShader gs;

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

		//
		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			Matrix4f::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
		gl.ClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			Matrix4f::Orbiting(
				Vec3f(),
				14.5,
				Degrees(time * 135),
				Degrees(std::sin(time * 0.3) * 30)
			)
		);

		cube.Bind();
		// draw 1 instance of the cube
		// the geometry shader will spawn 36 copies
		// and take care of their placement
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
