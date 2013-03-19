/**
 *  @example oglplus/009_metaballs.cpp
 *  @brief Shows how to draw a rectangle 2D metaballs
 *
 *  @oglplus_screenshot{009_metaballs}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <oglplus/bound/texture.hpp>

#include <vector>
#include <cstdlib>

#include "example.hpp"

namespace oglplus {

class MetaballExample : public Example
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

	// VBOs for the rectangle's vertices
	Buffer verts;

	// A 1D xyzw texture that contains metaball parameters
	Texture metaballs_tex;

	std::vector<CubicBezierLoop<Vec4f, double> > ball_paths;
public:
	MetaballExample(void)
	{
		for(GLuint i=0; i!=64; ++i)
		{
			GLuint j = 0, n = 3+std::rand()%3;
			std::vector<Vec4f> points(n);
			while(j != n)
			{
				points[j] = Vec4f(
					1.4*std::rand()/GLdouble(RAND_MAX) - 0.7,
					1.4*std::rand()/GLdouble(RAND_MAX) - 0.7,
					0.0,
					0.1*std::rand()/GLdouble(RAND_MAX) + 0.1
				);
				++j;
			}
			ball_paths.push_back(CubicBezierLoop<Vec4f, double>(points));
			++i;
		}

		// Set the vertex shader source
		vs.Source(StrLit(
			"#version 330\n"
			"in vec2 Position;"
			"out vec3 vertPosition;"
			"void main(void)"
			"{"
			"	vertPosition = vec3(Position, 0.0);"
			"	gl_Position = vec4(vertPosition, 1.0);"
			"}"
		));
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(StrLit(
			"#version 330\n"
			"uniform sampler1D Metaballs;"
			"in vec3 vertPosition;"
			"out vec3 fragColor;"

			"const vec3 AmbientColor = vec3(0.3, 0.4, 0.9);"
			"const vec3 DiffuseColor = vec3(0.5, 0.6, 1.0);"
			"const vec3 LightDir = normalize(vec3(1.0, 1.0, 1.0));"

			"void main(void)"
			"{"
			"	int i = 0, n = textureSize(Metaballs, 0);"

			"	float InvN = 1.0/n;"
			"	float Value = 0.0;"
			"	vec3 Normal = vec3(0.0, 0.0, 0.0);"
			"	while(i != n)"
			"	{"
			"		vec4 Metaball = texelFetch(Metaballs, i, 0);"
			"		float Radius = Metaball.w;"
			"		vec3 Vect = vertPosition - Metaball.xyz;"
			"		float Tmp = pow(Radius,2.0)/dot(Vect, Vect)-0.25;"
			"		Value += Tmp;"
			"		float Mul = max(Tmp, 0.0);"
			"		Normal += Mul*vec3(Vect.xy, Mul*InvN/Radius);"
			"		++i;"
			"	}"
			"	if(Value > 0.0)"
			"	{"
			"		float Diffuse = 1.4*max(dot("
			"			LightDir,"
			"			normalize(Normal)"
			"		), 0.0);"
			"		float Ambient = 0.3;"
			"		fragColor = "
			"			Ambient*AmbientColor+"
			"			Diffuse*DiffuseColor;"
			"	}"
			"	else fragColor = vec3(0.4, 0.4, 0.4);"
			"}"
		));
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog << vs << fs;
		// link and use it
		prog.Link().Use();

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
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(2, DataType::Float).Enable();
		//
		Texture::Active(0);
		UniformSampler(prog, "Metaballs").Set(0);

		{
			auto bound_tex = Bind(metaballs_tex, Texture::Target::_1D);
			bound_tex.Image1D(
				0,
				PixelDataInternalFormat::RGBA32F,
				ball_paths.size(),
				0,
				PixelDataFormat::RGBA,
				PixelDataType::Float,
				nullptr
			);
			bound_tex.MinFilter(TextureMinFilter::Nearest);
			bound_tex.MagFilter(TextureMagFilter::Nearest);
			bound_tex.WrapS(TextureWrap::MirroredRepeat);
		}

		gl.ClearDepth(1.0f);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
	}

	void Render(double time)
	{
		std::size_t metaball_count = ball_paths.size(), k = 0;
		std::vector<GLfloat> metaballs(metaball_count*4);
		for(std::size_t ball=0; ball != metaball_count; ++ball)
		{
			Vec4f pos = ball_paths[ball].Position(time / 10.0);

			for(std::size_t coord=0; coord != 4; ++coord)
				metaballs[k++] = pos.At(coord);
		}

		Texture::Image1D(
			Texture::Target::_1D,
			0,
			PixelDataInternalFormat::RGBA32F,
			metaball_count,
			0,
			PixelDataFormat::RGBA,
			PixelDataType::Float,
			metaballs.data()
		);
		gl.Clear().DepthBuffer();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
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
	return std::unique_ptr<Example>(new MetaballExample);
}

} // namespace oglplus
