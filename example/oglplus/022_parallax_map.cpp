/**
 *  @example oglplus/022_parallax_map.cpp
 *  @brief Shows how to achieve a simple view parallax effect on a checker cube
 *
 *  @image html 022_parallax_map.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/images/sphere_bmap.hpp>
#include <oglplus/bound/buffer.hpp>
#include <oglplus/bound/texture.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CubeExample : public Example
{
private:
	// helper object building cube vertex attributes
	shapes::Cube make_cube;
	// helper object encapsulating cube drawing instructions
	shapes::DrawingInstructions cube_instr;
	// indices pointing to cube primitive elements
	shapes::Cube::IndexArray cube_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertex attributes
	Buffer verts, normals, tangents, texcoords;

	// The bumpmap texture
	Texture bumpTex;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"uniform vec3 lightPos;"
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
			"		vec4(lightPos, 1.0)-"
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
			"	float depth = texture(bumpTex, fragTexC).w;"
			"	float maxOffs = min((depth*depthMult)/(-viewTgtN.z), 1.0);"
			"	vec3 viewOffs = vec3(0.0, 0.0, 0.0);"
			"	vec2 offsTexC = fragTexC + viewOffs.xy;"
			"	while(length(viewOffs) < maxOffs)"
			"	{"
			"		if(offsTexC.x <= 0.0 || offsTexC.x >= 1.0)"
			"			break;"
			"		if(offsTexC.y <= 0.0 || offsTexC.y >= 1.0)"
			"			break;"
			"		if(depth*depthMult*perp <= -viewOffs.z)"
			"			break;"
			"		viewOffs += sampleStep;"
			"		offsTexC = fragTexC + viewOffs.xy;"
			"		prevD = depth;"
			"		depth = texture(bumpTex, offsTexC).w;"
			"	}"
			"	offsTexC = vec2("
			"		clamp(offsTexC.x, 0.0, 1.0),"
			"		clamp(offsTexC.y, 0.0, 1.0) "
			"	);"
			"	float b = ("
			"		1 +"
			"		int(offsTexC.x*16) % 2+"
			"		int(offsTexC.y*16) % 2"
			"	) % 2;"
			"	vec3 c = vec3(b, b, b);"
			"	vec3 n = texture(bumpTex, offsTexC).xyz;"
			"	vec3 finalNormal = normalMatrix * n;"
			"	float l = length(fragLight);"
			"	float d = (l != 0.0) ?"
			"		dot(fragLight, finalNormal)/l:"
			"		0.0;"
			"	float i = 0.1 + 1.5*clamp(d, 0.0, 1.0);"
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

		// bind the VAO for the cube
		cube.Bind();

		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "vertex");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		tangents.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Tangents(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "tangent");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "texcoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		{
			Texture::Active(0);
			Uniform(prog, "bumpTex").Set(0);
			auto bound_tex = Bind(bumpTex, Texture::Target::_2D);
			{
				auto img = images::SphereBumpMap(512, 512, 2, 2);
				bound_tex.Image2D(img);
				Uniform(prog, "bumpTexWidth").Set(img.Width());
				Uniform(prog, "bumpTexHeight").Set(img.Height());
			}
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}
		//
		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);

		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_cube.FaceWinding());
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform(prog, "projectionMatrix").SetMatrix(
			CamMatrixf::Perspective(
				Degrees(24),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		auto lightAzimuth = FullCircles(time * -0.5);
		Uniform(prog, "lightPos").Set(
			Vec3f(
				-Cos(lightAzimuth),
				1.0f,
				-Sin(lightAzimuth)
			) * 2.0f
		);
		//
		Uniform(prog, "cameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				1.5f,
				Degrees(-45),
				Degrees(std::sin(time * 0.2) * 70)
			)
		);

		// set the model matrix
		Uniform(prog, "modelMatrix").SetMatrix(
			ModelMatrixf::RotationA(
				Vec3f(1.0f, 1.0f, 1.0f),
				FullCircles(-time * 0.05)
			)
		);

		cube.Bind();
		gl.CullFace(Face::Back);
		cube_instr.Draw(cube_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus
