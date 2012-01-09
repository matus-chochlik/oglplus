/**
 *  @example oglplus/030_shadow_volume.cpp
 *  @brief Shows how to draw volumetric shadow
 *
 *  @image html 030_shadow_volume.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/spiral_sphere.hpp>
#include <oglplus/bound/texture.hpp>
#include <oglplus/bound/framebuffer.hpp>

#include "example.hpp"

namespace oglplus {

class ShadowVolExample : public Example
{
private:
	// helper object building shape vertex attributes
	shapes::SpiralSphere make_shape;
	// helper object encapsulating shape drawing instructions
	shapes::DrawingInstructions shape_instr;
	// indices pointing to shape primitive elements
	shapes::SpiralSphere::IndexArray shape_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Shaders
	VertexShader shape_vs, depth_vs, light_vs;

	GeometryShader depth_gs, light_gs;

	FragmentShader shape_fs, depth_fs, light_fs;

	// Programs
	Program shape_prog, depth_prog, light_prog;

	// A vertex array object for the rendered shape
	VertexArray shape, light;

	// VBOs for the shape's and light-volume's vertex attributes
	Buffer shape_positions, shape_normals, light_positions;

	// The shadow cube map
	Texture depth_tex;

	// The framebuffer for offscreen rendering of the shadow map
	Framebuffer depth_fbo;

	// The dimension of the texture
	const size_t tex_side;

	// The number of samples
	const size_t sample_count;

	// The window width and height
	size_t width, height;
public:
	ShadowVolExample(void)
	 : shape_instr(make_shape.Instructions())
	 , shape_indices(make_shape.Indices())
	 , shape_vs("Shape vertex")
	 , depth_vs("Depth vertex")
	 , light_vs("Light vertex")
	 , depth_gs("Depth geometry")
	 , light_gs("Light geometry")
	 , shape_fs("Shape fragment")
	 , depth_fs("Depthfragment")
	 , light_fs("Light fragment")
	 , shape_prog("Shape")
	 , light_prog("Light")
	 , depth_prog("Depth")
	 , tex_side(128)
	 , sample_count(128)
	{
		shape_vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"in vec2 TexCoord;"
			"out vec3 vertNormal;"
			"out vec3 vertLightDir;"
			"out vec3 vertLightRefl;"
			"out vec3 vertViewDir;"
			"out vec3 vertViewRefl;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLightDir = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"	vertLightRefl = reflect("
			"		-normalize(vertLightDir),"
			"		normalize(vertNormal)"
			"	);"
			"	vertViewDir = ("
			"		vec4(0.0, 0.0, 1.0, 1.0)*"
			"		CameraMatrix"
			"	).xyz;"
			"	vertViewRefl = reflect("
			"		normalize(vertViewDir),"
			"		normalize(vertNormal)"
			"	);"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"}"
		);
		shape_vs.Compile();

		shape_fs.Source(
			"#version 330\n"
			"in vec3 vertNormal;"
			"in vec3 vertLightDir;"
			"in vec3 vertLightRefl;"
			"in vec3 vertViewDir;"
			"in vec3 vertViewRefl;"
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
			"	vec3 ambi = vec3(0.6, 0.3, 0.5);"
			"	vec3 diff = vec3(0.9, 0.7, 0.8);"
			"	vec3 spec = vec3(1.0, 0.9, 0.95);"
			"	fragColor = vec4("
			"		ambi * 0.3 + "
			"		diff * 0.7 * max(d, 0.0) + "
			"		spec * pow(max(s, 0.0), 64), "
			"		1.0"
			"	);"
			"}"
		);
		shape_fs.Compile();

		shape_prog.AttachShader(shape_vs);
		shape_prog.AttachShader(shape_fs);
		shape_prog.Link();

		depth_vs.Source(
			"#version 330\n"
			"uniform mat4 ModelMatrix;"
			"uniform vec3 LightPos;"
			"in vec4 Position;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		mat4("
			"			1.0, 0.0, 0.0, -LightPos.x,"
			"			0.0, 1.0, 0.0, -LightPos.y,"
			"			0.0, 0.0, 1.0, -LightPos.z,"
			"			0.0, 0.0, 0.0,  1.0"
			"		)*"
			"		ModelMatrix *"
			"		mat4("
			"			10.0,  0.0,  0.0,  0.0,"
			"			 0.0, 10.0,  0.0,  0.0,"
			"			 0.0,  0.0, 10.0,  0.0,"
			"			 0.0,  0.0,  0.0,  1.0 "
			"		)*"
			"		Position;"
			"}"
		);
		depth_vs.Compile();

		depth_gs.Source(
			"#version 330\n"
			"layout(triangles) in;"
			"layout(triangle_strip, max_vertices = 18) out;"

			"uniform mat4 ProjectionMatrix;"

			"const mat4 CubeFaceMatrix[6] = mat4[6]("
			"	mat4("
			"		 0.0,  0.0, -1.0,  0.0,"
			"		 0.0, -1.0,  0.0,  0.0,"
			"		-1.0,  0.0,  0.0,  0.0,"
			"		 0.0,  0.0,  0.0,  1.0 "
			"	), mat4("
			"		 0.0,  0.0,  1.0,  0.0,"
			"		 0.0, -1.0,  0.0,  0.0,"
			"		 1.0,  0.0,  0.0,  0.0,"
			"		 0.0,  0.0,  0.0,  1.0 "
			"	), mat4("
			"		 1.0,  0.0,  0.0,  0.0,"
			"		 0.0,  0.0, -1.0,  0.0,"
			"		 0.0,  1.0,  0.0,  0.0,"
			"		 0.0,  0.0,  0.0,  1.0 "
			"	), mat4("
			"		 1.0,  0.0,  0.0,  0.0,"
			"		 0.0,  0.0,  1.0,  0.0,"
			"		 0.0, -1.0,  0.0,  0.0,"
			"		 0.0,  0.0,  0.0,  1.0 "
			"	), mat4("
			"		 1.0,  0.0,  0.0,  0.0,"
			"		 0.0, -1.0,  0.0,  0.0,"
			"		 0.0,  0.0, -1.0,  0.0,"
			"		 0.0,  0.0,  0.0,  1.0 "
			"	), mat4("
			"		-1.0,  0.0,  0.0,  0.0,"
			"		 0.0, -1.0,  0.0,  0.0,"
			"		 0.0,  0.0,  1.0,  0.0,"
			"		 0.0,  0.0,  0.0,  1.0 "
			"	)"
			");"

			"void main(void)"
			"{"
			"	for(gl_Layer=0; gl_Layer!=6; ++gl_Layer)"
			"	{"
			"		for(int i=0; i!=3; ++i)"
			"		{"
			"			gl_Position = "
			"				ProjectionMatrix *"
			"				CubeFaceMatrix[gl_Layer]*"
			"				gl_in[i].gl_Position;"
			"			EmitVertex();"
			"		}"
			"		EndPrimitive();"
			"	}"
			"}"
		);
		depth_gs.Compile();

		depth_fs.Source(
			"#version 330\n"
			"void main(void)"
			"{"
			"	gl_FragDepth = gl_FragCoord.z;"
			"}"
		);
		depth_fs.Compile();

		depth_prog.AttachShader(depth_vs);
		depth_prog.AttachShader(depth_gs);
		depth_prog.AttachShader(depth_fs);
		depth_prog.Link();
		depth_prog.Use();

		Uniform<Mat4f>(depth_prog, "ProjectionMatrix").Set(
			CamMatrixf::Perspective(
				RightAngles(1.0),
				1.0,
				1.0,
				100.0
			)
		);

		// bind the VAO for the shape
		shape.Bind();

		shape_positions.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);

			shape_prog.Use();
			VertexAttribArray shape_attr(shape_prog, "Position");
			shape_attr.Setup(n_per_vertex, DataType::Float);
			shape_attr.Enable();

			depth_prog.Use();
			VertexAttribArray depth_attr(depth_prog, "Position");
			depth_attr.Setup(n_per_vertex, DataType::Float);
			depth_attr.Enable();
		}

		shape_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);

			shape_prog.Use();
			VertexAttribArray attr(shape_prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		light_vs.Source(
			"#version 330\n"
			"in vec3 Position;"
			"out float vertZOffs;"
			"uniform vec3 LightPos;"
			"uniform int SampleCount;"
			"void main(void)"
			"{"
			"	float hp = (SampleCount-1) * 0.5;"
			"	vertZOffs = (gl_InstanceID - hp)/hp;"
			"	gl_Position = vec4(Position + LightPos, 1.0);"
			"}"
		);
		light_vs.Compile();

		light_gs.Source(
			"#version 330\n"
			"layout(points) in;"
			"layout(triangle_strip, max_vertices = 4) out;"
			"in float vertZOffs[];"
			"out vec4 geomPosition;"
			"uniform mat4 CameraMatrix, ProjectionMatrix;"
			"uniform vec3 ViewX, ViewY, ViewZ;"
			"uniform float LightVolSize;"
			"void main(void)"
			"{"
			"	float zo = vertZOffs[0];"
			"	float yo[2] = float[2](-1.0, 1.0);"
			"	float xo[2] = float[2](-1.0, 1.0);"
			"	for(int j=0;j!=2;++j)"
			"	for(int i=0;i!=2;++i)"
			"	{"
			"		geomPosition = vec4("
			"			gl_in[0].gl_Position.xyz+"
			"			ViewX * xo[i] * LightVolSize+"
			"			ViewY * yo[j] * LightVolSize+"
			"			ViewZ * zo    * LightVolSize,"
			"			1.0"
			"		);"
			"		gl_Position = "
			"			ProjectionMatrix *"
			"			CameraMatrix *"
			"			geomPosition;"
			"		EmitVertex();"
			"	}"
			"	EndPrimitive();"
			"}"
		);
		light_gs.Compile();

		light_fs.Source(
			"#version 330\n"
			"in vec4 geomPosition;"
			"out vec4 fragColor;"
			"uniform samplerCubeShadow ShadowMap;"
			"uniform int SampleCount;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	vec3 LightDir = geomPosition.xyz - LightPos;"
			"	vec4 ShadowCoord = vec4("
			"		normalize(LightDir),"
			"		length(LightDir)"
			"	);"
			"	float s = texture(ShadowMap, ShadowCoord);"
			"	float alpha = s / (SampleCount * pow(length(LightDir), 2));"
			"	fragColor = vec4(1.0, 1.0, 1.0, alpha);"
			"}"
		);
		light_fs.Compile();

		light_prog.AttachShader(light_vs);
		light_prog.AttachShader(light_gs);
		light_prog.AttachShader(light_fs);
		light_prog.Link();
		light_prog.Use();

		// bind the VAO for the light volume
		light.Bind();

		// bind the VBO for the light volume plane positions
		light_positions.Bind(Buffer::Target::Array);
		{
			GLfloat position[3] = {0.0, 0.0, 0.0};
			Buffer::Data(Buffer::Target::Array, 3, position);
			VertexAttribArray attr(light_prog, "Position");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		Uniform<GLint>(light_prog, "SampleCount").Set(sample_count);
		Uniform<GLfloat>(light_prog, "LightVolSize").Set(4);
		UniformSampler(light_prog, "ShadowMap").Set(0);

		// Setup the texture and the offscreen FBO
		Texture::Active(0);
		{
			auto bound_tex = Bind(depth_tex, Texture::Target::CubeMap);
			bound_tex.MinFilter(TextureMinFilter::Linear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::ClampToEdge);
			bound_tex.WrapT(TextureWrap::ClampToEdge);
			bound_tex.WrapR(TextureWrap::ClampToEdge);
			bound_tex.CompareFunc(CompareFunction::LEqual);
			bound_tex.CompareMode(
				TextureCompareMode::CompareRefToTexture
			);

			for(int i=0; i!=6; ++i)
			{
				Texture::Image2D(
					Texture::CubeMapFace(i),
					0,
					PixelDataInternalFormat::DepthComponent,
					tex_side, tex_side,
					0,
					PixelDataFormat::DepthComponent,
					PixelDataType::Float,
					nullptr
				);
			}

			auto bound_fbo = Bind(
				depth_fbo,
				Framebuffer::Target::Draw
			);
			bound_fbo.AttachTexture(
				Framebuffer::Attachment::Depth,
				depth_tex,
				0
			);
		}
		//
		gl.ClearColor(0.2f, 0.05f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);

		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_shape.FaceWinding());
		gl.CullFace(Face::Back);

		gl.BlendFunc(BlendFunction::SrcAlpha, BlendFunction::One);
	}

	void Reshape(size_t vp_width, size_t vp_height)
	{
		width = vp_width;
		height = vp_height;
		Mat4f proj = CamMatrixf::Perspective(
			Degrees(48),
			double(width)/height,
			1, 100
		);
		SetProgramUniform(shape_prog, "ProjectionMatrix", proj);
		SetProgramUniform(light_prog, "ProjectionMatrix", proj);
	}

	void Render(double time)
	{
		//
		// the camera matrix
		Mat4f camera = CamMatrixf::Orbiting(
			Vec3f(),
			5.5 + SineWave(time / 16.0) * 1.5,
			FullCircles(time / 12.0),
			Degrees(SineWave(time / 30.0) * 90)
		);
		//
		// the model matrix
		Mat4f model = ModelMatrixf::RotationA(
			Vec3f(1.0f, 1.0f, 1.0f),
			FullCircles(time / 10.0)
		);
		// the light position
		Vec3f lightPos(0.0f, SineWave(time / 7.0) * 0.5, 0.0f);
		//
		SetProgramUniform(shape_prog, "LightPos", lightPos);
		SetProgramUniform(depth_prog, "LightPos", lightPos);
		SetProgramUniform(light_prog, "LightPos", lightPos);
		//
		SetProgramUniform(shape_prog, "CameraMatrix", camera);
		SetProgramUniform(light_prog, "CameraMatrix", camera);

		SetProgramUniform(shape_prog, "ModelMatrix", model);
		SetProgramUniform(depth_prog, "ModelMatrix", model);

		// render the shadow map
		depth_fbo.Bind(Framebuffer::Target::Draw);
		gl.DrawBuffer(ColorBuffer::None);

		gl.Viewport(tex_side, tex_side);
		gl.Clear().DepthBuffer();

		depth_prog.Use();
		shape.Bind();
		shape_instr.Draw(shape_indices);

		// render the output frame
		Framebuffer::BindDefault(Framebuffer::Target::Draw);
		gl.DrawBuffer(ColorBuffer::Back);

		gl.Viewport(width, height);
		gl.Clear().ColorBuffer().DepthBuffer();


		shape_prog.Use();
		shape.Bind();
		shape_instr.Draw(shape_indices);

		gl.Enable(Capability::Blend);

		light_prog.Use();
		SetUniform(light_prog, "ViewX", Row<0>(camera).xyz());
		SetUniform(light_prog, "ViewY", Row<1>(camera).xyz());
		SetUniform(light_prog, "ViewZ", Row<2>(camera).xyz());

		light.Bind();
		gl.DrawArraysInstanced(
			PrimitiveType::Points,
			0, 1,
			sample_count
		);

		gl.Disable(Capability::Blend);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new ShadowVolExample);
}

} // namespace oglplus
