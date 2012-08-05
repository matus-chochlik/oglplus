/**
 *  @file oglplus/shapes/tetrahedrons.hpp
 *  @brief Special shape builder used in implicit surface polygonisation
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_TETRAHEDRONS_1201311347_HPP
#define OGLPLUS_SHAPES_TETRAHEDRONS_1201311347_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/face_mode.hpp>
#if !OGLPLUS_NO_VARIADIC_TEMPLATES
#include <oglplus/shapes/vert_attr_info.hpp>
#endif

#include <cmath>
#include <cassert>

namespace oglplus {
namespace shapes {

/// Provides data and instructions for rendering of cube filling tetrahedrons
class Tetrahedrons
 : public DrawingInstructionWriter
{
private:
	GLdouble _side;
	size_t _divisions;
public:
	/// Makes a unit sized tetrahedra filled cube with 10 divisions
	Tetrahedrons(void)
	 : _side(1.0)
	 , _divisions(10)
	{ }

	/// Makes a cube with the specified @p side and number of @p divisions
	Tetrahedrons(GLdouble side, size_t divisions)
	 : _side(side)
	 , _divisions(divisions)
	{
		assert(_side > 0.0);
		assert(divisions > 0);
	}

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	/// Makes vertex coordinates and returns number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		const size_t n = _divisions + 1;
		size_t k = 0;
		dest.resize(n*n*n*3+3);

		dest[k++] = T(0);
		dest[k++] = T(0);
		dest[k++] = T(0);

		GLdouble step = _side / _divisions;
		//
		for(size_t z=0; z!=n; ++z)
		for(size_t y=0; y!=n; ++y)
		for(size_t x=0; x!=n; ++x)
		{
			dest[k++] = x*step;
			dest[k++] = y*step;
			dest[k++] = z*step;
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes texture coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		const size_t n = _divisions + 1;
		size_t k = 0;
		dest.resize(n*n*n*3+3);

		dest[k++] = T(0);
		dest[k++] = T(0);
		dest[k++] = T(0);

		GLdouble step = 1.0 / _divisions;
		//
		for(size_t z=0; z!=n; ++z)
		for(size_t y=0; y!=n; ++y)
		for(size_t x=0; x!=n; ++x)
		{
			dest[k++] = x*step;
			dest[k++] = y*step;
			dest[k++] = z*step;
		}
		assert(k == dest.size());
		return 3;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** Tetrahedrons provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "TexCoord" the STR texture coordinates (TexCoordinates)
	 */
	typedef VertexAttribsInfo<Tetrahedrons> VertexAttribs;
#elif !OGLPLUS_NO_VARIADIC_TEMPLATES
	typedef VertexAttribsInfo<
		Tetrahedrons,
		VertexPositionsTag,
		VertexTexCoordinatesTag
	> VertexAttribs;
#endif

	/// The type of index container returned by Indices()
	typedef std::vector<GLuint> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray IndicesWithAdjacency(void) const
	{
		const size_t n = _divisions;
		const size_t a = (n+1);
		const size_t b = (n+1)*(n+1);
		//
		IndexArray indices(n*n*n*6*6);
		size_t k = 0;

		/*
		 *   (E)-----(F)
		 *   /|      /|
		 *  / |     / |
		 *(H)-----(G) |
		 * | (A)---|-(B)
		 * | /     | /
		 * |/      |/
		 *(D)-----(C)
		 *
		 */

		for(size_t z=0; z!=n; ++z)
		for(size_t y=0; y!=n; ++y)
		for(size_t x=0; x!=n; ++x)
		{
			size_t A = (z+0)*b + (y+0)*a + (x+0) + 1;
			size_t B = (z+0)*b + (y+0)*a + (x+1) + 1;
			size_t C = (z+1)*b + (y+0)*a + (x+1) + 1;
			size_t D = (z+1)*b + (y+0)*a + (x+0) + 1;
			size_t E = (z+0)*b + (y+1)*a + (x+0) + 1;
			size_t F = (z+0)*b + (y+1)*a + (x+1) + 1;
			size_t G = (z+1)*b + (y+1)*a + (x+1) + 1;
			size_t H = (z+1)*b + (y+1)*a + (x+0) + 1;
			size_t O = 0;

			indices[k++] = C;
			indices[k++] = A;
			indices[k++] = B;
			indices[k++] = O;
			indices[k++] = G;
			indices[k++] = O;

			indices[k++] = B;
			indices[k++] = G;
			indices[k++] = A;
			indices[k++] = O;
			indices[k++] = F;
			indices[k++] = O;

			indices[k++] = E;
			indices[k++] = G;
			indices[k++] = F;
			indices[k++] = O;
			indices[k++] = A;
			indices[k++] = O;

			indices[k++] = E;
			indices[k++] = G;
			indices[k++] = A;
			indices[k++] = O;
			indices[k++] = H;
			indices[k++] = O;

			indices[k++] = A;
			indices[k++] = G;
			indices[k++] = D;
			indices[k++] = O;
			indices[k++] = H;
			indices[k++] = O;

			indices[k++] = D;
			indices[k++] = G;
			indices[k++] = A;
			indices[k++] = O;
			indices[k++] = C;
			indices[k++] = O;
		}

		assert(k == indices.size());
		//
		// return the indices
		return indices;
	}

	/// Returns the instructions for rendering
	DrawingInstructions InstructionsWithAdjacency(void) const
	{
		const size_t n = _divisions;
		auto instructions = this->MakeInstructions();
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawElements;
		operation.mode = PrimitiveType::TrianglesAdjacency;
		operation.first = GLuint(0);
		operation.count = GLuint(n*n*n*6*6);
		operation.phase = 0;
		this->AddInstruction(instructions, operation);
		return instructions;
	}
};

} // shapes
} // oglplus

#endif // include guard
