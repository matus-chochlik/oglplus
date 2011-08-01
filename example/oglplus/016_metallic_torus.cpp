/**
 *  @example oglplus/016_metallic_torus.cpp
 *  @brief Shows how to draw a metallic-looking torus
 *
 *  @image html 016_metallic_torus.png
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
	// helper object building torus vertex attributes
	shapes::Torus make_torus;
	// helper object encapsulating torus drawing instructions
	shapes::DrawingInstructions torus_instr;
	// indices pointing to torus primitive elements
	shapes::Torus::IndexArray torus_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered torus
	VertexArray torus;

	// VBOs for the torus's vertices and normals
	Buffer verts, normals;
public:
	TorusExample(void)
	 : make_torus(1.0, 0.5, 72, 48)
	 , torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out vec3 fragNormal;"
			"void main(void)"
			"{"
			"	fragNormal = ("
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform int colorCount;"
			"uniform vec4 color[8];"
			"in vec3 fragNormal;"
			"vec3 viewDir = vec3(0.0, 0.0, 1.0);"
			"vec3 topDir = vec3(0.0, 1.0, 0.0);"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float k = dot(fragNormal, viewDir);"
			"	vec3 reflDir = 2.0*k*fragNormal - viewDir;"
			"	float a = dot(reflDir, topDir);"
			"	vec3 reflColor;"
			"	for(int i = 0; i != (colorCount - 1); ++i)"
			"	{"
			"		if(a<color[i].a && a>=color[i+1].a)"
			"		{"
			"			float m = "
			"				(a - color[i].a)/"
			"				(color[i+1].a-color[i].a);"
			"			reflColor = mix("
			"				color[i].rgb,"
			"				color[i+1].rgb,"
			"				m"
			"			);"
			"			break;"
			"		}"
			"	}"
			"	float i = max(dot(fragNormal, topDir), 0.0);"
			"	vec3 diffColor = vec3(i, i, i);"
			"	fragColor = vec4("
			"		mix(reflColor, diffColor, 0.3 + i*0.7),"
			"		1.0"
			"	);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the torus
		torus.Bind();

		// bind the VBO for the torus vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the torus normals
		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
		//
		VertexArray::Unbind();

		// setup the color gradient
		Uniform(prog, "colorCount").Set(8);
		Uniform(prog, "color[0]").Set(Vec4f(1.0f, 1.0f, 0.9f, 1.00f));
		Uniform(prog, "color[1]").Set(Vec4f(1.0f, 0.9f, 0.8f, 0.97f));
		Uniform(prog, "color[2]").Set(Vec4f(0.9f, 0.7f, 0.5f, 0.95f));
		Uniform(prog, "color[3]").Set(Vec4f(0.5f, 0.5f, 1.0f, 0.95f));
		Uniform(prog, "color[4]").Set(Vec4f(0.2f, 0.2f, 0.7f, 0.00f));
		Uniform(prog, "color[5]").Set(Vec4f(0.1f, 0.1f, 0.1f, 0.00f));
		Uniform(prog, "color[6]").Set(Vec4f(0.2f, 0.2f, 0.2f,-0.10f));
		Uniform(prog, "color[7]").Set(Vec4f(0.5f, 0.5f, 0.5f,-1.00f));

		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_torus.FaceWinding());
		gl.CullFace(Face::Back);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(
				Degrees(24),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.5,
				Degrees(time * 35),
				Degrees(std::sin(time * 0.1) * 80)
			)
		);
		// set the model matrix
		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::RotationX(FullCircles(time * 0.25))
		);

		torus.Bind();
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
