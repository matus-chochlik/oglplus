/**
 *  @example oglplus/002_rect.cpp
 *  @brief Shows how to draw a shaded rectangle
 *
 *  @oglplus_screenshot{002_rect}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_gl{GL_VERSION_3_0}
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

	// Vertex and fragment shader
	Shader vs, fs;

	// Program
	Program prog;

	// A vertex array object for the rendered rectangle
	VertexArray rectangle;

	// VBOs for the rectangle's vertices and colors
	Buffer verts;
	Buffer colors;
public:
	RectangleExample(void)
	 : vs(ShaderType::Vertex)
	 , fs(ShaderType::Fragment)
	{
		// Set the vertex shader source
		vs.Source(StrLit(" \
			#version 330\n \
			in vec2 Position; \
			in vec3 Color; \
			out vec3 vertColor; \
			void main(void) \
			{ \
				vertColor = Color; \
				gl_Position = vec4(Position, 0.0, 1.0); \
			} \
		"));
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(StrLit(" \
			#version 330\n \
			in vec3 vertColor; \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = vec4(vertColor, 1.0); \
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
		vert_attr.Setup<Vec2f>().Enable();

		GLfloat rectangle_colors[12] = {
			1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
		// bind the VBO for the rectangle colors
		colors.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 12, rectangle_colors);
		// setup the vertex attribs array for the vertices
		VertexAttribArray color_attr(prog, "Color");
		color_attr.Setup<Vec3f>().Enable();
		//

		gl.ClearDepth(1.0f);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}
};

void setupExample(ExampleParams& /*params*/){ }

std::unique_ptr<ExampleThread> makeExampleThread(
	Example& /*example*/,
	unsigned /*thread_id*/,
	const ExampleParams& /*params*/
){ return std::unique_ptr<ExampleThread>(); }

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus
