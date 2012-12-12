/**
 *  @example oglplus/015_graph.cpp
 *  @brief Shows how to draw smooth lines and points
 *
 *  @oglplus_screenshot{015_graph}
 *
 *  Copyright 2008-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include <cmath>
#include <cassert>
#include <ctime>

#include "example.hpp"

namespace oglplus {

class GraphExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	// Program
	Program prog;

	// A vertex array object for the rendered cube
	VertexArray graph;

	// VBOs for the graph's vertices and edge element indices
	Buffer verts, edges;

	// Uniform variables
	LazyUniform<Mat4f> projection_matrix;
	LazyUniform<Mat4f> camera_matrix;


	// The number of nodes in the graph
	const GLuint node_count;
	// The number of edges in the graph
	GLuint edge_count;

	static double nrand(void)
	{
		return 2.0*(double(std::rand())/RAND_MAX - 0.5);
	}

	CubicBezierLoop<Vec3f, double> cam_path;
	CubicBezierLoop<Vec3f, double> tgt_path;

	static std::vector<Vec3f> make_cam_path_cps(void)
	{
		const Vec3f _points[6] = {
			Vec3f(-30.0f, -40.0f, -40.0f),
			Vec3f( 30.0f,   0.0f, -50.0f),
			Vec3f( 50.0f,  20.0f,  40.0f),
			Vec3f(-10.0f,  40.0f,  45.0f),
			Vec3f(-20.0f,  20.0f,   0.0f),
			Vec3f(-50.0f,   3.0f, -20.0f)
		};
		return std::vector<Vec3f>(_points, _points+6);
	}

	static std::vector<Vec3f> make_tgt_path_cps(void)
	{
		const Vec3f _points[6] = {
			Vec3f(-10.0f,   0.0f, -10.0f),
			Vec3f( 10.0f,  10.0f, -10.0f),
			Vec3f( 10.0f,   0.0f,  10.0f),
			Vec3f(-10.0f, - 5.0f,  15.0f),
			Vec3f(-10.0f, - 3.0f,   0.0f),
			Vec3f(-10.0f,   0.0f, -10.0f)
		};
		return std::vector<Vec3f>(_points, _points+6);
	}
public:
	GraphExample(void)
	 : prog()
	 , projection_matrix(prog, "ProjectionMatrix")
	 , camera_matrix(prog, "CameraMatrix")
	 , node_count(512)
	 , edge_count(0)
	 , cam_path(make_cam_path_cps())
	 , tgt_path(make_tgt_path_cps())
	{
		std::srand(std::time(0));

		// Vertex shader
		VertexShader vs;
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix;"
			"in vec4 Position;"
			"void main(void)"
			"{"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		Position;"
			"	gl_PointSize = 4.0 * gl_Position.w / gl_Position.z;"
			"}"
		);
		// compile it
		vs.Compile();

		// Fragment shader
		FragmentShader fs;
		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(0.0, 0.0, 0.0, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the cube
		graph.Bind();

		std::vector<GLfloat> positions(node_count * 3);
		// bind the VBO for the cube vertices
		verts.Bind(Buffer::Target::Array);
		{
			GLuint k = 0;
			for(GLuint p=0; p!=node_count; ++p)
			{
				positions[k++] = nrand() *120.0;
				positions[k++] = nrand() *  5.0;
				positions[k++] = nrand() *120.0;
			}
			assert(k == positions.size());

			// upload the data
			Buffer::Data(Buffer::Target::Array, positions);
			// setup the vertex attribs array for the vertices
			VertexAttribArray vert_attr(prog, "Position");
			vert_attr.Setup(3, DataType::Float);
			vert_attr.Enable();
		}

		// bind the VBO for cube edge indices
		edges.Bind(Buffer::Target::ElementArray);
		{
			std::vector<GLuint> edges;
			edges.reserve(node_count * 6);
			for(GLuint i=0; i!=node_count; ++i)
			{
				Vec3f pi(
					positions[i*3+0],
					positions[i*3+1],
					positions[i*3+2]
				);
				float min_dist = 1000.0f;
				GLuint m = i;
				for(GLuint j=i+1; j!=node_count; ++j)
				{
					Vec3f pj(
						positions[j*3+0],
						positions[j*3+1],
						positions[j*3+2]
					);
					float dist = Distance(pi, pj);
					if(min_dist > 1.0 && min_dist > dist)
					{
						min_dist = dist;
						m = j;
					}
				}
				min_dist *= 2.0f;
				GLuint done = 0;
				for(GLuint j=i+1; j!=node_count; ++j)
				{
					Vec3f pj(
						positions[j*3+0],
						positions[j*3+1],
						positions[j*3+2]
					);
					float dist = Distance(pi, pj);
					if(min_dist > dist)
					{
						float x = dist/min_dist;
						if(std::pow(nrand(), 2.0) >= x)
						{
							edges.push_back(i);
							edges.push_back(j);
							++done;
						}
					}
				}
				if(done == 0)
				{
					if(i != m)
					{
						edges.push_back(i);
						edges.push_back(m);
					}
				}
			}
			Buffer::Data(Buffer::Target::ElementArray, edges);
			assert(edges.size() % 2 == 0);
			edge_count = edges.size();
			positions.clear();
		}

		//
		gl.ClearColor(0.9f, 0.9f, 0.8f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::LineSmooth);
		gl.Enable(Capability::ProgramPointSize);
		gl.Enable(Capability::Blend);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);
	}

	void Reshape(GLuint width, GLuint height)
	{
		gl.Viewport(width, height);
		prog.Use();
		projection_matrix.Set(
			CamMatrixf::PerspectiveX(
				Degrees(48),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		// set the matrix for camera orbiting the origin
		camera_matrix.Set(
			CamMatrixf::LookingAt(
				cam_path.Position(time / 9.0),
				tgt_path.Position(time / 7.0)
			)
		);

		// draw the points
		gl.DrawArrays(PrimitiveType::Points, 0, node_count * 3);
		// draw the edges
		gl.DrawElements(
			PrimitiveType::Lines,
			edge_count,
			DataType::UnsignedInt
		);
	}

	bool Continue(double time)
	{
		return time < 60.0;
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& /*params*/)
{
	return std::unique_ptr<Example>(new GraphExample);
}

} // namespace oglplus
