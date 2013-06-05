/**
 *  @example oglplus/020_checkered_objects.cpp
 *  @brief Shows how to use shared shading program for drawing multiple objects
 *
 *  @oglplus_screenshot{020_checkered_objects}
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @oglplus_example_uses_gl{GL_VERSION_3_1}
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/plane.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/torus.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CheckerShaders
{
protected:
	VertexShader vertex_shader;
	FragmentShader fragment_shader;

	CheckerShaders(void)
	 : vertex_shader(
		ObjectDesc("Vertex shader"),
		StrLit("#version 330\n"
		"uniform vec3 LightPosition;"
		"uniform mat4 ProjectionMatrix, ModelMatrix, CameraMatrix;"
		"in vec4 Position;"
		"in vec3 Normal;"
		"in vec2 TexCoord;"
		"out vec3 vertNormal;"
		"out vec3 vertLightDir;"
		"out vec3 vertLightRefl;"
		"out vec3 vertViewDir;"
		"out vec2 vertTexCoord;"
		"void main(void)"
		"{"
		"	gl_Position = "
		"		ModelMatrix *"
		"		Position;"
		"	vertLightDir = LightPosition - gl_Position.xyz;"
		"	vertNormal = mat3(ModelMatrix)*Normal;"
		"	vertLightRefl = reflect("
		"		-normalize(vertLightDir),"
		"		normalize(vertNormal)"
		"	);"
		"	vertViewDir = ("
		"		vec4(0.0, 0.0, 1.0, 1.0)*"
		"		CameraMatrix"
		"	).xyz;"
		"	gl_Position = "
		"		ProjectionMatrix *"
		"		CameraMatrix *"
		"		gl_Position;"
		"	vertTexCoord = TexCoord;"
		"}")
	), fragment_shader(
		ObjectDesc("Fragment shader"),
		StrLit("#version 330\n"
		"uniform int SRepeat, TRepeat;"
		"uniform vec3 Color1, Color2;"
		"uniform float Refl1, Refl2;"
		"in vec3 vertNormal;"
		"in vec3 vertLightDir;"
		"in vec3 vertLightRefl;"
		"in vec3 vertViewDir;"
		"in vec2 vertTexCoord;"
		"out vec4 fragColor;"

		"void main(void)"
		"{"
		"	float l = length(vertLightDir);"
		"	float d = dot("
		"		normalize(vertNormal), "
		"		normalize(vertLightDir)"
		"	) / l;"
		"	float s = dot("
		"		normalize(vertLightRefl),"
		"		normalize(vertViewDir)"
		"	);"
		"	float c = ("
		"		int(vertTexCoord.x*SRepeat) % 2+"
		"		int(vertTexCoord.y*TRepeat) % 2"
		"	) % 2;"
		"	vec3 lt = vec3(1.0, 1.0, 1.0);"
		"	vec3 chkr = mix(Color1, Color2, c);"
		"	fragColor = vec4("
		"		chkr * 0.3 + "
		"		(lt + chkr) * 1.5 * max(d, 0.0) + "
		"		lt * pow(max(s, 0.0), mix(Refl1, Refl2, c)), "
		"		1.0"
		"	);"
		"}")
	)
	{ }
};

class CheckerProgram
 : public CheckerShaders
 , public QuickProgram
{
private:
	Program& prog(void) {return *this;}
public:
	Uniform<Vec3f> light_position;
	Uniform<Mat4f> projection_matrix, camera_matrix, model_matrix;
	Uniform<GLint> s_repeat, t_repeat;
	Uniform<Vec3f> color_1, color_2;
	Uniform<GLfloat> refl_1, refl_2;

	CheckerProgram(void)
	 : CheckerShaders()
	 , QuickProgram(false, vertex_shader, fragment_shader)
	 , light_position(prog(), "LightPosition")
	 , projection_matrix(prog(), "ProjectionMatrix")
	 , camera_matrix(prog(), "CameraMatrix")
	 , model_matrix(prog(), "ModelMatrix")
	 , s_repeat(prog(), "SRepeat")
	 , t_repeat(prog(), "TRepeat")
	 , color_1(prog(), "Color1")
	 , color_2(prog(), "Color2")
	 , refl_1(prog(), "Refl1")
	 , refl_2(prog(), "Refl2")
	{ }
};

template <typename ShapeBuilder>
class CheckerShape
{
private:
	Context gl;
	// helper object building shape vertex attributes
	ShapeBuilder make_shape;
	// helper object encapsulating shape drawing instructions
	shapes::DrawingInstructions shape_instr;
	// indices pointing to shape primitive elements
	typename ShapeBuilder::IndexArray shape_indices;

	// A vertex array object for the rendered shape
	VertexArray vao;

	// VBOs for the shape's vertex positions, normals and tex-coords
	Buffer positions, normals, tex_coords;

public:
	CheckerShape(const Program& prog, const ShapeBuilder& builder)
	 : make_shape(builder)
	 , shape_instr(make_shape.Instructions())
	 , shape_indices(make_shape.Indices())
	{
		// bind the VAO for the shape
		vao.Bind();

		// bind the VBO for the shape vertex positions
		positions.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Positions(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Position");
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		// bind the VBO for the shape normals
		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "Normal");
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}

		// bind the VBO for the shape texture coords
		tex_coords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_shape.TexCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(prog, "TexCoord");
			attr.Setup<GLfloat>(n_per_vertex);
			attr.Enable();
		}
	}

	void Draw(void)
	{
		vao.Bind();
		gl.FrontFace(make_shape.FaceWinding());
		shape_instr.Draw(shape_indices);
	}
};

class CheckerExample : public Example
{
private:

	// wrapper around the current OpenGL context
	Context gl;

	// The checker shading program
	CheckerProgram prog;

	CheckerShape<shapes::Plane> plane;
	CheckerShape<shapes::Sphere> sphere;
	CheckerShape<shapes::Cube> cube;
	CheckerShape<shapes::Torus> torus;
public:
	CheckerExample(void)
	 : prog()
	 , plane(prog, shapes::Plane(Vec3f(5.0, 0.0, 0.0), Vec3f(0.0, 0.0,-5.0)))
	 , sphere(prog, shapes::Sphere())
	 , cube(prog, shapes::Cube())
	 , torus(prog, shapes::Torus())
	{
		gl.ClearColor(0.6f, 0.6f, 0.5f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.CullFace(Face::Back);

		prog.Use();
		prog.light_position.Set(Vec3f(4.0, 10.0, 4.0));
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);

		prog.projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(60),
				double(width)/height,
				1, 30
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		prog.camera_matrix.Set(
			CamMatrixf::Orbiting(
				Vec3f(),
				10.0,
				FullCircles(time / 12.0),
				Degrees(45 + SineWave(time / 20.0) * 40)
			)
		);

		// Render the plane
		prog.model_matrix = ModelMatrixf();
		prog.s_repeat = 24;
		prog.t_repeat = 24;
		prog.color_1 = Vec3f(1.0f, 1.0f, 0.9f);
		prog.color_2 = Vec3f(1.0f, 0.9f, 0.8f);
		prog.refl_1 = 64;
		prog.refl_2 = 8;
		plane.Draw();

		// Render the sphere
		prog.model_matrix.Set(
			ModelMatrixf::Translation(0.0, 1.5, 0.0) *
			ModelMatrixf::RotationX(FullCircles(time / 9.0))
		);
		prog.s_repeat = 36;
		prog.t_repeat = 24;
		prog.color_1 = Vec3f(0.5f, 0.6f, 1.0f);
		prog.color_2 = Vec3f(0.2f, 0.3f, 0.7f);
		prog.refl_1 = 64;
		prog.refl_2 = 32;
		sphere.Draw();

		// Render the torus
		prog.model_matrix.Set(
			ModelMatrixf::Translation(3.0, 1.5, 0.0) *
			ModelMatrixf::RotationZ(FullCircles(time / 8.0))
		);
		prog.color_1 = Vec3f(0.5f, 1.0f, 0.6f);
		prog.color_2 = Vec3f(0.2f, 0.7f, 0.3f);
		prog.refl_1 = 64;
		prog.refl_2 = 64;
		torus.Draw();

		// Render the cube
		prog.model_matrix.Set(
			ModelMatrixf::Translation(-2.0, 1.5, 0.0) *
			ModelMatrixf::RotationA(Vec3f(1,1,1), FullCircles(time / 7.0))
		);
		prog.s_repeat = 8;
		prog.t_repeat = 8;
		prog.color_1 = Vec3f(1.0f, 0.6f, 0.5f);
		prog.color_2 = Vec3f(0.7f, 0.3f, 0.2f);
		prog.refl_1 = 64;
		prog.refl_2 = 8;
		cube.Draw();
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
	return std::unique_ptr<Example>(new CheckerExample);
}

} // namespace oglplus
