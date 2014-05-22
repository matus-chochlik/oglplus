/**
 *  @example standalone/020_oglplus_oalplus.cpp
 *  @brief Shows the usage of OGLplus and OALplus
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "glut_glew_example.hpp"

#include <oglplus/all.hpp>

#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/obj_mesh.hpp>
#include <oglplus/shapes/wrapper.hpp>

#include <oglplus/opt/resources.hpp>
#include <oglplus/opt/list_init.hpp>

#include <oglplus/images/random.hpp>

#include <oalplus/al.hpp>
#include <oalplus/alut.hpp>
#include <oalplus/all.hpp>

struct OGLOALExampleSource
{
	oglplus::Program prog;

	static oglplus::Program make_prog(void)
	{
		oglplus::VertexShader vs;
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"uniform vec3 SourcePosition;"

			"in vec4 Position;"

			"void main(void)"
			"{"
			"	vec4 TmpPos = Position;"
			"	TmpPos.xyz += SourcePosition;"
			"	gl_Position = ProjectionMatrix * CameraMatrix * TmpPos;"
			"}"
		).Compile();

		oglplus::FragmentShader fs;
		fs.Source(
			"#version 330\n"

			"out vec3 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec3(1, 1, 1);"
			"}"
		).Compile();

		oglplus::Program prog(oglplus::ObjectDesc("Source"));
		prog.AttachShader(vs).AttachShader(fs).Link().Use();

		return prog;
	}

	oglplus::Uniform<oglplus::Mat4f> projection_matrix;
	oglplus::Uniform<oglplus::Mat4f> camera_matrix;
	oglplus::Uniform<oglplus::Vec3f> light_position;

	oglplus::shapes::ShapeWrapper shape;

	static oglplus::shapes::ShapeWrapper create_source(void)
	{
		return oglplus::shapes::ShapeWrapper(
			oglplus::List("Position").Get(),
			oglplus::shapes::Sphere(1.0, 18, 12)
		);
	}

	oglplus::VertexArray vao;

	oalplus::ALUtilityToolkit alut;
	oalplus::Buffer sound_buffer;
	oalplus::Source sound;

	OGLOALExampleSource(void)
	 : prog(make_prog())
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , light_position(prog, "SourcePosition")
	 , shape(create_source())
	 , vao(shape.VAOForProgram(prog))
	 , alut(false)
	 , sound_buffer(alut.CreateBufferHelloWorld())
	{
		sound.Buffer(sound_buffer);
		sound.Looping(true);
		sound.ReferenceDistance(20);
		sound.Play();
	}
};

struct OGLOALExampleObjects
{
	oglplus::Context gl;
	oglplus::Program prog;

	static oglplus::Program make_prog(void)
	{
		oglplus::VertexShader vs;
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"uniform vec3 LightPosition;"

			"in vec4 Position;"
			"in vec3 Normal;"
			"in vec2 TexCoord;"

			"out vec3 vertNormal;"
			"out vec3 vertLightDir;"
			"out vec2 vertTexCoord;"

			"void main(void)"
			"{"
			"	gl_Position = ProjectionMatrix * CameraMatrix * Position;"
			"	vertNormal = Normal;"
			"	vertLightDir = LightPosition - Position.xyz;"
			"	vertTexCoord = TexCoord;"
			"}"
		).Compile();

		oglplus::FragmentShader fs;
		fs.Source(
			"#version 330\n"
			"uniform sampler2D RandTex;"

			"in vec3 vertNormal;"
			"in vec3 vertLightDir;"
			"in vec2 vertTexCoord;"

			"out vec3 fragColor;"
			"void main(void)"
			"{"
			"	vec3 Normal = normalize(vertNormal);"
			"	vec3 LightDir = normalize(vertLightDir);"
			"	float Ambient = 0.4;"
			"	float Diffuse = max(dot(Normal, LightDir), 0.0);"
			"	float x = texture(RandTex, vertTexCoord).r*"
			"		(0.6+texture(RandTex, vertTexCoord/9.0).r*0.4)*"
			"		(0.4+texture(RandTex, vertTexCoord/37.0).r*0.6);"
			"	vec3 Color = mix(vec3(0.4, 0.3, 0.2), vec3(1.0, 0.9, 0.8), x);"
			"	fragColor = Color*(Ambient+Diffuse);"
			"}"
		).Compile();

		oglplus::Program prog(oglplus::ObjectDesc("Object"));
		prog.AttachShader(vs).AttachShader(fs).Link().Use();

		return prog;
	}

	oglplus::Uniform<oglplus::Mat4f> projection_matrix;
	oglplus::Uniform<oglplus::Mat4f> camera_matrix;
	oglplus::Uniform<oglplus::Vec3f> light_position;

	oglplus::shapes::ShapeWrapper shape;

	static oglplus::shapes::ShapeWrapper load_objects(void)
	{
		std::ifstream input_stream;
		oglplus::OpenResourceFile(input_stream, "models", "monoliths", ".obj");
		if(!input_stream.good())
			throw std::runtime_error("Error opening file for reading");

		return oglplus::shapes::ShapeWrapper(
			oglplus::List("Position")("Normal")("TexCoord").Get(),
			oglplus::shapes::ObjMesh(
				input_stream,
				oglplus::shapes::ObjMesh::LoadingOptions()
			)
		);
	}

	oglplus::VertexArray vao;

	oglplus::Texture rand_tex;

	OGLOALExampleObjects(void)
	 : prog(make_prog())
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , light_position(prog, "LightPosition")
	 , shape(load_objects())
	 , vao(shape.VAOForProgram(prog))
	{
		using namespace oglplus;

		prog.Use();
		Uniform<GLint>(prog, "RandTex").Set(0);
		Texture::Active(0);

		rand_tex<< TextureTarget::_2D
			<< TextureMinFilter::LinearMipmapLinear
			<< TextureMagFilter::Linear
			<< TextureWrap::Repeat
			<< images::RandomRedUByte(2048, 2048)
			<< TextureMipmap()
		;
	}
};

class OGLOALExample
 : public oglplus::StandaloneExample
{
private:
	oglplus::Context gl;

	oalplus::Device al_device;
	oalplus::CurrentContext al;
	oalplus::Listener listener;

	OGLOALExampleSource source;

	OGLOALExampleObjects objects;

	oglplus::Query query;

	oglplus::Vec3f old_camera_position, camera_velocity;
	bool first_run;
public:
	OGLOALExample(int, const char**)
	 : al(al_device)
	 , first_run(true)
	{
		gl.ClearColor(0.9f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(oglplus::Capability::DepthTest);
	}

	void Reshape(void)
	{
		gl.Viewport(Width(), Height());

		oglplus::Mat4f projection =
			oglplus::CamMatrixf::PerspectiveX(
				oglplus::Degrees(110),
				Aspect(),
				1, 200
			);

		objects.prog.Use();
		objects.projection_matrix.Set(projection);
		source.prog.Use();
		source.projection_matrix.Set(projection);
	}

	void Render(void)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		double time = FrameTime();
		double crad = 3.0, trad = 10.0, lrad = 15.0;
		double ctime = time / 17.0;
		double ttime = time / 23.0;
		double ltime = time / 19.0;

		oglplus::Vec3f camera_position(
			+oglplus::SineWave(ctime)*crad,
			+oglplus::SineWave(time/9.0)+3.0,
			+oglplus::CosineWave(ctime)*crad
		);
		oglplus::Vec3f target_position(
			-oglplus::SineWave(ttime)*trad,
			-oglplus::CosineWave(time/17.0)+2.5,
			-oglplus::CosineWave(ttime)*trad
		);
		oglplus::Vec3f light_position(
			+oglplus::CosineWave(ltime)*lrad,
			+oglplus::CosineWave(time/19.0)+2.5,
			-oglplus::SineWave(ltime)*lrad
		);
		oglplus::Mat4f camera =
			oglplus::CamMatrixf::LookingAt(
				camera_position,
				target_position
			);

		listener.Position(camera_position);
		listener.Velocity(camera_velocity);
		listener.Orientation(
			target_position-
			camera_position,
			oalplus::Vec3f(0.0, 1.0, 0.0)
		);

		objects.prog.Use();
		objects.camera_matrix.Set(camera);
		objects.light_position.Set(light_position);

		objects.vao.Bind();
		objects.shape.Draw();

		oglplus::Query::Activator qa(
			query,
			oglplus::Query::Target::SamplesPassed
		);

		source.prog.Use();
		source.camera_matrix.Set(camera);
		source.light_position.Set(light_position);
		source.sound.Position(light_position);

		source.vao.Bind();
		source.shape.Draw();

		qa.Finish();

		GLuint sp = 0;
		query.WaitForResult(sp);

		double sound_gain = double(sp)/300.0;
		sound_gain = 0.2 + 0.8*sound_gain;
		if(sound_gain > 1.0) sound_gain = 1.0;
		source.sound.Gain(sound_gain);

		if(first_run)
		{
			first_run = false;
		}
		else
		{
			camera_velocity = camera_position - old_camera_position;
			old_camera_position = camera_position;
		}
	}
};

int main(int argc, char* argv[])
{
	return oglplus::GlutGlewMain<OGLOALExample>(
		"The usage of OGLplus with OALplus",
		argc, argv
	);
}

