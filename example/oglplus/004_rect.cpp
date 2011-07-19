/**
 *  @example oglplus/004_rect.cpp
 *  @brief Shows how to draw a custom shaded rectangle
 *
 *  @image html 004_rect.png
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
				coord = vertex; \
				gl_Position = vec4(vertex, 0.0, 1.0); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			const uniform float radius = 0.4; \
			uniform vec2 red_center, green_center, blue_center; \
			vec3 dist; \
			in vec2 coord; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				dist = vec3( \
					distance(coord, red_center), \
					distance(coord, green_center), \
					distance(coord, blue_center) \
				); \
				fragColor = vec4( \
					dist.r < radius ? 1 : (2*radius - dist.r) / radius, \
					dist.g < radius ? 1 : (2*radius - dist.g) / radius, \
					dist.b < radius ? 1 : (2*radius - dist.b) / radius, \
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
		Uniform(prog, "red_center").Set(-0.141f, 0.141f);
		Uniform(prog, "green_center").Set(0.141f, 0.141f);
		Uniform(prog, "blue_center").Set(0.0f, -0.2f);

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
