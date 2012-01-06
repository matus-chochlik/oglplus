/**
 *  @file oglplus/shapes/spiral_sphere.hpp
 *  @brief Builder of a partial sphere shape made from spiraling bands
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_SPIRAL_SPHERE_1107121519_HPP
#define OGLPLUS_SHAPES_SPIRAL_SPHERE_1107121519_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/face_mode.hpp>

#include <cmath>

namespace oglplus {
namespace shapes {

/// Class providing data and instructions for rendering of a "spiral sphere"
class SpiralSphere
 : public DrawingInstructionWriter
{
private:
	const GLdouble _radius, _thickness;
	const size_t _bands, _divisions, _segments;

	size_t _vertex_count(void) const
	{
		return	(_bands * 2)*
			(_divisions + 1)*
			(_segments + 1)+
			(_bands * 2)*
			(_segments + 1);
	}

	template <typename T>
	void _make_vectors(
		std::vector<T>& dest,
		size_t& k,
		GLdouble sign,
		GLdouble radius
	) const
	{
		GLdouble b_leap = (M_PI) / GLdouble(_bands);
		GLdouble b_step = b_leap / GLdouble(_divisions);
		GLdouble s_step = (M_PI) / GLdouble(_segments);

		GLdouble m = sign * radius;

		for(size_t b=0; b!=_bands; ++b)
		{
			for(size_t d=0; d!=(_divisions+1); ++d)
			{
				GLdouble b_offs = 0.0;
				for(size_t s=0; s!=(_segments+1); ++s)
				{
					GLdouble b_angle =
						2*b*b_leap + d*b_step + b_offs;
					GLdouble cb = std::cos(b_angle);
					GLdouble sb = std::sin(b_angle);

					GLdouble s_angle = s*s_step;
					GLdouble cs = std::cos(s_angle);
					GLdouble ss = std::sin(s_angle);

					dest[k++] = m* ss * cb;
					dest[k++] = m* cs;
					dest[k++] = m* ss * -sb;
					b_offs += ss * s_step;
				}
			}
		}
	}

	template <typename T>
	void _make_uv_coords(std::vector<T>& dest, size_t& k) const
	{
		GLdouble b_leap = 0.5 / GLdouble(_bands);
		GLdouble b_step = b_leap / GLdouble(_divisions);
		GLdouble s_step = 1.0 / GLdouble(_segments);

		GLdouble u = 0.0;
		for(size_t b=0; b!=_bands; ++b)
		{
			for(size_t d=0; d!=(_divisions+1); ++d)
			{
				GLdouble v = 1.0;
				for(size_t s=0; s!=(_segments+1); ++s)
				{
					dest[k++] = u;
					dest[k++] = v;
					v -= s_step;
				}
				u += b_step;
			}
			u += b_leap;
		}
	}

	template <typename T>
	void _make_side_verts(std::vector<T>& dest, size_t& k) const
	{
		GLdouble b_leap = (M_PI) / GLdouble(_bands);
		GLdouble b_slip = b_leap * _thickness * 0.5;
		GLdouble s_step = (M_PI) / GLdouble(_segments);

		GLdouble m = _radius + _thickness * 0.5;
		GLdouble g = -1.0;

		for(size_t b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			for(size_t s=0; s!=(_segments+1); ++s)
			{
				GLdouble b_angle =
					b*b_leap + b_offs + g*b_slip;
				GLdouble cb = std::cos(b_angle);
				GLdouble sb = std::sin(b_angle);

				GLdouble s_angle = s*s_step;
				GLdouble cs = std::cos(s_angle);
				GLdouble ss = std::sin(s_angle);

				dest[k++] = m* ss * cb;
				dest[k++] = m* cs;
				dest[k++] = m* ss * -sb;
				b_offs += ss * s_step;
			}
			g *= -1.0;
		}
	}

	template <typename T>
	void _make_side_norms(std::vector<T>& dest, size_t& k) const
	{
		GLdouble b_leap = (M_PI) / GLdouble(_bands);
		GLdouble s_step = (M_PI) / GLdouble(_segments);

		GLfloat m = 1.0;
		for(size_t b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			for(size_t s=0; s!=(_segments+1); ++s)
			{
				GLdouble b_angle =
					b*b_leap + b_offs;
				GLdouble cb = std::cos(b_angle);
				GLdouble sb = std::sin(b_angle);

				GLdouble s_angle = s*s_step;
				GLdouble cs = std::cos(s_angle);
				GLdouble ss = std::sin(s_angle);

				dest[k++] = m* -sb;
				dest[k++] = m* 0.0;
				dest[k++] = m* cb;
				b_offs += ss * s_step;
			}
			m *= -1.0;
		}
	}

	template <typename T>
	void _make_side_uvs(std::vector<T>& dest, size_t& k) const
	{
		GLdouble b_leap = 0.5 / GLdouble(_bands);
		GLdouble b_slip = b_leap * _thickness * 0.5;
		GLdouble s_step = 1.0 / GLdouble(_segments);

		GLdouble g = -1.0;

		for(size_t b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			GLdouble v = 1.0;
			for(size_t s=0; s!=(_segments+1); ++s)
			{
				dest[k++] = b*b_leap + b_offs + g*b_slip;
				dest[k++] = v;
				v -= s_step;
			}
			g *= -1.0;
		}
	}
public:
	/// Creates a default spiral sphere
	SpiralSphere(void)
	 : _radius(1.0)
	 , _thickness(0.1)
	 , _bands(4)
	 , _divisions(8)
	 , _segments(48)
	{ }

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CCW;
	}

	/// Makes vertex coordinates and returns number of values per vertex
	template <typename T>
	GLuint Positions(std::vector<T>& dest) const
	{
		dest.resize(_vertex_count() * 3);
		size_t k = 0;
		//
		_make_vectors(dest, k,  1.0, _radius);
		_make_vectors(dest, k,  1.0, _radius + _thickness);
		_make_side_verts(dest, k);
		//
		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex normals and returns number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize(_vertex_count() * 3);
		size_t k = 0;
		//
		_make_vectors(dest, k, -1.0, 1.0);
		_make_vectors(dest, k,  1.0, 1.0);
		_make_side_norms(dest, k);
		//
		assert(k == dest.size());
		// 3 values per vertex
		return 3;
	}

	/// Makes vertex tangents and returns number of values per vertex
	template <typename T>
	GLuint Tangents(std::vector<T>& dest) const
	{
		// TODO
		return 0;
	}

	/// Makes texture-coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize(_vertex_count() * 2);
		size_t k = 0;
		//
		_make_uv_coords(dest, k);
		_make_uv_coords(dest, k);
		_make_side_uvs(dest, k);
		//
		assert(k == dest.size());
		// 2 values per vertex
		return 2;
	}

	/// The type of index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		assert(
			(1 << (sizeof(GLushort) * 8)) - 1 >=
			_vertex_count()
		);
		const size_t n =
			(_bands * 2)*
			(_divisions * 2)*
			(_segments + 1)+
			(_bands * 8)*
			(_segments + 1)
		;
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t eoffs, offs = 0;
		const size_t edge = _segments + 1;
		const size_t band = edge * (_divisions + 1);
		const size_t surface = _bands * band;

		for(size_t n=0; n!=2; ++n)
		{
			size_t edge1 = n ? edge : 0;
			size_t edge2 = n ? 0 : edge;
			for(size_t b=0; b!=_bands; ++b)
			{
				for(size_t d=0; d!=_divisions; ++d)
				{
					for(size_t s=0; s!=edge; ++s)
					{
						indices[k++] = offs + s + edge1;
						indices[k++] = offs + s + edge2;
					}
					offs += edge;
				}
				offs += edge;
			}
		}

		offs = 0;
		eoffs = 2*surface;

		for(size_t b=0; b!=_bands; ++b)
		{
			for(size_t s=0; s!=edge; ++s)
			{
				indices[k++] = eoffs + s;
				indices[k++] = offs + s;
			}
			offs += band;
			eoffs += edge * 2;
		}

		offs = _divisions * edge;
		eoffs = 2*surface + edge;

		for(size_t b=0; b!=_bands; ++b)
		{
			for(size_t s=0; s!=edge; ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = eoffs + s;
			}
			offs += band;
			eoffs += edge * 2;
		}

		offs = surface;
		eoffs = 2*surface;

		for(size_t b=0; b!=_bands; ++b)
		{
			for(size_t s=0; s!=edge; ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = eoffs + s;
			}
			offs += band;
			eoffs += edge * 2;
		}

		offs = surface + _divisions * edge;
		eoffs = 2*surface + edge;

		for(size_t b=0; b!=_bands; ++b)
		{
			for(size_t s=0; s!=edge; ++s)
			{
				indices[k++] = eoffs + s;
				indices[k++] = offs + s;
			}
			offs += band;
			eoffs += edge * 2;
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
		const size_t edge = _segments + 1;

		auto method = DrawOperation::Method::DrawElements;
		auto primitive_type = PrimitiveType::TriangleStrip;

		GLuint offs = 0;
		GLuint phase = 0;
		for(size_t n=0; n!=2; ++n)
		{
			for(size_t b=0; b!=_bands; ++b)
			{
				for(size_t d=0; d!=_divisions; ++d)
				{
					this->AddInstruction(
						instructions,
						{
							method,
							primitive_type,
							offs,
							GLuint(edge * 2),
							phase
						}
					);
					offs += edge * 2;
				}
			}
			++phase;
		}
		for(size_t n=0; n!=4; ++n)
		{
			for(size_t b=0; b!=_bands; ++b)
			{
				this->AddInstruction(
					instructions,
					{
						method,
						primitive_type,
						offs,
						GLuint(edge * 2),
						phase
					}
				);
				offs += edge * 2;
			}
		}
		return std::move(instructions);
	}
};

} // shapes
} // oglplus

#endif // include guard
