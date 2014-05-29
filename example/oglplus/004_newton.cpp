/**
 *  @example oglplus/004_newton.cpp
 *  @brief Shows how to draw a rectangle with the Newton fractal.
 *
 *  @oglplus_screenshot{004_newton}
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
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

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered rectangle
	VertexArray rectangle;

	// VBOs for the rectangle's vertices used also as the viewport coords
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
				vertCoord = Position; \
				gl_Position = vec4(Position, 0.0, 1.0); \
			} \
		");
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(" \
			#version 330\n \
			in vec2 vertCoord; \
			uniform vec3 Color1, Color2; \
			out vec4 fragColor; \
			\
			vec2 f(vec2 n) \
			{ \
				return vec2( \
					n.x*n.x*n.x - 3.0*n.x*n.y*n.y - 1.0, \
					-n.y*n.y*n.y + 3.0*n.x*n.x*n.y \
				); \
			} \
			\
			vec2 df(vec2 n) \
			{ \
				return 3.0 * vec2( \
					n.x*n.x - n.y*n.y, \
					2.0 * n.x * n.y \
				); \
			} \
			\
			vec2 cdiv(vec2 a, vec2 b) \
			{ \
				float d = dot(b, b); \
				if(d == 0.0) return a; \
				else return vec2( \
					(a.x*b.x + a.y*b.y) / d, \
					(a.y*b.x - a.x*b.y) / d  \
				); \
			} \
			void main(void) \
			{ \
				vec2 z = vertCoord; \
				int i, max = 128; \
				for(i = 0; i != max; ++i) \
				{ \
					vec2 zn = z - cdiv(f(z), df(z)); \
					if(distance(zn, z) < 0.00001) break; \
					z = zn; \
				} \
				fragColor = vec4( \
					mix( \
						Color1.rgb, \
						Color2.rgb, \
						float(i) / float(max) \
					), \
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
		Buffer::Data(Buffer::Target::Array, rectangle_verts);
		// setup the vertex attribs array for the vertices
		VertexArrayAttrib vert_attr(prog, "Position");
		vert_attr.Setup<Vec2f>();
		vert_attr.Enable();
		//
		Uniform<Vec3f>(prog, "Color1").Set(Vec3f(0.2f, 0.02f, 0.05f));
		Uniform<Vec3f>(prog, "Color2").Set(Vec3f(1.0f, 0.95f, 0.98f));
		//
		gl.Disable(Capability::DepthTest);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
	}

	void Render(double)
	{
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
