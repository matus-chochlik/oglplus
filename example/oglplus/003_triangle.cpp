/**
 *  @example oglplus/003_triangle.cpp
 *  @brief Shows the basic usage of OGLplus by drawing a simple transformed triangle.
 *
 *  @image html 003_triangle.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
			in vec3 vertex; \
			in vec3 color; \
			uniform mat4 matrix; \
			out vec4 outColor; \
			void main(void) \
			{ \
				gl_Position = matrix * vec4(vertex, 1.0); \
				outColor = vec4(color, 1.0); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec4 outColor; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = outColor; \
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
		Buffer::Data(Buffer::Target::Array, triangle_verts, 9);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "vertex");
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
		Buffer::Data(Buffer::Target::Array, triangle_colors, 9);
		// setup the vertex attribs array
		VertexAttribArray color_attr(prog, "color");
		color_attr.Setup(3, DataType::Float);
		color_attr.Enable();

		// set the transformation matrix
		Uniform u1(prog, "matrix");
		u1.SetMatrix<4>(
			 2.0f,  0.0f,  0.0f,  0.0f,
			 0.0f,  2.0f,  0.0f,  0.0f,
			 0.0f,  0.0f,  2.0f,  0.0f,
			-1.0f, -1.0f,  0.0f,  1.0f
		);

		VertexArray::Unbind();
		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		gl.ClearDepth(1.0f);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		triangle.Bind();
		gl.DrawArrays(PrimitiveType::Triangles, 0, 3);
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new TriangleExample);
}

} // namespace oglplus
