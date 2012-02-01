/**
 *  @example oglplus/031_liquid.cpp
 *  @brief Shows implicit surface polygonization
 *  @note Still work in progress
 *
 *  @image html 031_liquid.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <oglplus/shapes/tetrahedrons.hpp>

#include <oglplus/bound/texture.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class LiquidVertShader
 : public VertexShader
{
public:
	LiquidVertShader(void)
	 : VertexShader(
		"Liquid vertex shader",
		"#version 330\n"
		"uniform mat4 CameraMatrix;"
		"uniform mat4 LightProjMatrix;"
		"uniform vec3 CameraPosition, LightPosition;"
		"uniform vec3 GridOffset;"
		"uniform sampler1D Metaballs;"

		"in vec4 Position;"

		"out vec3 vertNormal, vertLightDir, vertViewDir;"
		"out vec4 vertLightTexCoord;"
		"out float vertValue;"
		"void main(void)"
		"{"
		"	gl_Position = Position + vec4(GridOffset, 0.0);"

		"	vertValue = 0.0;"
		"	vertNormal = vec3(0.0, 0.0, 0.0);"
		"	int Ball = 0, BallCount = textureSize(Metaballs, 0);"
		"	while(Ball != BallCount)"
		"	{"
		"		vec4 Metaball = texelFetch(Metaballs, Ball, 0);"
		"		float Radius = Metaball.w;"
		"		vec3 Vect = gl_Position.xyz - Metaball.xyz;"
		"		float Tmp = pow(Radius,2.0)/dot(Vect, Vect) - 0.25;"
		"		vertValue += Tmp;"
		"		float Mul = max(Tmp, 0.0);"
		"		vertNormal += Mul*Vect;"
		"		++Ball;"
		"	}"

		"	vertLightDir = LightPosition - gl_Position.xyz;"
		"	vertViewDir = CameraPosition - gl_Position.xyz;"
		"	vertLightTexCoord = LightProjMatrix* gl_Position;"
		"	gl_Position = CameraMatrix * gl_Position;"
		"}"
	)
	{ }
};

class LiquidGeomShader
 : public GeometryShader
{
public:
	LiquidGeomShader(void)
	 : GeometryShader(
		"Liquid geometry shader",
		"#version 330\n"
		"layout(triangles_adjacency) in;"
		"layout(triangle_strip, max_vertices = 4) out;"

		"uniform mat4 ProjectionMatrix;"

		"in vec3 vertNormal[], vertLightDir[], vertViewDir[];"
		"in vec4 vertLightTexCoord[];"
		"in float vertValue[];"

		"out vec3 geomNormal, geomLightDir, geomViewDir;"
		"out vec4 geomLightTexCoord;"

		"void do_nothing(void){ };"

		"float find_t(int i1, int i2)"
		"{"
		"	float d = vertValue[i2] - vertValue[i1];"
		"	if(d <= 0.0) return 0.0;"
		"	else return -vertValue[i1]/d;"
		"}"

		"void make_vertex(int i1, int i2)"
		"{"
		"	float t = find_t(i1, i2);"
		"	gl_Position = ProjectionMatrix * mix("
		"		gl_in[i1].gl_Position,"
		"		gl_in[i2].gl_Position,"
		"		t"
		"	);"
		"	geomNormal = mix("
		"		vertNormal[i1],"
		"		vertNormal[i2],"
		"		t"
		"	);"
		"	geomLightDir = mix("
		"		vertLightDir[i1],"
		"		vertLightDir[i2],"
		"		t"
		"	);"
		"	geomViewDir= mix("
		"		vertViewDir[i1],"
		"		vertViewDir[i2],"
		"		t"
		"	);"
		"	geomLightTexCoord = mix("
		"		vertLightTexCoord[i1],"
		"		vertLightTexCoord[i2],"
		"		t"
		"	);"
		"	EmitVertex();"
		"}"

		"void make_triangle(int a1, int a2, int b1, int b2, int c1, int c2)"
		"{"
		"	make_vertex(a1, a2);"
		"	make_vertex(b1, b2);"
		"	make_vertex(c1, c2);"
		"	EndPrimitive();"
		"}"

		"void make_quad(int a1,int a2,int b1,int b2,int c1,int c2,int d1,int d2)"
		"{"
		"	make_vertex(a1, a2);"
		"	make_vertex(b1, b2);"
		"	make_vertex(c1, c2);"
		"	make_vertex(d1, d2);"
		"	EndPrimitive();"
		"}"

		"void process_tetrahedron(int a, int b, int c, int d)"
		"{"
		"	if(vertValue[a] >= 0.0)"
		"	{"
		"		if(vertValue[b] >= 0.0)"
		"		{"
		"			if(vertValue[c] >= 0.0)"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					do_nothing();"
		"				else make_triangle(d,a, d,b, d,c);"
		"			}"
		"			else"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_triangle(c,a, c,d, c,b);"
		"				else make_quad(c,a, d,a, c,b, d,b);"
		"			}"
		"		}"
		"		else"
		"		{"
		"			if(vertValue[c] >= 0.0)"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_triangle(b,a, b,c, b,d);"
		"				else make_quad(b,c, d,c, b,a, d,a);"
		"			}"
		"			else"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_quad(c,a, b,a, c,d, b,d);"
		"				else make_triangle(c,a, d,a, b,a);"
		"			}"
		"		}"
		"	}"
		"	else"
		"	{"
		"		if(vertValue[b] >= 0.0)"
		"		{"
		"			if(vertValue[c] >= 0.0)"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_triangle(a,b, a,d, a,c);"
		"				else make_quad(a,c, a,b, d,c, d,b);"
		"			}"
		"			else"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_quad(c,d, a,d, c,b, a,b);"
		"				else make_triangle(a,b, d,b, c,b);"
		"			}"
		"		}"
		"		else"
		"		{"
		"			if(vertValue[c] >= 0.0)"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_quad(b,c, b,d, a,c, a,d);"
		"				else make_triangle(b,c, d,c, a,c);"
		"			}"
		"			else"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_triangle(a,d, c,d, b,d);"
		"				else do_nothing();"
		"			}"
		"		}"
		"	}"
		"}"

		"void main(void)"
		"{"
		"	process_tetrahedron(0, 2, 4, 1);"
		"}"
	)
	{ }
};

class LiquidFragShader
 : public FragmentShader
{
public:
	LiquidFragShader(void)
	 : FragmentShader(
		"Liquid fragment shader",
		"#version 330\n"

		"in vec3 geomNormal, geomLightDir, geomViewDir;"
		"in vec4 geomLightTexCoord;"

		"out vec4 fragColor;"

		"const vec3 LightColor = vec3(1.0, 1.0, 1.0);"

		"void main(void)"
		"{"
		"	vec3 Color = normalize(geomNormal);"

		"	vec3 LightRefl = reflect("
		"		-normalize(geomLightDir),"
		"		normalize(geomNormal)"
		"	);"

		"	float Specular = pow(max(dot("
		"		normalize(LightRefl),"
		"		normalize(geomViewDir)"
		"	)+0.05, 0.0), 128);"

		"	float Diffuse = pow(pow(dot("
		"		normalize(geomNormal), "
		"		normalize(geomLightDir)"
		"	)+0.3, 2.0), 2.0);"

		"	float Ambient = 0.3;"

		"	fragColor = vec4("
		"		Color * Ambient +"
		"		LightColor * Color * Diffuse + "
		"		LightColor * Specular, "
		"		0.4 + min(Specular, 1.0)*0.3+geomLightTexCoord.x*0.001"
		"	);"
		"}"
	)
	{ }
};

class LiquidProgram
 : public HardwiredProgram<LiquidVertShader, LiquidGeomShader, LiquidFragShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Mat4f> camera_matrix, projection_matrix, light_proj_matrix;
	ProgramUniform<Vec3f> grid_offset, camera_position, light_position;
	ProgramUniformSampler metaballs;

	LiquidProgram(void)
	 : HardwiredProgram<LiquidVertShader,LiquidGeomShader,LiquidFragShader>(
		"Liquid program"
	), camera_matrix(prog(), "CameraMatrix")
	 , projection_matrix(prog(), "ProjectionMatrix")
	 , light_proj_matrix(prog(), "LightProjMatrix")
	 , grid_offset(prog(), "GridOffset")
	 , camera_position(prog(), "CameraPosition")
	 , light_position(prog(), "LightPosition")
	 , metaballs(prog(), "Metaballs")
	{ }
};


class Grid
{
protected:
	shapes::Tetrahedrons make_grid;
	shapes::DrawingInstructions grid_instr;
	typename shapes::Tetrahedrons::IndexArray grid_indices;

	Context gl;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBO for the grids's vertex positions
	Buffer vbo;

public:
	Grid(const Program& prog)
	 : make_grid(1.0, 20)
	 , grid_instr(make_grid.InstructionsWithAdjacency())
	 , grid_indices(make_grid.IndicesWithAdjacency())
	{
		// bind the VAO for the shape
		vao.Bind();

		std::vector<GLfloat> data;
		// bind the VBO for the vertex attribute
		vbo.Bind(Buffer::Target::Array);
		GLuint n_per_vertex = make_grid.Positions(data);
		// upload the data
		Buffer::Data(Buffer::Target::Array, data);
		// setup the vertex attribs array
		VertexAttribArray attr(prog, "Position");
		attr.Setup(n_per_vertex, DataType::Float);
		attr.Enable();
	}

	void Use(void)
	{
		vao.Bind();
	}

	void Draw(void)
	{
		grid_instr.Draw(grid_indices);
	}
};

class LiquidExample : public Example
{
private:

	// wrapper around the current OpenGL context
	Context gl;

	LiquidProgram liquid_prog;

	Grid grid;

	size_t width, height;

	std::vector<CubicBezierLoop<Vec4f, double> > ball_paths;

	// A 1D xyzw texture that contains metaball parameters
	Texture metaballs_tex;

	const size_t shadow_tex_side;
public:
	LiquidExample(void)
	 : liquid_prog()
	 , grid(liquid_prog)
	 , shadow_tex_side(1024)
	{
		for(size_t i=0; i!=32; ++i)
		{
			size_t j = 0, n = 3+std::rand()%3;
			std::vector<Vec4f> points(n);
			GLfloat ball_size = 0.2*std::rand()/GLdouble(RAND_MAX) + 0.2;
			while(j != n)
			{
				points[j] = Vec4f(
					1.4*std::rand()/GLdouble(RAND_MAX) - 0.7,
					1.4*std::rand()/GLdouble(RAND_MAX) - 0.7,
					1.4*std::rand()/GLdouble(RAND_MAX) - 0.7,
					ball_size
				);
				++j;
			}
			ball_paths.push_back(CubicBezierLoop<Vec4f, double>(points));
			++i;
		}
		//
		Texture::Active(0);
		liquid_prog.metaballs.Set(0);
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
			bound_tex.WrapS(TextureWrap::ClampToEdge);
		}
/*
		Texture::Active(1);
		sketch_prog.shadow_tex.Set(1);
		{
			auto bound_tex = Bind(shadow_tex, Texture::Target::_2D);
			bound_tex.MinFilter(TextureMinFilter::Linear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToEdge);
			bound_tex.WrapT(TextureWrap::ClampToEdge);
			bound_tex.CompareMode(TextureCompareMode::CompareRefToTexture);
			bound_tex.Image2D(
				0,
				PixelDataInternalFormat::DepthComponent32,
				shadow_tex_side, shadow_tex_side,
				0,
				PixelDataFormat::DepthComponent,
				PixelDataType::Float,
				nullptr
			);
		}

		{
			auto bound_fbo = Bind(
				frame_shadow_fbo,
				Framebuffer::Target::Draw
			);
			bound_fbo.AttachTexture(
				Framebuffer::Attachment::Depth,
				shadow_tex,
				0
			);
		}
*/

		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		//gl.Enable(Capability::CullFace);
		gl.FrontFace(FaceOrientation::CW);
		gl.CullFace(Face::Back);
	}

	void Reshape(size_t vp_width, size_t vp_height)
	{
		width = vp_width;
		height = vp_height;
	}

	void UpdateMetaballs(double time)
	{
		size_t metaball_count = ball_paths.size(), k = 0;
		std::vector<GLfloat> metaballs(metaball_count*4);
		for(size_t ball=0; ball != metaball_count; ++ball)
		{
			Vec4f pos = ball_paths[ball].Position(time / 21.0);

			for(size_t coord=0; coord != 4; ++coord)
				metaballs[k++] = pos.At(coord);
		}

		metaballs_tex.Bind(Texture::Target::_1D);
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
	}

	void RenderImage(double time)
	{
		// this is going into the on-screen framebuffer
		Framebuffer::BindDefault(Framebuffer::Target::Draw);

		gl.ClearColor(1.0f, 0.9f, 0.8f, 0.0f);
		gl.Viewport(width, height);
		gl.Clear().ColorBuffer().DepthBuffer();
		//

		Mat4f perspective = CamMatrixf::Perspective(
			Degrees(48),
			double(width)/height,
			1, 100
		);

		auto camera = CamMatrixf::Orbiting(
			Vec3f(0, 0, 0),
			4.0 - SineWave(time / 14.0),
			FullCircles(time / 26.0),
			Degrees(45 + SineWave(time / 17.0) * 40)
		);
		Vec3f camera_position = camera.Position();

		liquid_prog.camera_position.Set(camera_position);
		liquid_prog.camera_matrix.Set(camera);
		liquid_prog.projection_matrix.Set(perspective);

		grid.Use();

		int side = 1;
		for(int z=-side; z!=side+1; ++z)
		for(int y=-side; y!=side+1; ++y)
		for(int x=-side; x!=side+1; ++x)
		{
			liquid_prog.grid_offset.Set(x, y, z);
			grid.Draw();
		}

	}

	void Render(double time)
	{
		const Vec3f light_position(16.0, 10.0, 9.0);

		const Mat4f light_proj_matrix =
			CamMatrixf::Perspective(Degrees(4), 1.0, 1, 100) *
			CamMatrixf::LookingAt(light_position, Vec3f(0,0,0));

		liquid_prog.light_position.Set(light_position);
		liquid_prog.light_proj_matrix.Set(light_proj_matrix);

		UpdateMetaballs(time);
		RenderImage(time);
	}

	bool Continue(double time)
	{
		return time < 90.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new LiquidExample);
}

} // namespace oglplus
