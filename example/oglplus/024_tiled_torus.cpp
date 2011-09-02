/**
 *  @example oglplus/024_tiled_torus.cpp
 *  @brief Shows how to draw a partially covered surface of torus with an outline
 *
 *  @image html 024_tiled_torus.png
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

	VertexShader line_vs;
	GeometryShader line_gs;
	FragmentShader line_fs;
	Program line_prog;

	VertexShader fill_vs;
	GeometryShader fill_gs;
	FragmentShader fill_fs;
	Program fill_prog;

	// A vertex array object for the rendered torus
	VertexArray torus;

	// VBOs for the torus's vertices
	Buffer verts;
public:
	TorusExample(void)
	 : make_torus(1.0, 0.5, 72, 48)
	 , torus_instr(make_torus.InstructionsWithAdjacency())
	 , torus_indices(make_torus.IndicesWithAdjacency())
	{
		line_vs.Source(
			"#version 330\n"
			"uniform vec3 position;"
			"uniform mat4 modelMatrix;"
			"in vec4 vertex;"
			"out vec3 dir;"
			"void main(void)"
			"{"
			"	gl_Position = modelMatrix * vertex;"
			"	dir = position-gl_Position.xyz;"
			"}"
		);
		line_vs.Compile();

		line_gs.Source(
			"#version 330\n"
			"layout(triangles_adjacency) in;"
			"layout(line_strip, max_vertices = 6) out;"
			"uniform mat4 cameraMatrix, projectionMatrix;"
			"in vec3 dir[];"
			"void main(void)"
			"{"
			"	vec3 nf = cross("
			"		gl_in[2].gl_Position.xyz-"
			"		gl_in[0].gl_Position.xyz,"
			"		gl_in[4].gl_Position.xyz-"
			"		gl_in[0].gl_Position.xyz "
			"	);"
			"	for(int i=0; i!=6; i+=2)"
			"	{"
			"		int a = i, b = (i+2)%6, c = i+1;"
			"		vec4 pa = gl_in[a].gl_Position;"
			"		vec4 pb = gl_in[b].gl_Position;"
			"		vec4 pc = gl_in[c].gl_Position;"
			"		vec3 nc = cross((pb-pc).xyz,(pa-pc).xyz);"
			"		bool edge = "
			"			dot(nf,dir[a]) >= 0.0 &&"
			"			dot(nf,dir[b]) >= 0.0 &&"
			"			dot(nc,dir[c]) <= 0.0;"
			"		if(edge)"
			"		{"
			"			gl_Position = "
			"				projectionMatrix *"
			"				cameraMatrix * pa;"
			"			EmitVertex();"
			"			gl_Position = "
			"				projectionMatrix *"
			"				cameraMatrix * pb;"
			"			EmitVertex();"
			"			EndPrimitive();"
			"		}"
			"	}"
			"}"
		);
		line_gs.Compile();

		line_fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(0.0, 0.0, 0.0, 1.0);"
			"}"
		);
		line_fs.Compile();

		line_prog.AttachShader(line_vs);
		line_prog.AttachShader(line_gs);
		line_prog.AttachShader(line_fs);
		line_prog.Link();

		fill_vs.Source(
			"#version 330\n"
			"uniform vec3 lightPos;"
			"uniform mat4 modelMatrix;"
			"in vec4 vertex;"
			"out vec3 lightDir;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		modelMatrix *"
			"		vertex;"
			"	lightDir = lightPos - gl_Position.xyz;"
			"}"
		);
		fill_vs.Compile();

		fill_gs.Source(
			"#version 330\n"
			"layout(triangles_adjacency) in;"
			"layout(triangle_strip, max_vertices = 9) out;"
			"uniform mat4 projectionMatrix, cameraMatrix;"
			"in vec3 lightDir[];"
			"void main(void)"
			"{"
			"	vec3 nf = cross("
			"		gl_in[2].gl_Position.xyz-"
			"		gl_in[0].gl_Position.xyz,"
			"		gl_in[4].gl_Position.xyz-"
			"		gl_in[0].gl_Position.xyz "
			"	);"
			"	bool lighted = "
			"		dot(nf, lightDir[0]) >= 0.0 ||"
			"		dot(nf, lightDir[2]) >= 0.0 ||"
			"		dot(nf, lightDir[4]) >= 0.0;"
			"	if(lighted)"
			"	{"
			"		for(int i=0; i!=3; ++i)"
			"		{"
			"			gl_Position = "
			"				projectionMatrix *"
			"				cameraMatrix *"
			"				gl_in[i*2].gl_Position;"
			"			EmitVertex();"
			"		}"
			"		EndPrimitive();"
			"	}"
			"}"
		);
		fill_gs.Compile();

		fill_fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	if(gl_FrontFacing)"
			"		fragColor = vec4(0.9, 0.8, 0.0, 1.0);"
			"	else fragColor = vec4(0.7, 0.6, 0.0, 1.0);"
			"}"
		);
		fill_fs.Compile();

		fill_prog.AttachShader(fill_vs);
		fill_prog.AttachShader(fill_gs);
		fill_prog.AttachShader(fill_fs);
		fill_prog.Link();

		torus.Bind();
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);

			line_prog.Use();
			VertexAttribArray line_attr(line_prog, "vertex");
			line_attr.Setup(n_per_vertex, DataType::Float);
			line_attr.Enable();

			fill_prog.Use();
			VertexAttribArray fill_attr(fill_prog, "vertex");
			fill_attr.Setup(n_per_vertex, DataType::Float);
			fill_attr.Enable();
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
		line_prog.Use();
		Uniform(line_prog, "projectionMatrix").SetMatrix(projection);
		fill_prog.Use();
		Uniform(fill_prog, "projectionMatrix").SetMatrix(projection);
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

		Vec3f lightPos(4.0f, 4.0f, -8.0f);

		fill_prog.Use();
		Uniform(fill_prog, "cameraMatrix").SetMatrix(camera);
		Uniform(fill_prog, "modelMatrix").SetMatrix(model);
		Uniform(fill_prog, "lightPos").Set(lightPos);
		torus_instr.Draw(torus_indices);

		line_prog.Use();
		Uniform(line_prog, "cameraMatrix").SetMatrix(camera);
		Uniform(line_prog, "modelMatrix").SetMatrix(model);
		Uniform(line_prog, "position").Set(camera.Position());
		torus_instr.Draw(torus_indices);
		Uniform(line_prog, "position").Set(lightPos);
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
