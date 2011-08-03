/**
 *  .file devel/test02.cpp
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
#include <oglplus/shapes/torus.hpp>

#include <cmath>
#include <iostream>

#include "test.hpp"

namespace oglplus {

class Test02 : public Test
{
private:
	typedef shapes::Cube Shape;
	//
	Shape make_shape;
	Shape::IndexArray shape_indices;
	shapes::DrawingInstructions shape_instr;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shaders
	VertexShader vs_norm;
	VertexShader vs_refl;

	// Geometry shader
	GeometryShader gs_norm;
	GeometryShader gs_refl;

	// Fragment shader
	FragmentShader fs;

	// Programs
	Program prog_norm;
	Program prog_refl;

	// A vertex array object for the rendered shape
	VertexArray shape;
	// A vertex array object for the reflective plane
	VertexArray plane;

	// VBOs for the shape's vertices and normals
	Buffer shape_verts, shape_normals;
	// VBOs for the plane's vertices and normals
	Buffer plane_verts, plane_normals;
public:
	Test02(void)
	 : shape_indices(make_shape.Indices())
	 , shape_instr(make_shape.Instructions())
	{
		// Set the normal object vertex shader source
		vs_norm.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"in vec3 normal;"
			"out vec3 vertNormal;"
			"out vec3 fragNormal;"
			"out vec3 fragLight;"
			"uniform mat4 projectionMatrix, modelviewMatrix;"
			"uniform vec3 lightPos;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		projectionMatrix *"
			"		modelviewMatrix *"
			"		vertex;"
			"	vertNormal = normal;"
			"	fragNormal = (modelviewMatrix *"
			"		vec4(normal, 0.0)).xyz;"
			"	fragLight = (modelviewMatrix *"
			"		vec4(lightPos-vertex.xyz, 0.0)).xyz;"
			"}"
		);
		// compile it
		vs_norm.Compile();

		// Set the reflected object vertex shader source
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
			"void main(void)"
			"{"
			"	mat4 reflectionMatrix = mat4("
			"		1.0, 0.0, 0.0, 0.0,"
			"		0.0,-1.0, 0.0, 0.0,"
			"		0.0, 0.0, 1.0, 0.0,"
			"		0.0, 0.0, 0.0, 1.0 "
			"	);"
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
			"			cameraMatrix *"
			"			reflectionMatrix *"
			"			modelMatrix *"
			"			vec4(vertNormal, 0.0)"
			"		).xyz;"
			"		fragLight = ("
			"			cameraMatrix *"
			"			reflectionMatrix *"
			"			modelMatrix *"
			"			vec4(lightPos-vertex.xyz, 0.0)"
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

		std::cout << UniformBlock::MaxIn(Shader::Kind::Vertex) << std::endl;
		//
		prog_norm.Use();
		for(auto r=prog_norm.ActiveAttribs();!r.Empty();r.Next())
			std::cout << r.Front().Name() << std::endl;
		for(auto r=prog_norm.ActiveUniforms();!r.Empty();r.Next())
			std::cout << r.Front().Name() << std::endl;

		// attach the shaders to the reflection rendering program
		prog_refl.AttachShader(vs_refl);
		prog_refl.AttachShader(gs_refl);
		prog_refl.AttachShader(fs);
		// link it
		prog_refl.Link();

		prog_refl.Use();
		for(auto r=prog_refl.ActiveAttribs();!r.Empty();r.Next())
			std::cout << r.Front().Name() << std::endl;

		// bind the VAO for the shape
		shape.Bind();

		// bind the VBO for the shape vertices
		shape_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Vertices(data);
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

		// bind the VBO for the shape normals
		shape_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
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

		VertexArray::Unbind();
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
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			// setup the vertex attribs array for the vertices
			prog_norm.Use();
			VertexAttribArray attr(prog_norm, "vertex");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the shape normals
		plane_normals.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-0.1f, 1.0f,  0.1f,
				-0.1f, 1.0f, -0.1f,
				 0.1f, 1.0f,  0.1f,
				 0.1f, 1.0f, -0.1f
			};
			// upload the data
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			// setup the vertex attribs array for the vertices
			prog_norm.Use();
			VertexAttribArray attr(prog_norm, "normal");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}
		VertexArray::Unbind();

		// set the projection matrix fov = 24 deg. aspect = 1.25
		CamMatrixf projMatrix =
			CamMatrixf::Perspective(Degrees(24), 1.25, 1, 100);
		Vec3f lightPos(2.0, 2.0, 3.0);

		prog_norm.Use();
		Uniform(prog_norm, "projectionMatrix").SetMatrix(projMatrix);
		Uniform(prog_norm, "lightPos").Set(lightPos);
		prog_refl.Use();
		Uniform(prog_refl, "projectionMatrix").SetMatrix(projMatrix);
		Uniform(prog_refl, "lightPos").Set(lightPos);
		//
		//
		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		//
		//glFrontFace(GL_CCW);
		//glCullFace(GL_BACK);
		//gl.Enable(Capability::CullFace);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();
		// make the camera matrix
		CamMatrixf camera = CamMatrixf::Orbiting(
			Vec3f(),
			3.5,
			Degrees(time * 135),
			Degrees(15 + (-std::cos(time * 0.5)+1.0)* 0.5 * 75)
		);
		ModelMatrixf model = ModelMatrixf::Translation(0.0f, 1.5f, 0.0);
		//
		// draw the plane into the stencil buffer
		prog_norm.Use();

		gl.Disable(Capability::Blend);
		gl.Disable(Capability::DepthTest);
		gl.Enable(Capability::StencilTest);
		gl.ColorMask(false, false, false, false);
		gl.StencilFunc(CompareFunction::Always, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Replace);

		plane.Bind();
		Uniform(prog_norm, "modelviewMatrix").SetMatrix(camera);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		gl.ColorMask(true, true, true, true);
		gl.Enable(Capability::DepthTest);
		gl.StencilFunc(CompareFunction::Equal, 1, 1);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Keep);

		// draw the shape using the reflection program
		prog_refl.Use();
		Uniform(prog_refl, "cameraMatrix").SetMatrix(camera);
		Uniform(prog_refl, "modelMatrix").SetMatrix(model);
		shape.Bind();
		shape_instr.Draw(shape_indices);

		gl.Disable(Capability::StencilTest);

		prog_norm.Use();
		// draw the shape
		Uniform(prog_norm, "modelviewMatrix").SetMatrix(camera * model);
		shape_instr.Draw(shape_indices);

		// blend-in the plane
		gl.Enable(Capability::Blend);
		gl.BlendEquation(BlendEquation::Max);
		plane.Bind();
		Uniform(prog_norm, "modelviewMatrix").SetMatrix(camera);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Test> makeTest(void)
{
	return std::unique_ptr<Test>(new Test02);
}

} // namespace oglplus
