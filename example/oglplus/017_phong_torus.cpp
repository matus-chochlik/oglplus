/**
 *  @example oglplus/017_phong_torus.cpp
 *  @brief Shows how to draw a "phong" shaded torus using the Torus builder
 *
 *  @image html 017_phong_torus.png
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
			"uniform mat4 projectionMatrix, cameraMatrix;"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out vec3 fragNormal;"
			"out vec3 viewDir;"
			"void main(void)"
			"{"
			"	fragNormal = normal;"
			"	viewDir = (vec4(0.0, 0.0, 1.0, 1.0)*cameraMatrix).xyz;"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		vertex;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec3 fragNormal;"
			"in vec3 viewDir;"
			"out vec4 fragColor;"
			"uniform vec3 lightPos[3];"
			"void main(void)"
			"{"
			"	float amb = 0.2;"
			"	float diff = 0.0;"
			"	float spec = 0.0;"
			"	for(int i=0;i!=3;++i)"
			"	{"
			"		diff += max("
			"			dot(fragNormal,  lightPos[i])/"
			"			dot(lightPos[i], lightPos[i]),"
			"			0.0"
			"		);"
			"		float k = dot(fragNormal, lightPos[i]);"
			"		vec3 r = 2.0*k*fragNormal - lightPos[i];"
			"		spec += pow(max("
			"			dot(normalize(r), viewDir),"
			"			0.0"
			"		), 32.0 * dot(r, r));"
			"	}"
			"	fragColor = "
			"		vec4(1.0, 0.1, 0.3, 1.0)*(amb+diff)+"
			"		vec4(1.0, 1.0, 1.0, 1.0)*spec;"
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

		// set the light positions
		Uniform(prog, "lightPos[0]").Set(Vec3f(2.0f,-1.0f, 0.0f));
		Uniform(prog, "lightPos[1]").Set(Vec3f(0.0f, 3.0f, 0.0f));
		Uniform(prog, "lightPos[2]").Set(Vec3f(0.0f,-1.0f, 4.0f));
		//
		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			Matrix4f::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			Matrix4f::Orbiting(
				Vec3f(),
				1.5,
				Degrees(time * 135),
				Degrees(std::sin(time * 0.3) * 90)
			)
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
