/**
 *  @example oglplus/008_lyapunov.cpp
 *  @brief Shows how to draw the Lyapunov fractal
 *
 *  @oglplus_screenshot{008_lyapunov}
 *  @author Timo Keller
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
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

	// Program
	Program prog;

	// A vertex array object for the rendered rectangle
	VertexArray rectangle;

	// VBOs for the rectangle's vertices and the viewport coordinates
	Buffer verts;
	Buffer coords;

	// Scroll factor
	LazyUniform<GLfloat> scroll_factor;
public:
	RectangleExample(void)
	 : scroll_factor(prog, "ScrollFactor")
	{
		// Vertex shader
		VertexShader vs;
		// Set the vertex shader source
		vs.Source(StrLit(" \
			#version 330\n \
			uniform float ScrollFactor; \
			in vec2 Position; \
			in vec2 Coord; \
			out vec2 vertCoord; \
			void main(void) \
			{ \
				vertCoord = ScrollFactor * Coord; \
				gl_Position = vec4(Position, 0.0, 1.0); \
			} \
		"));
		// compile it
		vs.Compile();

		// Fragment shader
		FragmentShader fs;
		// set the fragment shader source
		fs.Source(StrLit(" \
			#version 330\n \
			in vec2 vertCoord; \
			out vec4 fragColor; \
			const int npasses = 100; \
			const int nclr = 5; \
			uniform vec4 clrs[5]; \
			void main(void) \
			{ \
				vec2 ab = vertCoord; \
				float x_n = 0.5; \
				float sum = 0; \
				for (int i = 0; i < npasses; ++i) \
				{ \
					x_n = ab.x * x_n * (1 - x_n); \
					sum += log(abs(ab.x*(1 - 2 * x_n))); \
					x_n = ab.x * x_n * (1 - x_n); \
					sum += log(abs(ab.x*(1 - 2 * x_n))); \
					x_n = ab.x * x_n * (1 - x_n); \
					sum += log(abs(ab.x*(1 - 2 * x_n))); \
					x_n = ab.x * x_n * (1 - x_n); \
					sum += log(abs(ab.x*(1 - 2 * x_n))); \
					x_n = ab.x * x_n * (1 - x_n); \
					sum += log(abs(ab.x*(1 - 2 * x_n))); \
					x_n = ab.x * x_n * (1 - x_n); \
					sum += log(abs(ab.x*(1 - 2 * x_n))); \
					x_n = ab.y * x_n * (1.0 - x_n); \
					sum += log(abs(ab.y*(1 - 2 * x_n))); \
					x_n = ab.y * x_n * (1.0 - x_n); \
					sum += log(abs(ab.y*(1 - 2 * x_n))); \
					x_n = ab.y * x_n * (1.0 - x_n); \
					sum += log(abs(ab.y*(1 - 2 * x_n))); \
					x_n = ab.y * x_n * (1.0 - x_n); \
					sum += log(abs(ab.y*(1 - 2 * x_n))); \
					x_n = ab.y * x_n * (1.0 - x_n); \
					sum += log(abs(ab.y*(1 - 2 * x_n))); \
					x_n = ab.y * x_n * (1.0 - x_n); \
					sum += log(abs(ab.y*(1 - 2 * x_n))); \
				} \
				float Lambda = sum / (12 * npasses); \
				float a = (clamp(Lambda, -2.0, 2.0) + 2.0) / 4; \
				for(int i = 0; i != (nclr - 1); ++i) \
				{ \
					if(a >= clrs[i].a && a < clrs[i+1].a) \
					{ \
						float m = (a - clrs[i].a) / (clrs[i+1].a - clrs[i].a); \
						fragColor = vec4( \
							mix(clrs[i].rgb, clrs[i+1].rgb, m), \
							1.0 \
						); \
						break; \
					} \
				} \
			} \
		"));
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

		GLfloat min = 3.0f;
		GLfloat max = 4.0f;
		GLfloat rectangle_coords[8] = {
			 min, min,
			 min, max,
			 max, min,
			 max, max
		};
		// bind the VBO for the rectangle vertices
		coords.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 8, rectangle_coords);
		// setup the vertex attribs array for the vertices
		VertexAttribArray coord_attr(prog, "Coord");
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
		Uniform<GLfloat>(prog, "clrs").SetVectors<4>(nclr, colormap);
		//
		gl.ClearDepth(1.0f);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		scroll_factor = 1.0f / (0.005 * time + 1.0f);

		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 15.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus
