/**
 *  @file oglplus/shapes/plane.hpp
 *  @brief Plane builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_PLANE_1107121519_HPP
#define OGLPLUS_SHAPES_PLANE_1107121519_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/face_mode.hpp>

#include <cmath>
#include <cassert>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Plane
class Plane
 : public DrawingInstructionWriter
{
private:
	Vec3f _point;
	Vec3f _u, _v;
	size_t _udiv, _vdiv;

	size_t _vertex_count(void) const
	{
		return (_udiv+1)*(_vdiv+1);
	}
public:
	/// Creates a default plane
	Plane(void)
	 : _point(0.0f, 0.0f, 0.0f)
	 , _u(1.0f, 0.0f, 0.0f)
	 , _v(0.0f, 0.0f,-1.0f)
	 , _udiv(2)
	 , _vdiv(2)
	{ }

	/// Creates a plane with going through origin specified by @p u and @p v
	Plane(const Vec3f u, const Vec3f v)
	 : _point(0.0f, 0.0f, 0.0f)
	 , _u(u)
	 , _v(v)
	 , _udiv(2)
	 , _vdiv(2)
	{
		assert(Length(_u) > 0.0f);
		assert(Length(_v) > 0.0f);
	}

	/// Creates a plane with going through @p p specified by @p u and @p v
	Plane(
		const Vec3f p,
		const Vec3f u,
		const Vec3f v,
		size_t udiv,
		size_t vdiv
	): _point(p)
	 , _u(u)
	 , _v(v)
	 , _udiv(udiv)
	 , _vdiv(vdiv)
	{
		assert(Length(_u) > 0.0f);
		assert(Length(_v) > 0.0f);
		assert(_udiv != 0);
		assert(_vdiv != 0);
	}

	const Vec3f& Point(void) const
	{
		return _point;
	}

	const Vec3f& U(void) const
	{
		return _u;
	}

	const Vec3f& V(void) const
	{
		return _v;
	}

	inline Vec3f Normal(void) const
	{
		return Normalized(Cross(_u, _v));
	}

	inline Vec3f Tangential(void) const
	{
		return Normalized(_u);
	}

	inline Vec3f Binormal(void) const
	{
		return Normalized(_v);
	}

	Vec4f Equation(void) const
	{
		return Vec4f(Normal(), -Dot(Normal(), _point));
	}

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	/// Makes vertex normals and returns number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		size_t k = 0, n = _vertex_count();
		dest.resize(n * 3);
		Vec3f normal = Normal();

		for(size_t i=0; i!=n; ++i)
		{
			dest[k++] = normal.x();
			dest[k++] = normal.y();
			dest[k++] = normal.z();
		}
		//
		assert(k == dest.size());
		// 3 values per vertex
		return 3;
	}

	/// Makes vertex tangents and returns number of values per vertex
	template <typename T>
	GLuint Tangents(std::vector<T>& dest) const
	{
		size_t k = 0, n = _vertex_count();
		dest.resize(n * 3);
		Vec3f tangent(Normalized(_u));

		for(size_t i=0; i!=n; ++i)
		{
			dest[k++] = tangent.x();
			dest[k++] = tangent.y();
			dest[k++] = tangent.z();
		}
		//
		assert(k == dest.size());
		// 3 values per vertex
		return 3;
	}

	/// Makes vertex coordinates and returns number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		size_t k = 0, n = _vertex_count();
		dest.resize(n * 3);


		Vec3f pos(_point - _u - _v);
		Vec3f ustep(_u * (2.0 / _udiv));
		Vec3f vstep(_v * (2.0 / _vdiv));

		size_t leap = _udiv+1;

		for(size_t j=0; j!=(_vdiv+1); ++j)
		{
			Vec3f tmp = pos;
			for(size_t i=0; i!=leap; ++i)
			{
				dest[k++] = tmp.x();
				dest[k++] = tmp.y();
				dest[k++] = tmp.z();
				tmp += ustep;
			}
			pos += vstep;
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes texture-coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		size_t k = 0, n = _vertex_count();
		dest.resize(n * 2);


		T uc, vc = T(0);
		T ustep = T(1) / _udiv;
		T vstep = T(1) / _vdiv;

		size_t leap = _udiv+1;


		for(size_t j=0; j!=(_vdiv+1); ++j)
		{
			uc = T(0);
			for(size_t i=0; i!=leap; ++i)
			{
				dest[k++] = uc;
				dest[k++] = vc;
				uc += ustep;
			}
			vc += vstep;
		}
		assert(k == dest.size());
		// 2 values per vertex
		return 2;
	}

	/// The type of index container returned by Indices()
	typedef std::vector<GLuint> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		size_t k = 0;
		size_t offs = 0, leap = _udiv + 1;
		IndexArray indices(2 * _vdiv * leap);

		for(size_t j=0; j!=_vdiv; ++j)
		{
			for(size_t i=0; i!=leap; ++i)
			{
				indices[k++] = offs + i;
				indices[k++] = offs + i + leap;
			}
			offs += leap;
		}
		assert(k == indices.size());
		//
		// return the indices
		return std::move(indices);
	}

	/// Returns the instructions for rendering
	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		for(size_t j=0; j!=_vdiv; ++j)
		{
			this->AddInstruction(
				instructions,
				{
					DrawOperation::Method::DrawElements,
					PrimitiveType::TriangleStrip,
					GLuint(j * (_udiv + 1) * 2),
					GLuint((_udiv + 1) * 2)
				}
			);
		}
		return std::move(instructions);
	}
};

} // shapes
} // oglplus

#endif // include guard
