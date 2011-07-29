/**
 *  @example oglplus/025_reflected_torus.cpp
 *  @brief Shows how to draw a torus reflected in a horizontal plane
 *
 *  @image html 025_reflected_torus.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/torus.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class ReflectionExample : public Example
{
private:
	// the torus vertex attribute builder
	shapes::Torus make_torus;
	// here will be stored the indices used by the drawing instructions
	shapes::Torus::IndexArray torus_indices;
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
	 : torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	{
		// Set the normal object vertex shader source
		vs_norm.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out vec3 vertNormal;"
			"out vec3 fragNormal;"
			"out vec3 fragLight;"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"uniform vec3 lightPos;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
			"	vertNormal = normal;"
			"	fragNormal = ("
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	fragLight = ("
			"		vec4(lightPos, 0.0)-"
			"		modelMatrix*vertex"
			"	).xyz;"
			"}"
		);
		// compile it
		vs_norm.Compile();

		// Set the reflected object vertex shader source
		// which just passes data to the geometry shader
		vs_refl.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out vec3 geomNormal;"
			"void main(void)"
			"{"
			"	gl_Position = vertex;"
			"	geomNormal = normal;"
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

			"in vec3 geomNormal[];"

			"uniform mat4 projectionMatrix;"
			"uniform mat4 cameraMatrix;"
			"uniform mat4 modelMatrix;"

			"out vec3 vertNormal;"
			"out vec3 fragNormal;"
			"out vec3 fragLight;"
			"uniform vec3 lightPos;"

			"mat4 reflectionMatrix = mat4("
			"	1.0, 0.0, 0.0, 0.0,"
			"	0.0,-1.0, 0.0, 0.0,"
			"	0.0, 0.0, 1.0, 0.0,"
			"	0.0, 0.0, 0.0, 1.0 "
			");"
			"void main(void)"
			"{"
			"	for(int v=0; v!=gl_in.length(); ++v)"
			"	{"
			"		vec4 vertex = gl_in[v].gl_Position;"
			"		gl_Position = "
			"			projectionMatrix *"
			"			cameraMatrix *"
			"			reflectionMatrix *"
			"			modelMatrix *"
			"			vertex;"
			"		vertNormal = geomNormal[v];"
			"		fragNormal = ("
			"			modelMatrix *"
			"			vec4(vertNormal, 0.0)"
			"		).xyz;"
			"		fragLight = ("
			"			vec4(lightPos, 0.0)-"
			"			modelMatrix * vertex"
			"		).xyz;"
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
			"in vec3 vertNormal;"
			"in vec3 fragNormal;"
			"in vec3 fragLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = dot(fragLight, fragLight);"
			"	float d = max(dot(fragNormal, fragLight)/l,0.0);"
			"	float i = clamp(0.2 + d * 2.0, 0.0, 1.0);"
			"	fragColor = vec4(abs(vertNormal)*i, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the normal rendering program
		prog_norm.AttachShader(vs_norm);
		//prog_norm.AttachShader(gs);
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
		torus_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			prog_norm.Use();
			VertexAttribArray attr_n(prog_norm, "vertex");
			attr_n.Setup(n_per_vertex, DataType::Float);
			attr_n.Enable();
			//
			prog_refl.Use();
			VertexAttribArray attr_r(prog_refl, "vertex");
			attr_r.Setup(n_per_vertex, DataType::Float);
			attr_r.Enable();
		}

		// bind the VBO for the torus normals
		torus_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the normals
			prog_norm.Use();
			VertexAttribArray attr_n(prog_norm, "normal");
			attr_n.Setup(n_per_vertex, DataType::Float);
			attr_n.Enable();
			//
			prog_refl.Use();
			VertexAttribArray attr_r(prog_refl, "normal");
			attr_r.Setup(n_per_vertex, DataType::Float);
			attr_r.Enable();
		}

		// bind the VAO for the plane
		plane.Bind();

		// bind the VBO for the plane vertices
		plane_verts.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-2.0f, 0.0f,  2.0f,
				-2.0f, 0.0f, -2.0f,
				 2.0f, 0.0f,  2.0f,
				 2.0f, 0.0f, -2.0f
			};
			// upload the data
			Buffer::Data(Buffer::Target::Array, data, 4*3);
			// setup the vertex attribs array for the vertices
			prog_norm.Use();
			VertexAttribArray attr(prog_norm, "vertex");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the torus normals
		plane_normals.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-0.1f, 1.0f,  0.1f,
				-0.1f, 1.0f, -0.1f,
				 0.1f, 1.0f,  0.1f,
				 0.1f, 1.0f, -0.1f
			};
			// upload the data
			Buffer::Data(Buffer::Target::Array, data, 4*3);
			// setup the vertex attribs array for the normals
			prog_norm.Use();
			VertexAttribArray attr(prog_norm, "normal");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}
		VertexArray::Unbind();

		Vec3f lightPos(2.0f, 2.0f, 3.0f);
		prog_norm.Use();
		Uniform(prog_norm, "lightPos").Set(lightPos);
		prog_refl.Use();
		Uniform(prog_refl, "lightPos").Set(lightPos);
		//
		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.ClearStencil(0);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto projection = CamMatrixf::Perspective(
			Degrees(24),
			double(width)/height,
			1, 100
		);
		prog_norm.Use();
		Uniform(prog_norm, "projectionMatrix").SetMatrix(projection);
		prog_refl.Use();
		Uniform(prog_refl, "projectionMatrix").SetMatrix(projection);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();
		// make the camera matrix orbiting around the origin
		// at radius of 3.5 with elevation between 15 and 90 degrees
		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			3.5,
			Degrees(time * 135),
			Degrees(15 + (-std::cos(time * 0.5)+1.0)* 0.5 * 75)
		);
		ModelMatrixf model = ModelMatrixf::Translation(0.0f, 1.5f, 0.0);
		ModelMatrixf identity;
		//
		prog_norm.Use();
		Uniform(prog_norm, "cameraMatrix").SetMatrix(camera);
		prog_refl.Use();
		Uniform(prog_refl, "cameraMatrix").SetMatrix(camera);
		// draw the plane into the stencil buffer
		prog_norm.Use();

		gl.Disable(Capability::Blend);
		gl.Disable(Capability::DepthTest);
		gl.Enable(Capability::StencilTest);
		gl.ColorMask(false, false, false, false);
		gl.StencilFunc(CompareFunction::Always, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Replace);

		Uniform(prog_norm, "modelMatrix").SetMatrix(identity);
		plane.Bind();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		gl.ColorMask(true, true, true, true);
		gl.Enable(Capability::DepthTest);
		gl.StencilFunc(CompareFunction::Equal, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Keep);

		// draw the torus using the reflection program
		prog_refl.Use();
		Uniform(prog_refl, "modelMatrix").SetMatrix(model);
		torus.Bind();
		torus_instr.Draw(torus_indices);

		gl.Disable(Capability::StencilTest);

		prog_norm.Use();
		// draw the torus using the normal object program
		Uniform(prog_norm, "modelMatrix").SetMatrix(model);
		torus_instr.Draw(torus_indices);

		// blend-in the plane
		gl.Enable(Capability::Blend);
		gl.BlendEquation(BlendEquation::Max);
		Uniform(prog_norm, "modelMatrix").SetMatrix(identity);
		plane.Bind();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new ReflectionExample);
}

} // namespace oglplus
