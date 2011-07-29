/**
 *  @example oglplus/012_checker_sphere.cpp
 *  @brief Shows how to draw a checkered sphere using the Sphere builder
 *
 *  @image html 012_checker_sphere.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/sphere.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class SphereExample : public Example
{
private:
	// helper object building sphere vertex attributes
	shapes::Sphere make_sphere;
	// helper object encapsulating sphere drawing instructions
	shapes::DrawingInstructions sphere_instr;
	// indices pointing to sphere primitive elements
	shapes::Sphere::IndexArray sphere_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered sphere
	VertexArray sphere;

	// VBOs for the sphere's vertices and uv-coordinates
	Buffer verts;
	Buffer uvcoords;
public:
	SphereExample(void)
	 : sphere_instr(make_sphere.Instructions())
	 , sphere_indices(make_sphere.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix;"
			"in vec4 vertex;"
			"in vec2 uvcoord;"
			"out vec2 uv;"
			"void main(void)"
			"{"
			"	uv = uvcoord;"
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
			"in vec2 uv;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float i = (int(uv.x*18)%2 + int(uv.y*14)%2)%2;"
			"	fragColor = vec4(1-i/2, 1-i/2, 1-i/2, 1.0);"
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

		// bind the VAO for the sphere
		sphere.Bind();

		// bind the VBO for the sphere vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the sphere UV-coordinates
		uvcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.UVCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "uvcoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
		//
		VertexArray::Unbind();
		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		// set the projection matrix fov = 24 deg. aspect = width/height
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
				1.5,
				Degrees(time * 135),
				Degrees(std::sin(time * 0.3) * 90)
			)
		);

		sphere.Bind();
		sphere_instr.Draw(sphere_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new SphereExample);
}

} // namespace oglplus
