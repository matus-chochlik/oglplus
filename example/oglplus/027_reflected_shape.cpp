/**
 *  @example oglplus/027_reflected_shape.cpp
 *  @brief Show a how to do texture-based blurry reflection
 *
 *  @image html 027_reflected_shape.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/plane.hpp>
#include <oglplus/shapes/spiral_sphere.hpp>

#include <oglplus/bound/texture.hpp>
#include <oglplus/bound/framebuffer.hpp>
#include <oglplus/bound/renderbuffer.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class ReflectionExample : public Example
{
private:
	// helper object building and storing plane drawing instructions
	shapes::Plane make_plane;
	shapes::DrawingInstructions plane_instr;
	shapes::Plane::IndexArray plane_indices;


	// helper object building and storing shape drawing instructions
	typedef shapes::SpiralSphere Shape;
	Shape make_shape;
	shapes::DrawingInstructions shape_instr;
	Shape::IndexArray shape_indices;

	Context gl;

	VertexShader plane_vs, shape_vs;

	FragmentShader plane_fs, shape_fs;

	Program plane_prog, shape_prog;

	VertexArray plane, shape;

	Buffer plane_verts, plane_texcoords;
	Buffer shape_verts, shape_normals;

	// Texture user for the simulation of reflection
	Texture reflect_tex;

	Framebuffer fbo;
	Renderbuffer rbo;

	size_t width, height, tex_side;
public:
	ReflectionExample(void)
	 : make_plane(
		Vec3f(),
		Vec3f(3.0f, 0.0f, 0.0f),
		Vec3f(0.0f, 0.0f, -3.0f),
		15,
		15
	), plane_instr(make_plane.Instructions())
	 , plane_indices(make_plane.Indices())
	 , make_shape()
	 , shape_instr(make_shape.Instructions())
	 , shape_indices(make_shape.Indices())
	 , plane_vs("Plane vertex")
	 , shape_vs("Shape vertex")
	 , plane_fs("Plane fragment")
	 , shape_fs("Shape fragment")
	 , width(800)
	 , height(600)
	 , tex_side(width > height ? height : width)
	{
		plane_vs.Source(
			"#version 330\n"
			"uniform vec3 LightPosition;"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"out vec3 vertLightDir;"
			"out vec4 vertTexCoord;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ModelMatrix* "
			"		Position;"
			"	vertLightDir = normalize("
			"		LightPosition - gl_Position.xyz"
			"	);"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"	vertTexCoord = gl_Position;"
			"}"
		);
		plane_vs.Compile();

		plane_fs.Source(
			"#version 330\n"
			"uniform sampler2D ReflectTex;"
			"uniform vec3 Normal;"
			"uniform float Aspect;"
			"in vec3 vertLightDir;"
			"in vec4 vertTexCoord;"
			"out vec4 fragColor;"
			"const int n = 5;"
			"const int ns = (n*n);"
			"const float blur = 0.15/n;"
			"void main(void)"
			"{"
			"	float d = dot("
			"		Normal, "
			"		vertLightDir"
			"	);"
			"	float intensity = 0.5 + pow(1.4*d, 2.0);"
			"	vec3 color = vec3(0.0, 0.0, 0.0);"
			"	int n = 2;"
			"	for(int y=-n; y!=(n+1); ++y)"
			"	for(int x=-n; x!=(n+1); ++x)"
			"	{"
			"		vec2 coord = vertTexCoord.xy;"
			"		coord += vec2(blur*x, blur*y);"
			"		coord /= vertTexCoord.w;"
			"		coord *= 0.5;"
			"		coord += vec2(Aspect*0.5, 0.5);"
			"		color += texture(ReflectTex, coord).rgb/ns;"
			"	}"
			"	fragColor = vec4(color*intensity, 1.0);"
			"}"
		);
		plane_fs.Compile();

		plane_prog.AttachShader(plane_vs);
		plane_prog.AttachShader(plane_fs);
		plane_prog.Link();
		plane_prog.Use();

		Vec3f lightPos(3.0f, 0.5f, 2.0f);
		Uniform<Vec3f>(plane_prog, "LightPosition").Set(lightPos);
		Uniform<Vec3f>(plane_prog, "Normal").Set(make_plane.Normal());

		plane.Bind();

		plane_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_plane.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(plane_prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
		//
		Texture::Active(0);
		UniformSampler(plane_prog, "ReflectTex").Set(0);
		{
			auto bound_tex = Bind(reflect_tex, Texture::Target::_2D);
			bound_tex.Image2D(
				0,
				PixelDataInternalFormat::RGB,
				tex_side, tex_side,
				0,
				PixelDataFormat::RGB,
				PixelDataType::UnsignedByte,
				nullptr
			);
			bound_tex.MinFilter(TextureMinFilter::Linear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToEdge);
			bound_tex.WrapT(TextureWrap::ClampToEdge);
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
				reflect_tex,
				0
			);
			bound_fbo.AttachRenderbuffer(
				Framebuffer::Attachment::Depth,
				rbo
			);
		}

		shape_vs.Source(
			"#version 330\n"
			"uniform vec3 LightPosition;"
			"uniform mat4 ProjectionMatrix, ModelMatrix, CameraMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertNormal;"
			"out vec3 vertLightDir;"
			"out vec3 vertLightRefl;"
			"out vec3 vertViewDir;"
			"out vec3 vertColor;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ModelMatrix *"
			"		Position;"
			"	vertLightDir = LightPosition - gl_Position.xyz;"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLightRefl = reflect("
			"		-normalize(vertLightDir),"
			"		normalize(vertNormal)"
			"	);"
			"	vertViewDir = ("
			"		vec4(0.0, 0.0, 1.0, 1.0)*"
			"		CameraMatrix"
			"	).xyz;"
			"	vertColor = vec3(1, 1, 1) - vertNormal;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"}"
		);
		shape_vs.Compile();

		shape_fs.Source(
			"#version 330\n"
			"uniform sampler2D ReflectTex;"
			"in vec3 vertNormal;"
			"in vec3 vertLightDir;"
			"in vec3 vertLightRefl;"
			"in vec3 vertViewDir;"
			"in vec3 vertColor;"
			"out vec4 fragColor;"

			"void main(void)"
			"{"
			"	float l = length(vertLightDir);"
			"	float d = dot("
			"		normalize(vertNormal), "
			"		normalize(vertLightDir)"
			"	) / l;"
			"	float s = dot("
			"		normalize(vertLightRefl),"
			"		normalize(vertViewDir)"
			"	);"
			"	vec3 lt = vec3(1.0, 1.0, 1.0);"
			"	fragColor = vec4("
			"		vertColor * 0.4 + "
			"		(lt + vertColor)*pow(max(2.5*d, 0.0), 3) + "
			"		lt * pow(max(s, 0.0), 64), "
			"		1.0"
			"	);"
			"}"
		);
		shape_fs.Compile();

		shape_prog.AttachShader(shape_vs);
		shape_prog.AttachShader(shape_fs);
		shape_prog.Link();
		shape_prog.Use();

		Uniform<Vec3f>(shape_prog, "LightPosition").Set(lightPos);

		shape.Bind();

		shape_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(shape_prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		shape_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(shape_prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
		//
		gl.ClearColor(0.5f, 0.5f, 0.4f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(size_t vp_width, size_t vp_height)
	{
		width = vp_width;
		height = vp_height;
		tex_side = width > height ? height : width;

		auto bound_tex = Bind(reflect_tex, Texture::Target::_2D);
		bound_tex.Image2D(
			0,
			PixelDataInternalFormat::RGB,
			tex_side, tex_side,
			0,
			PixelDataFormat::RGB,
			PixelDataType::UnsignedByte,
			nullptr
		);
		auto bound_rbo = Bind(rbo, Renderbuffer::Target::Renderbuffer);
		bound_rbo.Storage(
			PixelDataInternalFormat::DepthComponent,
			tex_side, tex_side
		);
	}

	void Render(double time)
	{
		static const ModelMatrixf reflection(
			 1.0, 0.0, 0.0, 0.0,
			 0.0,-1.0, 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			 0.0, 0.0, 0.0, 1.0
		);

		float aspect = float(width)/height;

		auto projection = CamMatrixf::Perspective(
			Degrees(48), aspect, 1, 100
		);

		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			3.5,
			FullCircles(time / 10.0),
			Degrees(45.0 - SineWave(time / 7.0)*35.0)
		);

		shape_prog.Use();
		shape.Bind();

		Uniform<Mat4f>(shape_prog, "ModelMatrix").Set(
			ModelMatrixf::Translation(0.0f, 0.6f, 0.0f) *
			ModelMatrixf::RotationX(FullCircles(time / 12.0))
		);
		Uniform<Mat4f>(shape_prog, "ProjectionMatrix").Set(projection);

		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_shape.FaceWinding());

		// render into the off-screen framebuffer
		fbo.Bind(Framebuffer::Target::Draw);
		gl.Viewport(
			(width - tex_side) / 2,
			(height - tex_side) / 2,
			tex_side, tex_side
		);
		gl.Clear().ColorBuffer().DepthBuffer();

		Uniform<Mat4f>(shape_prog, "CameraMatrix").Set(
			camera *
			ModelMatrixf::Translation(0.0f, -1.0f, 0.0f) *
			reflection
		);

		gl.CullFace(Face::Front);
		shape_instr.Draw(shape_indices);

		Framebuffer::BindDefault(Framebuffer::Target::Draw);
		gl.Viewport(width, height);
		gl.Clear().ColorBuffer().DepthBuffer();

		Uniform<Mat4f>(shape_prog, "CameraMatrix").Set(camera);

		gl.CullFace(Face::Back);
		shape_instr.Draw(shape_indices);

		gl.Disable(Capability::CullFace);

		// Render the plane
		plane_prog.Use();
		plane.Bind();

		Uniform<Mat4f>(plane_prog, "ProjectionMatrix").Set(projection);
		Uniform<Mat4f>(plane_prog, "CameraMatrix").Set(camera);
		Uniform<Mat4f>(plane_prog, "ModelMatrix").Set(
			ModelMatrixf::Translation(0.0f, -0.5f, 0.0f)
		);
		Uniform<GLfloat>(plane_prog, "Aspect").Set(aspect);

		plane_instr.Draw(plane_indices);

	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new ReflectionExample);
}

} // namespace oglplus
