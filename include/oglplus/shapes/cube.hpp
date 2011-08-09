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
	GLuint Vertices(std::vector<T>& dest) const
	{
		const T c[8][3] = {
			{+T(_x)/T(2), +T(_y)/T(2), -T(_z)/T(2)},
			{+T(_x)/T(2), +T(_y)/T(2), +T(_z)/T(2)},
			{+T(_x)/T(2), -T(_y)/T(2), +T(_z)/T(2)},
			{+T(_x)/T(2), -T(_y)/T(2), -T(_z)/T(2)},
			{-T(_x)/T(2), +T(_y)/T(2), -T(_z)/T(2)},
			{-T(_x)/T(2), +T(_y)/T(2), +T(_z)/T(2)},
			{-T(_x)/T(2), -T(_y)/T(2), +T(_z)/T(2)},
			{-T(_x)/T(2), -T(_y)/T(2), -T(_z)/T(2)}
		};
		dest = {
			c[0][0], c[0][1], c[0][2],
			c[3][0], c[3][1], c[3][2],
			c[1][0], c[1][1], c[1][2],
			c[1][0], c[1][1], c[1][2],
			c[3][0], c[3][1], c[3][2],
			c[2][0], c[2][1], c[2][2],

			c[0][0], c[0][1], c[0][2],
			c[1][0], c[1][1], c[1][2],
			c[4][0], c[4][1], c[4][2],
			c[1][0], c[1][1], c[1][2],
			c[5][0], c[5][1], c[5][2],
			c[4][0], c[4][1], c[4][2],

			c[1][0], c[1][1], c[1][2],
			c[2][0], c[2][1], c[2][2],
			c[5][0], c[5][1], c[5][2],
			c[2][0], c[2][1], c[2][2],
			c[6][0], c[6][1], c[6][2],
			c[5][0], c[5][1], c[5][2],

			c[4][0], c[4][1], c[4][2],
			c[5][0], c[5][1], c[5][2],
			c[6][0], c[6][1], c[6][2],
			c[4][0], c[4][1], c[4][2],
			c[6][0], c[6][1], c[6][2],
			c[7][0], c[7][1], c[7][2],

			c[2][0], c[2][1], c[2][2],
			c[3][0], c[3][1], c[3][2],
			c[7][0], c[7][1], c[7][2],
			c[2][0], c[2][1], c[2][2],
			c[7][0], c[7][1], c[7][2],
			c[6][0], c[6][1], c[6][2],

			c[0][0], c[0][1], c[0][2],
			c[4][0], c[4][1], c[4][2],
			c[3][0], c[3][1], c[3][2],
			c[3][0], c[3][1], c[3][2],
			c[4][0], c[4][1], c[4][2],
			c[7][0], c[7][1], c[7][2]
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
			{ T(0),  T(0),  +(1)},
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

	/// Returns the instructions for rendering
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
};

} // shapes
} // oglplus

#endif // include guard
