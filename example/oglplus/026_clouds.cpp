/**
 *  @example oglplus/026_clouds.cpp
 *  @brief Shows how to render dynamically lighted clouds using a 3d texture
 *
 *  @image html 026_clouds.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/curve.hpp>

#include <oglplus/bound/texture.hpp>
#include <oglplus/images/cloud.hpp>
#include <oglplus/shapes/sphere.hpp>

#include <vector>

#include "example.hpp"

namespace oglplus {

class CloudExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	VertexShader light_vs, cloud_vs;

	GeometryShader cloud_gs;

	FragmentShader light_fs, cloud_fs;

	Program light_prog, cloud_prog;

	shapes::Sphere make_sphere;
	shapes::DrawingInstructions sphere_instr;
	shapes::Sphere::IndexArray sphere_indices;

	VertexArray light;
	Buffer buffer;

	VertexArray clouds;
	Buffer pos_buffer, size_buffer;

	const size_t samples;
	const std::vector<Vec3f> positions;
	const std::vector<GLfloat> sizes;
	Array<Texture> cloud_tex;

	CubicBezierLoop<Vec3f, double> lightPath;
public:
	CloudExample(void)
	 : sphere_instr(make_sphere.Instructions())
	 , sphere_indices(make_sphere.Indices())
	 , samples(50)
	 , positions(
		{
			{-1.4f, -0.3f, -0.7f},
			{-1.6f, +0.4f, +0.7f},
			{+0.6f, -0.1f, +0.1f}
		}
	), sizes({1.0f, 1.2f, 1.5f})
	 , cloud_tex(positions.size())
	 , lightPath(
		{
			{-3.0f, -3.0f, -3.0f},
			{ 0.0f,  0.0f,  0.0f},
			{ 3.0f,  3.0f,  3.0f},
			{ 3.0f, -3.0f, -3.0f},
			{ 0.0f,  0.0f,  0.0f},
			{-3.0f,  3.0f,  3.0f}
		}
	)
	{
		assert(positions.size() == sizes.size());
		std::srand(123456);

		light_vs.Source(
			"#version 330\n"
			"in vec3 vertex;"
			"uniform vec3 lightPos;"
			"uniform mat4 cameraMatrix, projectionMatrix;"
			"void main(void)"
			"{"
			"	float s = 0.1;"
			"	gl_Position = "
			"		projectionMatrix*"
			"		cameraMatrix*"
			"		vec4(vertex*s + lightPos, 1.0);"
			"}"
		);
		light_vs.Compile();

		light_fs.Source(
			"#version 330\n"
			"out vec4 fragLight;"
			"void main(void)"
			"{"
			"	fragLight = vec4(1.0, 1.0, 1.0, 1.0);"
			"}"
		);
		light_fs.Compile();

		light_prog.AttachShader(light_vs);
		light_prog.AttachShader(light_fs);
		light_prog.Link();
		light_prog.Use();

		light.Bind();

		buffer.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(light_prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		cloud_vs.Source(
			"#version 330\n"
			"in vec4 position;"
			"in float size;"
			"uniform int n_samples;"
			"uniform mat4 cameraMatrix;"
			"uniform vec3 viewZ;"
			"out float zo;"
			"out float s;"
			"void main(void)"
			"{"
			"	float hp = (n_samples-1) * 0.5;"
			"	zo = (gl_InstanceID - hp)/hp;"
			"	s = size;"
			"	gl_Position = vec4("
			"		position.xyz +"
			"		viewZ*zo*size*0.5,"
			"		1.0"
			"	);"
			"}"
		);
		cloud_vs.Compile();

		cloud_gs.Source(
			"#version 330\n"
			"layout(points) in;"
			"layout(triangle_strip, max_vertices = 4) out;"
			"in float zo[];"
			"in float s[];"
			"uniform vec3 lightPos;"
			"uniform mat4 cameraMatrix, projectionMatrix;"
			"uniform vec3 viewX, viewY, viewZ;"
			"out vec3 fragTexCoord;"
			"out vec3 lightDir;"
			"void main(void)"
			"{"
			"	float yo[2] = float[2](-1.0, 1.0);"
			"	float xo[2] = float[2](-1.0, 1.0);"
			"	for(int j=0;j!=2;++j)"
			"	for(int i=0;i!=2;++i)"
			"	{"
			"		vec4 v = vec4("
			"			gl_in[0].gl_Position.xyz+"
			"			viewX * xo[i] * s[0] * 0.5+"
			"			viewY * yo[j] * s[0] * 0.5,"
			"			1.0"
			"		);"
			"		gl_Position = projectionMatrix * cameraMatrix * v;"
			"		lightDir = lightPos - v.xyz;"
			"		fragTexCoord = "
			"			vec3(0.5, 0.5, 0.5)+"
			"			viewX*(xo[i])*0.707+"
			"			viewY*(yo[j])*0.707+"
			"			viewZ*(zo[0])*0.707;"
			"		EmitVertex();"
			"	}"
			"	EndPrimitive();"
			"}"
		);
		cloud_gs.Compile();

		cloud_fs.Source(
			"#version 330\n"
			"uniform sampler3D cloudTex;"
			"in vec3 fragTexCoord;"
			"in vec3 lightDir;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float d = texture(cloudTex, fragTexCoord).r;"
			"	float o = 1.0;"
			"	float s = 2.0/128.0;"
			"	float r = s * 8.0;"
			"	vec3 sampleOffs = normalize(lightDir) * s;"
			"	vec3 samplePos = fragTexCoord;"
			"	if(d > 0.01) while(o > 0.0)"
			"	{"
			"		if(samplePos.x<0.0 || samplePos.x>1.0)"
			"			break;"
			"		if(samplePos.y<0.0 || samplePos.y>1.0)"
			"			break;"
			"		if(samplePos.z<0.0 || samplePos.z>1.0)"
			"			break;"
			"		o -= texture(cloudTex, samplePos).r*r;"
			"		samplePos += sampleOffs;"
			"	}"
			"	float a = 0.4 * d;"
			"	float i = mix(0.2, 1.0, o);"
			"	fragColor = vec4(i, i, i, a);"
			"}"
		);
		cloud_fs.Compile();

		cloud_prog.AttachShader(cloud_vs);
		cloud_prog.AttachShader(cloud_gs);
		cloud_prog.AttachShader(cloud_fs);
		cloud_prog.Link();
		cloud_prog.Use();

		// bind the VAO for the clouds
		clouds.Bind();

		// bind the VBO for the cloud positions
		pos_buffer.Bind(Buffer::Target::Array);
		{
			Buffer::Data(Buffer::Target::Array, positions);
			VertexAttribArray attr(cloud_prog, "position");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the cloud sizes
		size_buffer.Bind(Buffer::Target::Array);
		{
			Buffer::Data(Buffer::Target::Array, sizes);
			VertexAttribArray attr(cloud_prog, "size");
			attr.Setup(1, DataType::Float);
			attr.Enable();
		}

		// set the number of samples
		Uniform(cloud_prog, "n_samples").Set(int(samples));

		Texture::Active(0);
		Uniform(cloud_prog, "cloudTex").Set(0);
		for(size_t i=0, n=positions.size(); i!=n; ++i)
		{
			auto bound_tex = Bind(cloud_tex[i], Texture::Target::_3D);
			bound_tex.Image3D(
				images::Cloud(
					128, 128, 128,
					Vec3f(0.1f, -0.5f, 0.3f),
					0.5f
				)
			);
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.BorderColor(Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
			bound_tex.WrapS(TextureWrap::ClampToBorder);
			bound_tex.WrapT(TextureWrap::ClampToBorder);
			bound_tex.WrapR(TextureWrap::ClampToBorder);
		}

		gl.ClearColor(0.0f, 0.1f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Disable(Capability::DepthTest);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto perspective = CamMatrixf::Perspective(
			Degrees(24),
			double(width)/height,
			1, 100
		);
		cloud_prog.Use();
		Uniform(cloud_prog, "projectionMatrix").SetMatrix(perspective);
		light_prog.Use();
		Uniform(light_prog, "projectionMatrix").SetMatrix(perspective);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		auto lightPos = lightPath.Position(time * 0.05);
		auto cameraMatrix = CamMatrixf::Orbiting(
			Vec3f(),
			2.5f,
			Degrees(0),
			Degrees(std::sin(time * 0.3) * 80)
		);

		light.Bind();
		light_prog.Use();

		Uniform(light_prog, "lightPos").Set(lightPos);
		Uniform(light_prog, "cameraMatrix").SetMatrix(cameraMatrix);

		sphere_instr.Draw(sphere_indices);

		clouds.Bind();
		cloud_prog.Use();

		Uniform(cloud_prog, "lightPos").Set(lightPos);
		Uniform(cloud_prog, "cameraMatrix").SetMatrix(cameraMatrix);
		auto cameraPosition = cameraMatrix.Position();
		for(size_t i=0, n=positions.size(); i!=n; ++i)
		{
			auto viewMatrix = CamMatrixf::LookingAt(
				cameraPosition,
				positions[i]
			);
			Uniform(cloud_prog, "viewX").Set(
				Row<0>(cameraMatrix).xyz()
			);
			Uniform(cloud_prog, "viewY").Set(
				Row<1>(cameraMatrix).xyz()
			);
			Uniform(cloud_prog, "viewZ").Set(
				Row<2>(cameraMatrix).xyz()
			);
			cloud_tex[i].Bind(Texture::Target::_3D);
			gl.DrawArraysInstanced(
				PrimitiveType::Points,
				i, 1,
				samples
			);
		}
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new CloudExample);
}

} // namespace oglplus
