/**
 *  @example oglplus/019_honeycomb_cube.cpp
 *  @brief Shows how to draw a semi-transparent textured cube
 *
 *  @oglplus_screenshot{019_honeycomb_cube}
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_gl{GL_VERSION_3_0}
 *  @oglplus_example_uses_texture{honeycomb}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/images/load.hpp>
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

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// Uniforms in prog
	LazyUniform<Mat4f> projection_matrix, camera_matrix, model_matrix;

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertex attributes
	Buffer verts, normals, texcoords;

	// The stained glass texture
	DefaultTexture tex;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , model_matrix(prog, "ModelMatrix")
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"in vec2 TexCoord;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"out vec2 vertTexCoord;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	vertNormal = mat3(ModelMatrix)*Normal;"
			"	gl_Position = ModelMatrix * Position;"
			"	vertLight = LightPos - gl_Position.xyz;"
			"	vertTexCoord = TexCoord * 6.0;"
			"	gl_Position = ProjectionMatrix * CameraMatrix * gl_Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform sampler2D TexUnit;"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = dot(vertLight, vertLight);"
			"	float d = l != 0.0 ? dot("
			"		vertNormal, "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	vec3 c = vec3(0.9, 0.8, 0.2);"
			"	vec4 t  = texture(TexUnit, vertTexCoord);"
			"	float a = 1.0 - sqrt(abs(d)), e;"
			"	if(gl_FrontFacing)"
			"	{"
			"		e = d >= 0.0 ?"
			"		d * mix(0.5, 1.0, t.a):"
			"		(-0.9*d) * (1.0 - t.a);"
			"	}"
			"	else"
			"	{"
			"		e = d >= 0.0 ?"
			"		(0.6*d) * (1.0 - t.a):"
			"		(-0.7*d) * mix(0.5, 1.0, t.a);"
			"	}"
			"	float i = 0.1 + 9.0*e;"
			"	fragColor = vec4("
			"		t.r*c.r*i, "
			"		t.g*c.g*i, "
			"		t.b*c.b*i, "
			"		clamp(pow(t.a,2) + a*0.4, 0.0, 1.0)"
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
		gl.Use(prog);

		// bind the VAO for the cube
		gl.Bind(cube);

		gl.Bind(Buffer::Target::Array, verts);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		gl.Bind(Buffer::Target::Array, normals);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Normal");
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		gl.Bind(Buffer::Target::Array, texcoords);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "TexCoord");
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		// setup the texture
		gl.Bound(Texture::Target::_2D, tex)
			.Image2D(images::LoadTexture("honeycomb"))
			.GenerateMipmap()
			.MinFilter(TextureMinFilter::LinearMipmapLinear)
			.MagFilter(TextureMagFilter::Linear)
			.WrapS(TextureWrap::MirroredRepeat)
			.WrapT(TextureWrap::MirroredRepeat)
			.Anisotropy(2);
		//
		UniformSampler(prog, "TexUnit").Set(0);
		Uniform<Vec3f>(prog, "LightPos").Set(Vec3f(1.0f, 2.0f, 3.0f));
		//
		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(
			BlendFn::SrcAlpha,
			BlendFn::OneMinusSrcAlpha
		);

		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_cube.FaceWinding());
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(80),
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
		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				4.0 - SineWave(time / 6.0) * 2.0,
				FullCircles(time * 0.4),
				Degrees(SineWave(time / 30.0) * 90)
			)
		);

		// set the model matrix
		model_matrix.Set(
			ModelMatrixf::RotationZ(FullCircles(time * 0.1))
		);

		gl.CullFace(Face::Front);
		cube_instr.Draw(cube_indices);
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
