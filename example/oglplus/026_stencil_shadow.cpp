/**
 *  @example oglplus/026_stencil_shadow.cpp
 *  @brief Shows how to render shadows using geometry shader and stencil buffer
 *
 *  @image html 026_stencil_shadow.png
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

class ShadowExample : public Example
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

	// Shaders and program for rendering of the objects
	VertexShader vs_object;
	FragmentShader fs_object;
	Program object_prog;

	// Shaders and program for rendering of the shadow effect
	VertexShader vs_shadow;
	GeometryShader gs_shadow;
	FragmentShader fs_shadow;
	Program shadow_prog;

	// A vertex array object for the torus
	VertexArray torus;
	// VBOs for the torus' vertices and normals
	Buffer torus_verts, torus_normals;

	// A vertex array object for the shadowed plane
	VertexArray plane;
	// VBOs for the plane's vertices and normals
	Buffer plane_verts, plane_normals;
public:
	ShadowExample(void)
	 : make_torus(1.0, 0.7, 72, 48)
	 , torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	{
		vs_object.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"in vec3 normal;"
			"uniform mat4 projectionMatrix, cameraMatrix, modelMatrix;"
			"uniform vec3 lightPos;"
			"out vec3 fragNormal;"
			"out vec3 fragLight;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		projectionMatrix *"
			"		cameraMatrix *"
			"		modelMatrix *"
			"		vertex;"
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
		vs_object.Compile();

		fs_object.Source(
			"#version 330\n"
			"in vec3 fragNormal;"
			"in vec3 fragLight;"
			"uniform vec3 color;"
			"uniform float lightMult;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = sqrt(length(fragLight));"
			"	float d = l > 0.0 ?"
			"		dot("
			"			fragNormal,"
			"			normalize(fragLight)"
			"		) / l : 0.0;"
			"	float i = 0.3 + d * lightMult;"
			"	fragColor = vec4(color*i, 1.0);"
			"}"
		);
		fs_object.Compile();

		object_prog.AttachShader(vs_object);
		object_prog.AttachShader(fs_object);
		object_prog.Link();

		vs_shadow.Source(
			"#version 330\n"
			"in vec4 vertex;"
			"in vec3 normal;"
			"uniform mat4 modelMatrix;"
			"uniform vec3 lightPos;"
			"out float ld;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		modelMatrix *"
			"		vertex;"
			"	vec3 geomNormal = ("
			"		modelMatrix *"
			"		vec4(normal, 0.0)"
			"	).xyz;"
			"	vec3 lightDir = ("
			"		vec4(lightPos, 0.0)-"
			"		gl_Position"
			"	).xyz;"
			"	ld = dot(geomNormal, normalize(lightDir));"
			"}"
		);
		vs_shadow.Compile();

		gs_shadow.Source(
			"#version 330\n"
			"layout(triangles) in;"
			"layout(triangle_strip, max_vertices = 12) out;"

			"in float ld[];"

			"uniform mat4 cameraMatrix, projectionMatrix;"
			"uniform vec3 lightPos;"

			"void main(void)"
			"{"
			"	for(int v=0; v!=3; ++v)"
			"	{"
			"		int a = v, b = (v+1)%3, c = (v+2)%3;"
			"		vec4 pa = gl_in[a].gl_Position;"
			"		vec4 pb = gl_in[b].gl_Position;"
			"		vec4 pc = gl_in[c].gl_Position;"
			"		vec4 px, py;"
			"		if(ld[a] == 0.0 && ld[b] == 0.0)"
			"		{"
			"			px = pa;"
			"			py = pb;"
			"		}"
			"		else if(ld[a] > 0.0 && ld[b] < 0.0)"
			"		{"
			"			float x = ld[a]/(ld[a]-ld[b]);"
			"			float y;"
			"			px = mix(pa, pb, x);"
			"			if(ld[c] < 0.0)"
			"			{"
			"				y = ld[a]/(ld[a]-ld[c]);"
			"				py = mix(pa, pc, y);"
			"			}"
			"			else"
			"			{"
			"				y = ld[c]/(ld[c]-ld[b]);"
			"				py = mix(pc, pb, y);"
			"			}"
			"		}"
			"		else continue;"
			"		vec3 vx = px.xyz - lightPos;"
			"		vec3 vy = py.xyz - lightPos;"
			"		vec4 sx = vec4(px.xyz + vx*10.0, 1.0);"
			"		vec4 sy = vec4(py.xyz + vy*10.0, 1.0);"
			"		vec4 cpx = cameraMatrix * px;"
			"		vec4 cpy = cameraMatrix * py;"
			"		vec4 csx = cameraMatrix * sx;"
			"		vec4 csy = cameraMatrix * sy;"
			"		gl_Position = projectionMatrix * cpy;"
			"		EmitVertex();"
			"		gl_Position = projectionMatrix * cpx;"
			"		EmitVertex();"
			"		gl_Position = projectionMatrix * csy;"
			"		EmitVertex();"
			"		gl_Position = projectionMatrix * csx;"
			"		EmitVertex();"
			"		EndPrimitive();"
			"		break;"
			"	}"
			"}"
		);
		gs_shadow.Compile();

		fs_shadow.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(0.0, 0.0, 0.0, 1.0);"
			"}"
		);
		fs_shadow.Compile();

		shadow_prog.AttachShader(vs_shadow);
		shadow_prog.AttachShader(gs_shadow);
		shadow_prog.AttachShader(fs_shadow);
		shadow_prog.Link();

		// bind the VAO for the torus
		torus.Bind();

		// bind the VBO for the torus vertices
		torus_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);

			object_prog.Use();
			VertexAttribArray attr_o(object_prog, "vertex");
			attr_o.Setup(n_per_vertex, DataType::Float);
			attr_o.Enable();

			shadow_prog.Use();
			VertexAttribArray attr_s(shadow_prog, "vertex");
			attr_s.Setup(n_per_vertex, DataType::Float);
			attr_s.Enable();
		}

		// bind the VBO for the torus normals
		torus_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);

			object_prog.Use();
			VertexAttribArray attr_o(object_prog, "normal");
			attr_o.Setup(n_per_vertex, DataType::Float);
			attr_o.Enable();
		}
		// bind the VAO for the plane
		plane.Bind();

		// bind the VBO for the plane vertices
		plane_verts.Bind(Buffer::Target::Array);
		{
			GLfloat data[4*3] = {
				-9.0f, 0.0f,  9.0f,
				-9.0f, 0.0f, -9.0f,
				 9.0f, 0.0f,  9.0f,
				 9.0f, 0.0f, -9.0f
			};
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			object_prog.Use();
			VertexAttribArray attr(object_prog, "vertex");
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
			Buffer::Data(Buffer::Target::Array, 4*3, data);
			object_prog.Use();
			VertexAttribArray attr(object_prog, "normal");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		Vec3f lightPos(2.0f, 9.0f, 3.0f);
		object_prog.Use();
		Uniform(object_prog, "lightPos").Set(lightPos);
		shadow_prog.Use();
		Uniform(shadow_prog, "lightPos").Set(lightPos);

		gl.ClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.ClearStencil(0);

		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_torus.FaceWinding());
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto projection = CamMatrixf::Perspective(
			Degrees(24),
			double(width)/height,
			1, 100
		);
		object_prog.Use();
		Uniform(object_prog, "projectionMatrix").SetMatrix(projection);
		shadow_prog.Use();
		Uniform(shadow_prog, "projectionMatrix").SetMatrix(projection);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();

		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			5.5,
			FullCircles(time * 0.1),
			Degrees(15 + (-std::cos(time * 0.5)+1.0)* 0.5 * 75)
		);
		ModelMatrixf identity;
		ModelMatrixf model =
			ModelMatrixf::Translation(0.0f, 2.5f, 0.0) *
			ModelMatrixf::RotationA(
				Vec3f(1.0f, 1.0f, 1.0f),
				FullCircles(time * 0.2)
			);

		gl.CullFace(Face::Back);
		gl.ColorMask(true, true, true, true);
		gl.DepthMask(true);
		gl.Disable(Capability::StencilTest);

		object_prog.Use();
		Uniform(object_prog, "cameraMatrix").SetMatrix(camera);
		Uniform(object_prog, "lightMult").Set(0.2f);

		Uniform(object_prog, "modelMatrix").SetMatrix(identity);
		plane.Bind();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		Uniform(object_prog, "modelMatrix").SetMatrix(model);
		torus.Bind();
		torus_instr.Draw(torus_indices);

		gl.ColorMask(false, false, false, false);
		gl.DepthMask(false);
		gl.Enable(Capability::StencilTest);
		gl.StencilFunc(CompareFunction::Always);
		gl.StencilOpSeparate(
			Face::Front,
			StencilOp::Keep,
			StencilOp::Keep,
			StencilOp::Incr
		);
		gl.StencilOpSeparate(
			Face::Back,
			StencilOp::Keep,
			StencilOp::Keep,
			StencilOp::Decr
		);

		shadow_prog.Use();
		Uniform(shadow_prog, "cameraMatrix").SetMatrix(camera);
		Uniform(shadow_prog, "modelMatrix").SetMatrix(model);

		gl.CullFace(Face::Back);
		torus_instr.Draw(torus_indices);
		gl.CullFace(Face::Front);
		torus_instr.Draw(torus_indices);
		gl.CullFace(Face::Back);

		gl.ColorMask(true, true, true, true);
		gl.DepthMask(true);
		gl.Clear().DepthBuffer();
		gl.StencilFunc(CompareFunction::Equal, 0);
		gl.StencilOp(StencilOp::Keep, StencilOp::Keep, StencilOp::Keep);

		object_prog.Use();
		Uniform(object_prog, "lightMult").Set(2.5f);

		Uniform(object_prog, "modelMatrix").SetMatrix(identity);
		Uniform(object_prog, "color").Set(Vec3f(0.8f, 0.7f, 0.4f));
		plane.Bind();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		Uniform(object_prog, "modelMatrix").SetMatrix(model);
		Uniform(object_prog, "color").Set(Vec3f(0.9f, 0.8f, 0.1f));
		torus.Bind();
		torus_instr.Draw(torus_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new ShadowExample);
}

} // namespace oglplus
