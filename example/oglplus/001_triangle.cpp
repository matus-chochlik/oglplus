/**
 *  @example oglplus/001_triangle.cpp
 *  @brief Shows the basic usage of OGLplus by drawing a simple red triangle.
 *
 *  @oglplus_screenshot{001_triangle}
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
	// VBO for the triangle's vertices
	Buffer verts;
public:
	TriangleExample(void)
	{
for(auto r=EnumValueRange<Texture::Target>(); !r.Empty(); r.Next())
{
	std::cerr << EnumValueName(r.Front()).c_str() << std::endl;
}
		// Set the vertex shader source
		vs.Source(StrLit(" \
			#version 330\n \
			in vec3 Position; \
			void main(void) \
			{ \
				gl_Position = vec4(Position, 1.0); \
			} \
		"));
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(StrLit(" \
			#version 330\n \
			out vec4 fragColor; \
			void main(void) \
			{ \
				fragColor = vec4(1.0, 0.0, 0.0, 1.0); \
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

		// bind the VAO for the triangle
		triangle.Bind();

		GLfloat triangle_verts[9] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};
		// bind the VBO for the triangle vertices
		verts.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 9, triangle_verts);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(3, DataType::Float);
		vert_attr.Enable();

		gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gl.ClearDepth(1.0f);
	}

	void Reshape(size_t width, size_t height)
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
