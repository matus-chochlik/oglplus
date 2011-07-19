/**
 *  @example oglplus/003_rect.cpp
 *  @brief Shows how to draw a shaded rectangle
 *
 *  @image html 003_rect.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include "example.hpp"

namespace oglplus {

class RectangleExample : public Example
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

	// A vertex array object for the rendered rectangle
	VertexArray rectangle;

	// VBOs for the rectangle's vertices
	Buffer verts;
public:
	RectangleExample(void)
	{
		// Set the vertex shader source
		vs.Source(" \
			#version 330\n \
			in vec2 vertex; \
			out vec2 coord; \
			void main(void) \
			{ \
				gl_Position = vec4(vertex, 0.0, 1.0); \
				coord = vec2((vertex.x + 1.0)/2.0, (vertex.y + 1.0)/2.0); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec2 coord; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = vec4( \
					coord.x - coord.x * coord.y, \
					coord.y - coord.x * coord.y, \
					coord.x * coord.y, \
					1.0 \
				); \
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

		// bind the VAO for the rectangle
		rectangle.Bind();

		GLfloat rectangle_verts[8] = {
			-1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f
		};
		// bind the VBO for the rectangle vertices
		verts.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, rectangle_verts, 8);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "vertex");
		vert_attr.Setup(2, DataType::Float);
		vert_attr.Enable();
		//

		VertexArray::Unbind();
		gl.ClearDepth(1.0f);
	}

	void Render(void)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		rectangle.Bind();
		VertexArray::Draw(PrimitiveType::TriangleStrip, 0, 4);
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus
