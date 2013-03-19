/**
 *  @file oglplus/shapes/cube.hpp
 *  @brief Cube builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_CUBE_1107121519_HPP
#define OGLPLUS_SHAPES_CUBE_1107121519_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/shapes/vert_attr_info.hpp>

#include <cmath>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a cube
class Cube
 : public DrawingInstructionWriter
{
private:
	GLdouble _x, _y, _z;
public:
	/// Constructs a unit cube centered at the origin
	Cube(void)
	 : _x(1.0)
	 , _y(1.0)
	 , _z(1.0)
	{ }

	/// Constructs a cube with width, height, depth
	Cube(GLdouble w, GLdouble h, GLdouble d)
	 : _x(w)
	 , _y(h)
	 , _z(d)
	{ }

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	typedef GLuint (Cube::*VertexAttribFunc)(std::vector<GLfloat>&) const;

	/// Makes the vertices and returns the number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		/*
		 *   (E)-----(A)
		 *   /|      /|
		 *  / |     / |
		 *(F)-----(B) |
		 * | (H)---|-(D)
		 * | /     | /
		 * |/      |/
		 *(G)-----(C)
		 *
		 */
		const T half_x = T(_x)/T(2);
		const T half_y = T(_y)/T(2);
		const T half_z = T(_z)/T(2);
		const T c[8][3] = {
			{+half_x, +half_y, -half_z}, //(A)
			{+half_x, +half_y, +half_z}, //(B)
			{+half_x, -half_y, +half_z}, //(C)
			{+half_x, -half_y, -half_z}, //(D)
			{-half_x, +half_y, -half_z}, //(E)
			{-half_x, +half_y, +half_z}, //(F)
			{-half_x, -half_y, +half_z}, //(G)
			{-half_x, -half_y, -half_z}  //(H)
		};
		const unsigned A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7;
		const T _positions[108] = {
			c[A][0], c[A][1], c[A][2],
			c[D][0], c[D][1], c[D][2],
			c[B][0], c[B][1], c[B][2],
			c[B][0], c[B][1], c[B][2],
			c[D][0], c[D][1], c[D][2],
			c[C][0], c[C][1], c[C][2],

			c[A][0], c[A][1], c[A][2],
			c[B][0], c[B][1], c[B][2],
			c[E][0], c[E][1], c[E][2],
			c[B][0], c[B][1], c[B][2],
			c[F][0], c[F][1], c[F][2],
			c[E][0], c[E][1], c[E][2],

			c[B][0], c[B][1], c[B][2],
			c[C][0], c[C][1], c[C][2],
			c[F][0], c[F][1], c[F][2],
			c[C][0], c[C][1], c[C][2],
			c[G][0], c[G][1], c[G][2],
			c[F][0], c[F][1], c[F][2],

			c[E][0], c[E][1], c[E][2],
			c[F][0], c[F][1], c[F][2],
			c[G][0], c[G][1], c[G][2],
			c[E][0], c[E][1], c[E][2],
			c[G][0], c[G][1], c[G][2],
			c[H][0], c[H][1], c[H][2],

			c[C][0], c[C][1], c[C][2],
			c[D][0], c[D][1], c[D][2],
			c[H][0], c[H][1], c[H][2],
			c[C][0], c[C][1], c[C][2],
			c[H][0], c[H][1], c[H][2],
			c[G][0], c[G][1], c[G][2],

			c[A][0], c[A][1], c[A][2],
			c[E][0], c[E][1], c[E][2],
			c[D][0], c[D][1], c[D][2],
			c[D][0], c[D][1], c[D][2],
			c[E][0], c[E][1], c[E][2],
			c[H][0], c[H][1], c[H][2]
		};
		dest.assign(_positions, _positions+108);
		return 3;
	}

	/// Makes the normals and returns the number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		const T n[6][3] = {
			{+T(1),  T(0),  T(0)},
			{ T(0), +T(1),  T(0)},
			{ T(0),  T(0), +T(1)},
			{-T(1),  T(0),  T(0)},
			{ T(0), -T(1),  T(0)},
			{ T(0),  T(0), -T(1)}
		};
		const T _normals[108] = {
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],

			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],

			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],

			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],

			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],

			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2]
		};
		dest.assign(_normals, _normals+108);
		return 3;
	}

	/// Makes the tangents and returns the number of values per vertex
	template <typename T>
	GLuint Tangents(std::vector<T>& dest) const
	{
		const T n[6][3] = {
			{ T(0),  T(0), -T(1)},
			{+T(1),  T(0),  T(0)},
			{+T(1),  T(0),  T(0)},
			{ T(0),  T(0), +T(1)},
			{-T(1),  T(0),  T(0)},
			{-T(1),  T(0),  T(0)}
		};
		const T _tangents[108] = {
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],
			n[0][0], n[0][1], n[0][2],

			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],
			n[1][0], n[1][1], n[1][2],

			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],
			n[2][0], n[2][1], n[2][2],

			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],
			n[3][0], n[3][1], n[3][2],

			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],
			n[4][0], n[4][1], n[4][2],

			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2],
			n[5][0], n[5][1], n[5][2]
		};
		dest.assign(_tangents, _tangents+108);
		return 3;
	}

	/// Makes the texture coordinates and returns the number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		const T _tex_coords[108] = {
			T(1), T(1), T(0),
			T(1), T(0), T(0),
			T(0), T(1), T(0),
			T(0), T(1), T(0),
			T(1), T(0), T(0),
			T(0), T(0), T(0),

			T(1), T(1), T(1),
			T(1), T(0), T(1),
			T(0), T(1), T(1),
			T(1), T(0), T(1),
			T(0), T(0), T(1),
			T(0), T(1), T(1),

			T(1), T(1), T(2),
			T(1), T(0), T(2),
			T(0), T(1), T(2),
			T(1), T(0), T(2),
			T(0), T(0), T(2),
			T(0), T(1), T(2),

			T(0), T(1), T(3),
			T(1), T(1), T(3),
			T(1), T(0), T(3),
			T(0), T(1), T(3),
			T(1), T(0), T(3),
			T(0), T(0), T(3),

			T(1), T(1), T(4),
			T(1), T(0), T(4),
			T(0), T(0), T(4),
			T(1), T(1), T(4),
			T(0), T(0), T(4),
			T(0), T(1), T(4),

			T(0), T(1), T(5),
			T(1), T(1), T(5),
			T(0), T(0), T(5),
			T(0), T(0), T(5),
			T(1), T(1), T(5),
			T(1), T(0), T(5)
		};
		dest.assign(_tex_coords, _tex_coords+108);
		return 3;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** Cube provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normal" the vertex normal vectors (Normals)
	 *  - "Tangent" the vertex tangent vector (Tangents)
	 *  - "TexCoord" the ST texture coordinates (TexCoordinates)
	 */
	typedef VertexAttribsInfo<Cube> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		Cube,
		std::tuple<
			VertexPositionsTag,
			VertexNormalsTag,
			VertexTangentsTag,
			VertexTexCoordinatesTag
		>
	> VertexAttribs;
#endif

	/// Queries the bounding sphere coordinates and dimensions
	template <typename T>
	void BoundingSphere(Vector<T, 4>& center_and_radius) const
	{
		center_and_radius = Vector<T, 4>(
			T(0),
			T(0),
			T(0),
			T(std::sqrt(_x*_x + _y*_y + _z*_z))
		);
	}

	/// The type of the index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		return IndexArray();
	}

	/// Returns the instructions for rendering of faces
	DrawingInstructions Instructions(void) const
	{
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawArrays;
		operation.mode = PrimitiveType::Triangles;
		operation.first = 0;
		operation.count = 36;
		operation.restart_index = DrawOperation::NoRestartIndex();
		operation.phase = 0;

		return this->MakeInstructions(operation);
	}

	/// Returns element indices for the Cube's edges
	IndexArray EdgeIndices(void) const
	{
		/*
		 *   (E)-----(A)
		 *   /|      /|
		 *  / |     / |
		 *(F)-----(B) |
		 * | (H)---|-(D)
		 * | /     | /
		 * |/      |/
		 *(G)-----(C)
		 *
		 */
		GLushort _indices[24] = {
			 0,  1,  5,  2, //+x
			19, 22, 23, 18, //-x
			 6,  7, 10, 11, //+y
			26, 29, 24, 25, //-y
			12, 13, 16, 17, //+z
			31, 35, 32, 30  //-z
		};
		IndexArray indices(_indices, _indices+24);
		return indices;
	}

	/// Returns the instructions for rendering of edges
	DrawingInstructions EdgeInstructions(void) const
	{
		auto instructions = this->MakeInstructions();
		for(unsigned r=0; r!=6; ++r)
		{
			DrawOperation operation;
			operation.method = DrawOperation::Method::DrawElements;
			operation.mode = PrimitiveType::LineLoop;
			operation.first = GLuint(r*4);
			operation.count = GLuint(4);
			operation.restart_index = DrawOperation::NoRestartIndex();
			operation.phase = 0;

			this->AddInstruction(instructions, operation);
		}
		return instructions;
	}
};

} // shapes
} // oglplus

#endif // include guard
