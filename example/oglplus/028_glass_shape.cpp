/**
 *  @example oglplus/028_glass_shape.cpp
 *  @brief Show a simple simulation of refractive transparent object
 *
 *  @image html 028_glass_shape.png
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

#include <cmath>

#include "example.hpp"

namespace oglplus {

class GlassExample : public Example
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

	// Texture user for the simulation of refraction
	Texture refract_tex;

	size_t width, height, tex_side;
public:
	GlassExample(void)
	 : make_plane(Vec3f(2.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, -2.0f))
	 , plane_instr(make_plane.Instructions())
	 , plane_indices(make_plane.Indices())
	 , make_shape()
	 , shape_instr(make_shape.Instructions())
	 , shape_indices(make_shape.Indices())
	 , plane_vs(ObjectDesc("Plane vertex"))
	 , shape_vs(ObjectDesc("Shape vertex"))
	 , plane_fs(ObjectDesc("Plane fragment"))
	 , shape_fs(ObjectDesc("Shape fragment"))
	 , width(512)
	 , height(512)
	 , tex_side(512)
	{
		plane_vs.Source(
			"#version 330\n"
			"uniform vec3 LightPosition;"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"in vec2 TexCoord;"
			"out vec3 vertLightDir;"
			"out vec2 vertTexCoord;"
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
			"	vertTexCoord = TexCoord;"
			"}"
		);
		plane_vs.Compile();

		plane_fs.Source(
			"#version 330\n"
			"uniform vec3 Normal;"
			"in vec3 vertLightDir;"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float checker = ("
			"		int(vertTexCoord.x*18) % 2+"
			"		int(vertTexCoord.y*18) % 2"
			"	) % 2;"
			"	vec3 color = mix("
			"		vec3(0.2, 0.4, 0.9),"
			"		vec3(0.2, 0.2, 0.7),"
			"		checker"
			"	);"
			"	float d = dot("
			"		Normal, "
			"		vertLightDir"
			"	);"
			"	float intensity = 0.5 + pow(1.4*d, 2.0);"
			"	fragColor = vec4(color*intensity, 1.0);"
			"}"
		);
		plane_fs.Compile();

		plane_prog.AttachShader(plane_vs);
		plane_prog.AttachShader(plane_fs);
		plane_prog.Link();
		plane_prog.Use();

		Vec3f lightPos(3.0f, 3.0f, 3.0f);
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

		plane_texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_plane.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(plane_prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		shape_vs.Source(
			"#version 330\n"
			"uniform vec3 LightPosition;"
			"uniform mat4 ProjectionMatrix, ModelMatrix, CameraMatrix;"
			"uniform vec4 ClipPlane;"
			"uniform float ClipDirection;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertNormal;"
			"out vec3 vertLightDir;"
			"out vec3 vertLightRefl;"
			"out vec3 vertViewDir;"
			"out vec2 vertTexCoord;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ModelMatrix *"
			"		Position;"
			"	gl_ClipDistance[0] = "
			"		ClipDirection* "
			"		dot(ClipPlane, gl_Position);"
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
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"	vec3 TexOffs = ("
			"		CameraMatrix *"
			"		vec4(vertNormal, 0.0)"
			"	).xyz * 0.05;"
			"	vertTexCoord = "
			"		vec2(0.5, 0.5) +"
			"		(gl_Position.xy/gl_Position.w)*0.5 +"
			"		(TexOffs.z<0.0 ? TexOffs.xy : -TexOffs.xy);"
			"}"
		);
		shape_vs.Compile();

		shape_fs.Source(
			"#version 330\n"
			"uniform sampler2D RefractTex;"
			"in vec3 vertNormal;"
			"in vec3 vertLightDir;"
			"in vec3 vertLightRefl;"
			"in vec3 vertViewDir;"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"

			"float adj_lt(float i)"
			"{"
			"	return i > 0.0 ? i : -0.7*i;"
			"}"

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
			"	vec3 tex = texture(RefractTex, vertTexCoord).rgb;"
			"	fragColor = vec4("
			"		tex * 0.5 + "
			"		(lt + tex) * 1.5 * adj_lt(d) + "
			"		lt * pow(adj_lt(s), 64), "
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
		Texture::Active(0);
		UniformSampler(shape_prog, "RefractTex").Set(0);
		{
			auto bound_tex = Bind(refract_tex, Texture::Target::_2D);
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
			bound_tex.WrapS(TextureWrap::MirroredRepeat);
			bound_tex.WrapT(TextureWrap::MirroredRepeat);
		}
		//
		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(size_t vp_width, size_t vp_height)
	{
		width = vp_width;
		height = vp_height;
		tex_side = width < height ? width : height;

		gl.Viewport(width, height);

		Mat4f projection = CamMatrixf::PerspectiveX(
			Degrees(48),
			double(width)/height,
			1, 100
		);
		SetProgramUniform(plane_prog, "ProjectionMatrix", projection);
		SetProgramUniform(shape_prog, "ProjectionMatrix", projection);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			3.5,
			FullCircles(time / 10.0),
			Degrees(45.0 + SineWave(time / 7.0)*30.0)
		);

		// Render the plane
		plane_prog.Use();
		Uniform<Mat4f>(plane_prog, "CameraMatrix").Set(camera);

		Uniform<Mat4f>(plane_prog, "ModelMatrix").Set(
			ModelMatrixf::Translation(0.0f, -1.1f, 0.0f)
		);

		plane.Bind();
		plane_instr.Draw(plane_indices);


		// Render the shape
		shape_prog.Use();

		auto clip_plane = Planef::FromNormal(Vec3f(Data(Row<2>(camera)), 3));

		Uniform<Vec4f>(shape_prog, "ClipPlane").Set(clip_plane.Equation());

		Uniform<Mat4f>(shape_prog, "CameraMatrix").Set(camera);

		Uniform<Mat4f>(shape_prog, "ModelMatrix").Set(
			ModelMatrixf::RotationX(FullCircles(time / 12.0))
		);

		shape.Bind();

		gl.Enable(Capability::CullFace);
		gl.Enable(Functionality::ClipDistance, 0);

		gl.FrontFace(make_shape.FaceWinding());

		GLfloat clip_dirs[2] = {-1.0f, 1.0f};
		Face facing_dirs[2] = {Face::Front, Face::Back};

		Uniform<GLfloat> clip_direction(shape_prog, "ClipDirection");
		for(int c=0; c!=2; ++c)
		{
			clip_direction.Set(clip_dirs[c]);
			for(int f=0; f!=2; ++f)
			{
				Texture::CopyImage2D(
					Texture::Target::_2D,
					0,
					PixelDataInternalFormat::RGB,
					tex_side == width ? 0 : (width - tex_side) / 2,
					tex_side == height? 0 : (height- tex_side) / 2,
					tex_side, tex_side,
					0
				);
				gl.CullFace(facing_dirs[f]);
				shape_instr.Draw(shape_indices);
			}
		}

		gl.Disable(Functionality::ClipDistance, 0);
		gl.Disable(Capability::CullFace);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new GlassExample);
}

} // namespace oglplus
