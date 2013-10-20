/**
 *  @example standalone/002_dsa_buffer.cpp
 *  @brief Shows usage of the direct state access buffer wrapper
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "glut_glew_example.hpp"

#include <oglplus/all.hpp>
#include <oglplus/ext/EXT_direct_state_access/buffer.hpp>

#include <vector>

class DSABufferExample
 : public oglplus::StandaloneExample
{
private:
	oglplus::Context gl;

	oglplus::Program prog;

	static oglplus::Program make_prog(void)
	{
		using namespace oglplus;

		Program prog;

		Shader vs(ShaderType::Vertex);
		vs.Source(" \
			#version 330\n \
			in vec4 Position; \
			in vec2 Coord; \
			out vec2 vertCoord; \
			void main(void) \
			{ \
				gl_Position = Position; \
				vertCoord = Coord; \
			} \
		").Compile();

		Shader fs(ShaderType::Fragment);
		fs.Source(" \
			#version 330\n \
			in vec2 vertCoord; \
			out vec3 fragColor; \
			void main(void) \
			{ \
				vec2 z = vec2(0.0, 0.0); \
				vec2 c = vertCoord; \
				int i = 0, max = 128; \
				while((i != max) && (distance(z, c) < 2.0)) \
				{ \
					vec2 zn = vec2( \
						z.x * z.x - z.y * z.y + c.x, \
						2.0 * z.x * z.y + c.y \
					); \
					z = zn; \
					++i; \
				} \
				float a = pow(float(max-i) / float(max), 16.0); \
				fragColor = vec3(a, a, a); \
			} \
		").Compile();

		prog.AttachShader(vs).AttachShader(fs).Link().Use();

		return prog;
	}

	oglplus::VertexArray quad;

	oglplus::DSABufferEXT positions, coords;

public:
	DSABufferExample(int /*argc*/, const char** /*argv*/)
	 : gl()
	 , prog(make_prog())
	{
		using namespace oglplus;

		quad.Bind();

		GLfloat rectangle_verts[8] = {
			-1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f
		};
		positions.target = Buffer::Target::Array;
		positions.Data(rectangle_verts);
		positions.Bind();
		(prog|"Position").Setup<Vec2f>().Enable();

		GLfloat rectangle_coords[8] = {
			-1.4f,  0.0f,
			-1.4f,  1.0f,
			 0.0f,  0.0f,
			 0.0f,  1.0f
		};
		coords.target = Buffer::Target::Array;
		coords.Data(rectangle_coords);
		coords.Bind();
		(prog|"Coord").Setup<Vec2f>().Enable();

		coords.Unbind();

		gl.Disable(Capability::DepthTest);
	}

	void Render(void)
	{
		using namespace oglplus;

		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	void Reshape(void)
	{
		using namespace oglplus;

		gl.Viewport(Width(), Height());
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<DSABufferExample>(
		"Example of EXT_direct_state_access buffer usage",
		argc, argv
	);
}

