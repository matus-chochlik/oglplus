/**
 *  @example oglplus/023_reflected_cube.cpp
 *  @brief Shows how to draw a cube reflected in a horizontal plane
 *
 *  @image html 023_reflected_cube.png
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

class ReflectionExample : public Example
{
private:
	// the cube vertex attribute builder
	shapes::Cube make_cube;
	// here will be stored the indices used by the drawing instructions
	shapes::Cube::IndexArray cube_indices;
	// the instructions for drawing the cube
	shapes::DrawingInstructions cube_instr;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Programs
	Program prog;

	// A vertex array object for the cube
	VertexArray cube;
	// A vertex array object for the reflective plane
	VertexArray plane;

	// VBOs for the cube's vertices and normals
	Buffer cube_verts, cube_normals;
	// VBOs for the plane's vertices and normals
	Buffer plane_verts, plane_normals;
public:
	ReflectionExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out vec3 vertNormal;"
			"out vec3 fragNormal;"
			"out vec3 fragLight;"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"uniform vec3 lightPos;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
			"	vertNormal = normal;"
			"	fragNormal = ("
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	fragLight = ("
			"		vec4(lightPos, 0.0)-"
			"		modelMatrix*vertex"
			"	).xyz;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec3 vertNormal;"
			"in vec3 fragNormal;"
			"in vec3 fragLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = dot(fragLight, fragLight);"
			"	float d = max(dot(fragNormal, fragLight)/l,0.0);"
			"	float i = clamp(0.2 + d * 2.0, 0.0, 1.0);"
			"	fragColor = vec4(abs(vertNormal)*i, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link it
		prog.Link();
		prog.Use();

		// bind the VAO for the cube
		cube.Bind();

		// bind the VBO for the cube vertices
		cube_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr_n(prog, "vertex");
			attr_n.Setup(n_per_vertex, DataType::Float);
			attr_n.Enable();
		}

		// bind the VBO for the cube normals
		cube_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the normals
			prog.Use();
			VertexAttribArray attr_n(prog, "normal");
			attr_n.Setup(n_per_vertex, DataType::Float);
			attr_n.Enable();
		}

		// bind the VAO for the plane
		plane.Bind();

		// bind the VBO for the plane vertices
		plane_verts.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-2.0f, 0.0f,  2.0f,
				-2.0f, 0.0f, -2.0f,
				 2.0f, 0.0f,  2.0f,
				 2.0f, 0.0f, -2.0f
			};
			// upload the data
			Buffer::Data(Buffer::Target::Array, data, 4*3);
			// setup the vertex attribs array for the vertices
			prog.Use();
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the cube normals
		plane_normals.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-0.1f, 1.0f,  0.1f,
				-0.1f, 1.0f, -0.1f,
				 0.1f, 1.0f,  0.1f,
				 0.1f, 1.0f, -0.1f
			};
			// upload the data
			Buffer::Data(Buffer::Target::Array, data, 4*3);
			// setup the vertex attribs array for the normals
			prog.Use();
			VertexAttribArray attr(prog, "normal");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}
		VertexArray::Unbind();

		Uniform(prog, "lightPos").Set(Vec3f(1.5, 2.0, 2.5));
		//
		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.ClearStencil(0);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(
				Degrees(24),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();
		// make the camera matrix orbiting around the origin
		// at radius of 3.5 with elevation between 15 and 90 degrees
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				3.5,
				Degrees(time * 10),
				Degrees(15 + (-std::cos(time * 0.5)+1.0)*0.5*75)
			)
		);
		ModelMatrixf identity;
		// make the model transformation matrix
		ModelMatrixf model =
			ModelMatrixf::Translation(0.0f, 1.5f, 0.0) *
			ModelMatrixf::RotationA(
				Vec3f(1.0f, 1.0f, 1.0f),
				Degrees(time * 90)
			);
		// make the reflection matrix
		ModelMatrixf reflection(
			1.0, 0.0, 0.0, 0.0,
			0.0,-1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
		//
		gl.Disable(Capability::Blend);
		gl.Disable(Capability::DepthTest);
		gl.Enable(Capability::StencilTest);
		gl.ColorMask(false, false, false, false);
		gl.StencilFunc(CompareFunction::Always, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Replace);

		plane.Bind();
		Uniform(prog, "modelMatrix").SetMatrix(identity);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		gl.ColorMask(true, true, true, true);
		gl.Enable(Capability::DepthTest);
		gl.StencilFunc(CompareFunction::Equal, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Keep);

		// draw the cube using the reflection program
		Uniform(prog, "modelMatrix").SetMatrix(reflection * model);
		cube.Bind();
		cube_instr.Draw(cube_indices);

		gl.Disable(Capability::StencilTest);

		// draw the cube using the normal object program
		Uniform(prog, "modelMatrix").SetMatrix(model);
		cube_instr.Draw(cube_indices);

		// blend-in the plane
		gl.Enable(Capability::Blend);
		gl.BlendEquation(BlendEquation::Max);
		plane.Bind();
		Uniform(prog, "modelMatrix").SetMatrix(identity);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new ReflectionExample);
}

} // namespace oglplus
