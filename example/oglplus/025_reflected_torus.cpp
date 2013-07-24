/**
 *  @example oglplus/025_reflected_torus.cpp
 *  @brief Shows how to draw a torus reflected in a horizontal plane
 *
 *  @oglplus_screenshot{025_reflected_torus}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_cxx11{FUNCTION_TEMPLATE_DEFAULT_ARGS}
 *
 *  @oglplus_example_uses_gl{GL_VERSION_4_1}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/opt/smart_enums.hpp>
#include <oglplus/shapes/twisted_torus.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class ReflectionExample : public Example
{
private:
	// the torus vertex attribute builder
	shapes::TwistedTorus make_torus;
	// here will be stored the indices used by the drawing instructions
	shapes::TwistedTorus::IndexArray torus_indices;
	// the instructions for drawing the torus
	shapes::DrawingInstructions torus_instr;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shaders for the normally rendered and the reflected objects
	VertexShader vs_norm;
	VertexShader vs_refl;

	// Geometry shader for the reflected objects
	GeometryShader gs_refl;

	// Fragment shader
	FragmentShader fs;

	// Programs
	Program prog_norm;
	Program prog_refl;

	// A vertex array object for the torus
	VertexArray torus;
	// A vertex array object for the reflective plane
	VertexArray plane;

	// VBOs for the torus' vertices and normals
	Buffer torus_verts, torus_normals;
	// VBOs for the plane's vertices and normals
	Buffer plane_verts, plane_normals;
public:
	ReflectionExample(void)
	 : torus_indices(make_torus.Indices())
	 , torus_instr(make_torus.Instructions())
	 , vs_norm(ObjectDesc("Vertex-Normal"))
	 , vs_refl(ObjectDesc("Vertex-Reflection"))
	 , gs_refl(ObjectDesc("Geometry-Reflection"))
	{
		namespace se = oglplus::smart_enums;
		// Set the normal object vertex shader source
		vs_norm.Source(
			"#version 330\n"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 geomColor;"
			"out vec3 geomNormal;"
			"out vec3 geomLight;"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"uniform vec3 LightPos;"
			"void main(void)"
			"{"
			"	gl_Position = ModelMatrix * Position;"
			"	geomColor = Normal;"
			"	geomNormal = mat3(ModelMatrix)*Normal;"
			"	geomLight = LightPos-gl_Position.xyz;"
			"	gl_Position = ProjectionMatrix * CameraMatrix * gl_Position;"
			"}"
		);
		// compile it
		vs_norm.Compile();

		// Set the reflected object vertex shader source
		// which just passes data to the geometry shader
		vs_refl.Source(
			"#version 330\n"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertNormal;"
			"void main(void)"
			"{"
			"	gl_Position = Position;"
			"	vertNormal = Normal;"
			"}"
		);
		// compile it
		vs_refl.Compile();

		// Set the reflected object geometry shader source
		// This shader creates a reflection matrix that
		// relies on the fact that the reflection is going
		// to be done by the y-plane
		gs_refl.Source(
			"#version 330\n"
			"layout(triangles) in;"
			"layout(triangle_strip, max_vertices = 6) out;"

			"in vec3 vertNormal[];"

			"uniform mat4 ProjectionMatrix;"
			"uniform mat4 CameraMatrix;"
			"uniform mat4 ModelMatrix;"

			"out vec3 geomColor;"
			"out vec3 geomNormal;"
			"out vec3 geomLight;"
			"uniform vec3 LightPos;"

			"mat4 ReflectionMatrix = mat4("
			"	1.0, 0.0, 0.0, 0.0,"
			"	0.0,-1.0, 0.0, 0.0,"
			"	0.0, 0.0, 1.0, 0.0,"
			"	0.0, 0.0, 0.0, 1.0 "
			");"
			"void main(void)"
			"{"
			"	for(int v=0; v!=gl_in.length(); ++v)"
			"	{"
			"		vec4 Position = gl_in[v].gl_Position;"
			"		gl_Position = ModelMatrix * Position;"
			"		geomColor = vertNormal[v];"
			"		geomNormal = mat3(ModelMatrix)*vertNormal[v];"
			"		geomLight = LightPos - gl_Position.xyz;"
			"		gl_Position = "
			"			ProjectionMatrix *"
			"			CameraMatrix *"
			"			ReflectionMatrix *"
			"			gl_Position;"
			"		EmitVertex();"
			"	}"
			"	EndPrimitive();"
			"}"
		);
		// compile it
		gs_refl.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"in vec3 geomColor;"
			"in vec3 geomNormal;"
			"in vec3 geomLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(geomLight);"
			"	float d = l > 0.0 ? dot("
			"		geomNormal, "
			"		normalize(geomLight)"
			"	 ) / l : 0.0;"
			"	float i = 0.2 + max(d, 0.0) * 2.0;"
			"	fragColor = vec4(abs(geomNormal)*i, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the normal rendering program
		prog_norm.AttachShader(vs_norm);
		prog_norm.AttachShader(fs);
		// link it
		prog_norm.Link();

		// attach the shaders to the reflection rendering program
		prog_refl.AttachShader(vs_refl);
		prog_refl.AttachShader(gs_refl);
		prog_refl.AttachShader(fs);
		// link it
		prog_refl.Link();

		// bind the VAO for the torus
		torus.Bind();

		// bind the VBO for the torus vertices
		torus_verts.Bind(se::Array());
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Positions(data);
			// upload the data
			Buffer::Data(se::Array(), data);

			// setup the vertex attribs array for the vertices
			typedef VertexAttribArray VAA;
			VertexAttribSlot
				loc_norm = VAA::GetLocation(prog_norm, "Position"),
				loc_refl = VAA::GetLocation(prog_refl, "Position");

			assert(loc_norm == loc_refl);
			VertexAttribArray attr(loc_norm);
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		// bind the VBO for the torus normals
		torus_normals.Bind(se::Array());
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Normals(data);
			// upload the data
			Buffer::Data(se::Array(), data);

			// setup the vertex attribs array for the normals
			typedef VertexAttribArray VAA;
			VertexAttribSlot
				loc_norm = VAA::GetLocation(prog_norm, "Normal"),
				loc_refl = VAA::GetLocation(prog_refl, "Normal");

			assert(loc_norm == loc_refl);
			VertexAttribArray attr(loc_norm);
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		// bind the VAO for the plane
		plane.Bind();

		// bind the VBO for the plane vertices
		plane_verts.Bind(se::Array());
		{
			GLfloat data[4*3] = {
				-2.0f, 0.0f,  2.0f,
				-2.0f, 0.0f, -2.0f,
				 2.0f, 0.0f,  2.0f,
				 2.0f, 0.0f, -2.0f
			};
			// upload the data
			Buffer::Data(se::Array(), 4*3, data);
			// setup the vertex attribs array for the vertices
			prog_norm.Use();
			VertexAttribArray attr(prog_norm, "Position");
			attr.Setup<Vec3f>();
			attr.Enable();
		}

		// bind the VBO for the torus normals
		plane_normals.Bind(se::Array());
		{
			GLfloat data[4*3] = {
				-0.1f, 1.0f,  0.1f,
				-0.1f, 1.0f, -0.1f,
				 0.1f, 1.0f,  0.1f,
				 0.1f, 1.0f, -0.1f
			};
			// upload the data
			Buffer::Data(se::Array(), 4*3, data);
			// setup the vertex attribs array for the normals
			prog_norm.Use();
			VertexAttribArray attr(prog_norm, "Normal");
			attr.Setup<Vec3f>();
			attr.Enable();
		}
		VertexArray::Unbind();

		Vec3f lightPos(2.0f, 2.0f, 3.0f);
		prog_norm.Use();
		SetUniform(prog_norm, "LightPos", lightPos);
		prog_refl.Use();
		SetUniform(prog_refl, "LightPos", lightPos);
		//
		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.ClearStencil(0);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		Mat4f projection = CamMatrixf::PerspectiveX(
			Degrees(65),
			double(width)/height,
			1, 40
		);
		SetProgramUniform(prog_norm, "ProjectionMatrix", projection);
		SetProgramUniform(prog_refl, "ProjectionMatrix", projection);
	}

	void Render(double time)
	{
		namespace se = oglplus::smart_enums;
		gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();
		// make the camera matrix orbiting around the origin
		// at radius of 3.5 with elevation between 15 and 90 degrees
		Mat4f camera = CamMatrixf::Orbiting(
			Vec3f(),
			6.5,
			Degrees(time * 135),
			Degrees(15 + (-SineWave(0.25+time/12.5)+1.0)*0.5*75)
		);
		ModelMatrixf model = ModelMatrixf::Translation(0.0f, 1.5f, 0.0);
		ModelMatrixf identity;
		//
		SetProgramUniform(prog_norm, "CameraMatrix", camera);
		SetProgramUniform(prog_refl, "CameraMatrix", camera);
		// draw the plane into the stencil buffer
		prog_norm.Use();

		gl.Disable(se::Blend());
		gl.Disable(se::DepthTest());
		gl.Enable(se::StencilTest());
		gl.ColorMask(false, false, false, false);
		gl.StencilFunc(se::Always(), 1, 1);
		gl.StencilOp(se::Keep(), se::Keep(), se::Replace());

		Uniform<Mat4f> model_matrix_norm(prog_norm, "ModelMatrix");
		model_matrix_norm.Set(identity);
		plane.Bind();
		gl.DrawArrays(se::TriangleStrip(), 0, 4);

		gl.ColorMask(true, true, true, true);
		gl.Enable(se::DepthTest());
		gl.StencilFunc(se::Equal(), 1, 1);
		gl.StencilOp(se::Keep(), se::Keep(), se::Keep());

		// draw the torus using the reflection program
		prog_refl.Use();
		Uniform<Mat4f>(prog_refl, "ModelMatrix").Set(model);
		torus.Bind();
		torus_instr.Draw(torus_indices);

		gl.Disable(se::StencilTest());

		prog_norm.Use();
		// draw the torus using the normal object program
		model_matrix_norm.Set(model);
		torus_instr.Draw(torus_indices);

		// blend-in the plane
		gl.Enable(se::Blend());
		gl.BlendEquation(se::Max());
		model_matrix_norm.Set(identity);
		plane.Bind();
		gl.DrawArrays(se::TriangleStrip(), 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
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
	return std::unique_ptr<Example>(new ReflectionExample);
}

} // namespace oglplus
