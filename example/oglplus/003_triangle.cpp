/**
 *  @example oglplus/003_triangle.cpp
 *  @brief Shows the basic usage of OGLplus by drawing a simple transformed triangle.
 *
 *  @oglplus_screenshot{003_triangle}
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_cxx11{VARIADIC_TEMPLATES}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include "example.hpp"

namespace oglplus {

class TriangleExample : public Example
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

	// A vertex array object for the rendered triangle
	VertexArray triangle;

	// Array of VBOs [0] -> vertex coords, [1] -> vertex colors
	Array<Buffer> buffs;
public:
	TriangleExample(void)
	 : buffs(2)
	{
		// Set the vertex shader source
		vs.Source(" \
			#version 330\n \
			in vec3 Position; \
			in vec3 Color; \
			uniform mat4 Matrix; \
			out vec4 vertColor; \
			void main(void) \
			{ \
				gl_Position = Matrix * vec4(Position, 1.0); \
				vertColor = vec4(Color, 1.0); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec4 vertColor; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = vertColor; \
			} \
		");
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the triangle
		triangle.Bind();

		GLfloat triangle_verts[9] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};
		// bind the VBO for the triangle vertices
		buffs[0].Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 9, triangle_verts);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(3, DataType::Float);
		vert_attr.Enable();
		//

		GLfloat triangle_colors[9] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
		// bind the VBO for the triangle colors
		buffs[1].Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 9, triangle_colors);
		// setup the vertex attribs array
		VertexAttribArray color_attr(prog, "Color");
		color_attr.Setup(3, DataType::Float);
		color_attr.Enable();

		// set the transformation matrix
		Uniform<Mat4f> u1(prog, "Matrix");
		u1.Set(Mat4f(
			 2.0f,  0.0f,  0.0f, -1.0f,
			 0.0f,  2.0f,  0.0f, -1.0f,
			 0.0f,  0.0f,  2.0f,  0.0f,
			 0.0f,  0.0f,  0.0f,  1.0f
		));

		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		gl.ClearDepth(1.0f);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		gl.DrawArrays(PrimitiveType::Triangles, 0, 3);
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new TriangleExample);
}

} // namespace oglplus
