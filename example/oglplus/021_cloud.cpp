/**
 *  @example oglplus/021_cloud.cpp
 *  @brief Shows how to render a cloud using a geometry shader and a 3d texture
 *
 *  @oglplus_screenshot{021_cloud}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_gl{GL_VERSION_3_0}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <oglplus/bound/texture.hpp>
#include <oglplus/images/cloud.hpp>

#include "example.hpp"

namespace oglplus {

class CloudExample : public Example
{
private:
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

	// Uniforms
	LazyUniform<Mat4f> projection_matrix, camera_matrix;

	VertexArray clouds;
	Buffer buffer;

	Texture cloud_tex;
public:
	CloudExample(void)
	 : projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	{
		// Set the vertex shader source

		vs.Source(
			"#version 330\n"
			"in vec4 Position;"
			"uniform mat4 CameraMatrix;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		CameraMatrix *"
			"		Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// Set the geometry shader source
		gs.Source(
			"#version 330\n"
			"layout(points) in;"
			"layout(triangle_strip, max_vertices = 100) out;"
			"const int p = 25;"
			"const float hp = (p-1)*0.5;"
			"uniform vec3 LightPos;"
			"uniform mat4 CameraMatrix, ProjectionMatrix;"
			"out vec3 geomTexCoord;"
			"out vec3 geomLightDir;"
			"void main(void)"
			"{"
			"	float s = 0.6;"
			"	float yo[2] = float[2](-1.0, 1.0);"
			"	float xo[2] = float[2](-1.0, 1.0);"
			"	vec3 cx = vec3("
			"		CameraMatrix[0][0],"
			"		CameraMatrix[1][0],"
			"		CameraMatrix[2][0] "
			"	);"
			"	vec3 cy = vec3("
			"		CameraMatrix[0][1],"
			"		CameraMatrix[1][1],"
			"		CameraMatrix[2][1] "
			"	);"
			"	vec3 cz = vec3("
			"		CameraMatrix[0][2],"
			"		CameraMatrix[1][2],"
			"		CameraMatrix[2][2] "
			"	);"
			"	for(int k=0;k!=p;++k)"
			"	{"
			"		for(int j=0;j!=2;++j)"
			"		for(int i=0;i!=2;++i)"
			"		{"
			"			float zo = ((k - hp) / hp);"
			"			float xoffs = xo[i]*s;"
			"			float yoffs = yo[j]*s;"
			"			float zoffs = zo   *s;"
			"			vec4 v = vec4("
			"				gl_in[0].gl_Position.x+xoffs,"
			"				gl_in[0].gl_Position.y+yoffs,"
			"				gl_in[0].gl_Position.z+zoffs,"
			"				1.0"
			"			);"
			"			gl_Position = ProjectionMatrix * v;"
			"			geomLightDir = LightPos - v.xyz;"
			"			geomTexCoord = "
			"				vec3(0.5, 0.5, 0.5)+"
			"				cx*(xo[i])*0.707+"
			"				cy*(yo[j])*0.707+"
			"				cz*(zo   )*0.707;"
			"			EmitVertex();"
			"		}"
			"		EndPrimitive();"
			"	}"
			"}"
		);
		// compile it
		gs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform sampler3D cloudTex;"
			"in vec3 geomTexCoord;"
			"in vec3 geomLightDir;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float d = texture(cloudTex, geomTexCoord).r;"
			"	float o = 1.0;"
			"	float s = 2.0/128.0;"
			"	float r = s * 8.0;"
			"	vec3 sampleOffs = normalize(geomLightDir) * s;"
			"	vec3 samplePos = geomTexCoord;"
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
			"	float a = 0.2 * d;"
			"	float i = mix(0.4, 1.0, o);"
			"	fragColor = vec4(i, i, i, a);"
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

		// bind the VAO for the clouds
		clouds.Bind();

		// bind the VBO for the cloud positions
		buffer.Bind(Buffer::Target::Array);
		{
			GLfloat positions[3] = {0.5f, 0.1f, 0.2f};
			Buffer::Data(Buffer::Target::Array, 3, positions);
			VertexAttribArray attr(prog, "Position");
			attr.Setup<Vec3f>();
			attr.Enable();
		}

		{
			Texture::Active(0);
			UniformSampler(prog, "cloudTex").Set(0);
			auto bound_tex = Bind(cloud_tex, Texture::Target::_3D);
			bound_tex.Image3D(images::Cloud(128, 128, 128));
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.BorderColor(Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
			bound_tex.WrapS(TextureWrap::ClampToBorder);
			bound_tex.WrapT(TextureWrap::ClampToBorder);
			bound_tex.WrapR(TextureWrap::ClampToBorder);
		}

		Uniform<Vec3f>(prog, "LightPos").Set(Vec3f(10.0f, 1.0f, 5.0f));

		gl.ClearColor(0.2f, 0.3f, 0.4f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(60),
				double(width)/height,
				1, 80
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				3.5 + SineWave(time / 6.0)*0.5,
				FullCircles(time * 0.2),
				Degrees(SineWave(time / 20.0) * 80)
			)
		);
		gl.DrawArrays(PrimitiveType::Points, 0, 1);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

void setupExample(ExampleParams& /*params*/){ }

std::unique_ptr<ExampleThread> makeExampleThread(
	Example& /*example*/,
	unsigned /*thread_id*/,
	const ExampleParams& /*params*/
){ return std::unique_ptr<ExampleThread>(); }

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new CloudExample);
}

} // namespace oglplus
