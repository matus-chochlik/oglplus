/**
 *  @example oglplus/025_rendered_texture.cpp
 *  @brief Shows how to render into a texture
 *
 *  @image html 025_rendered_texture.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/shapes/torus.hpp>
#include <oglplus/bound/texture.hpp>
#include <oglplus/bound/framebuffer.hpp>
#include <oglplus/bound/renderbuffer.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class FBTexExample : public Example
{
private:
	// The torus builder and rendering instructions
	shapes::Cube make_cube;
	shapes::DrawingInstructions cube_instr;
	shapes::Cube::IndexArray cube_indices;

	// The torus builder and rendering instructions
	shapes::Torus make_torus;
	shapes::DrawingInstructions torus_instr;
	shapes::Torus::IndexArray torus_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Cube and torus fragment shader
	FragmentShader cube_fs, torus_fs;

	// Program
	Program cube_prog, torus_prog;

	// A vertex array objects for the rendered shapes
	VertexArray cube, torus;

	// VBOs for the shape vertex attributes
	Buffer cube_verts, cube_normals, cube_texcoords;
	Buffer torus_verts, torus_normals, torus_texcoords;

	/// The FBO and RBO for offscreen rendering
	Framebuffer fbo;
	Renderbuffer rbo;

	// The dynamically rendered texture
	Texture tex;
	size_t tex_side;

	size_t width, height;
public:
	FBTexExample(void)
	 : make_cube()
	 , cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , make_torus(1.0, 0.5, 72, 48)
	 , torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	 , vs("Vertex")
	 , cube_fs("Cube fragment")
	 , torus_fs("Torus fragment")
	 , tex_side(512)
	 , width(tex_side)
	 , height(tex_side)
	{
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
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLight = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"	vertTexCoord = TexCoord;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"}"
		);
		vs.Compile();

		cube_fs.Source(
			"#version 330\n"
			"uniform sampler2D TexUnit;"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = sqrt(length(vertLight));"
			"	float d = l > 0? dot("
			"		vertNormal, "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float i = 0.6 + max(d, 0.0);"
			"	fragColor = texture(TexUnit, vertTexCoord)*i;"
			"}"
		);
		cube_fs.Compile();

		cube_prog.AttachShader(vs);
		cube_prog.AttachShader(cube_fs);
		cube_prog.Link();
		cube_prog.Use();

		cube.Bind();

		cube_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(cube_prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		cube_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(cube_prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		cube_texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(cube_prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		UniformSampler(cube_prog, "TexUnit").Set(0);
		Uniform<Vec3f>(cube_prog, "LightPos").Set(4.0f, 4.0f, -8.0f);

		torus_fs.Source(
			"#version 330\n"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float d = dot("
			"		vertNormal, "
			"		normalize(vertLight)"
			"	);"
			"	float i = ("
			"		int(vertTexCoord.x*18) % 2+"
			"		int(vertTexCoord.y*14) % 2"
			"	) % 2;"
			"	float c = (0.4 + max(d, 0.0))*(1-i/2);"
			"	fragColor = vec4(c, c, c, 1.0);"
			"}"
		);
		torus_fs.Compile();

		torus_prog.AttachShader(vs);
		torus_prog.AttachShader(torus_fs);
		torus_prog.Link();
		torus_prog.Use();

		torus.Bind();

		torus_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(torus_prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		torus_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(torus_prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		torus_texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(torus_prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		Uniform<Vec3f>(torus_prog, "LightPos").Set(2.0f, 3.0f, 4.0f);

		{
			auto bound_tex = Bind(tex, Texture::Target::_2D);
			bound_tex.Image2D(
				0,
				PixelDataInternalFormat::RGBA,
				tex_side, tex_side,
				0,
				PixelDataFormat::RGBA,
				PixelDataType::UnsignedByte,
				nullptr
			);
			bound_tex.MinFilter(TextureMinFilter::Linear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}

		{
			auto bound_fbo = Bind(
				fbo,
				Framebuffer::Target::Draw
			);
			auto bound_rbo = Bind(
				rbo,
				Renderbuffer::Target::Renderbuffer
			);
			bound_rbo.Storage(
				PixelDataInternalFormat::DepthComponent,
				tex_side,
				tex_side
			);
			bound_fbo.AttachTexture(
				Framebuffer::Attachment::Color,
				tex,
				0
			);
			bound_fbo.AttachRenderbuffer(
				Framebuffer::Attachment::Depth,
				rbo
			);
		}

		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.CullFace(Face::Back);
	}

	void Reshape(size_t vp_width, size_t vp_height)
	{
		width = vp_width;
		height = vp_height;
	}

	void Render(double time)
	{
		// render into the texture
		fbo.Bind(Framebuffer::Target::Draw);
		gl.Viewport(tex_side, tex_side);
		gl.ClearDepth(1.0f);
		gl.ClearColor(0.4f, 0.9f, 0.4f, 1.0f);
		gl.Clear().ColorBuffer().DepthBuffer();
		torus_prog.Use();

		Uniform<Mat4f>(torus_prog, "ProjectionMatrix").Set(
			CamMatrixf::Perspective(Degrees(48), 1.0, 1, 100)
		);

		Uniform<Mat4f>(torus_prog, "CameraMatrix").Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.5,
				Degrees(time * 25),
				Degrees(SineWave(time / 30.0) * 90)
			)
		);

		Uniform<Mat4f>(torus_prog, "ModelMatrix").Set(
			ModelMatrixf::RotationA(
				Vec3f(1.0f, 1.0f, 1.0f),
				FullCircles(time * 0.5)
			)
		);

		torus.Bind();
		gl.FrontFace(make_torus.FaceWinding());
		torus_instr.Draw(torus_indices);

		// render the textured cube
		Framebuffer::BindDefault(Framebuffer::Target::Draw);
		gl.Viewport(width, height);
		gl.ClearDepth(1.0f);
		gl.ClearColor(0.8f, 0.8f, 0.8f, 0.0f);
		gl.Clear().ColorBuffer().DepthBuffer();
		cube_prog.Use();

		Uniform<Mat4f>(cube_prog, "ProjectionMatrix").Set(
			CamMatrixf::Perspective(
				Degrees(54),
				double(width)/height,
				1, 100
			)
		);

		Uniform<Mat4f>(cube_prog, "CameraMatrix").Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.0,
				Degrees(time * 35),
				Degrees(SineWave(time / 20.0) * 60)
			)
		);

		Uniform<Mat4f>(cube_prog, "ModelMatrix").Set(
			ModelMatrixf::RotationX(FullCircles(time * 0.25))
		);

		cube.Bind();
		gl.FrontFace(make_cube.FaceWinding());
		cube_instr.Draw(cube_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params)
{
	return std::unique_ptr<Example>(new FBTexExample);
}

} // namespace oglplus
