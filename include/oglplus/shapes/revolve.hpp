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
	const std::vector<Type> _sections, _section_factors;
	const size_t _rings;

	const std::vector<Vector<Type, 3>> _positions_0, _positions_1;
	const std::vector<Vector<Type, 3>> _normals_0, _normals_1;
	const std::vector<Vector<Type, 3>> _tex_coords_0, _tex_coords_1;

	static Vector<Type, 3> _mix(
		const Vector<Type, 3>& a,
		const Vector<Type, 3>& b,
		Type factor
	)
	{
		if(factor < Type(0)) factor = Type(0);
		if(factor > Type(1)) factor = Type(1);
		return a * (Type(1) - factor) + b * factor;
	}

	Vector<Type, 3> _get_position(size_t ring, size_t section) const
	{
		return _mix(
			_positions_0[ring],
			_positions_1[ring],
			_section_factors[section]
		);
	}

	Vector<Type, 3> _get_normal(size_t ring, size_t section) const
	{
		return _mix(
			_normals_0[ring],
			_normals_1[ring],
			_section_factors[section]
		);
	}

	Vector<Type, 3> _get_tex_coord(size_t ring, size_t section) const
	{
		return _mix(
			_tex_coords_0[ring],
			_tex_coords_1[ring],
			_section_factors[section]
		);
	}

	static std::vector<Type> _make_default_sections(size_t sections)
	{
		std::vector<Type> result(sections + 1);
		const Type s_step = Type(1) / Type(sections);
		Type s = Type(0);
		for(auto i=result.begin(), e=result.end(); i!=e; ++i, s+=s_step)
			*i = s;
		return result;
	}

	static std::vector<Vector<Type, 3>> _calculate_normals(
		const std::vector<Vector<Type, 3>>& pos,
		const std::vector<Vector<Type, 3>>& nml
	)
	{
		if(!nml.empty())
		{
			assert(pos.size() == nml.size());
			return nml;
		}
		std::vector<Vector<Type, 3>> result(pos.size());

		const size_t n = result.size()-1;
		const Vec3f tgnt(0.0, 0.0, -1.0);

		result[0] = Normalized(Cross(tgnt, pos[1] - pos[0]));
		for(size_t i=1; i!=n; ++i)
			result[i] = Normalized(Cross(tgnt, pos[i+1]-pos[i-1]));
		result[n] = Normalized(Cross(tgnt, pos[n] - pos[n-1]));
		return result;
	}

	void _check(void)
	{
		assert(_rings > 1);
		assert(_sections.size() > 2);
		assert(_sections.size() == _section_factors.size());

		assert(_positions_0.size() == _rings);
		assert(_positions_1.size() == _rings);
		assert(_normals_0.size() == _rings);
		assert(_normals_1.size() == _rings);
		assert(_tex_coords_0.size() == _rings);
		assert(_tex_coords_1.size() == _rings);
	}
public:
	/// Creates a shape by revolving curve approximation around the y-axis
	RevolveY(
		size_t sections,
		const std::vector<Vector<Type, 3>>& positions,
		const std::vector<Vector<Type, 3>>& normals,
		const std::vector<Vector<Type, 3>>& tex_coords
	): _sections(_make_default_sections(sections))
	 , _section_factors(_sections.size(), Type(0))
	 , _rings(positions.size())
	 , _positions_0(positions)
	 , _positions_1(_positions_0)
	 , _normals_0(_calculate_normals(_positions_0, normals))
	 , _normals_1(_normals_0)
	 , _tex_coords_0(tex_coords)
	 , _tex_coords_1(_tex_coords_0)
	{
		_check();
	}

	/// Creates a shape by revolving curve approximation around the y-axis
	RevolveY(
		const std::vector<Type>& section_factors,
		const std::vector<Vector<Type, 3>>& positions_0,
		const std::vector<Vector<Type, 3>>& positions_1,
		const std::vector<Vector<Type, 3>>& normals_0,
		const std::vector<Vector<Type, 3>>& normals_1,
		const std::vector<Vector<Type, 3>>& tex_coords_0,
		const std::vector<Vector<Type, 3>>& tex_coords_1
	): _sections(_make_default_sections(section_factors.size()-1))
	 , _section_factors(section_factors)
	 , _rings(positions_0.size())
	 , _positions_0(positions_0)
	 , _positions_1(positions_1)
	 , _normals_0(_calculate_normals(_positions_0, normals_0))
	 , _normals_1(_calculate_normals(_positions_1, normals_1))
	 , _tex_coords_0(tex_coords_0)
	 , _tex_coords_1(tex_coords_1)
	{
		_check();
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
		dest.resize(_rings * _sections.size() * 3);
		size_t k = 0;
		//
		for(size_t si=0, sn=_sections.size(); si!=sn; ++si)
		{
			const auto angle = FullCircles(_sections[si]);
			const auto mat = ModelMatrix<Type>::RotationY(angle);

			for(size_t r=0; r!=_rings; ++r)
			{
				const Vector<Type, 4> in(_get_position(r, si), 1);
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
		dest.resize(_rings * _sections.size() * 3);
		size_t k = 0;
		//
		for(size_t si=0, sn=_sections.size(); si!=sn; ++si)
		{
			const auto angle = FullCircles(_sections[si]);
			const auto mat = ModelMatrix<Type>::RotationY(angle);

			for(size_t r=0; r!=_rings; ++r)
			{
				const Vector<Type, 4> in(_get_normal(r, si), 0);
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
		dest.resize(_rings * _sections.size() * 3);
		size_t k = 0;

		const Vector<Type, 4> in(0.0, 0.0, -1.0, 0.0);

		for(size_t si=0, sn=_sections.size(); si!=sn; ++si)
		{
			const auto angle = FullCircles(_sections[si]);
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
		dest.resize(_rings * _sections.size() * 3);
		size_t k = 0;
		//
		const Vector<Type, 4> in(0.0, 0.0, -1.0, 0.0);

		for(size_t si=0, sn=_sections.size(); si!=sn; ++si)
		{
			const T u_mult = _sections[si];

			for(size_t r=0; r!=_rings; ++r)
			{
				auto tc = _get_tex_coord(r, si);
				dest[k++] = tc.x()*u_mult;
				dest[k++] = tc.y();
				dest[k++] = tc.z();
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
		const size_t sn = _sections.size() - 1;
		const size_t n = 2 * _rings * sn;
		assert((1<<(sizeof(GLushort)*8)) - 1 >= n);
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t offs = 0;
		// the triangle strips
		for(size_t s=0; s!=sn; ++s)
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
	}
*/

	/// Returns the instructions for rendering
	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		const size_t sn = _sections.size() - 1;
		const size_t step = _rings * 2;
		for(size_t s=0; s!=sn; ++s)
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
	}
*/
};

} // shapes
} // oglplus

#endif // include guard
