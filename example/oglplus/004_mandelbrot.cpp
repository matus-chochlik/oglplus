/**
 *  @example oglplus/004_mandelbrot.cpp
 *  @brief Shows how to draw a rectangle with the mandelbrot set
 *
 *  @image html 004_mandelbrot.png
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

	// VBOs for the rectangle's vertices and the mandelbrot set viewport
	Buffer verts;
	Buffer coords;
public:
	RectangleExample(void)
	{
		// Set the vertex shader source
		vs.Source(" \
			#version 330\n \
			in vec2 vertex; \
			in vec2 coord; \
			out vec2 c; \
			void main(void) \
			{ \
				c = coord; \
				gl_Position = vec4(vertex, 0.0, 1.0); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec2 c; \
			out vec4 fragColor; \
			const uniform int nclr = 5; \
			uniform vec4 clrs[5]; \
			void main(void) \
			{ \
				vec2 z = vec2(0.0, 0.0); \
				int i, max = 128; \
				for(i = 0; (i != max) && (distance(z, c) < 2.0); ++i) \
				{ \
					vec2 zn = vec2( \
						z.x * z.x - z.y * z.y + c.x, \
						2.0 * z.x * z.y + c.y \
					); \
					z = zn; \
				} \
				float a = sqrt(float(i) / float(max)); \
				for(i = 0; i != (nclr - 1); ++i) \
				{ \
					if(a >= clrs[i].a && a < clrs[i+1].a) \
					{ \
						float m = (a - clrs[i].a) / (clrs[i+1].a - clrs[i].a); \
						fragColor = vec4( \
							mix(clrs[i].r, clrs[i+1].r, m), \
							mix(clrs[i].g, clrs[i+1].g, m), \
							mix(clrs[i].b, clrs[i+1].b, m), \
							1.0 \
						); \
						break; \
					} \
				} \
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

		GLfloat rectangle_coords[8] = {
			-1.5f, -0.5f,
			-1.5f,  1.0f,
			 0.5f, -0.5f,
			 0.5f,  1.0f
		};
		// bind the VBO for the rectangle vertices
		coords.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, rectangle_coords, 8);
		// setup the vertex attribs array for the vertices
		VertexAttribArray coord_attr(prog, "coord");
		coord_attr.Setup(2, DataType::Float);
		coord_attr.Enable();
		//
		// color map used in the fragment shader to colorize the fractal
		const size_t nclr = 5;
		GLfloat colormap[nclr*4] = {
			0.4f, 0.2f, 1.0f, 0.00f,
			1.0f, 0.2f, 0.2f, 0.30f,
			1.0f, 1.0f, 1.0f, 0.95f,
			1.0f, 1.0f, 1.0f, 0.98f,
			0.1f, 0.1f, 0.1f, 1.00f
		};
		Uniform(prog, "clrs").Set<4>(nclr, colormap);
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
