/**
 *  @example oglplus/016_metallic_torus.cpp
 *  @brief Shows how to draw a metallic-looking torus
 *
 *  @oglplus_screenshot{016_metallic_torus}
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/torus.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class TorusExample : public Example
{
private:
	// helper object building torus vertex attributes
	shapes::Torus make_torus;
	// helper object encapsulating torus drawing instructions
	shapes::DrawingInstructions torus_instr;
	// indices pointing to torus primitive elements
	shapes::Torus::IndexArray torus_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// Uniforms
	LazyUniform<Mat4f> projection_matrix, camera_matrix, model_matrix;

	// A vertex array object for the rendered torus
	VertexArray torus;

	// VBOs for the torus's vertices and normals
	Buffer verts, normals;
public:
	TorusExample(void)
	 : make_torus(1.0, 0.5, 72, 48)
	 , torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , model_matrix(prog, "ModelMatrix")
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertNormal;"
			"void main(void)"
			"{"
			"	vertNormal = ("
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform int ColorCount;"
			"uniform vec4 Color[8];"
			"in vec3 vertNormal;"
			"vec3 ViewDir = vec3(0.0, 0.0, 1.0);"
			"vec3 TopDir = vec3(0.0, 1.0, 0.0);"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float k = dot(vertNormal, ViewDir);"
			"	vec3 reflDir = 2.0*k*vertNormal - ViewDir;"
			"	float a = dot(reflDir, TopDir);"
			"	vec3 reflColor;"
			"	for(int i = 0; i != (ColorCount - 1); ++i)"
			"	{"
			"		if(a<Color[i].a && a>=Color[i+1].a)"
			"		{"
			"			float m = "
			"				(a - Color[i].a)/"
			"				(Color[i+1].a-Color[i].a);"
			"			reflColor = mix("
			"				Color[i].rgb,"
			"				Color[i+1].rgb,"
			"				m"
			"			);"
			"			break;"
			"		}"
			"	}"
			"	float i = max(dot(vertNormal, TopDir), 0.0);"
			"	vec3 diffColor = vec3(i, i, i);"
			"	fragColor = vec4("
			"		mix(reflColor, diffColor, 0.3 + i*0.7),"
			"		1.0"
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

		// bind the VAO for the torus
		torus.Bind();

		// bind the VBO for the torus vertices
		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Positions(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the torus normals
		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the color gradient
		Uniform<GLint>(prog, "ColorCount").Set(8);
		Uniform<Vec4f>(prog, "Color[0]").Set(1.0f, 1.0f, 0.9f, 1.00f);
		Uniform<Vec4f>(prog, "Color[1]").Set(1.0f, 0.9f, 0.8f, 0.97f);
		Uniform<Vec4f>(prog, "Color[2]").Set(0.9f, 0.7f, 0.5f, 0.95f);
		Uniform<Vec4f>(prog, "Color[3]").Set(0.5f, 0.5f, 1.0f, 0.95f);
		Uniform<Vec4f>(prog, "Color[4]").Set(0.2f, 0.2f, 0.7f, 0.00f);
		Uniform<Vec4f>(prog, "Color[5]").Set(0.1f, 0.1f, 0.1f, 0.00f);
		Uniform<Vec4f>(prog, "Color[6]").Set(0.2f, 0.2f, 0.2f,-0.10f);
		Uniform<Vec4f>(prog, "Color[7]").Set(0.5f, 0.5f, 0.5f,-1.00f);

		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_torus.FaceWinding());
		gl.CullFace(Face::Back);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(60),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				2.5,
				Degrees(time * 35),
				Degrees(SineWave(time / 60.0) * 80)
			)
		);
		// set the model matrix
		model_matrix.Set(
			ModelMatrixf::RotationX(FullCircles(time * 0.25))
		);

		torus_instr.Draw(torus_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new TorusExample);
}

} // namespace oglplus
