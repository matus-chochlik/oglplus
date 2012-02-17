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
			in vec2 Position; \
			out vec2 vertCoord; \
			void main(void) \
			{ \
				gl_Position = vec4(Position, 0.0, 1.0); \
				vertCoord = vec2( \
					(Position.x + 1.0)/2.0, \
					(Position.y + 1.0)/2.0  \
				); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec2 vertCoord; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = vec4( \
					vertCoord.x - vertCoord.x * vertCoord.y,\
					vertCoord.y - vertCoord.x * vertCoord.y,\
					vertCoord.x * vertCoord.y, \
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
		Buffer::Data(Buffer::Target::Array, 8, rectangle_verts);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(2, DataType::Float);
		vert_attr.Enable();
		//

		gl.ClearDepth(1.0f);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus
