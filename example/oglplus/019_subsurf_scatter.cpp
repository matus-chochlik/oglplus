/**
 *  @example oglplus/019_subsurf_scatter.cpp
 *  @brief Shows how to draw a cube with a subsurface light scattering effect
 *
 *  @image html 019_subsurf_scatter.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>

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

	// VBOs for the cube's vertices and normals
	Buffer verts, normals;

	// number of instances of the cube that we are going to draw
	int inst_count;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , inst_count(32)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"uniform vec3 LightPos;"
			"uniform int InstCount;"
			"uniform int FrontFacing;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out float vertMult;"
			"out vec3 vertColor;"
			"out vec3 vertWrapNormal;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"void main(void)"
			"{"
			"	int inst = (FrontFacing != 0) ? "
			"		(InstCount - gl_InstanceID - 1):"
			"		gl_InstanceID;"
			"	vertMult = float(inst) / float(InstCount-1);"
			"	float sca = 1.0 - 0.3 * pow(vertMult, 2);"
			"	mat4 ScaleMatrix = mat4("
			"		sca, 0.0, 0.0, 0.0,"
			"		0.0, sca, 0.0, 0.0,"
			"		0.0, 0.0, sca, 0.0,"
			"		0.0, 0.0, 0.0, 1.0 "
			"	);"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ScaleMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"	vertColor = Normal;"
			"	vec3 wrap = Position.xyz - Normal;"
			"	vertWrapNormal = ("
			"		ModelMatrix * vec4("
			"			normalize(mix("
			"				Normal,"
			"				wrap,"
			"				mix(0.5, 1.0, vertMult)"
			"			)),"
			"			0.0"
			"		)"
			"	).xyz;"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLight = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix*Position"
			"	).xyz;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in float vertMult;"
			"in vec3 vertColor;"
			"in vec3 vertWrapNormal;"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"out vec4 fragColor;"
			"uniform int InstCount;"
			"void main(void)"
			"{"
			"	float l = dot(vertLight, vertLight);"
			"	float d = l > 0.0 ? dot("
			"		vertNormal, "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float s = max("
			"		dot(vertWrapNormal, vertLight)/l,"
			"		0.0"
			"	);"
			"	float intensity = clamp("
			"		0.2 + d * 3.0 + s * 5.5,"
			"		0.0,"
			"		1.0"
			"	);"
			"	fragColor = vec4("
			"		abs(vertColor) * intensity,"
			"		(2.5 + 1.5*d + 1.5*s) / InstCount"
			"	);"
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

		// bind the VBO for the cube vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the cube normals
		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}
		// the light position
		Uniform(prog, "LightPos").Set(Vec3f(-3.0f, -2.0f, -3.0f));
		// and the instance count
		Uniform(prog, "InstCount").Set(inst_count);
		//
		gl.ClearColor(0.5f, 0.6f, 0.5f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_cube.FaceWinding());
		gl.Enable(Capability::Blend);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform(prog, "ProjectionMatrix").SetMatrix(
			CamMatrixf::Perspective(
				Degrees(54),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		Uniform(prog, "CameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.0f,
				Degrees(time * 50),
				Degrees(SineWave(time / 16.0) * 80)
			)
		);
		// the model matrix
		Uniform(prog, "ModelMatrix").SetMatrix(
			ModelMatrixf::RotationY(Degrees(time * 25))
		);
		// draw 36 instances of the cube
		// first the back faces
		gl.CullFace(Face::Front);
		Uniform(prog, "FrontFacing").Set(0);
		cube_instr.Draw(cube_indices, inst_count);
		// then the front faces
		gl.CullFace(Face::Back);
		Uniform(prog, "FrontFacing").Set(1);
		cube_instr.Draw(cube_indices, inst_count);
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
