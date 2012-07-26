/**
 *  @example oglplus/025_multi_viewport.cpp
 *  @brief Shows how to draw into multiple viewport at the same time
 *
 *  @image html 025_multi_viewport.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_cxx11{LAMBDAS}
 *  @oglplus_example_uses_cxx11{VARIADIC_TEMPLATES}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/spiral_sphere.hpp>
#include <oglplus/images/newton.hpp>
#include <oglplus/bound/texture.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class MultiViewportExample : public Example
{
private:
	typedef shapes::SpiralSphere Shape;
	// helper object building shape vertex attributes
	Shape make_shape;
	// helper object encapsulating shape drawing instructions
	shapes::DrawingInstructions shape_instr;
	// indices pointing to shape primitive elements
	Shape::IndexArray shape_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Geometry shader
	GeometryShader gs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered shape
	VertexArray shape;

	// VBOs for the shape's vertex attributes
	Buffer verts, normals;

	// The environment cube map
	Texture tex;

	Mat4f projection;
public:
	MultiViewportExample(void)
	 : make_shape(1.0, 0.1, 8, 4, 48)
	 , shape_instr(make_shape.Instructions())
	 , shape_indices(make_shape.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ModelMatrix;"
			"uniform vec3 LightPos;"

			"in vec4 Position;"
			"in vec3 Normal;"

			"out vec3 vertNormal;"
			"out vec3 vertTexCoord;"
			"out vec3 vertLightDir;"
			"out vec3 vertLightRefl;"

			"void main(void)"
			"{"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertTexCoord = Normal;"
			"	vertLightDir = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"	vertLightRefl = reflect("
			"		-vertLightDir,"
			"		vertNormal"
			"	);"
			"	gl_Position = "
			"		ModelMatrix *"
			"		Position;"
			"}"
		);
		vs.Compile();

		// Set the geometry shader source
		gs.Source(
			"#version 330\n"
			"#extension GL_ARB_viewport_array : enable\n"
			"layout(triangles) in;"
			"layout(triangle_strip, max_vertices = 12) out;"

			"uniform mat4 CameraMatrix[4];"
			"uniform vec3 CameraPosition[4];"

			"in vec3 vertNormal[];"
			"in vec3 vertTexCoord[];"
			"in vec3 vertLightDir[];"
			"in vec3 vertLightRefl[];"

			"out vec3 geomNormal;"
			"out vec3 geomTexCoord;"
			"out vec3 geomLightDir;"
			"out vec3 geomLightRefl;"
			"out vec3 geomViewDir;"
			"out vec3 geomViewRefl;"

			"void main(void)"
			"{"
			"	for(int vp=0; vp!=4; ++vp)"
			"	{"
			"		gl_ViewportIndex = vp;"
			"		for(int v=0; v!=3; ++v)"
			"		{"
			"			geomNormal = vertNormal[v];"
			"			geomTexCoord = vertTexCoord[v];"
			"			geomLightDir = vertLightDir[v];"
			"			geomLightRefl = vertLightRefl[v];"
			"			geomViewDir = "
			"				CameraPosition[vp] - "
			"				gl_in[v].gl_Position.xyz;"
			"			geomViewRefl = reflect("
			"				-geomViewDir,"
			"				geomNormal"
			"			);"
			"			gl_Position = "
			"				CameraMatrix[vp] *"
			"				gl_in[v].gl_Position;"
			"			EmitVertex();"
			"		}"
			"		EndPrimitive();"
			"	}"
			"}"
		);
		gs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform samplerCube TexUnit;"
			"in vec3 geomNormal;"
			"in vec3 geomTexCoord;"
			"in vec3 geomLightDir;"
			"in vec3 geomLightRefl;"
			"in vec3 geomViewDir;"
			"in vec3 geomViewRefl;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(geomLightDir);"
			"	float d = dot("
			"		normalize(geomNormal), "
			"		normalize(geomLightDir)"
			"	) / l;"
			"	float s = dot("
			"		normalize(geomLightRefl),"
			"		normalize(geomViewDir)"
			"	);"
			"	vec3 lt = vec3(1.0, 1.0, 1.0);"
			"	vec3 tex = texture(TexUnit, geomTexCoord).rgb;"
			"	fragColor = vec4("
			"		tex * 0.4 + "
			"		(lt + tex) * 1.5 * max(d, 0.0) + "
			"		lt * pow(max(s, 0.0), 64), "
			"		1.0"
			"	);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(gs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the shape
		shape.Bind();

		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the texture
		{
			size_t tex_side = 512;
			auto image = images::NewtonFractal(
				tex_side, tex_side,
				Vec3f(0.8f, 0.8f, 1.0f),
				Vec3f(0.1f, 0.0f, 0.2f),
				Vec2f(-0.707f, -0.707f),
				Vec2f( 0.707f,  0.707f),
				images::NewtonFractal::X4Minus1(),
				[](double x) -> double
				{
					return pow(SineWave(pow(x,0.5)), 4.0);
				}
			);
			auto bound_tex = Bind(tex, Texture::Target::CubeMap);
			bound_tex.MinFilter(TextureMinFilter::Linear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToEdge);
			bound_tex.WrapT(TextureWrap::ClampToEdge);
			bound_tex.WrapR(TextureWrap::ClampToEdge);

			for(int i=0; i!=6; ++i)
				Texture::Image2D(Texture::CubeMapFace(i), image);
		}
		//
		UniformSampler(prog, "TexUnit").Set(0);
		Uniform<Vec3f>(prog, "LightPos").Set(Vec3f(3.0f, 5.0f, 4.0f));
		//
		gl.ClearColor(0.1f, 0.05f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);

		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_shape.FaceWinding());
		gl.CullFace(Face::Back);

		Uniform<Vec3f>(prog, "CameraPosition[0]").Set(Vec3f(2, 0, 0));
		Uniform<Vec3f>(prog, "CameraPosition[1]").Set(Vec3f(0, 2, 0));
		Uniform<Vec3f>(prog, "CameraPosition[2]").Set(Vec3f(0, 0, 2));
	}

	void Reshape(size_t width, size_t height)
	{
		GLfloat w_2f = width / 2.0f;
		GLfloat h_2f = height/ 2.0f;
		GLfloat viewports[4*4] = {
			0.0f, 0.0f, w_2f, h_2f,
			w_2f, 0.0f, w_2f, h_2f,
			0.0f, h_2f, w_2f, h_2f,
			w_2f, h_2f, w_2f, h_2f
		};
		gl.ViewportArray(0, 4, viewports);

		projection = CamMatrixf::PerspectiveX(
			Degrees(52),
			double(width)/height,
			1, 10
		);

		Uniform<Mat4f>(prog, "CameraMatrix[0]").Set(
			projection *
			Mat4f(
				 0, 0,-1, 0,
				 0, 1, 0, 0,
				 1, 0, 0,-2,
				 0, 0, 0, 1
			)
		);
		Uniform<Mat4f>(prog, "CameraMatrix[1]").Set(
			projection *
			Mat4f(
				 1, 0, 0, 0,
				 0, 0,-1, 0,
				 0, 1, 0,-2,
				 0, 0, 0, 1
			)
		);
		Uniform<Mat4f>(prog, "CameraMatrix[2]").Set(
			projection *
			Mat4f(
				 1, 0, 0, 0,
				 0, 1, 0, 0,
				 0, 0, 1,-2,
				 0, 0, 0, 1
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		CamMatrixf camera = CamMatrixf::Orbiting(
			Vec3f(),
			3.5 - SineWave(time / 16.0) * 1.5,
			FullCircles(time / 12.0),
			Degrees(SineWave(time / 30.0) * 90)
		);
		// set the matrix for camera orbiting the origin
		Uniform<Mat4f>(prog, "CameraMatrix[3]").Set(projection * camera);
		Uniform<Vec3f>(prog, "CameraPosition[3]").Set(camera.Position());

		// set the model matrix
		Uniform<Mat4f>(prog, "ModelMatrix").Set(
			ModelMatrixf::RotationX(FullCircles(time / 10.0))
		);

		shape.Bind();
		shape_instr.Draw(shape_indices);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}

	double ScreenshotTime(void) const
	{
		return 3.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new MultiViewportExample);
}

} // namespace oglplus
