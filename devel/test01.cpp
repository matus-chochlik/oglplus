/**
 *  .file devel/test01.cpp
 *  Development / testing file.
 *  NOTE. this file is here for feature development / testing purposes only
 *  and its source code, input, output can change witout prior notice.
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/torus.hpp>
#include <oglplus/bound/buffer.hpp>
#include <oglplus/bound/texture.hpp>

#include <iostream>

#include <oglplus/images/random.hpp>
#include <oglplus/images/newton.hpp>
#include <oglplus/images/load.hpp>
#include <oglplus/images/sphere_bmap.hpp>
#include <oglplus/images/normal_map.hpp>

#include <cmath>

#include "test.hpp"

namespace oglplus {
namespace images {

} // namespace images


class Test01 : public Test
{
private:
	typedef shapes::Cube Shape;
	//typedef shapes::Sphere Shape;
	//typedef shapes::Torus Shape;
	//
	Shape shape;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered shape
	VertexArray vao;

	static const size_t n_vert_array = 4;
	// VBOs for the shape's vertices and normals
	Array<Buffer> vert_array;

	// textures for the shape
	Texture color_tex, bump_tex;
public:
	Test01(void)
	 : vert_array(n_vert_array)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"in vec4 vertex;"
			"in vec3 normal;"
			"in vec3 tangent;"
			"in vec2 texcoord;"
			"out vec3 fragEye;"
			"out vec3 fragLight;"
			"out vec3 fragNormal;"
			"out vec2 fragTexC;"
			"out vec3 viewTgt;"
			"out mat3 normalMatrix;"
			"const vec4 lightPos = vec4(1.0, 2.0, 3.0, 1.0);"
			"void main(void)"
			"{"
			"	vec4 vertEye = "
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
			"	fragEye = vertEye.xyz;"
			"	vec3 fragTangent = ("
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vec4(tangent, 0.0)"
			"	).xyz;"
			"	fragNormal = ("
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	fragLight = ("
			"		cameraMatrix *"
			"		lightPos-"
			"		vertEye"
			"	).xyz;"
			"	normalMatrix = mat3("
			"		fragTangent,"
			"		cross(fragNormal, fragTangent),"
			"		fragNormal"
			"	);"
			"	viewTgt = vec3("
			"		dot(normalMatrix[0], vertEye.xyz),"
			"		dot(normalMatrix[1], vertEye.xyz),"
			"		dot(normalMatrix[2], vertEye.xyz) "
			"	);"
			"	fragTexC = texcoord;"
			"	gl_Position = projectionMatrix *"
			"		vertEye;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform sampler2D colorTex;"
			"uniform sampler2D bumpTex;"
			"uniform int bumpTexWidth;"
			"uniform int bumpTexHeight;"
			"float depthMult = 0.1;"
			"in vec3 fragEye;"
			"in vec3 fragLight;"
			"in vec3 fragNormal;"
			"in vec2 fragTexC;"
			"in vec3 viewTgt;"
			"in mat3 normalMatrix;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	vec3 viewTgtN = normalize(viewTgt);"
			"	float perp = -dot(normalize(fragEye), fragNormal);"
			"	float sampleInterval = 1.0/length("
			"		vec2(bumpTexWidth, bumpTexHeight)"
			"	);"
			"	vec3 sampleStep = viewTgtN*sampleInterval;"
			"	float prevD = 0.0;"
			"	float depth = texture2D(bumpTex, fragTexC).w;"
			"	float maxOffs = min((depth*depthMult*perp)/(-viewTgtN.z), 1.0);"
			"	vec3 viewOffs = vec3(0.0, 0.0, 0.0);"
			"	vec2 offsTexC = fragTexC + viewOffs.xy;"
			"	while(length(viewOffs) < maxOffs)"
			"	{"
/*
			"		if(offsTexC.x <= 0.0 || offsTexC.x >= 1.0)"
			"			discard;"
			"		if(offsTexC.y <= 0.0 || offsTexC.y >= 1.0)"
			"			discard;"
*/
			"		if(depth*depthMult*perp <= -viewOffs.z)"
			"			break;"
			"		viewOffs += sampleStep;"
			"		offsTexC = fragTexC + viewOffs.xy;"
			"		prevD = depth;"
			"		depth = texture2D(bumpTex, offsTexC).w;"
			"	}"
			"	vec3 c = texture2D(colorTex, offsTexC).xyz;"
			"	vec3 n = texture2D(bumpTex, offsTexC).xyz;"
			"	vec3 finalNormal = normalMatrix * n;"
			"	float l = length(fragLight);"
			"	float d = (l != 0.0) ?"
			"		dot(fragLight, finalNormal)/l:"
			"		0.0;"
			"	float i = 0.2 + 1.5*clamp(d, 0.0, 1.0);"
			"	fragColor = vec4(c*i, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the shape
		vao.Bind();

		typedef GLuint (Shape::*DataFunc)(std::vector<GLfloat>&) const;
		DataFunc data_fn[n_vert_array] = {
			&Shape::Vertices,
			&Shape::Normals,
			&Shape::Tangents,
			&Shape::TexCoordinates
		};

		const char* attr_name[n_vert_array] = {
			"vertex",
			"normal",
			"tangent",
			"texcoord"
		};

		for(size_t a=0; a!=n_vert_array; ++a)
		try {
			std::vector<GLfloat> data;
			GLuint n_per_vertex = (shape.*data_fn[a])(data);
			Bind(vert_array[a], Buffer::Target::Array).Data(data);
			VertexAttribArray attr(prog, attr_name[a]);
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		} catch(...) { }

		// setup the textures
		try {
			Texture::Active(0);
			Uniform(prog, "colorTex").Set(0);
			auto bound_tex = Bind(color_tex, Texture::Target::_2D);
			//bound_tex.Image2D(images::SphereBumpMap(512, 512));
			//bound_tex.Image2D(images::LoadTexture("stones"));
			bound_tex.Image2D(images::LoadTexture("wooden_crate"));
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		} catch(...) { }
		try {
			Texture::Active(1);
			Uniform(prog, "bumpTex").Set(1);
			auto bound_tex = Bind(bump_tex, Texture::Target::_2D);
			try {
				//auto image = images::SphereBumpMap(512, 512, 7, 16);
				//auto image = images::NormalMap(images::LoadTexture("stones-hmap"));
				auto image = images::NormalMap(images::LoadTexture("wooden_crate-hmap"));
				bound_tex.Image2D(image);
				Uniform(prog, "bumpTexWidth").Set(image.Width());
				Uniform(prog, "bumpTexHeight").Set(image.Height());
			} catch(...) { }
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		} catch(...) { }

		// set the projection matrix fov = 24 deg. aspect = 1.25
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(Degrees(24), 1.25, 1, 100)
		);
		//
		VertexArray::Unbind();
		gl.ClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		//
		gl.FrontFace(shape.FaceWinding());
		gl.CullFace(Face::Back);
		gl.Enable(Capability::CullFace);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				//4.5 + std::sin(time)*3.0,
				2.5,
				FullCircles(-time * 0.2),
				Degrees(std::sin(time * 0.2) * 70)
			)
		);

		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::RotationA(
				Vec3f(1.0, 1.0, 1.0),
				FullCircles(time * 0.2)
			)
		);

		vao.Bind();
		// This is not very effective
		shape.Instructions().Draw(shape.Indices());
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Test> makeTest(void)
{
	return std::unique_ptr<Test>(new Test01);
}

} // namespace oglplus
