/**
 *  @example oglplus/019_bpatch_tess.cpp
 *  @brief Shows tesellation of a cubic bezier patch
 *
 *  @oglplus_screenshot{019_bpatch_tess}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include "example.hpp"

namespace oglplus {

class TessellationExample : public Example
{
private:
	Context gl;

	Program prog;

	Buffer positions;

	VertexArray vao;

	LazyUniform<Mat4f> projection_matrix, camera_matrix;
public:
	TessellationExample(void)
	 : prog()
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	{
		VertexShader vert(ObjectDesc("Vertex"));
		vert.Source(StrLit(
			"#version 410\n"
			"uniform mat4 CameraMatrix;"

			"in vec4 Position;"
			"out vec4 vertPosition;"

			"void main(void)"
			"{"
			"	vertPosition = CameraMatrix * Position;"
			"}"
		));
		vert.Compile();
		prog << vert;

		TessControlShader teco(ObjectDesc("TessControl"));
		teco.Source(StrLit(
			"#version 410\n"
			"layout(vertices = 16) out;"

			"in vec4 vertPosition[];"
			"out vec3 tecoPosition[];"

			"int tl_inc(void)"
			"{"
			"	return 1-int(100.0 / vertPosition[gl_InvocationID].z);"
			"}"

			"void main(void)"
			"{"
			"	if(gl_InvocationID == 0)"
			"	{"
			"		gl_TessLevelInner[0] = tl_inc();"
			"		gl_TessLevelInner[1] = tl_inc();"
			"		gl_TessLevelOuter[0] = tl_inc();"
			"		gl_TessLevelOuter[1] = tl_inc();"
			"		gl_TessLevelOuter[2] = tl_inc();"
			"		gl_TessLevelOuter[3] = tl_inc();"
			"	}"
			"	tecoPosition[gl_InvocationID] = "
			"		vertPosition[gl_InvocationID].xyz;"
			"}"
		));
		teco.Compile();
		prog << teco;

		TessEvaluationShader teev(ObjectDesc("TessEvaluation"));
		teev.Source(StrLit(
			"#version 410\n"
			"layout(quads, equal_spacing, ccw) in;"
			"uniform mat4 ProjectionMatrix;"
			"in vec3 tecoPosition[];"

			"const mat4 B = mat4("
			"	-1, 3,-3, 1,"
			"	 3,-6, 3, 0,"
			"	-3, 3, 0, 0,"
			"	 1, 0, 0, 0 "
			");"

			"void main(void)"
			"{"
			"	float u = gl_TessCoord.x, v = gl_TessCoord.y;"

			"	mat4 Px = mat4("
			"		tecoPosition[ 0].x, tecoPosition[ 1].x, tecoPosition[ 2].x, tecoPosition[ 3].x,"
			"		tecoPosition[ 4].x, tecoPosition[ 5].x, tecoPosition[ 6].x, tecoPosition[ 7].x,"
			"		tecoPosition[ 8].x, tecoPosition[ 9].x, tecoPosition[10].x, tecoPosition[11].x,"
			"		tecoPosition[12].x, tecoPosition[13].x, tecoPosition[14].x, tecoPosition[15].x "
			"	);"
			"	mat4 Py = mat4("
			"		tecoPosition[ 0].y, tecoPosition[ 1].y, tecoPosition[ 2].y, tecoPosition[ 3].y,"
			"		tecoPosition[ 4].y, tecoPosition[ 5].y, tecoPosition[ 6].y, tecoPosition[ 7].y,"
			"		tecoPosition[ 8].y, tecoPosition[ 9].y, tecoPosition[10].y, tecoPosition[11].y,"
			"		tecoPosition[12].y, tecoPosition[13].y, tecoPosition[14].y, tecoPosition[15].y "
			"	);"
			"	mat4 Pz = mat4("
			"		tecoPosition[ 0].z, tecoPosition[ 1].z, tecoPosition[ 2].z, tecoPosition[ 3].z,"
			"		tecoPosition[ 4].z, tecoPosition[ 5].z, tecoPosition[ 6].z, tecoPosition[ 7].z,"
			"		tecoPosition[ 8].z, tecoPosition[ 9].z, tecoPosition[10].z, tecoPosition[11].z,"
			"		tecoPosition[12].z, tecoPosition[13].z, tecoPosition[14].z, tecoPosition[15].z "
			"	);"

			"	mat4 Cx = B * Px * B;"
			"	mat4 Cy = B * Py * B;"
			"	mat4 Cz = B * Pz * B;"

			"	vec4 up = vec4(u*u*u, u*u, u, 1);"
			"	vec4 vp = vec4(v*v*v, v*v, v, 1);"

			"	vec4 tempPosition = vec4(dot(Cx * vp, up), dot(Cy * vp, up), dot(Cz * vp, up), 1.0);"

			"	gl_Position = ProjectionMatrix * tempPosition;"
			"}"
		));
		teev.Compile();
		prog << teev;

		FragmentShader frag(ObjectDesc("Fragment"));
		frag.Source(StrLit(
			"#version 410\n"
			"out vec3 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec3(0.1, 0.1, 0.1);"
			"}"
		));
		frag.Compile();
		prog << frag;

		prog.Link();
		prog.Use();

		vao.Bind();

		GLfloat patch_cp_pos[16*3] = {
			-2.0f,  0.0f, -2.0f,
			-1.0f,  0.0f, -3.0f,
			 1.0f,  0.0f, -5.0f,
			 2.0f,  0.0f, -2.0f,
			-1.0f,  0.0f, -1.0f,
			 0.0f,  4.0f, -1.0f,
			 1.0f,  4.0f, -1.0f,
			 3.0f,  0.0f, -1.0f,
			-1.0f,  0.0f,  1.0f,
			-1.0f,  4.0f,  1.0f,
			 0.0f,  4.0f,  1.0f,
			 1.0f,  0.0f,  1.0f,
			-2.0f,  0.0f,  2.0f,
			-1.0f,  0.0f,  5.0f,
			 1.0f,  0.0f,  3.0f,
			 2.0f,  0.0f,  2.0f
		};
		positions.Bind(Buffer::Target::Array);
		Buffer::Data(Buffer::Target::Array, 16*3, patch_cp_pos);
		VertexAttribArray position_attr(prog, "Position");
		position_attr.Setup(3, DataType::Float);
		position_attr.Enable();

		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.PolygonMode(PolygonMode::Line);
		gl.PatchParameter(PatchParameter::PatchVertices, 16);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(50),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				30.0 - SineWave(time / 17.0)*27.0,
				Degrees(time * 47),
				Degrees(SineWave(time / 31.0) * 90)
			)
		);

		gl.DrawArrays(PrimitiveType::Patches, 0, 16);
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new TessellationExample);
}

} // namespace oglplus
