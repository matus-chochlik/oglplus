/**
 *  @example oglplus/034_billiard_balls.cpp
 *  @brief Shows rendering into a cube map and simple raytracing
 *  @note Still work-in-progress
 *
 *  @image html 034_billiard_balls.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <oglplus/shapes/plane.hpp>
#include <oglplus/shapes/sphere.hpp>

#include <oglplus/images/brushed_metal.hpp>
#include <oglplus/images/load.hpp>

#include <oglplus/bound/texture.hpp>
#include <oglplus/bound/framebuffer.hpp>
#include <oglplus/bound/renderbuffer.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CommonVertShader
 : public VertexShader
{
public:
	CommonVertShader(void)
	 : VertexShader(
		"Common vertex shader",
		"#version 330\n"
		"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
		"uniform mat3 TextureMatrix;"
		"uniform vec3 CameraPosition, LightPosition;"
		"in vec4 Position;"
		"in vec3 Normal;"
		"in vec3 Tangent;"
		"in vec2 TexCoord;"
		"out vec3 vertNormal;"
		"out vec3 vertTangent;"
		"out vec3 vertBinormal;"
		"out vec3 vertLightDir;"
		"out vec3 vertViewDir;"
		"out vec2 vertTexCoord;"
		"out vec2 vertSTCoord;"
		"void main(void)"
		"{"
		"	gl_Position = ModelMatrix * Position;"
		"	vertLightDir = LightPosition - gl_Position.xyz;"
		"	vertViewDir = CameraPosition - gl_Position.xyz;"
		"	vertNormal =  (ModelMatrix * vec4(Normal,  0.0)).xyz;"
		"	vertTangent = (ModelMatrix * vec4(Tangent, 0.0)).xyz;"
		"	vertBinormal = cross(vertNormal, vertTangent);"
		"	vertTexCoord = (TextureMatrix * vec3(TexCoord,1.0)).xy;"
		"	vertSTCoord = TexCoord;"
		"	gl_Position = ProjectionMatrix*CameraMatrix * gl_Position;"
		"}"
	)
	{ }
};

class TransformProgram
 : public HardwiredProgram<CommonVertShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Mat4f> projection_matrix, camera_matrix, model_matrix;
	ProgramUniform<Mat3f> texture_matrix;
	ProgramUniform<Vec3f> camera_position, light_position;

	TransformProgram(void)
	 : HardwiredProgram<CommonVertShader>("Transform", true)
	 , projection_matrix(prog(), "ProjectionMatrix")
	 , camera_matrix(prog(), "CameraMatrix")
	 , model_matrix(prog(), "ModelMatrix")
	 , texture_matrix(prog(), "TextureMatrix")
	 , camera_position(prog(), "CameraPosition")
	 , light_position(prog(), "LightPosition")
	{ }
};

class ClothFragmentShader
 : public FragmentShader
{
public:
	ClothFragmentShader(void)
	 : FragmentShader(
		"Cloth fragment shader",
		"#version 330\n"
		"uniform vec3 Color1, Color2;"
		"uniform sampler2D ClothTex, LightMap;"
		"in vec3 vertNormal;"
		"in vec3 vertTangent;"
		"in vec3 vertBinormal;"
		"in vec3 vertLightDir;"
		"in vec3 vertViewDir;"
		"in vec2 vertTexCoord;"
		"in vec2 vertSTCoord;"
		"out vec4 fragColor;"

		"void main(void)"
		"{"
		"	vec3 LightColor = texture(LightMap, vertSTCoord).rgb;"
		"	vec3 Sample = 0.5*("
		"		0.5*texture(ClothTex, vertTexCoord*0.5).rgb+"
		"		1.0*texture(ClothTex, vertTexCoord*1.0).rgb+"
		"		0.5*texture(ClothTex, vertTexCoord*2.0).rgb "
		"	);"

		"	vec3 Normal = normalize("
		"		2.0*vertNormal + "
		"		(Sample.r - 0.5)*vertTangent + "
		"		(Sample.g - 0.5)*vertBinormal"
		"	);"
		"	vec3 LightDir = normalize(vertLightDir);"
		"	vec3 LightRefl = reflect(-LightDir, Normal);"

		"	float Amount = pow(Sample.b, 2.0);"

		"	float Specular = pow(clamp(dot("
		"		LightRefl,"
		"		normalize(vertViewDir)"
		"	)+0.1, 0.0, 1.0)*0.9, 16.0+16.0*Amount)*(0.2+2.0*Amount);"

		"	float Diffuse = clamp(2.0*(dot("
		"		Normal, "
		"		LightDir"
		"	)-0.5), 0.0, 1.0);"

		"	float Ambient = 0.2;"

		"	vec3 Color = mix(Color1, Color2, Amount);"

		"	fragColor = vec4("
		"		Color * Ambient +"
		"		LightColor * Color * Diffuse + "
		"		LightColor * Specular, "
		"		1.0"
		"	);"
		"}"
	)
	{ }
};

class ClothProgram
 : public HardwiredProgram<ClothFragmentShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Vec3f> color_1, color_2;
	ProgramUniformSampler cloth_tex;
	ProgramUniformSampler light_map;

	ClothProgram(void)
	 : HardwiredProgram<ClothFragmentShader>("Cloth", true)
	 , color_1(prog(), "Color1")
	 , color_2(prog(), "Color2")
	 , cloth_tex(prog(), "ClothTex")
	 , light_map(prog(), "LightMap")
	{ }
};

class BallFragmentShader
 : public FragmentShader
{
public:
	BallFragmentShader(void)
	 : FragmentShader(
		"Ball fragment shader",
		"#version 330\n"
		"uniform vec3 Color1, Color2;"
		"uniform sampler2DArray NumberTex;"
		"uniform int NumberIdx;"
		"in vec3 vertNormal;"
		"in vec3 vertTangent;"
		"in vec3 vertBinormal;"
		"in vec3 vertLightDir;"
		"in vec3 vertViewDir;"
		"in vec2 vertTexCoord;"
		"in vec2 vertSTCoord;"
		"out vec4 fragColor;"

		"void main(void)"
		"{"
		"	vec3 TexCoord = vec3(vertTexCoord, float(NumberIdx));"
		"	vec4 Sample = texture(NumberTex, TexCoord);"
		"	vec3 LightColor = vec3(1.0, 1.0, 1.0);"

		"	vec3 Normal = normalize(vertNormal);"
		"	vec3 LightDir = normalize(vertLightDir);"
		"	vec3 LightRefl = reflect(-LightDir, Normal);"

		"	float Specular = pow(max(dot("
		"		LightRefl,"
		"		normalize(vertViewDir)"
		"	)+0.1, 0.0), 64.0)*(0.5 - Sample.a*(1.0-Sample.r)*0.4);"

		"	float Diffuse = max(dot("
		"		Normal, "
		"		LightDir"
		"	)+0.1, 0.0);"

		"	float Ambient = 0.2;"

		"	float ColorSwitch = ("
		"		vertSTCoord.t < 0.25 ||"
		"		vertSTCoord.t > 0.75"
		"	)? 0.0 : 1.0;"
		"	vec3 Color = mix("
		"		mix(Color1, Color2, ColorSwitch),"
		"		vec3(1.0, 1.0, 0.9)*Sample.r,"
		"		Sample.a"
		"	);"

		"	fragColor = vec4("
		"		Color * Ambient +"
		"		LightColor * Color * Diffuse + "
		"		LightColor * Specular, "
		"		1.0"
		"	);"
		"}"
	)
	{ }
};

class BallProgram
 : public HardwiredProgram<BallFragmentShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Vec3f> color_1, color_2;
	ProgramUniformSampler number_tex;
	ProgramUniform<GLint> number_idx;

	BallProgram(void)
	 : HardwiredProgram<BallFragmentShader>("Ball", true)
	 , color_1(prog(), "Color1")
	 , color_2(prog(), "Color2")
	 , number_tex(prog(), "NumberTex")
	 , number_idx(prog(), "NumberIdx")
	{ }
};


class LightmapVertShader
 : public VertexShader
{
public:
	LightmapVertShader(void)
	 : VertexShader(
		"Lightmap vertex shader",
		"#version 330\n"
		"uniform mat4 TransformMatrix;"
		"in vec4 Position;"
		"out vec3 vertPosition;"
		"void main(void)"
		"{"
		"	vertPosition = Position.xyz;"
		"	gl_Position = TransformMatrix * Position;"
		"}"
	)
	{ }
};

class LightmapFragShader
 : public FragmentShader
{
public:
	LightmapFragShader(void)
	 : FragmentShader(
		"Lightmap fragment shader",
		"#version 330\n"
		"uniform vec3 LightPosition;"
		"uniform vec3 BallPositions[15];"
		"in vec3 vertPosition;"
		"out vec4 fragColor;"
		"void main(void)"
		"{"
		"	float d_max = 0.0;"
		"	vec3 L = LightPosition;"
		"	vec3 R = normalize(vertPosition - LightPosition);"
		"	for(int i=0; i!=15; ++i)"
		"	{"
		"		vec3 S = BallPositions[i];"
		"		float a = dot(R, R);"
		"		float b = 2*dot(L-S, R);"
		"		float c = dot(L-S, L-S)-1.0;"
		"		float d = b*b - 4*a*c;"
		"		if(d_max < d) d_max = d;"
		"	}"
		"	float lt = exp(-d_max*0.8);"
		"	fragColor = vec4(lt, lt, lt, 1.0);"
		"}"
	)
	{ }

};

class LightmapProgram
 : public HardwiredProgram<LightmapVertShader, LightmapFragShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Mat4f> transform_matrix;
	ProgramUniform<Vec3f> light_position;
	ProgramUniform<Vec3f> ball_positions;

	LightmapProgram(void)
	 : HardwiredProgram<LightmapVertShader, LightmapFragShader>("Lightmap")
	 , transform_matrix(prog(), "TransformMatrix")
	 , light_position(prog(), "LightPosition")
	 , ball_positions(prog(), "BallPositions")
	{ }
};

template <typename ShapeBuilder>
class Shape
{
protected:
	// helper object building shape vertex attributes
	ShapeBuilder make_shape;
	// helper object encapsulating shape drawing instructions
	shapes::DrawingInstructions shape_instr;
	// indices pointing to shape primitive elements
	typename ShapeBuilder::IndexArray shape_indices;

	Context gl;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// number of vertex attributes
	const size_t nva;

	// VBOs for the shape's vertex attributes
	Array<Buffer> vbos;

	// number of values per vertex for individual VAs
	std::vector<GLuint> npvs;

public:
	Shape(const Program& prog, const ShapeBuilder& builder)
	 : make_shape(builder)
	 , shape_instr(make_shape.Instructions())
	 , shape_indices(make_shape.Indices())
	 , nva(4)
	 , vbos(nva)
	 , npvs(nva)
	{
		// bind the VAO for the shape
		vao.Bind();

		typename ShapeBuilder::VertexAttribs vert_attr_info;
		const GLchar* vert_attr_name[] = {
			"Position",
			"Normal",
			"Tangent",
			"TexCoord"
		};
		for(int va=0; va!=nva; ++va)
		{
			const GLchar* name = vert_attr_name[va];
			std::vector<GLfloat> data;
			auto getter = vert_attr_info.VertexAttribGetter(data, name);
			if(getter != nullptr)
			try
			{
				// bind the VBO for the vertex attribute
				vbos[va].Bind(Buffer::Target::Array);
				npvs[va] = getter(make_shape, data);
				// upload the data
				Buffer::Data(Buffer::Target::Array, data);
				// setup the vertex attribs array
				VertexAttribArray attr(prog, name);
				attr.Setup(npvs[va], DataType::Float);
				attr.Enable();
			}
			catch(Error& error)
			{ }
		}
	}

	void Draw(void)
	{
		vao.Bind();
		gl.FrontFace(make_shape.FaceWinding());
		shape_instr.Draw(shape_indices);
	}
};

class BilliardExample : public Example
{
private:

	// wrapper around the current OpenGL context
	Context gl;

	TransformProgram transf_prog;
	ClothProgram cloth_prog;
	BallProgram ball_prog;

	ProgramPipeline cloth_pp, ball_pp;

	Vec3f plane_u, plane_v;
	Shape<shapes::Plane> plane;
	Shape<shapes::Sphere> sphere;

	std::vector<Vec3f> ball_colors;
	std::vector<Vec3f> ball_offsets;
	std::vector<Vec3f> ball_rotations;

	// The texture used to render the cloth
	Texture cloth_texture;

	// An array texture storing the ball number decals
	Texture numbers_texture;

	// The table light map and the associated framebuffer
	Texture table_light_map;
public:
	BilliardExample(void)
	 : transf_prog()
	 , cloth_prog()
	 , plane_u(16, 0, 0)
	 , plane_v(0, 0,-16)
	 , plane(transf_prog, shapes::Plane(plane_u, plane_v))
	 , sphere(transf_prog, shapes::Sphere(1.0, 72, 48))
	 , ball_colors(
		{
			{0.8f, 0.5f, 0.2f},
			{0.2f, 0.2f, 0.5f},
			{0.6f, 0.2f, 0.4f},
			{0.1f, 0.1f, 0.3f},
			{0.0f, 0.0f, 0.0f},
			{0.3f, 0.1f, 0.2f},
			{0.2f, 0.5f, 0.2f},
			{0.6f, 0.3f, 0.2f}
		}
	), ball_offsets(
		{
			{ 3.0f, 1.0f, 6.5f},
			{ 5.0f, 1.0f, 5.0f},
			{ 3.0f, 1.0f,-1.0f},
			{-0.1f, 1.0f,-1.1f},
			{-3.0f, 1.0f, 3.0f},
			{-2.8f, 1.0f, 7.0f},
			{-1.1f, 1.0f, 9.0f},
			{ 3.0f, 1.0f, 2.0f},
			{-7.0f, 1.0f, 3.0f},
			{-9.5f, 1.0f, 4.5f},
			{ 1.0f, 1.0f, 5.2f},
			{-8.0f, 1.0f, 8.0f},
			{-5.0f, 1.0f, 1.0f},
			{ 2.0f, 1.0f, 9.0f},
			{ 8.0f, 1.0f, 7.5f}
		}
	), ball_rotations(
		{
			{ 0.3f,-0.2f,-0.1f},
			{ 0.2f, 0.3f, 0.4f},
			{-0.4f,-0.4f, 0.2f},
			{ 0.2f, 0.3f,-0.4f},
			{-0.7f,-0.2f, 0.6f},
			{ 0.3f, 0.3f, 0.2f},
			{ 0.5f, 0.2f, 0.3f},
			{-0.4f, 0.4f,-0.4f},
			{ 0.3f,-0.3f, 0.1f},
			{ 0.1f,-0.2f,-0.2f},
			{-0.2f,-0.3f,-0.0f},
			{-0.3f, 0.5f, 0.3f},
			{-0.4f, 0.1f, 0.1f},
			{ 0.3f, 0.3f,-0.2f},
			{-0.2f,-0.2f, 0.4f}
		}
	)
	{

		Program::UseNone();

		cloth_pp.Bind();
		cloth_pp.UseStages(transf_prog).Vertex();
		cloth_pp.UseStages(cloth_prog).Fragment();

		ball_pp.Bind();
		ball_pp.UseStages(transf_prog).Vertex();
		ball_pp.UseStages(ball_prog).Fragment();

		const Vec3f light_position(0.0, 20.0, -2.0);

		cloth_prog.color_1.Set(Vec3f(0.1, 0.3, 0.1));
		cloth_prog.color_2.Set(Vec3f(0.3, 0.4, 0.3));

		Texture::Active(0);
		cloth_prog.light_map.Set(0);
		{
			size_t light_map_side = 512;
			auto bound_tex = Bind(table_light_map, Texture::Target::_2D);
			bound_tex.Image2D(
				0,
				PixelDataInternalFormat::RGB,
				light_map_side,
				light_map_side,
				0,
				PixelDataFormat::RGB,
				PixelDataType::UnsignedByte,
				nullptr
			);
			bound_tex.MinFilter(TextureMinFilter::Linear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToEdge);
			bound_tex.WrapT(TextureWrap::ClampToEdge);

			PrerenderLightmap(light_position, light_map_side);
		}
		transf_prog.light_position.Set(light_position);

		Texture::Active(1);
		cloth_prog.cloth_tex.Set(1);
		{
			auto bound_tex = Bind(cloth_texture, Texture::Target::_2D);
			bound_tex.Image2D(
				images::BrushedMetalUByte(
					512, 512,
					10240,
					-16, +16,
					8, 32
				)
			);
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}

		Texture::Active(2);
		ball_prog.number_tex.Set(2);
		{
			auto bound_tex = Bind(numbers_texture, Texture::Target::_2DArray);
			bound_tex.BorderColor(Vec4f(0,0,0,0));
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToBorder);
			bound_tex.WrapT(TextureWrap::ClampToBorder);
			bound_tex.WrapR(TextureWrap::ClampToBorder);
			const char* tex_names[15] = {
				"pool_ball_1",
				"pool_ball_2",
				"pool_ball_3",
				"pool_ball_4",
				"pool_ball_5",
				"pool_ball_6",
				"pool_ball_7",
				"pool_ball_8",
				"pool_ball_9",
				"pool_ball10",
				"pool_ball11",
				"pool_ball12",
				"pool_ball13",
				"pool_ball14",
				"pool_ball15",
			};
			for(int i=0; i!=15; ++i)
			{
				auto image = images::LoadTexture(tex_names[i]);
				if(i == 0)
				{
					bound_tex.Image3D(
						0,
						PixelDataInternalFormat::RGBA,
						image.Width(),
						image.Height(),
						16,
						0,
						image.Format(),
						image.Type(),
						nullptr
					);
				}
				bound_tex.SubImage3D(
					0,
					0, 0, i,
					image.Width(),
					image.Height(),
					1,
					image.Format(),
					image.Type(),
					image.RawData()
				);
			}
			bound_tex.GenerateMipmap();
		}

		gl.ClearColor(0.12f, 0.13f, 0.11f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.CullFace(Face::Back);
	}

	void PrerenderLightmap(const Vec3f& light_position, size_t tex_side)
	{
		Framebuffer table_light_fbo;

		table_light_fbo.Bind(Framebuffer::Target::Draw);

		Framebuffer::AttachTexture(
			Framebuffer::Target::Draw,
			Framebuffer::Attachment::Color,
			table_light_map,
			0
		);

		gl.Viewport(tex_side, tex_side);
		gl.ClearColor(1.0 ,1.0, 1.0, 0.0);
		gl.Clear().ColorBuffer();

		LightmapProgram prog;

		Shape<shapes::Plane> plane(prog, shapes::Plane(plane_u, plane_v));


		GLfloat i_u = Length(plane_u);
		i_u = 1.0 / (i_u*i_u);
		GLfloat i_v = Length(plane_v);
		i_v = 1.0 / (i_v*i_v);
		prog.transform_matrix.Set(
			Mat4f(
				Vec4f(plane_u * i_u, 0.0),
				Vec4f(plane_v * i_v, 0.0),
				Vec4f(0.0, 1.0, 0.0, 0.0),
				Vec4f(0.0, 0.0, 0.0, 1.0)
			)
		);
		prog.light_position.Set(light_position);
		prog.ball_positions.Set(ball_offsets);

		gl.Disable(Capability::DepthTest);

		plane.Draw();

		gl.Enable(Capability::DepthTest);

		Program::UseNone();

		Framebuffer::BindDefault(Framebuffer::Target::Draw);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);

		transf_prog.projection_matrix.Set(
			CamMatrixf::Perspective(
				Degrees(48),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		// setup the camera
		Vec3f camera_target(0.0, 2.2, 5.0);
		auto camera = CamMatrixf::Orbiting(
			camera_target,
			14.0 - SineWave(time / 15.0)*12.0,
			FullCircles(time / 24.0),
			Degrees(50 + SineWave(time / 20.0) * 35)
		);

		Vec3f camera_position = camera.Position();
		transf_prog.camera_matrix.Set(camera);
		transf_prog.camera_position.Set(camera_position);

		// Render the plane
		cloth_pp.Bind();

		transf_prog.model_matrix = ModelMatrixf();
		transf_prog.texture_matrix.Set(Mat3f(
			16.0,  0.0,  0.0,
			 0.0, 16.0,  0.0,
			 0.0,  0.0,  1.0
		));

		plane.Draw();

		// Render the balls
		ball_pp.Bind();

		transf_prog.texture_matrix.Set(Mat3f(
			6.0, 0.0, 0.0,
			0.0, 3.0,-1.0,
			0.0, 0.0, 1.0
		));
		for(int i=0; i!=15; ++i)
		{
			Vec3f rot = ball_rotations[i];
			int ci = ((i / 4) % 2 == 0)?i : ((i/4)+2)*4-i-1;
			ci %= 8;
			Vec3f col = ball_colors[ci];
			transf_prog.model_matrix = ModelMatrixf(
				ModelMatrixf::Translation(ball_offsets[i]) *
				ModelMatrixf::RotationZ(FullCircles(rot.z())) *
				ModelMatrixf::RotationY(FullCircles(rot.y())) *
				ModelMatrixf::RotationX(FullCircles(rot.x()))
			);
			if(i > 7) ball_prog.color_1 = Vec3f(1.0, 0.9, 0.8);
			else ball_prog.color_1 = col;
			ball_prog.color_2 = col;
			ball_prog.number_idx = i;

			sphere.Draw();
		}
	}

	bool Continue(double time)
	{
		return time < 90.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new BilliardExample);
}

} // namespace oglplus
