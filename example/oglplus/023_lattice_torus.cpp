/**
 *  @example oglplus/023_lattice_torus.cpp
 *  @brief Shows how to draw a torus with lattice surface
 *
 *  @image html 023_lattice_torus.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/torus.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class TorusExample : public Example
{
private:
	shapes::Torus make_torus;
	shapes::DrawingInstructions torus_instr;
	shapes::Torus::IndexArray torus_indices;

	// wrapper around the current OpenGL context
	Context gl;

	VertexShader vs;
	GeometryShader gs;
	FragmentShader fs;
	Program prog;

	// A vertex array object for the rendered torus
	VertexArray torus;

	// VBOs for the torus's vertices
	Buffer verts;
public:
	TorusExample(void)
	 : make_torus(1.0, 0.5, 12, 12)
	 , torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	{
		vs.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"uniform mat4 modelMatrix, cameraMatrix;"
			"void main(void)"
			"{"
			"	gl_Position = cameraMatrix *"
			"		modelMatrix * vertex;"
			"}"
		);
		vs.Compile();

		gs.Source(
			"#version 330\n"
			"layout(triangles) in;"
			"layout(triangle_strip, max_vertices = 8) out;"
			"uniform mat4 projectionMatrix;"
			"uniform vec4 lightPosCam;"
			"out vec3 lightDir;"
			"out float opacity;"
			"void main(void)"
			"{"
			"	vec4 c = vec4(("
			"		gl_in[0].gl_Position.xyz+"
			"		gl_in[1].gl_Position.xyz+"
			"		gl_in[2].gl_Position.xyz "
			"	) * 0.333333, 1.0);"
			"	for(int v = 0; v != 4; ++v)"
			"	{"
			"		vec4 a = gl_in[v%3].gl_Position;"
			"		gl_Position = projectionMatrix * a;"
			"		lightDir = (lightPosCam - a).xyz;"
			"		opacity = 1.0;"
			"		EmitVertex();"
			"		vec4 b = vec4("
			"			a.xyz + (c.xyz - a.xyz)*0.3,"
			"			1.0"
			"		);"
			"		gl_Position = projectionMatrix * b;"
			"		lightDir = (lightPosCam - b).xyz;"
			"		opacity = 0.0;"
			"		EmitVertex();"
			"	}"
			"	EndPrimitive();"
			"}"
		);
		gs.Compile();

		fs.Source(
			"#version 330\n"
			"in vec3 lightDir;"
			"in float opacity;"
			"uniform vec3 frontColor, backColor;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(lightDir);"
			"	vec3 color = gl_FrontFacing?"
			"		frontColor:"
			"		backColor;"
			"	fragColor = vec4(color*(4.0/l), opacity);"
			"}"
		);
		fs.Compile();

		prog.AttachShader(vs);
		prog.AttachShader(gs);
		prog.AttachShader(fs);
		prog.Link();

		torus.Bind();
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);

			prog.Use();
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		gl.ClearColor(0.8f, 0.7f, 0.6f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.DepthFunc(CompareFn::LEqual);
		gl.FrontFace(make_torus.FaceWinding());
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto projection = CamMatrixf::Perspective(
			Degrees(24),
			double(width)/height,
			1, 100
		);
		prog.Use();
		Uniform(prog, "projectionMatrix").SetMatrix(projection);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			2.5,
			Degrees(time * 35),
			Degrees(std::sin(time * 0.3) * 60)
		);

		auto model =
			ModelMatrixf::RotationY(FullCircles(time * 0.25)) *
			ModelMatrixf::RotationX(FullCircles(0.25));

		Vec4f lightPos(4.0f, 4.0f, -8.0f, 1.0f);

		prog.Use();
		Uniform(prog, "cameraMatrix").SetMatrix(camera);
		Uniform(prog, "modelMatrix").SetMatrix(model);
		Uniform(prog, "lightPosCam").Set(camera * lightPos);

		Uniform(prog, "frontColor").Set(Vec3f(0.3, 0.2, 0.0));
		Uniform(prog, "backColor").Set(Vec3f(0.2, 0.1, 0.0));
		gl.PolygonMode(Face::Front, PolygonMode::Line);
		gl.PolygonMode(Face::Back, PolygonMode::Line);
		torus_instr.Draw(torus_indices);

		Uniform(prog, "frontColor").Set(Vec3f(0.9, 0.8, 0.1));
		Uniform(prog, "backColor").Set(Vec3f(0.7, 0.6, 0.2));
		gl.PolygonMode(Face::Front, PolygonMode::Fill);
		gl.PolygonMode(Face::Back, PolygonMode::Fill);
		torus_instr.Draw(torus_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new TorusExample);
}

} // namespace oglplus
