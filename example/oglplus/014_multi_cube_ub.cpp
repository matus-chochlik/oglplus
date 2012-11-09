/**
 *  @example oglplus/014_multi_cube_ub.cpp
 *  @brief Shows how to transform and draw multiple instances of a cube
 *
 *  @oglplus_screenshot{014_multi_cube_ub}
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_cxx11{VARIADIC_TEMPLATES}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>

#include <algorithm>

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

	// Uniforms
	LazyUniform<Mat4f> projection_matrix, camera_matrix;

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertices and the uniform block
	Buffer verts, block_buf;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"layout (std140) uniform ModelBlock {"
			"	mat4 ModelMatrices[36];"
			"};"
			"in vec4 Position;"
			"out vec3 vertColor;"
			"void main(void)"
			"{"
			"	mat4 ModelMatrix = ModelMatrices[gl_InstanceID];"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"	vertColor = abs(normalize((ModelMatrix*Position).yxz));"
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

		// make the matrices
		{
			// 36 x 4x4 matrices
			std::vector<GLfloat> matrix_data(36*16);
			auto p = matrix_data.begin(), e = matrix_data.end();

			Angle<GLfloat> angle, astep = Angle<GLfloat>::Degrees(10);
			while(p != e)
			{
				GLfloat cx = Cos(angle);
				GLfloat sx = Sin(angle);
				auto matrix = Transposed(Mat4f(
					 cx, 0.0, -sx, 0.0,
					0.0, 1.0, 0.0, 0.0,
					 sx, 0.0,  cx, 0.0,
					0.0, 0.0, 0.0, 1.0
				) * Mat4f(
					 1.0, 0.0, 0.0,12.0,
					 0.0, 1.0, 0.0, 0.0,
					 0.0, 0.0, 1.0, 0.0,
					 0.0, 0.0, 0.0, 1.0
				));
				p = std::copy(
					Data(matrix),
					Data(matrix)+Size(matrix),
					p
				);
				angle += astep;
			}

			UniformBlock model_block(prog, "ModelBlock");
			model_block.Binding(0);

			block_buf.Bind(Buffer::Target::Uniform);
			Buffer::Data(
				Buffer::Target::Uniform,
				matrix_data,
				BufferUsage::DynamicDraw
			);
			block_buf.BindBaseUniform(0);
		}

		//
		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(GLuint width, GLuint height)
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
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		camera_matrix.Set(
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

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus
