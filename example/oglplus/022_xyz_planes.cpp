/**
 *  @example oglplus/022_xyz_planes.cpp
 *  @brief Shows how to use clipping for proper blending of overlapping objects
 *
 *  @image html 022_xyz_planes.png
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/torus.hpp>
#include <oglplus/shapes/plane.hpp>

#include <sstream>

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

	// similar helpers for the X-,Y- and Z-plane
	std::vector<shapes::Plane> make_plane;
	shapes::DrawingInstructions plane_instr;
	shapes::Plane::IndexArray plane_indices;

	// wrapper around the current OpenGL context
	Context gl;

	VertexShader torus_vs, plane_vs;
	FragmentShader torus_fs, plane_fs;

	Program torus_prog, plane_prog;

	// A vertex array objects for the rendered torus and planes
	VertexArray torus;
	Array<VertexArray> plane;

	// VBOs for the torus's vertex attributes
	Buffer torus_positions, torus_texcoords;
	// VBOs for plane vertex positions
	Array<Buffer> plane_positions;

	// Uniform references
	std::vector<ProgramUniform<GLfloat>> torus_clip_sign;
	std::vector<ProgramUniform<GLfloat>> plane_clip_sign;
public:
	TorusExample(void)
	 : make_torus(1.0, 0.5, 36, 24)
	 , torus_instr(make_torus.Instructions())
	 , torus_indices(make_torus.Indices())
	 , make_plane(
		{
			{Vec3f( 0.0f,  2.0f,  0.0f), Vec3f( 0.0f,  0.0f,  2.0f)},
			{Vec3f( 2.0f,  0.0f,  0.0f), Vec3f( 0.0f,  0.0f, -2.0f)},
			{Vec3f( 2.0f,  0.0f,  0.0f), Vec3f( 0.0f,  2.0f,  0.0f)}
		}
	), plane_instr(make_plane[0].Instructions())
	 , plane_indices(make_plane[0].Indices())
	 , torus_vs("Torus vertex")
	 , plane_vs("Plane vertex")
	 , torus_fs("Torus fragment")
	 , plane_fs("Plane fragment")
	 , torus_prog("Torus")
	 , plane_prog("Plane")
	 , plane(make_plane.size())
	 , plane_positions(make_plane.size())
	{
		std::stringstream plane_count_def;
		plane_count_def <<"#define PlaneCount "<<plane.size()<<'\n';
		torus_vs.Source({
			"#version 330\n",
			plane_count_def.str().c_str(),
			"uniform mat4 ProjectionMatrix, ModelMatrix, CameraMatrix;"
			"uniform float ClipSign[PlaneCount];"
			"uniform vec4 ClipPlane[PlaneCount];"
			"in vec4 Position;"
			"in vec2 TexCoord;"
			"out vec2 vertTexCoord;"
			"void main(void)"
			"{"
			"	vertTexCoord = TexCoord;"
			"	gl_Position = "
			"		ModelMatrix *"
			"		Position;"
			"	for(int p=0; p!=PlaneCount; ++p)"
			"	{"
			"		gl_ClipDistance[p] = "
			"			ClipSign[p]* "
			"			dot(ClipPlane[p], gl_Position);"
			"	}"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"}"
		});
		torus_vs.Compile();

		torus_fs.Source(
			"#version 330\n"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float i = ("
			"		int(vertTexCoord.x*36) % 2+"
			"		int(vertTexCoord.y*24) % 2"
			"	) % 2;"
			"	fragColor = vec4(1-i/2, 1-i/2, 1-i/2, 1.0);"
			"}"
		);
		torus_fs.Compile();

		torus_prog.AttachShader(torus_vs);
		torus_prog.AttachShader(torus_fs);
		torus_prog.Link();
		torus_prog.Use();

		// bind the VAO for the torus
		torus.Bind();

		// bind the VBO for the torus vertices
		torus_positions.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.Positions(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(torus_prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// bind the VBO for the torus UV-coordinates
		torus_texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_torus.TexCoordinates(data);
			// upload the data
			Buffer::Data(Buffer::Target::Array, data);
			// setup the vertex attribs array for the vertices
			VertexAttribArray attr(torus_prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		plane_vs.Source({
			"#version 330\n",
			plane_count_def.str().c_str(),
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"uniform float ClipSign[PlaneCount];"
			"uniform vec4 ClipPlane[PlaneCount];"
			"uniform vec3 Normal;"
			"in vec4 Position;"
			"out vec3 vertColor;"
			"void main(void)"
			"{"
			"	gl_Position = Position;"
			"	for(int p=0; p!=PlaneCount; ++p)"
			"	{"
			"		gl_ClipDistance[p] = "
			"			ClipSign[p]* "
			"			dot(ClipPlane[p], gl_Position);"
			"	}"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		gl_Position;"
			"	vertColor = normalize("
			"		abs(Normal) + "
			"		0.4*Position.xyz"
			"	);"
			"}"
		});
		plane_vs.Compile();

		plane_fs.Source(
			"#version 330\n"
			"in vec3 vertColor;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(vertColor, 0.7);"
			"}"
		);
		plane_fs.Compile();

		plane_prog.AttachShader(plane_vs);
		plane_prog.AttachShader(plane_fs);
		plane_prog.Link();
		plane_prog.Use();


		for(size_t p=0; p!=plane.size(); ++p)
		{
			plane[p].Bind();

			plane_positions[p].Bind(Buffer::Target::Array);
			{
				std::vector<GLfloat> data;
				GLuint n = make_plane[p].Positions(data);
				// upload the data
				Buffer::Data(Buffer::Target::Array, data);
				VertexAttribArray attr(plane_prog, "Position");
				attr.Setup(n, DataType::Float);
				attr.Enable();
			}
			{
				auto eq = make_plane[p].Equation();
				std::stringstream uni_name;
				uni_name << "ClipPlane[" << p << "]";
				ProgramUniform<Vec4f>(
					torus_prog,
					uni_name.str()
				).Set(eq);
				ProgramUniform<Vec4f>(
					plane_prog,
					uni_name.str()
				).Set(eq);
			}
			{
				std::stringstream uni_name;
				uni_name << "ClipSign[" << p << "]";
				torus_clip_sign.push_back(ProgramUniform<GLfloat>(
					torus_prog,
					uni_name.str())
				);
				plane_clip_sign.push_back(ProgramUniform<GLfloat>(
					plane_prog,
					uni_name.str())
				);
			}
		}

		//
		gl.ClearColor(0.8f, 0.8f, 0.7f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.FrontFace(make_torus.FaceWinding());
		gl.Enable(Capability::DepthTest);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		auto proj = CamMatrixf::Perspective(
			Degrees(48),
			double(width)/height,
			1, 100
		);
		ProgramUniform<Mat4f>(torus_prog, "ProjectionMatrix").Set(proj);
		ProgramUniform<Mat4f>(plane_prog, "ProjectionMatrix").Set(proj);
	}

	void RenderTorus(void)
	{
		torus_prog.Use();
		torus.Bind();
		torus_instr.Draw(torus_indices);
	}

	void RenderPlane(size_t p)
	{
		gl.Enable(Capability::Blend);
		plane_prog.Use();
		Uniform<Vec3f>(plane_prog, "Normal").Set(make_plane[p].Normal());
		plane[p].Bind();
		plane_instr.Draw(plane_indices);
		gl.Disable(Capability::Blend);
	}

	void BSP(const Mat4f& camera, size_t p)
	{
		assert(p < plane.size());
		// the normal vector of the plane
		Vec4f normal(make_plane[p].Normal(), 0.0);
		// check if we are seeing the front or the back face
		GLfloat sign = ((camera*normal).z() >= 0.0f)? 1.0f: -1.0f;
		bool at_leaf = p+1 == plane.size();

		gl.Enable(Functionality::ClipDistance, p);
		torus_clip_sign[p].Set(-sign);
		plane_clip_sign[p].Set(-sign);
		if(at_leaf) RenderTorus();
		else BSP(camera, p+1);
		gl.Disable(Functionality::ClipDistance, p);

		RenderPlane(p);

		gl.Enable(Functionality::ClipDistance, p);
		torus_clip_sign[p].Set(+sign);
		plane_clip_sign[p].Set(+sign);
		if(at_leaf) RenderTorus();
		else BSP(camera, p+1);
		gl.Disable(Functionality::ClipDistance, p);

	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		auto camera = CamMatrixf::Orbiting(
			Vec3f(),
			4.5,
			FullCircles(time / 10.0),
			Degrees(45.0 + SineWave(time / 7.0)*30.0)
		);
		auto model = ModelMatrixf::RotationX(FullCircles(time / 12.0));

		ProgramUniform<Mat4f>(plane_prog, "CameraMatrix").Set(camera);
		ProgramUniform<Mat4f>(torus_prog, "CameraMatrix").Set(camera);
		ProgramUniform<Mat4f>(torus_prog, "ModelMatrix").Set(model);

		BSP(camera, 0);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new TorusExample);
}

} // namespace oglplus
