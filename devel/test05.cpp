/**
 *  .file devel/test05.cpp
 *  Development / testing file.
 *  NOTE. this file is here for feature development / testing purposes only
 *  and its source code, input, output can change witout prior notice.
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/torus.hpp>
#include <oglplus/bound/buffer.hpp>
#include <oglplus/bound/texture.hpp>

#include <iostream>

#include <cmath>

#include "test.hpp"

namespace oglplus {
namespace images {

} // namespace images


class Test01 : public Test
{
private:
	typedef shapes::Torus Shape;
	//
	Shape shape;
	shapes::DrawingInstructions shape_instr;
	shapes::Torus::IndexArray shape_indices;

	// wrapper around the current OpenGL context
	Context gl;

	VertexShader vs;

	GeometryShader gs;

	FragmentShader fs;

	Program prog;

	// A vertex array object for the rendered shape
	VertexArray vao;

	Buffer verts;
	Buffer normals;

	// textures for the shape
	Texture color_tex, normal_tex;
public:
	Test01(void)
	 : shape()
	 , shape_instr(shape.InstructionsWithAdjacency())
	 , shape_indices(shape.IndicesWithAdjacency())
	{
		vs.Source(
			"#version 330\n"
			"uniform vec3 cameraPos;"
			"uniform mat4 cameraMatrix, modelMatrix;"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out float s;"
			"void main(void)"
			"{"
			"	vec4 v = modelMatrix * vertex;"
			"	vec4 n = modelMatrix * vec4(normal, 0.0);"
			"	s = dot(n.xyz, normalize(cameraPos-v.xyz));"
			"	gl_Position = cameraMatrix * v;"
			"}"
		);
		vs.Compile();

		gs.Source(
			"#version 330\n"
			"layout(triangles_adjacency) in;"
			"layout(line_strip, max_vertices = 2) out;"
			"uniform mat4 projectionMatrix;"
			"in float s[];"
			"void main(void)"
			"{"
			"	for(int i=0; i!=6; i+=2)"
			"	if(s[i]>=0.0 && s[(i+2)%6]>=0.0 && s[i+1]<=0.0)"
			"	{"
			"		gl_Position = projectionMatrix*"
			"			gl_in[i].gl_Position;"
			"		EmitVertex();"
			"		gl_Position = projectionMatrix*"
			"			gl_in[(i+2)%6].gl_Position;"
			"		EmitVertex();"
			"		EndPrimitive();"
			"	}"
			"}"
		);
		gs.Compile();

		fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(1, 1, 1, 1.0);"
			"}"
		);
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(gs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the shape
		vao.Bind();

		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = shape.Vertices(data);
			Bind(verts, Buffer::Target::Array).Data(data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = shape.Normals(data);
			Bind(normals, Buffer::Target::Array).Data(data);
			// setup the vertex attribs array for the normals
			VertexAttribArray attr(prog, "normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		gl.ClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		//
		gl.FrontFace(shape.FaceWinding());
		gl.CullFace(Face::Back);
		gl.Enable(Capability::CullFace);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		auto cameraMatrix = CamMatrixf::Orbiting(
			Vec3f(),
			3.0 + std::sin(time)*1.0,
			FullCircles(time * 0.2),
			Degrees(std::sin(time * 0.2) * 70)
		);
		Uniform(prog, "cameraPos").Set(cameraMatrix.Position());
		Uniform(prog, "cameraMatrix").SetMatrix(cameraMatrix);

		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::RotationA(
				Vec3f(1.0f, 1.0f, 1.0f),
				FullCircles(time * 0.1)
			)
		);

		shape_instr.Draw(shape_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Test> makeTest(void)
{
	return std::unique_ptr<Test>(new Test01);
}

} // namespace oglplus
