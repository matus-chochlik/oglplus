/**
 *  @file oglplus/shapes/icosahedron.hpp
 *  @brief Icosahedron builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_ICOSAHEDRON_1206011111_HPP
#define OGLPLUS_SHAPES_ICOSAHEDRON_1206011111_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/shapes/vert_attr_info.hpp>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for drawing of a icosahedron
class Icosahedron
 : public DrawingInstructionWriter
{
private:
public:
	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	typedef GLuint (Icosahedron::*VertexAttribFunc)(std::vector<GLfloat>&) const;

	/// Makes the vertices and returns the number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		const T _positions[12*3] = {
			T( 0.000), T( 1.000), T( 0.000), // (A)
			T( 0.894), T( 0.447), T( 0.000), // (B)
			T( 0.276), T( 0.447), T( 0.851), // (C)
			T(-0.724), T( 0.447), T( 0.526), // (D)
			T(-0.724), T( 0.447), T(-0.526), // (E)
			T( 0.276), T( 0.447), T(-0.851), // (F)
			T( 0.724), T(-0.447), T( 0.526), // (G)
			T(-0.276), T(-0.447), T( 0.851), // (H)
			T(-0.894), T(-0.447), T( 0.000), // (I)
			T(-0.276), T(-0.447), T(-0.851), // (J)
			T( 0.724), T(-0.447), T(-0.526), // (K)
			T( 0.000), T(-1.000), T( 0.000)  // (L)
		};
		dest.assign(_positions, _positions+12*3);
		return 3;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** Icosahedron provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 */
	typedef VertexAttribsInfo<Icosahedron> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		Icosahedron,
		std::tuple<
			VertexPositionsTag
		>
	> VertexAttribs;
#endif

	/// The type of the index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		const GLushort _indices[20*3] = {
			 2,  1,  0,
			 3,  2,  0,
			 4,  3,  0,
			 5,  4,  0,
			 1,  5,  0,
			11,  6,  7,
			11,  7,  8,
			11,  8,  9,
			11,  9, 10,
			11, 10,  6,
			 1,  2,  6,
			 2,  3,  7,
			 3,  4,  8,
			 4,  5,  9,
			 5,  1, 10,
			 2,  7,  6,
			 3,  8,  7,
			 4,  9,  8,
			 5, 10,  9,
			 1,  6, 10
		};
		return IndexArray(_indices, _indices+20*3);
	}

	/// Returns the instructions for rendering of faces
	DrawingInstructions Instructions(
		PrimitiveType mode = PrimitiveType::Triangles
	) const
	{
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawElements;
		operation.mode = mode;
		operation.first = 0;
		operation.count = 20*3;
		operation.restart_index = DrawOperation::NoRestartIndex();
		operation.phase = 0;

		return this->MakeInstructions(operation);
	}
};

} // shapes
} // oglplus

#endif // include guard
