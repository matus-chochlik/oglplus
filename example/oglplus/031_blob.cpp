/**
 *  @example oglplus/031_blob.cpp
 *  @brief Shows implicit surface polygonization
 *
 *  @image html 031_blob.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <oglplus/bound/texture.hpp>

#include <oglplus/shapes/tetrahedrons.hpp>
#include <oglplus/shapes/plane.hpp>
#include <oglplus/shapes/wrapper.hpp>

#include <oglplus/images/brushed_metal.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class BlobVertShader
 : public VertexShader
{
public:
	BlobVertShader(void)
	 : VertexShader(
		"Blob vertex shader",
		"#version 330\n"
		"uniform vec3 GridOffset;"
		"uniform sampler1D Metaballs;"

		"in vec4 Position;"

		"out vec3 vertCenter;"
		"out float vertValue;"

		"void main(void)"
		"{"
		"	gl_Position = Position + vec4(GridOffset, 0.0);"

		"	float Sum = 0.0;"
		"	vertValue = 0.0;"
		"	vertCenter = vec3(0.0, 0.0, 0.0);"
		"	int Ball = 0, BallCount = textureSize(Metaballs, 0);"
		"	while(Ball != BallCount)"
		"	{"
		"		vec4 Metaball = texelFetch(Metaballs, Ball, 0);"
		"		vec3 Center = Metaball.xyz;"
		"		float Radius = Metaball.w;"
		"		vec3 Vect = gl_Position.xyz - Center;"
		"		float Tmp = (Radius*Radius)/dot(Vect, Vect);"
		"		vertValue += Tmp - 0.25;"
		"		float Mul = max(Tmp - 0.10, 0.0);"
		"		if(Mul > 0.0)"
		"		{"
		"			vertCenter += Mul * Center;"
		"			Sum += Mul;"
		"		}"
		"		++Ball;"
		"	}"
		"	if(Sum > 0.0) vertCenter = vertCenter / Sum;"
		"}"
	)
	{ }
};

class BlobGeomShader
 : public GeometryShader
{
public:
	BlobGeomShader(void)
	 : GeometryShader(
		"Blob geometry shader",
		"#version 330\n"
		"layout(triangles_adjacency) in;"
		"layout(triangle_strip, max_vertices = 4) out;"

		"uniform mat4 CameraMatrix;"
		"uniform vec3 CameraPosition, LightPosition;"

		"in vec3 vertCenter[];"
		"in float vertValue[];"

		"out vec3 geomNormal, geomLightDir, geomViewDir;"

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
		"	gl_Position = mix("
		"		gl_in[i1].gl_Position,"
		"		gl_in[i2].gl_Position,"
		"		t"
		"	);"
		"	geomNormal = normalize("
		"		gl_Position.xyz - "
		"		mix(vertCenter[i1], vertCenter[i2], t)"
		"	);"
		"	geomLightDir = LightPosition - gl_Position.xyz;"
		"	geomViewDir = CameraPosition - gl_Position.xyz;"
		"	gl_Position = CameraMatrix * gl_Position;"
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
		"					make_triangle(b,c, b,d, b,a);"
		"				else make_quad(b,c, d,c, b,a, d,a);"
		"			}"
		"			else"
		"			{"
		"				if(vertValue[d] >= 0.0)"
		"					make_quad(c,a, c,d, b,a, b,d);"
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
		"					make_quad(a,b, a,d, c,b, c,d);"
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

class BlobFragShader
 : public FragmentShader
{
public:
	BlobFragShader(void)
	 : FragmentShader(
		"Blob fragment shader",
		"#version 330\n"

		"in vec3 geomNormal, geomLightDir, geomViewDir;"

		"out vec4 fragColor;"

		"const vec3 LightColor = vec3(1.0, 1.0, 0.9);"

		"void main(void)"
		"{"
		"	vec3 Color = vec3(1.0, 1.0, 0.9);"
		"	vec3 Normal = normalize(geomNormal);"
		"	vec3 LightDir = normalize(geomLightDir);"
		"	vec3 ViewDir = normalize(geomViewDir);"

		"	vec3 LightRefl = reflect(-LightDir, Normal);"

		"	float Specular = pow(max(dot(LightRefl,ViewDir), 0.0), 64);"

		"	float LightHit = dot(Normal, LightDir);"

		"	float Diffuse = pow(1.05*max(LightHit-0.05, 0.0), 2.0);"

		"	float ViewLight = max(0.3-dot(ViewDir, LightDir), 0.0);"
		"	float Translucent = "
		"		ViewLight*"
		"		pow(0.4*exp(sin(-0.3-LightHit*(1.2+1.2*ViewLight))),3.0)*"
		"		0.2;"

		"	float Ambient = 0.5;"

		"	fragColor = vec4("
		"		Color * Ambient +"
		"		LightColor * Color * (Diffuse + Translucent) + "
		"		LightColor * Specular, "
		"		1.0"
		"	);"
		"}"
	)
	{ }
};

class BlobProgram
 : public HardwiredProgram<BlobVertShader, BlobGeomShader, BlobFragShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Mat4f> camera_matrix;
	ProgramUniform<Vec3f> grid_offset, camera_position, light_position;
	ProgramUniformSampler metaballs;

	BlobProgram(void)
	 : HardwiredProgram<BlobVertShader,BlobGeomShader,BlobFragShader>(
		"Blob program"
	), camera_matrix(prog(), "CameraMatrix")
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

class MetalVertShader
 : public VertexShader
{
public:
	MetalVertShader(void)
	 : VertexShader(
		"Metal vertex shader",
		"#version 330\n"
		"uniform mat4 CameraMatrix;"
		"uniform vec3 CameraPosition, LightPosition;"
		"in vec4 Position;"
		"in vec3 Normal, Tangent;"
		"in vec2 TexCoord;"

		"out vec3 vertNormal, vertTangent, vertBinormal;"
		"out vec3 vertLightDir, vertViewDir;"
		"out vec2 vertTexCoord;"
		"void main(void)"
		"{"
		"	gl_Position = Position - vec4(0.0, 1.0, 0.0, 0.0);"
		"	vertLightDir = LightPosition - gl_Position.xyz;"
		"	vertViewDir = CameraPosition - gl_Position.xyz;"
		"	vertNormal = Normal;"
		"	vertTangent = Tangent;"
		"	vertBinormal = cross(vertNormal, vertTangent);"
		"	vertTexCoord = TexCoord * 9.0;"
		"	gl_Position = CameraMatrix * gl_Position;"
		"}"
	)
	{ }
};

class MetalFragShader
 : public FragmentShader
{
public:
	MetalFragShader(void)
	 : FragmentShader(
		"Metal fragment shader",
		"#version 330\n"
		"const vec3 Color1 = vec3(0.7, 0.6, 0.5);"
		"const vec3 Color2 = vec3(0.9, 0.8, 0.7);"

		"uniform sampler2D MetalTex;"

		"in vec3 vertNormal, vertTangent, vertBinormal;"
		"in vec3 vertLightDir, vertViewDir;"
		"in vec2 vertTexCoord;"

		"out vec3 fragColor;"

		"void main(void)"
		"{"
		"	vec3 Sample = texture(MetalTex, vertTexCoord).rgb;"
		"	vec3 LightColor = vec3(1.0, 1.0, 0.9);"

		"	vec3 Normal = normalize("
		"		2.0*vertNormal + "
		"		(Sample.r - 0.5)*vertTangent + "
		"		(Sample.g - 0.5)*vertBinormal"
		"	);"

		"	vec3 LightRefl = reflect("
		"		-normalize(vertLightDir),"
		"		Normal"
		"	);"

		"	float Specular = pow(max(dot("
		"		normalize(LightRefl),"
		"		normalize(vertViewDir)"
		"	)+0.04, 0.0), 16+Sample.b*48)*pow(0.4+Sample.b*1.6, 4.0);"

		"	Normal = normalize(vertNormal*3.0 + Normal);"

		"	float Diffuse = pow(max(dot("
		"		normalize(Normal), "
		"		normalize(vertLightDir)"
		"	), 0.0), 2.0);"

		"	float Ambient = 0.5;"

		"	vec3 Color = mix(Color1, Color2, Sample.b);"

		"	fragColor = "
		"		Color * Ambient +"
		"		LightColor * Color * Diffuse + "
		"		LightColor * Specular;"
		"}"
	)
	{ }
};

class MetalProgram
 : public HardwiredProgram<MetalVertShader, MetalFragShader>
{
private:
	const Program& prog(void) const { return *this; }
public:
	ProgramUniform<Mat4f> camera_matrix;
	ProgramUniform<Vec3f> camera_position, light_position;
	ProgramUniformSampler metal_tex;

	MetalProgram(void)
	 : HardwiredProgram<MetalVertShader, MetalFragShader>("Metal program")
	 , camera_matrix(prog(), "CameraMatrix")
	 , camera_position(prog(), "CameraPosition")
	 , light_position(prog(), "LightPosition")
	 , metal_tex(prog(), "MetalTex")
	{ }
};

class Plate
 : public shapes::ShapeWrapper<shapes::Plane>
{
public:
	Plate(const Program& program)
	 : shapes::ShapeWrapper<shapes::Plane>(
		{"Position", "Normal", "Tangent", "TexCoord"},
		shapes::Plane(Vec3f(9, 0, 0), Vec3f(0, 0,-9)),
		program
	)
	{ }
};

class BlobExample : public Example
{
private:

	// wrapper around the current OpenGL context
	Context gl;

	BlobProgram blob_prog;
	MetalProgram metal_prog;

	Grid grid;
	Plate plane;

	size_t width, height;

	std::vector<CubicBezierLoop<Vec4f, double> > ball_paths;

	// A 1D xyzw texture that contains metaball parameters
	Texture metaballs_tex;

	// A 2D metal texture
	Texture metal_tex;
public:
	BlobExample(void)
	 : blob_prog()
	 , metal_prog()
	 , grid(blob_prog)
	 , plane(metal_prog)
	{
		std::srand(234);
		for(size_t i=0; i!=32; ++i)
		{
			size_t j = 0, n = 3+std::rand()%3;
			std::vector<Vec4f> points(n);
			GLfloat ball_size = 0.15*std::rand()/GLdouble(RAND_MAX) + 0.25;
			while(j != n)
			{
				points[j] = Vec4f(
					1.2*std::rand()/GLdouble(RAND_MAX) - 0.6,
					1.2*std::rand()/GLdouble(RAND_MAX) - 0.6,
					1.2*std::rand()/GLdouble(RAND_MAX) - 0.6,
					ball_size
				);
				++j;
			}
			ball_paths.push_back(CubicBezierLoop<Vec4f, double>(points));
			++i;
		}
		//
		Texture::Active(0);
		blob_prog.metaballs.Set(0);
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

		Texture::Active(1);
		metal_prog.metal_tex.Set(1);
		{
			auto bound_tex = Bind(metal_tex, Texture::Target::_2D);
			bound_tex.Image2D(
				images::BrushedMetalUByte(
					512, 512,
					5120,
					-3, +3,
					32, 128
				)
			);
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}

		const Vec3f light_position(12.0, 1.0, 8.0);
		blob_prog.light_position.Set(light_position);
		metal_prog.light_position.Set(light_position);

		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);

		gl.Enable(Capability::CullFace);
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

		gl.ClearColor(0.8f, 0.7f, 0.6f, 0.0f);
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
			3.0 - SineWave(time / 14.0),
			FullCircles(time / 26.0),
			Degrees(45 + SineWave(time / 17.0) * 40)
		);
		Vec3f camera_position = camera.Position();

		metal_prog.Use();
		metal_prog.camera_position.Set(camera_position);
		metal_prog.camera_matrix.Set(perspective*camera);

		plane.Use();
		plane.Draw();

		blob_prog.Use();
		blob_prog.camera_position.Set(camera_position);
		blob_prog.camera_matrix.Set(perspective*camera);

		grid.Use();

		int side = 1;
		for(int z=-side; z!=side+1; ++z)
		for(int y=-side; y!=side+1; ++y)
		for(int x=-side; x!=side+1; ++x)
		{
			blob_prog.grid_offset.Set(x, y, z);
			grid.Draw();
		}

	}

	void Render(double time)
	{
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
	return std::unique_ptr<Example>(new BlobExample);
}

} // namespace oglplus
