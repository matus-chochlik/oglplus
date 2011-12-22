/**
 *  @file oglplus/shapes/cube.hpp
 *  @brief Cube builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_CUBE_1107121519_HPP
#define OGLPLUS_SHAPES_CUBE_1107121519_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/face_mode.hpp>

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
		const size_t A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7;
		dest = {
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
		dest = {
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
		dest = {
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
		return 3;
	}

	/// Makes the texture coordinates and returns the number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest = {
			T(1), T(1),
			T(1), T(0),
			T(0), T(1),
			T(0), T(1),
			T(1), T(0),
			T(0), T(0),

			T(1), T(1),
			T(1), T(0),
			T(0), T(1),
			T(1), T(0),
			T(0), T(0),
			T(0), T(1),

			T(1), T(1),
			T(1), T(0),
			T(0), T(1),
			T(1), T(0),
			T(0), T(0),
			T(0), T(1),

			T(0), T(1),
			T(1), T(1),
			T(1), T(0),
			T(0), T(1),
			T(1), T(0),
			T(0), T(0),

			T(1), T(1),
			T(1), T(0),
			T(0), T(0),
			T(1), T(1),
			T(0), T(0),
			T(0), T(1),

			T(0), T(1),
			T(1), T(1),
			T(0), T(0),
			T(0), T(0),
			T(1), T(1),
			T(1), T(0)
		};
		return 2;
	}

	/// The type of the index container returned by Indices()
	typedef std::vector<GLubyte> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		return IndexArray();
	}

	/// Returns the instructions for rendering of faces
	DrawingInstructions Instructions(void) const
	{
		return this->MakeInstructions({
			{
				DrawOperation::Method::DrawArrays,
				PrimitiveType::Triangles,
				0, 36
			}
		});
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
		IndexArray indices({
			 0,  1,  5,  2, //+x
			19, 22, 23, 18, //-x
			 6,  7, 10, 11, //+y
			26, 29, 24, 25, //-y
			12, 13, 16, 17, //+z
			31, 35, 32, 30  //-z
		});
		return std::move(indices);
	}

	/// Returns the instructions for rendering of edges
	DrawingInstructions EdgeInstructions(void) const
	{
		auto instructions = this->MakeInstructions();
		for(size_t r=0; r!=6; ++r)
		{
			this->AddInstruction(
				instructions,
				{
					DrawOperation::Method::DrawElements,
					PrimitiveType::LineLoop,
					GLuint(r*4), GLuint(4)
				}
			);
		}
		return std::move(instructions);
	}
};

} // shapes
} // oglplus

#endif // include guard
