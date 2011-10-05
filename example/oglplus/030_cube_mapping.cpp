/**
 *  @example oglplus/030_cube_mapping.cpp
 *  @brief Shows how to do dynamic reflection using cube mapping
 *
 *  @image html 030_cube_mapping.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/cube.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

// NOTE: this example is still work in progress and incomplete
class CubeMapExample : public Example
{
private:
	// helper object building sphere vertex attributes
	shapes::Sphere make_sphere;
	// helper object encapsulating sphere drawing instructions
	shapes::DrawingInstructions sphere_instr;
	// indices pointing to sphere primitive elements
	shapes::Sphere::IndexArray sphere_indices;

	// helper object building cube vertex attributes
	shapes::Cube make_cube;
	// helper object encapsulating cube drawing instructions
	shapes::DrawingInstructions cube_instr;
	// indices pointing to cube primitive elements
	shapes::Cube::IndexArray cube_indices;

	// The offsets of the individual instances of the cube
	std::vector<Vec3f> cube_offsets;

	// Returns a vector of cube offsets
	static std::vector<Vec3f> MakeCubeOffsets(
		GLfloat distance,
		GLint cubes_per_side
	)
	{
		GLint instance_count =
			2 * cubes_per_side * cubes_per_side +
			2 * cubes_per_side * (cubes_per_side-2) +
			2 * (cubes_per_side-2) * (cubes_per_side-2);
		std::vector<Vec3f> offsets(instance_count);

		int cpf = cubes_per_side * cubes_per_side;
		int cpe = cubes_per_side - 2;
		int cpl = 2*cubes_per_side + 2*cpe;
		int cpi = cpl*cpe;

		for(GLint i=0; i!=instance_count; ++i)
		{
			int id = i;
			float omax = (cubes_per_side - 1)*0.5;
			float imax = (cpe-1)*0.5;
			float dx, dy, dz;
			if(id < cpf)
			{
				dx = -omax;
				dy = (id / cubes_per_side)-omax;
				dz = (id % cubes_per_side)-omax;
			}
			else if(id < cpf+cpi)
			{
				id -= cpf;
				dx = (id / cpl) - imax;
				id = id % cpl;
				if(id < cubes_per_side)
				{
					dy = -omax;
					dz = id-omax;
				}
				else if(id < cubes_per_side + cpe*2)
				{
					id -= cubes_per_side;
					dy = -imax + id / 2;
					dz = (id %  2 == 1) ? omax : -omax;
				}
				else
				{
					id -= cubes_per_side + cpe*2;
					dy = omax;
					dz = id-omax;
				}
			}
			else
			{
				id -= cpf+cpi;
				dx = omax;
				dy = (id / cubes_per_side) - omax;
				dz = (id % cubes_per_side) - omax;
			}
			offsets[i] = Vec3f(
				dx * distance,
				dy * distance,
				dz * distance
			);
		}
		return offsets;
	}

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shaders
	VertexShader sphere_vs, cube_vs, cmap_vs;

	// Geometry shader
	GeometryShader cmap_gs;

	// Fragment shaders
	FragmentShader sphere_fs, cube_fs;

	// Programs
	Program sphere_prog, cube_prog, cmap_prog;

	// A vertex array object for the rendered sphere and cubes
	VertexArray sphere, cube;

	// VBOs for the objects' vertice positions, normals and st coords
	Buffer sphere_verts, sphere_normals, sphere_tangents, sphere_texcoords;
	Buffer cube_verts, cube_normals;

	// Path of the light
	CubicBezierLoop<Vec3f, double> light_path;
public:
	CubeMapExample(void)
	 : make_sphere(1.0, 72, 48)
	 , sphere_instr(make_sphere.Instructions())
	 , sphere_indices(make_sphere.Indices())
	 , cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	 , cube_offsets(MakeCubeOffsets(2.0f, 10))
	 , sphere_vs("Sphere Vertex")
	 , cube_vs("Cube Vertex")
	 , cmap_vs("Cube map Vertex")
	 , cmap_gs("Cube map Geometry")
	 , sphere_fs("Sphere Fragment")
	 , cube_fs("Cube Fragment")
	 , sphere_prog("Sphere")
	 , cube_prog("Cube")
	 , cmap_prog("Cube map")
	 , light_path({
		{ 0.0f,  7.0f,  0.0f},
		{-4.0f, -5.0f,  4.0f},
		{ 0.0f, -4.0f, -5.0f},
		{ 4.0f, -5.0f,  4.0f}
	})
	{
		// Set the vertex shader source
		sphere_vs.Source(
			"#version 330\n"
			"uniform float Time;"
			"uniform mat4 CameraMatrix, ProjectionMatrix;"
			"uniform vec4 LightPos;"
			"in vec4 Position;"
			"in vec3 Normal, Tangent;"
			"in vec2 TexCoord;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"void main(void)"
			"{"
			"	float amps = 0.02, ampt = 0.05;"
			"	float pers = 6.0, pert = 4.0+Time*0.1;"
			"	float vels = 4.0, velt = 3.0;"
			"	float as = (TexCoord.s + Time/vels)*3.1415*2.0;"
			"	float at = (TexCoord.t + Time/velt)*3.1415*2.0;"

			"	vec3 Binormal = cross(Normal, Tangent);"
			"	vec2 Sin = vec2(sin(as*pers), sin(at*pert));"
			"	vec2 Cos = vec2(cos(as*pers), cos(at*pert));"

			"	vertNormal = normalize("
			"		Normal - Tangent * cos(as*pers)*amps*5.0+"
			"		Normal - Binormal* cos(at*pert)*ampt*5.0 "
			"	);"
			"	gl_Position = vec4("
			"		Position.xyz + Normal * ("
			"			amps * sin(as*pers)+"
			"			ampt * sin(at*pert) "
			"		), 1.0"
			"	);"
			"	vertLight = LightPos.xyz - gl_Position.xyz;"
			"	gl_Position ="
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"}"
		);
		// compile it
		sphere_vs.Compile();

		// set the fragment shader source
		sphere_fs.Source(
			"#version 330\n"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(vertLight);"
			"	float d = l > 0? dot("
			"		normalize(vertNormal),"
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float i = 0.1 + 4.2*d;"
			"	fragColor = vec4(i, i, i, 1.0);"
			"}"
		);
		// compile it
		sphere_fs.Compile();

		// attach the shaders to the program
		sphere_prog.AttachShader(sphere_vs);
		sphere_prog.AttachShader(sphere_fs);
		// link and use it
		sphere_prog.Link();
		sphere_prog.Use();

		// bind the VAO for the sphere
		sphere.Bind();

		// bind the VBO for the sphere vertices
		sphere_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(sphere_prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the sphere normals
		sphere_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(sphere_prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the sphere tangents
		sphere_tangents.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.Tangents(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(sphere_prog, "Tangent");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the sphere st coords
		sphere_texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_sphere.TexCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(sphere_prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// Set the vertex shader source
		cube_vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"uniform vec4 LightPos;"
			"uniform vec3 Offset;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertColor;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"void main(void)"
			"{"
			"	gl_Position = vec4(Position.xyz+Offset, 1.0);"
			"	vertColor = normalize(vec3(1.0, 1.0, 1.0) - Normal);"
			"	vertNormal = Normal;"
			"	vertLight = LightPos.xyz - gl_Position.xyz;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"}"
		);
		// compile it
		cube_vs.Compile();

		// set the fragment shader source
		cube_fs.Source(
			"#version 330\n"
			"in vec3 vertColor;"
			"in vec3 vertNormal;"
			"in vec3 vertLight;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = length(vertLight);"
			"	float d = l > 0? dot("
			"		normalize(vertNormal), "
			"		normalize(vertLight)"
			"	) / l : 0.0;"
			"	float i = 0.1 + 4.2*d;"
			"	fragColor = vec4(vertColor*i, 1.0);"
			"}"
		);
		// compile it
		cube_fs.Compile();

		// attach the shaders to the program
		cube_prog.AttachShader(cube_vs);
		cube_prog.AttachShader(cube_fs);
		// link and use it
		cube_prog.Link();
		cube_prog.Use();

		// Set the vertex shader source
		cmap_vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"uniform vec4 LightPos;"
			"uniform vec3 Offset;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"out vec3 vertColor;"
			"out vec3 vertNormal;"
			"out vec3 vertLight;"
			"void main(void)"
			"{"
			"	gl_Position = vec4(Position.xyz+Offset, 1.0);"
			"	vertColor = normalize(vec3(1.0, 1.0, 1.0) - Normal);"
			"	vertNormal = Normal;"
			"	vertLight = LightPos.xyz - gl_Position.xyz;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"}"
		);
		// compile it
		cmap_vs.Compile();

		// attach the shaders to the program
		cmap_prog.AttachShader(cmap_vs);
		cmap_prog.AttachShader(cube_fs);
		// link and use it
		cmap_prog.Link();
		cmap_prog.Use();

		// bind the VAO for the cube
		cube.Bind();

		// bind the VBO for the cube vertices
		cube_verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Vertices(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			cube_prog.Use();
			VertexAttribArray cube_attr(cube_prog, "Position");
			cube_attr.Setup(n_per_vertex, DataType::Float);
			cube_attr.Enable();

			cmap_prog.Use();
			VertexAttribArray cmap_attr(cmap_prog, "Position");
			cmap_attr.Setup(n_per_vertex, DataType::Float);
			cmap_attr.Enable();
		}

		// bind the VBO for the cube normals
		cube_normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			cube_prog.Use();
			VertexAttribArray cube_attr(cube_prog, "Normal");
			cube_attr.Setup(n_per_vertex, DataType::Float);
			cube_attr.Enable();

			cmap_prog.Use();
			VertexAttribArray cmap_attr(cmap_prog, "Normal");
			cmap_attr.Setup(n_per_vertex, DataType::Float);
			cmap_attr.Enable();
		}

		//
		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.CullFace(Face::Back);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto persp = CamMatrixf::Perspective(
			Degrees(25),
			double(width)/height,
			1, 100
		);
		cube_prog.Use();
		Uniform(cube_prog, "ProjectionMatrix").SetMatrix(persp);
		sphere_prog.Use();
		Uniform(sphere_prog, "ProjectionMatrix").SetMatrix(persp);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//

		auto cameraMatrix = CamMatrixf::Orbiting(
			Vec3f(),
			3.0,
			FullCircles(time / 8.0),
			Degrees(SineWave(time / 20.0) * 30)
		);
		Vec4f lightPos(Vec4f(light_path.Position(time / 10.0), 1.0));

		cube_prog.Use();
		Uniform(cube_prog, "CameraMatrix").SetMatrix(cameraMatrix);
		Uniform(cube_prog, "LightPos").Set(lightPos);
		auto object_offs = Uniform(cube_prog, "Offset");

		gl.FrontFace(make_cube.FaceWinding());
		cube.Bind();
		auto b=cube_offsets.begin(), e = cube_offsets.end();
		for(auto i=b; i!=e; ++i)
		{
			object_offs.Set(*i);
			cube_instr.Draw(cube_indices);
		}

		sphere_prog.Use();
		Uniform(sphere_prog, "CameraMatrix").SetMatrix(cameraMatrix);
		Uniform(sphere_prog, "LightPos").Set(lightPos);
		Uniform(sphere_prog, "Time").Set(GLfloat(time));

		gl.FrontFace(make_sphere.FaceWinding());
		sphere.Bind();
		sphere_instr.Draw(sphere_indices);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new CubeMapExample);
}

} // namespace oglplus
