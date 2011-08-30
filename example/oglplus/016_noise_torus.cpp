/**
 *  @example oglplus/016_noise_torus.cpp
 *  @brief Shows how to draw a torus with a grayscale noise texture
 *
 *  @image html 016_noise_torus.png
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

	// VBOs for the torus's vertex attributes
	Buffer verts, normals, texcoords;

	// texture for the torus
	Texture tex;
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
			"in vec2 texcoord;"
			"out vec3 fragNormal;"
			"out vec3 fragLight;"
			"out vec2 fragTex;"
			"uniform vec3 lightPos;"
			"void main(void)"
			"{"
			"	fragNormal = ("
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	fragLight = ("
			"		vec4(lightPos, 0.0)-"
			"		modelMatrix*vertex"
			"	).xyz;"
			"	fragTex = texcoord;"
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
			"uniform sampler2D tex;"
			"in vec3 fragNormal;"
			"in vec3 fragLight;"
			"in vec2 fragTex;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(fragLight);"
			"	float d = l > 0? dot(fragNormal, fragLight)/l: 0.0;"
			"	float i = 1.2*max(d, 0.0) + 0.2;"
			"	fragColor = texture(tex, fragTex)*i;"
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

		// bind the VBO for the torus texture coordinates
		texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.TexCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "texcoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the texture
		Texture::Target tex_tgt = Texture::Target::_2D;
		tex.Bind(tex_tgt);
		{
			size_t s = 256;
			std::vector<GLubyte> tex_data(s*s);
			for(size_t v=0;v!=s;++v)
				for(size_t u=0;u!=s;++u)
					tex_data[v*s+u] = rand() % 0x100;
			Texture::Image2D(
				tex_tgt,
				0,
				PixelDataInternalFormat::Red,
				s, s,
				0,
				PixelDataFormat::Red,
				PixelDataType::UnsignedByte,
				tex_data.data()
			);
			Texture::MinFilter(tex_tgt, TextureMinFilter::Linear);
			Texture::MagFilter(tex_tgt, TextureMagFilter::Linear);
			Texture::WrapS(tex_tgt, TextureWrap::Repeat);
			Texture::WrapT(tex_tgt, TextureWrap::Repeat);
			Texture::SwizzleG(tex_tgt, TextureSwizzle::Red);
			Texture::SwizzleB(tex_tgt, TextureSwizzle::Red);
		}
		//
		Uniform(prog, "tex").Set(0);
		Uniform(prog, "lightPos").Set(Vec3f(4.0f, 4.0f, -8.0f));

		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_torus.FaceWinding());
		gl.CullFace(Face::Back);
		gl.PolygonMode(Face::Front, PolygonMode::Fill);
		gl.PolygonMode(Face::Back, PolygonMode::Line);
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
				Degrees(std::sin(time * 0.3) * 60)
			)
		);
		// set the model matrix
		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::RotationX(FullCircles(time * 0.25))
		);

		torus.Bind();
		gl.CullFace(Face::Front);
		torus_instr.Draw(torus_indices);
		//
		gl.CullFace(Face::Back);
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
