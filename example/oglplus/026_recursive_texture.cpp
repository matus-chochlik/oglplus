/**
 *  @example oglplus/026_recursive_texture.cpp
 *  @brief Shows how to render into a texture
 *
 *  @image html 026_recursive_texture.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "example_gl.hpp"
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
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

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array objects for the rendered cube
	VertexArray cube;

	// VBOs for the cube vertex attributes
	Buffer verts, normals, texcoords;

	/// The FBOs and RBOs for offscreen rendering
	Array<Framebuffer> fbos;
	Array<Renderbuffer> rbos;

	// The dynamically rendered textures
	Array<Texture> texs;
	// The currently used texture
	GLuint current_tex;
	size_t tex_side;

	size_t width, height;
public:
	FBTexExample(void)
	 : make_cube()
	 , cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , vs("Vertex")
	 , fs("Fragment")
	 , fbos(2)
	 , rbos(2)
	 , texs(2)
	 , current_tex(0)
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

		fs.Source(
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
		fs.Compile();

		prog.AttachShader(vs);
		prog.AttachShader(fs);
		prog.Link();
		prog.Use();

		cube.Bind();

		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		Uniform<Vec3f>(prog, "LightPos").Set(4.0f, 4.0f, -8.0f);

		for(GLuint i=0; i!=2; ++i)
		{
			Texture::Active(i);
			auto bound_tex = Bind(texs[i], Texture::Target::_2D);
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

			auto bound_fbo = Bind(
				fbos[i],
				Framebuffer::Target::Draw
			);
			auto bound_rbo = Bind(
				rbos[i],
				Renderbuffer::Target::Renderbuffer
			);
			bound_rbo.Storage(
				PixelDataInternalFormat::DepthComponent,
				tex_side,
				tex_side
			);
			bound_fbo.AttachTexture(
				Framebuffer::Attachment::Color,
				texs[i],
				0
			);
			bound_fbo.AttachRenderbuffer(
				Framebuffer::Attachment::Depth,
				rbos[i]
			);
		}

		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.CullFace(Face::Back);
		gl.FrontFace(make_cube.FaceWinding());
		gl.ClearDepth(1.0f);
		gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void Reshape(size_t vp_width, size_t vp_height)
	{
		width = vp_width;
		height = vp_height;
	}

	void Render(double time)
	{
		GLint front = current_tex;
		GLint back = (current_tex+1)%2;
		current_tex = back;

		// render into the texture
		UniformSampler(prog, "TexUnit").Set(front);

		Uniform<Mat4f> camera_matrix(prog, "CameraMatrix");
		Uniform<Mat4f> model_matrix(prog, "ModelMatrix");
		Uniform<Mat4f> projection_matrix(prog, "ProjectionMatrix");


		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.0,
				Degrees(time * 35),
				Degrees(SineWave(time / 20.0) * 60)
			)
		);

		model_matrix.Set(ModelMatrixf::RotationX(FullCircles(time * 0.25)));

		projection_matrix.Set(
			CamMatrixf::Perspective(Degrees(28), 1.0, 1, 100)
		);

		fbos[back].Bind(Framebuffer::Target::Draw);
		gl.Viewport(tex_side, tex_side);
		gl.Clear().ColorBuffer().DepthBuffer();

		cube_instr.Draw(cube_indices);

		// render the textured cube
		Framebuffer::BindDefault(Framebuffer::Target::Draw);
		gl.Viewport(width, height);
		gl.Clear().ColorBuffer().DepthBuffer();

		time += 0.3;
		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.0,
				Degrees(time * 35),
				Degrees(SineWave(time / 20.0) * 60)
			)
		);

		projection_matrix.Set(
			CamMatrixf::Perspective(
				Degrees(54),
				double(width)/height,
				1, 100
			)
		);

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
