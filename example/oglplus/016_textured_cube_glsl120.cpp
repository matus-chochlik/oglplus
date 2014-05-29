/**
 *  @example oglplus/016_textured_cube_glsl120.cpp
 *  @brief Shows how to draw a simple textured cube (using GLSL 120)
 *
 *  @oglplus_screenshot{016_textured_cube_glsl120}
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_gl{GL_VERSION_3_0}
 *  @oglplus_example_uses_cpp_feat{FUNCTION_TEMPLATE_DEFAULT_ARGS}
 *  @oglplus_example_uses_cpp_feat{LAMBDAS}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/opt/smart_enums.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/images/newton.hpp>
#include <oglplus/bound/texture.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CubeExample : public Example
{
private:
	// helper object building cube vertex attributes
	shapes::Cube make_cube;
	// helper object encapsulating cube drawing instructions
	shapes::DrawingInstructions cube_instr;
	// indices pointing to cube primitive elements
	shapes::Cube::IndexArray cube_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Program
	Program prog;

	// Uniforms
	Lazy<Uniform<Mat4f>> projection_matrix, camera_matrix, model_matrix;

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertex attributes
	Buffer verts, normals, texcoords;

	// The stained glass texture
	Texture tex;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , model_matrix(prog, "ModelMatrix")
	{
		namespace se = oglplus::smart_enums;
		VertexShader vs;
		vs.Source(
			"#version 120\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"attribute vec4 Position;"
			"attribute vec3 Normal;"
			"attribute vec2 TexCoord;"
			"varying vec3 vertNormal;"
			"varying vec3 vertLight;"
			"varying vec2 vertTexCoord;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	vertNormal = mat3(ModelMatrix)*Normal;"
			"	gl_Position = ModelMatrix * Position;"
			"	vertLight = LightPos - gl_Position.xyz;"
			"	vertTexCoord = TexCoord;"
			"	gl_Position = ProjectionMatrix * CameraMatrix * gl_Position;"
			"}"
		).Compile();

		FragmentShader fs;
		fs.Source(
			"#version 120\n"
			"uniform sampler2D TexUnit;"
			"varying vec3 vertNormal;"
			"varying vec3 vertLight;"
			"varying vec2 vertTexCoord;"
			"void main(void)"
			"{"
			"	float l = length(vertLight);"
			"	float d = l > 0 ? dot(vertNormal, normalize(vertLight)) / l : 0.0;"
			"	float i = 0.3 + 2.0*max(d, 0.0);"
			"	vec4 t = texture2D(TexUnit, vertTexCoord);"
			"	gl_FragColor = vec4(t.rgb*i, 1.0);"
			"}"
		).Compile();

		prog.AttachShader(vs).AttachShader(fs).Link().Use();

		// bind the VAO for the cube
		cube.Bind();

		verts.Bind(se::Array());
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Positions(data);
			Buffer::Data(se::Array(), data);
			(prog|"Position").Setup<GLfloat>(n_per_vertex).Enable();
		}

		normals.Bind(se::Array());
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(se::Array(), data);
			(prog|"Normal").Setup<GLfloat>(n_per_vertex).Enable();
		}

		texcoords.Bind(se::Array());
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.TexCoordinates(data);
			Buffer::Data(se::Array(), data);
			(prog|"TexCoord").Setup<GLfloat>(n_per_vertex).Enable();
		}

		// setup the texture
		{
			auto image = images::NewtonFractal(
				512, 512,
				Vec3f(1.0f, 1.4f, 1.3f),
				Vec3f(0.2f, 0.3f, 0.1f),
				Vec2f(-1.0f, -1.0f),
				Vec2f( 1.0f,  1.0f),
				images::NewtonFractal::X4Minus1(),
				[](double x) -> double
				{
					return pow(SineWave(pow(x,0.5)), 4.0);
				}
			);
			gl.Bound(se::_2D(), tex)
				.MinFilter(se::LinearMipmapLinear())
				.MagFilter(se::Linear())
				.WrapS(se::Repeat())
				.WrapT(se::Repeat())
				.Image2D(image)
				.GenerateMipmap();
		}
		// set the uniform values
		(prog/"TexUnit") = 0;
		(prog/"LightPos") = Vec3f(1.0f, 2.0f, 3.0f);
		//
		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(se::DepthTest());

		gl.Enable(se::CullFace());
		gl.FrontFace(make_cube.FaceWinding());
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(60),
				GLfloat(width)/height,
				0.1, 30
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				7.5 - SineWave(time / 6.0) * 6.0,
				FullCircles(time * 0.03),
				Degrees(SineWave(time / 30.0) * 90)
			)
		);

		// set the model matrix
		model_matrix.Set(
			ModelMatrixf::RotationX(FullCircles(time * 0.01))
		);

		cube.Bind();
		gl.CullFace(Face::Back);
		cube_instr.Draw(cube_indices);
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
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus
