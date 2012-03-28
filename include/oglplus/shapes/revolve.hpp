/**
 *  @file oglplus/shapes/revolve.hpp
 *  @brief Shape builders revolving splines in full circles
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_REVOLVE_1107121519_HPP
#define OGLPLUS_SHAPES_REVOLVE_1107121519_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/shapes/vert_attr_info.hpp>
#include <oglplus/face_mode.hpp>

#include <oglplus/vector.hpp>
#include <oglplus/matrix.hpp>

#include <cmath>

namespace oglplus {
namespace shapes {

/// Class providing attributes and instructions for rendering of a revolved shape
template <typename Type>
class RevolveY
 : public DrawingInstructionWriter
{
private:
	const std::vector<Vector<Type, 3>> _positions;
	std::vector<Vector<Type, 3>> _normals;
	std::vector<Vector<Type, 3>> _tex_coords;
	const size_t _sections, _rings;

	void _calculate_normals(void)
	{
		assert(_normals.empty());
		_normals.resize(_positions.size());
		const size_t n = _normals.size()-1;
		const Vec3f tangent(0.0, 0.0, -1.0);
		_normals[0] = Normalized(Cross(
			tangent,
			_positions[1] - _positions[0]
		));
		for(size_t i=1; i!=n; ++i)
		{
			_normals[i] = Normalized(Cross(
				tangent,
				_positions[i+1] - _positions[i-1]
			));
		}
		_normals[n] = Normalized(Cross(
			tangent,
			_positions[n] - _positions[n-1]
		));
	}

	void _check_and_init(void)
	{
		assert(_rings > 1);
		assert(_sections > 2);
		if(_normals.empty()) _calculate_normals();
	}
public:
	/// Creates a shape by revolving curve approximation around the y-axis
	RevolveY(
		size_t sections,
		const std::vector<Vector<Type, 3>>& positions,
		const std::vector<Vector<Type, 3>>& normals,
		const std::vector<Vector<Type, 3>>& tex_coords
	): _positions(positions)
	 , _normals(normals)
	 , _tex_coords(tex_coords)
	 , _sections(sections)
	 , _rings(_positions.size())
	{
		_check_and_init();
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
		dest.resize((_rings) * (_sections + 1) * 3);
		size_t k = 0;
		//
		const GLdouble s_step = (1.0) / GLdouble(_sections);

		for(size_t s=0; s!=(_sections+1); ++s)
		{
			const auto angle = FullCircles(s*s_step);
			const auto mat = ModelMatrix<Type>::RotationY(angle);

			for(size_t r=0; r!=_rings; ++r)
			{
				const Vector<Type, 4> in(_positions[r], 1.0);
				const Vector<Type, 4> out = mat * in;

				dest[k++] = out.x();
				dest[k++] = out.y();
				dest[k++] = out.z();
			}
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex normals and returns number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize((_rings) * (_sections + 1) * 3);
		size_t k = 0;
		//
		const GLdouble s_step = (1.0) / GLdouble(_sections);

		for(size_t s=0; s!=(_sections+1); ++s)
		{
			const auto angle = FullCircles(s*s_step);
			const auto mat = ModelMatrix<Type>::RotationY(angle);

			for(size_t r=0; r!=_rings; ++r)
			{
				const Vector<Type, 4> in(_normals[r], 0.0);
				const Vector<Type, 4> out = mat * in;

				dest[k++] = out.x();
				dest[k++] = out.y();
				dest[k++] = out.z();
			}
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex tangents and returns number of values per vertex
	template <typename T>
	GLuint Tangents(std::vector<T>& dest) const
	{
		dest.resize((_rings) * (_sections + 1) * 3);
		size_t k = 0;
		//
		GLdouble s_step = (1.0) / GLdouble(_sections);

		const Vector<Type, 4> in(0.0, 0.0, -1.0, 0.0);

		for(size_t s=0; s!=(_sections+1); ++s)
		{
			const auto angle = FullCircles(s*s_step);
			const auto mat = ModelMatrix<Type>::RotationY(angle);
			const auto out = mat * in;

			for(size_t r=0; r!=_rings; ++r)
			{
				dest[k++] = out.x();
				dest[k++] = out.y();
				dest[k++] = out.z();
			}
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes texture coordinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize((_rings) * (_sections + 1) * 3);
		size_t k = 0;
		//
		GLdouble s_step = (1.0) / GLdouble(_sections);

		const Vector<Type, 4> in(0.0, 0.0, -1.0, 0.0);

		for(size_t s=0; s!=(_sections+1); ++s)
		{
			const T u_mult = s*s_step;
			const auto angle = FullCircles(u_mult);

			for(size_t r=0; r!=_rings; ++r)
			{
				dest[k++] = _tex_coords[r].x()*u_mult;
				dest[k++] = _tex_coords[r].y();
				dest[k++] = _tex_coords[r].z();
			}
		}
		assert(k == dest.size());
		return 3;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** Torus provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normal" the vertex normal vectors (Normals)
	 *  - "Tangent" the vertex tangent vector (Tangents)
	 *  - "TexCoord" the ST texture coordinates (TexCoordinates)
	 */
	typedef VertexAttribsInfo<RevolveY> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		RevolveY,
		VertexPositionsTag,
		VertexNormalsTag,
		VertexTangentsTag,
		VertexTexCoordinatesTag
	> VertexAttribs;
#endif

	/// The type of index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		const size_t n = 2 * (_rings)*(_sections);
		assert((1<<(sizeof(GLushort)*8)) - 1 >= n);
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t offs = 0;
		// the triangle strips
		for(size_t s=0; s!=_sections; ++s)
		{
			for(size_t r=0; r!=_rings; ++r)
			{
				indices[k++] = offs + r + _rings;
				indices[k++] = offs + r;
			}
			offs += _rings;
		}
		assert(k == indices.size());
		//
		// return the indices
		return std::move(indices);
	}

	/// Returns element indices that are used with the drawing instructions
/* TODO
	IndexArray IndicesWithAdjacency(void) const
	{
		const size_t m = (_rings)*(_sections + 1);
		const size_t n = 4 * m;
		assert((1<<(sizeof(GLushort)*8)) - 1 >= n);
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t offs = 0;

		for(size_t r=0; r!=(_rings); ++r)
		{
			indices[k++] = offs;
			indices[k++] = offs + (2*_sections);
			indices[k++] = offs + (_sections+1);
			for(size_t s=0; s!=_sections; ++s)
			{
				indices[k++] = (offs + m-(_sections+1))%m + s+1;
				indices[k++] = offs + s + 1;
				indices[k++] = (offs + 2*(_sections+1)) % m + s;
				indices[k++] = offs + (_sections+1) + s + 1;
			}
			indices[k++] = offs + 1;
			offs += _sections + 1;
		}
		assert(k == indices.size());
		//
		// return the indices
		return std::move(indices);
	}
*/

	/// Returns the instructions for rendering
	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		size_t step = _rings * 2;
		for(size_t s=0; s!=_sections; ++s)
		{
			this->AddInstruction(
				instructions,
				{
					DrawOperation::Method::DrawElements,
					PrimitiveType::TriangleStrip,
					GLuint(s * step),
					GLuint(step),
					0
				}
			);
		}
		return std::move(instructions);
	}

	/// Returns the instructions for rendering
/* TODO
	DrawingInstructions InstructionsWithAdjacency(void) const
	{
		auto instructions = this->MakeInstructions();
		for(size_t r=0; r!=_rings; ++r)
		{
			this->AddInstruction(
				instructions,
				{
					DrawOperation::Method::DrawElements,
					PrimitiveType::TriangleStripAdjacency,
					GLuint(r * (_sections + 1) * 4),
					GLuint((_sections + 1) * 4),
					0
				}
			);
		}
		return std::move(instructions);
	}
*/
};

} // shapes
} // oglplus

#endif // include guard
