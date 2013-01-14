/**
 *  @example oglplus/017_blender_mesh.cpp
 *  @brief Shows how to use the BlenderMesh shape generator/loader
 *
 *  @oglplus_screenshot{017_blender_mesh}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <oglplus/shapes/blender_mesh.hpp>
#include <oglplus/shapes/wrapper.hpp>

#include <oglplus/opt/resources.hpp>
#include <oglplus/opt/list_init.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class ShapeProgram
 : public Program
{
private:
	const Program& prog(void) const { return *this; }
public:
	LazyProgramUniform<Mat4f>
		projection_matrix,
		camera_matrix,
		model_matrix;

	LazyProgramUniform<Vec3f> colors;

	ShapeProgram(void)
	 : projection_matrix(prog(), "ProjectionMatrix")
	 , camera_matrix(prog(), "CameraMatrix")
	 , model_matrix(prog(), "ModelMatrix")
	 , colors(prog(), "Colors")
	{
		VertexShader vs;
		vs.Source(
			"#version 330\n"
			"uniform mat4  ProjectionMatrix,CameraMatrix,ModelMatrix;"
			"mat3 RotMatrix = mat3(ModelMatrix);"

			"const vec3 LightPosition = vec3(12.0, 11.0, 17.0);"

			"in vec4 Position;"
			"in vec3 Normal;"
			"in float Material;"

			"out vec3 vertLightDir;"
			"out vec3 vertNormal;"
			"flat out int vertMaterial;"
			"void main(void)"
			"{"
			"	gl_Position = ModelMatrix * Position;"
			"	vertLightDir = LightPosition - gl_Position.xyz;"
			"	vertNormal = RotMatrix * Normal;"
			"	vertMaterial = int(Material);"
			"	gl_Position = ProjectionMatrix * CameraMatrix * gl_Position;"
			"}"
		);
		vs.Compile();
		AttachShader(vs);

		FragmentShader fs;
		fs.Source(
			"#version 330\n"

			"uniform vec3 Colors[3];"

			"in vec3 vertLightDir;"
			"in vec3 vertNormal;"
			"flat in int vertMaterial;"

			"out vec3 fragColor;"
			"void main(void)"
			"{"
			"	vec3 Normal = normalize(vertNormal);"
			"	vec3 LightDir = normalize(vertLightDir);"
			"	float Ambi = 0.6;"
			"	float Diff  = max(dot(LightDir, Normal)+0.1, 0.0);"
			"	fragColor = (Ambi + Diff) * Colors[vertMaterial];"
			"}"
		);
		fs.Compile();

		AttachShader(fs);
		Link();
	}
};

class BlenderMeshExample : public Example
{
private:
	Context gl;

	ShapeProgram prog;

	shapes::ShapeWrapper shape;

	static shapes::ShapeWrapper make_shape(const Program& prog)
	{
		std::ifstream input;
		OpenResourceFile(input, "models", "monkeys", ".blend");
		if(!input.good())
			throw std::runtime_error("Error opening file for reading");
		imports::BlendFile blend_file(input);

		return shapes::ShapeWrapper(
			List("Position")("Normal")("Material").Get(),
			shapes::BlenderMesh(
				blend_file,
				List("Monkey1")("Monkey2")("Monkey3").Get(),
				shapes::BlenderMesh::LoadingOptions().Nothing().Normals().Materials()
			),
			prog
		);
	}

	Texture tex;
public:
	BlenderMeshExample(void)
	 : prog()
	 , shape(make_shape(prog))
	{
		prog.Use();

		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		prog.projection_matrix.Set(
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

		prog.camera_matrix.Set(
			CamMatrixf::Orbiting(
				shape.BoundingSphereCenter(),
				5.0,
				FullCircles(time / 19.0),
				Degrees(SineWave(time / 17.0) * 90)
			)
		);


		const Vec3f colors[3][3] = {
			{Vec3f(1.0, 0.3, 0.3), Vec3f(1.0, 0.5, 0.5), Vec3f(1.0, 0.7, 0.7)},
			{Vec3f(0.3, 1.0, 0.3), Vec3f(0.5, 1.0, 0.5), Vec3f(0.7, 1.0, 0.7)},
			{Vec3f(0.3, 0.3, 1.0), Vec3f(0.5, 0.5, 1.0), Vec3f(0.7, 0.7, 1.0)}
		};

		const Mat4f rot_matrices[3] = {
			ModelMatrixf::RotationA(Vec3f(1, 1, 1), Degrees(19 * time)),
			ModelMatrixf::RotationA(Vec3f(1, 1, 1), Degrees(31 * time)),
			ModelMatrixf::RotationA(Vec3f(1, 1, 1), Degrees(47 * time))
		};
		const Mat4f pos_matrices[3] = {
			ModelMatrixf::RotationY(Degrees(120))*
			ModelMatrixf::TranslationZ(2.0),
			ModelMatrixf::RotationY(Degrees(240))*
			ModelMatrixf::TranslationZ(2.0),
			ModelMatrixf::TranslationZ(2.0)
		};

		shape.Draw(
			// the phase is here the index of the mesh as listed
			// when loading the blend file
			// i.e. (0 = Monkey1, 1 = Monkey2, 2 = Monkey3)
			[&prog, &colors, &rot_matrices, &pos_matrices](GLuint phase) -> bool
			{
				for(GLuint i=0; i!=3; ++i)
					prog.colors[i].Set(colors[phase][i]);
				prog.model_matrix.Set(pos_matrices[phase]*rot_matrices[phase]);
				return true;
			}
		);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new BlenderMeshExample);
}

} // namespace oglplus
