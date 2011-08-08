/**
 *  .file devel/test01.cpp
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
#include <oglplus/shapes/cube.hpp>
#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/torus.hpp>

#include <cmath>

#include "test.hpp"

namespace oglplus {

class Test01 : public Test
{
private:
	//typedef shapes::Cube Shape;
	//typedef shapes::Sphere Shape;
	typedef shapes::Torus Shape;
	//
	Shape shape;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBOs for the shape's vertices and normals
	Buffer verts;
	Buffer normals;
	Buffer uvcoords;

	// texture for the shape
	Texture tex;
public:
	Test01(void)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix;"
			"in vec4 vertex;"
			"in vec3 normal;"
			"in vec2 uvcoord;"
			"out vec3 fragNormal;"
			"out vec2 fragUV;"
			"void main(void)"
			"{"
			"	fragNormal = ("
			"		cameraMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	fragUV = uvcoord;"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		vertex;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		// (uses the absolute value of normal as color)
		fs.Source(
			"#version 330\n"
			"uniform sampler2D tex;"
			"in vec3 fragNormal;"
			"in vec2 fragUV;"
			"out vec4 fragColor;"
			"const vec3 lightPos = vec3(1.0, 1.0, 1.0);"
			"void main(void)"
			"{"
			"	float l = length(lightPos);"
			"	float d = l > 0? dot(fragNormal, lightPos)/l: 0;"
			"	float i = clamp(0.2 + 2.0*d, 0.0, 1.0);"
			"	fragColor = texture2D(tex, fragUV)*i;"
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

		// bind the VAO for the shape
		vao.Bind();

		// bind the VBO for the shape vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> vertices;
			GLuint n_per_vertex = shape.Vertices(vertices);
			// upload the data
			Buffer::Data(Buffer::Target::Array, vertices);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the shape normals
		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> normals;
			GLuint n_per_vertex = shape.Normals(normals);
			// upload the data
			Buffer::Data(Buffer::Target::Array, normals);
			// setup the vertex attribs array for the normals
			VertexAttribArray attr(prog, "normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the shape uv-coords
		uvcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> uv;
			GLuint n_per_vertex = shape.UVCoordinates(uv);
			// upload the data
			Buffer::Data(Buffer::Target::Array, uv);
			VertexAttribArray attr(prog, "uvcoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the texture
		tex.Bind(Texture::Target::_2D);
		{
			size_t s = 256;
			std::vector<GLubyte> tex_data(s*s);
			for(size_t v=0;v!=s;++v)
				for(size_t u=0;u!=s;++u)
					tex_data[v*s+u] = rand() % 0x100;
			Texture::Image2D(
				Texture::ImageTarget::_2D,
				0,
				PixelDataInternalFormat::Red,
				s, s,
				0,
				PixelDataFormat::Red,
				PixelDataType::UnsignedByte,
				tex_data.data()
			);
			Texture::MinFilter(
				Texture::Target::_2D,
				TextureMinFilter::Linear
			);
			Texture::MagFilter(
				Texture::Target::_2D,
				TextureMagFilter::Linear
			);
			Texture::WrapS(
				Texture::Target::_2D,
				TextureWrap::Repeat
			);
			Texture::WrapT(
				Texture::Target::_2D,
				TextureWrap::Repeat
			);
		}

		Uniform(prog, "tex").Set(0);
		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.03f, 0.03f, 0.03f, 0.0f);
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
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				1.5,
				Degrees(time * 135),
				Degrees(std::sin(time * 0.3) * 90)
			)
		);

		vao.Bind();
		// This is not very effective
		shape.Instructions().Draw(shape.Indices());
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
