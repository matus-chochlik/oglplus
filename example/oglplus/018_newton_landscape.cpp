/**
 *  @example oglplus/018_newton_landscape.cpp
 *  @brief Shows how to use a texture for vertex transformations
 *
 *  @oglplus_screenshot{018_newton_landscape}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/opt/list_init.hpp>
#include <oglplus/shapes/plane.hpp>
#include <oglplus/images/newton.hpp>

#include "example.hpp"

namespace oglplus {

class LandscapeExample : public Example
{
private:
	GLuint grid_side;

	// helper object building plane vertex attributes
	shapes::Plane make_plane;
	// helper object encapsulating plane drawing instructions
	shapes::DrawingInstructions plane_instr;
	// indices pointing to plane primitive elements
	shapes::Plane::IndexArray plane_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Program
	Program prog;

	// Uniforms
	LazyUniform<Vec3f> light_pos;
	LazyUniform<Mat4f> projection_matrix, camera_matrix;

	// A vertex array object for the rendered plane
	VertexArray plane;

	// VBOs for the plane's vertex attributes
	Buffer verts, texcoords;

	// the heightmap texture
	Texture tex;

	// Path of the light
	CubicBezierLoop<Vec3f, double> light_path;
public:
	LandscapeExample(void)
	 : grid_side(128)
	 , make_plane(
		Vec3f(0.0f, 0.0f, 0.0f),
		Vec3f(9.0f, 0.0f, 0.0f),
		Vec3f(0.0f, 0.0f,-9.0f),
		grid_side*3, grid_side*3
	), plane_instr(make_plane.Instructions())
	 , plane_indices(make_plane.Indices())
	 , light_pos(prog, "LightPos")
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , light_path(
		ListOf<Vec3f>
			(Vec3f(-3.0f,  2.0f, -3.5f))
			(Vec3f( 0.0f,  5.0f,  0.5f))
			(Vec3f( 3.0f,  3.0f,  3.0f))
			(Vec3f( 3.0f,  3.0f, -3.0f))
			(Vec3f( 0.0f,  5.0f,  0.5f))
			(Vec3f(-3.2f,  2.0f,  3.0f))
		.Get()
	)
	{
		VertexShader vs;
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"uniform sampler2D TexUnit;"
			"in vec4 Position;"
			"in vec2 TexCoord;"
			"out vec3 vertLight;"
			"out vec3 vertNormal;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	gl_Position = Position;"
			"	float o = 0.0;"
			"	float s[9];"
			"	int k=0;"
			"	for(int y=-1; y!=2; ++y)"
			"	for(int x=-1; x!=2; ++x)"
			"	{"
			"		s[k] = sqrt(texture("
			"			TexUnit, "
			"			TexCoord*3.0+"
			"			vec2(x, y)/128.0"
			"		).r);"
			"		o += s[k++];"
			"	}"
			"	gl_Position.y += o*0.5;"
			"	vec3 c = vec3( 0.0, s[4], 0.0);"
			"	float d = 1.0/32.0;"
			"	vertNormal = normalize("
			"		cross("
			"			vec3( 0.0, s[1],  -d) - c,"
			"			vec3(  -d, s[3], 0.0) - c"
			"		)+"
			"		cross("
			"			vec3(   d, s[5], 0.0) - c,"
			"			vec3( 0.0, s[1],  -d) - c"
			"		)+"
			"		cross("
			"			vec3( 0.0, s[7],   d) - c,"
			"			vec3(   d, s[5], 0.0) - c"
			"		)+"
			"		cross("
			"			vec3(  -d, s[3], 0.0) - c,"
			"			vec3( 0.0, s[7],   d) - c"
			"		)"
			"	);"
			"	vertLight = LightPos - gl_Position.xyz;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"}"
		);
		vs.Compile();

		FragmentShader fs;
		fs.Source(
			"#version 330\n"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(vertLight);"
			"	float d = l > 0? dot("
			"		normalize(vertNormal), "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float i = 0.1 + 1.2*max(d, 0.0) + 4.2*pow(d, 2.0);"
			"	fragColor = vec4(i*0.7, i*0.7, i*0.3, 1.0);"
			"}"
		);
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the plane
		plane.Bind();

		// bind the VBO for the plane vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_plane.Positions(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the plane texture coordinates
		texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_plane.TexCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the texture
		Texture::Target tex_tgt = Texture::Target::_2D;
		tex.Bind(tex_tgt);
		{
			auto image = images::NewtonFractal(
				grid_side, grid_side,
				Vec3f(0.0f, 0.1f, 0.2f),
				Vec3f(1.0f, 0.8f, 0.9f),
				Vec2f(-1.0f, -1.0f),
				Vec2f( 1.0f,  1.0f),
				images::NewtonFractal::X3Minus1(),
				images::NewtonFractal::DefaultMixer()
			);
			Texture::Image2D(tex_tgt, image);
			Texture::MinFilter(tex_tgt, TextureMinFilter::Linear);
			Texture::MagFilter(tex_tgt, TextureMagFilter::Linear);
			Texture::WrapS(tex_tgt, TextureWrap::MirroredRepeat);
			Texture::WrapT(tex_tgt, TextureWrap::MirroredRepeat);
		}
		//
		UniformSampler(prog, "TexUnit").Set(0);

		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_plane.FaceWinding());
		gl.CullFace(Face::Back);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
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
				Vec3f(0.0f, 0.5f, 0.0f),
				4.5,
				Degrees(time * 35),
				Degrees(55 - SineWave(time / 20.0) * 30)
			)
		);
		light_pos.Set(light_path.Position(time / 10.0));

		plane.Bind();
		plane_instr.Draw(plane_indices);
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
	return std::unique_ptr<Example>(new LandscapeExample);
}

} // namespace oglplus
