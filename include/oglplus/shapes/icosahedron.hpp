/**
 *  @file oglplus/shapes/icosahedron.hpp
 *  @brief Icosahedron builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_ICOSAHEDRON_1206011111_HPP
#define OGLPLUS_SHAPES_ICOSAHEDRON_1206011111_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/shapes/vert_attr_info.hpp>
#include <oglplus/vector.hpp>

namespace oglplus {
namespace shapes {

class IcosahedronBase
{
protected:
	static const GLushort* _indices(void);
	static const GLdouble* _positions(void);
};

/// Class providing vertex attributes and instructions for drawing of a icosahedron
class SimpleIcosahedron
 : public DrawingInstructionWriter
 , public IcosahedronBase
{
public:
	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	typedef GLuint (SimpleIcosahedron::*VertexAttribFunc)(std::vector<GLfloat>&) const;

	/// Makes the positions and returns the number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		const GLdouble* p = _positions();
		dest.assign(p, p+12*3);
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
		SimpleIcosahedron,
		std::tuple<VertexPositionsTag>
	> VertexAttribs;
#endif

	/// Queries the bounding sphere coordinates and dimensions
	template <typename T>
	void BoundingSphere(Vector<T, 4>& center_and_radius) const
	{
		center_and_radius = Vector<T, 4>(T(0), T(0), T(0), T(1));
	}

	/// The type of the index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		const GLushort* i = _indices();
		return IndexArray(i, i+20*3);
	}

	/// Returns the instructions for rendering of faces
	DrawingInstructions Instructions(void) const
	{
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawElements;
		operation.mode = PrimitiveType::Triangles;
		operation.first = 0;
		operation.count = 20*3;
		operation.restart_index = DrawOperation::NoRestartIndex();
		operation.phase = 0;

		return this->MakeInstructions(operation);
	}
};

/// Class providing vertex attributes and instructions for drawing of a icosahedron
class Icosahedron
 : public DrawingInstructionWriter
 , public IcosahedronBase
{
public:
	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	typedef GLuint (Icosahedron::*VertexAttribFunc)(std::vector<GLfloat>&) const;

	/// Makes the positions and returns the number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		dest.resize(20*3*3);

		const GLdouble* p = _positions();
		const GLushort* i = _indices();

		for(GLuint f=0; f!=20; ++f)
		{
			for(GLuint v=0; v!=3; ++v)
			{
				for(GLuint c=0; c!=3; ++c)
				{
					dest[f*9+v*3+c] = p[i[f*3+v]*3+c];
				}
			}
		}
		return 3;
	}

	/// Makes the normals and returns the number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize(20*3*3);

		const GLdouble* p = _positions();
		const GLushort* i = _indices();

		for(GLuint f=0; f!=20; ++f)
		{
			Vector<T, 3> v0(p+i[f*3+0]*3, 3);
			Vector<T, 3> v1(p+i[f*3+1]*3, 3);
			Vector<T, 3> v2(p+i[f*3+2]*3, 3);
			Vector<T, 3> fn(Normalized(Cross(v1-v0, v2-v0)));

			for(GLuint v=0; v!=3; ++v)
			{
				for(GLuint c=0; c!=3; ++c)
				{
					dest[f*9+v*3+c] = fn[c];
				}
			}
		}
		return 3;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** Icosahedron provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normals" the vertex normals (Normals)
	 */
	typedef VertexAttribsInfo<Icosahedron> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		Icosahedron,
		std::tuple<
			VertexPositionsTag,
			VertexNormalsTag
		>
	> VertexAttribs;
#endif

	/// Queries the bounding sphere coordinates and dimensions
	template <typename T>
	void BoundingSphere(Vector<T, 4>& center_and_radius) const
	{
		center_and_radius = Vector<T, 4>(T(0), T(0), T(0), T(1));
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
		operation.count = 20*3;
		operation.restart_index = DrawOperation::NoRestartIndex();
		operation.phase = 0;

		return this->MakeInstructions(operation);
	}
};

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
OGLPLUS_LIB_FUNC
const GLushort* IcosahedronBase::_indices(void)
{
	static const GLushort indices[20*3] = {
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
	return indices;
}

OGLPLUS_LIB_FUNC
const GLdouble* IcosahedronBase::_positions(void)
{
	static const GLdouble positions[12*3] = {
		 0.000,  1.000,  0.000,
		 0.894,  0.447,  0.000,
		 0.276,  0.447,  0.851,
		-0.724,  0.447,  0.526,
		-0.724,  0.447, -0.526,
		 0.276,  0.447, -0.851,
		 0.724, -0.447,  0.526,
		-0.276, -0.447,  0.851,
		-0.894, -0.447,  0.000,
		-0.276, -0.447, -0.851,
		 0.724, -0.447, -0.526,
		 0.000, -1.000,  0.000
	};
	return positions;
}
#endif // OGLPLUS_LINK_LIBRARY

} // shapes
} // oglplus

#endif // include guard
