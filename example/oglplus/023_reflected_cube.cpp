/**
 *  @example oglplus/023_reflected_cube.cpp
 *  @brief Shows how to draw a cube reflected in a horizontal plane
 *
 *  @oglplus_screenshot{023_reflected_cube}
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

	// Uniforms
	LazyUniform<Mat4f> projection_matrix, camera_matrix, model_matrix;

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
	 : cube_indices(make_cube.Indices())
	 , cube_instr(make_cube.Instructions())
	 , vs(ObjectDesc("Vertex"))
	 , fs(ObjectDesc("Fragment"))
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , model_matrix(prog, "ModelMatrix")
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertColor;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"	vertColor = Normal;"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLight = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec3 vertColor;"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = dot(vertLight, vertLight);"
			"	float d = l > 0.0 ? dot("
			"		vertNormal, "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float i = 0.2 + max(d * 2.2, 0.0);"
			"	fragColor = vec4(abs(vertColor)*i, 1.0);"
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
			GLuint n_per_vertex = make_cube.Positions(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the cube normals
		cube_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the normals
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
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
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			// setup the vertex attribs array for the vertices
			prog.Use();
			VertexAttribArray attr(prog, "Position");
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
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			// setup the vertex attribs array for the normals
			prog.Use();
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}
		VertexArray::Unbind();

		Uniform<Vec3f>(prog, "LightPos").Set(1.5, 2.0, 2.5);
		//
		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.ClearStencil(0);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
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
		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				3.5,
				Degrees(time * 10),
				Degrees(15 + (-SineWave(0.25+time/12.5)+1.0)*0.5*75)
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
		auto reflection = ModelMatrixf::Reflection(false, true, false);
		//
		gl.Disable(Capability::Blend);
		gl.Disable(Capability::DepthTest);
		gl.Enable(Capability::StencilTest);
		gl.ColorMask(false, false, false, false);
		gl.StencilFunc(CompareFunction::Always, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Replace);

		plane.Bind();
		model_matrix.Set(identity);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		gl.ColorMask(true, true, true, true);
		gl.Enable(Capability::DepthTest);
		gl.StencilFunc(CompareFunction::Equal, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Keep);

		// draw the cube using the reflection program
		model_matrix.Set(reflection * model);
		cube.Bind();
		cube_instr.Draw(cube_indices);

		gl.Disable(Capability::StencilTest);

		// draw the cube using the normal object program
		model_matrix.Set(model);
		cube_instr.Draw(cube_indices);

		// blend-in the plane
		gl.Enable(Capability::Blend);
		gl.BlendEquation(BlendEquation::Max);
		plane.Bind();
		model_matrix.Set(identity);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new ReflectionExample);
}

} // namespace oglplus
