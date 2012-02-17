/**
 *  @example oglplus/026_stencil_shadow.cpp
 *  @brief Shows how to render shadows using geometry shader and stencil buffer
 *
 *  @image html 026_stencil_shadow.png
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
			"in vec4 Position;"
			"in vec3 Normal;"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"uniform vec3 LightPos;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"	vertNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vertLight = ("
			"		vec4(LightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"}"
		);
		vs_object.Compile();

		fs_object.Source(
			"#version 330\n"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"uniform vec3 Color;"
			"uniform float lightMult;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = sqrt(length(vertLight));"
			"	float d = l > 0.0 ?"
			"		dot("
			"			vertNormal,"
			"			normalize(vertLight)"
			"		) / l : 0.0;"
			"	float i = 0.3 + max(d, 0.0) * lightMult;"
			"	fragColor = vec4(Color*i, 1.0);"
			"}"
		);
		fs_object.Compile();

		object_prog.AttachShader(vs_object);
		object_prog.AttachShader(fs_object);
		object_prog.Link();

		vs_shadow.Source(
			"#version 330\n"
			"in vec4 Position;"
			"in vec3 Normal;"
			"uniform mat4 ModelMatrix;"
			"uniform vec3 LightPos;"
			"out float ld;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ModelMatrix *"
			"		Position;"
			"	vec3 geomNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vec3 lightDir = ("
			"		vec4(LightPos, 0.0)-"
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

			"uniform mat4 CameraMatrix, ProjectionMatrix;"
			"uniform vec3 LightPos;"

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
			"		vec3 vx = px.xyz - LightPos;"
			"		vec3 vy = py.xyz - LightPos;"
			"		vec4 sx = vec4(px.xyz + vx*10.0, 1.0);"
			"		vec4 sy = vec4(py.xyz + vy*10.0, 1.0);"
			"		vec4 cpx = CameraMatrix * px;"
			"		vec4 cpy = CameraMatrix * py;"
			"		vec4 csx = CameraMatrix * sx;"
			"		vec4 csy = CameraMatrix * sy;"
			"		gl_Position = ProjectionMatrix * cpy;"
			"		EmitVertex();"
			"		gl_Position = ProjectionMatrix * cpx;"
			"		EmitVertex();"
			"		gl_Position = ProjectionMatrix * csy;"
			"		EmitVertex();"
			"		gl_Position = ProjectionMatrix * csx;"
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
			GLuint n_per_vertex = make_torus.Positions(data);
			Buffer::Data(Buffer::Target::Array, data);

			object_prog.Use();
			VertexAttribArray attr_o(object_prog, "Position");
			attr_o.Setup(n_per_vertex, DataType::Float);
			attr_o.Enable();

			shadow_prog.Use();
			VertexAttribArray attr_s(shadow_prog, "Position");
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
			VertexAttribArray attr_o(object_prog, "Normal");
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
			VertexAttribArray attr(object_prog, "Position");
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
			VertexAttribArray attr(object_prog, "Normal");
			attr.Setup(3, DataType::Float);
			attr.Enable();
		}

		Vec3f lightPos(2.0f, 9.0f, 3.0f);
		SetProgramUniform(object_prog, "LightPos", lightPos);
		SetProgramUniform(shadow_prog, "LightPos", lightPos);

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
		Mat4f projection = CamMatrixf::Perspective(
			Degrees(54),
			double(width)/height,
			1, 100
		);
		SetProgramUniform(object_prog, "ProjectionMatrix", projection);
		SetProgramUniform(shadow_prog, "ProjectionMatrix", projection);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();

		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			6.5,
			FullCircles(time * 0.1),
			Degrees(15 + (-SineWave(0.25+time/12.5)+1.0)* 0.5 * 75)
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
		Uniform<Mat4f>(object_prog, "CameraMatrix").Set(camera);
		Uniform<GLfloat>(object_prog, "lightMult").Set(0.2);

		Uniform<Mat4f>(object_prog, "ModelMatrix").Set(identity);
		plane.Bind();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		Uniform<Mat4f>(object_prog, "ModelMatrix").Set(model);
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
		Uniform<Mat4f>(shadow_prog, "CameraMatrix").Set(camera);
		Uniform<Mat4f>(shadow_prog, "ModelMatrix").Set(model);

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
		Uniform<GLfloat>(object_prog, "lightMult").Set(2.5);

		Uniform<Mat4f>(object_prog, "ModelMatrix").Set(identity);
		Uniform<Vec3f>(object_prog, "Color").Set(0.8f, 0.7f, 0.4f);
		plane.Bind();
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);

		Uniform<Mat4f>(object_prog, "ModelMatrix").Set(model);
		Uniform<Vec3f>(object_prog, "Color").Set(0.9f, 0.8f, 0.1f);
		torus.Bind();
		torus_instr.Draw(torus_indices);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params)
{
	return std::unique_ptr<Example>(new ShadowExample);
}

} // namespace oglplus
