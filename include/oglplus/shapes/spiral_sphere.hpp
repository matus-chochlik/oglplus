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

#include <oglplus/shapes/vert_attr_info.hpp>

#include <oglplus/math.hpp>

namespace oglplus {
namespace shapes {

/// Class providing data and instructions for rendering of a "spiral sphere"
class SpiralSphere
 : public DrawingInstructionWriter
{
private:
	const GLdouble _radius, _thickness;
	const unsigned _bands, _divisions, _segments;

	unsigned _vertex_count(void) const
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
		unsigned& k,
		GLdouble sign,
		GLdouble radius
	) const
	{
		GLdouble b_leap = (math::pi()) / GLdouble(_bands);
		GLdouble b_step = b_leap / GLdouble(_divisions);
		GLdouble s_step = (math::pi()) / GLdouble(_segments);

		GLdouble m = sign * radius;

		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned d=0; d!=(_divisions+1); ++d)
			{
				GLdouble b_offs = 0.0;
				for(unsigned s=0; s!=(_segments+1); ++s)
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
	void _make_tangents(
		std::vector<T>& dest,
		unsigned& k,
		GLdouble sign
	) const
	{
		GLdouble b_leap = (math::pi()) / GLdouble(_bands);
		GLdouble b_step = b_leap / GLdouble(_divisions);
		GLdouble s_step = (math::pi()) / GLdouble(_segments);

		GLdouble m = sign;

		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned d=0; d!=(_divisions+1); ++d)
			{
				GLdouble b_offs = 0.0;
				for(unsigned s=0; s!=(_segments+1); ++s)
				{
					GLdouble b_angle =
						2*b*b_leap + d*b_step + b_offs;
					GLdouble cb = std::cos(b_angle);
					GLdouble sb = std::sin(b_angle);

					GLdouble s_angle = s*s_step;
					GLdouble ss = std::sin(s_angle);

					dest[k++] = m*-sb;
					dest[k++] = T(0);
					dest[k++] = m* cb;
					b_offs += ss * s_step;
				}
			}
		}
	}

	template <typename T>
	void _make_uv_coords(std::vector<T>& dest, unsigned& k) const
	{
		GLdouble b_leap = 0.5 / GLdouble(_bands);
		GLdouble b_step = b_leap / GLdouble(_divisions);
		GLdouble s_step = 1.0 / GLdouble(_segments);

		GLdouble u = 0.0;
		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned d=0; d!=(_divisions+1); ++d)
			{
				GLdouble v = 1.0;
				for(unsigned s=0; s!=(_segments+1); ++s)
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
	void _make_side_verts(std::vector<T>& dest, unsigned& k) const
	{
		GLdouble b_leap = (math::pi()) / GLdouble(_bands);
		GLdouble b_slip = b_leap * _thickness * 0.5;
		GLdouble s_step = (math::pi()) / GLdouble(_segments);

		GLdouble m = _radius + _thickness * 0.5;
		GLdouble g = -1.0;

		for(unsigned b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			for(unsigned s=0; s!=(_segments+1); ++s)
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
	void _make_side_norms(std::vector<T>& dest, unsigned& k) const
	{
		GLdouble b_leap = (math::pi()) / GLdouble(_bands);
		GLdouble s_step = (math::pi()) / GLdouble(_segments);

		GLfloat m = 1.0;
		for(unsigned b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			for(unsigned s=0; s!=(_segments+1); ++s)
			{
				GLdouble b_angle =
					b*b_leap + b_offs;
				GLdouble cb = std::cos(b_angle);
				GLdouble sb = std::sin(b_angle);

				GLdouble s_angle = s*s_step;
				GLdouble ss = std::sin(s_angle);

				dest[k++] = m* -sb;
				dest[k++] = T(0);
				dest[k++] = m* cb;
				b_offs += ss * s_step;
			}
			m *= -1.0;
		}
	}

	template <typename T>
	void _make_side_tgts(std::vector<T>& dest, unsigned& k) const
	{
		GLdouble b_leap = (math::pi()) / GLdouble(_bands);
		GLdouble s_step = (math::pi()) / GLdouble(_segments);

		GLfloat m = -1.0;
		for(unsigned b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			for(unsigned s=0; s!=(_segments+1); ++s)
			{
				GLdouble b_angle =
					b*b_leap + b_offs;
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
			m *= -1.0;
		}
	}

	template <typename T>
	void _make_side_uvs(std::vector<T>& dest, unsigned& k) const
	{
		GLdouble b_leap = 0.5 / GLdouble(_bands);
		GLdouble b_slip = b_leap * _thickness * 0.5;
		GLdouble s_step = 1.0 / GLdouble(_segments);

		GLdouble g = -1.0;

		for(unsigned b=0; b!=_bands*2; ++b)
		{
			GLdouble b_offs = 0.0;
			GLdouble v = 1.0;
			for(unsigned s=0; s!=(_segments+1); ++s)
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

	/// Creates a custom spiral sphere
	SpiralSphere(
		GLdouble radius,
		GLdouble thickness,
		unsigned bands,
		unsigned divisions,
		unsigned segments
	): _radius(radius)
	 , _thickness(thickness)
	 , _bands(bands)
	 , _divisions(divisions)
	 , _segments(segments)
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
		unsigned k = 0;
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
		unsigned k = 0;
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
		dest.resize(_vertex_count() * 3);
		unsigned k = 0;
		//
		_make_tangents(dest, k, -1.0);
		_make_tangents(dest, k,  1.0);
		_make_side_tgts(dest, k);
		//
		assert(k == dest.size());
		// 3 values per vertex
		return 3;
	}

	/// Makes texture-coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize(_vertex_count() * 2);
		unsigned k = 0;
		//
		_make_uv_coords(dest, k);
		_make_uv_coords(dest, k);
		_make_side_uvs(dest, k);
		//
		assert(k == dest.size());
		// 2 values per vertex
		return 2;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** SpiralSphere provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normal" the vertex normal vectors (Normals)
	 *  - "Tangent" the vertex tangent vector (Tangents)
	 *  - "TexCoord" the ST texture coordinates (TexCoordinates)
	 */
	typedef VertexAttribsInfo<SpiralSphere> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		SpiralSphere,
		std::tuple<
			VertexPositionsTag,
			VertexNormalsTag,
			VertexTangentsTag,
			VertexTexCoordinatesTag
		>
	> VertexAttribs;
#endif

	/// The type of index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		assert(
			(1 << (sizeof(GLushort) * 8)) - 1 >=
			_vertex_count()
		);
		const unsigned n =
			(_bands * 2)*
			(_divisions * 2)*
			(_segments + 1)+
			(_bands * 8)*
			(_segments + 1)
		;
		//
		IndexArray indices(n);
		unsigned k = 0;
		unsigned eoffs, offs = 0;
		const unsigned edge = _segments + 1;
		const unsigned band = edge * (_divisions + 1);
		const unsigned surface = _bands * band;

		for(unsigned n=0; n!=2; ++n)
		{
			unsigned edge1 = n ? edge : 0;
			unsigned edge2 = n ? 0 : edge;
			for(unsigned b=0; b!=_bands; ++b)
			{
				for(unsigned d=0; d!=_divisions; ++d)
				{
					for(unsigned s=0; s!=edge; ++s)
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

		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned s=0; s!=edge; ++s)
			{
				indices[k++] = eoffs + s;
				indices[k++] = offs + s;
			}
			offs += band;
			eoffs += edge * 2;
		}

		offs = _divisions * edge;
		eoffs = 2*surface + edge;

		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned s=0; s!=edge; ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = eoffs + s;
			}
			offs += band;
			eoffs += edge * 2;
		}

		offs = surface;
		eoffs = 2*surface;

		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned s=0; s!=edge; ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = eoffs + s;
			}
			offs += band;
			eoffs += edge * 2;
		}

		offs = surface + _divisions * edge;
		eoffs = 2*surface + edge;

		for(unsigned b=0; b!=_bands; ++b)
		{
			for(unsigned s=0; s!=edge; ++s)
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
		return indices;
	}

	/// Returns the instructions for rendering
	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		const unsigned edge = _segments + 1;

		auto method = DrawOperation::Method::DrawElements;
		auto primitive_type = PrimitiveType::TriangleStrip;

		GLuint offs = 0;
		GLuint restart_index = DrawOperation::NoRestartIndex();
		GLuint phase = 0;
		for(unsigned n=0; n!=2; ++n)
		{
			for(unsigned b=0; b!=_bands; ++b)
			{
				for(unsigned d=0; d!=_divisions; ++d)
				{
					DrawOperation operation;
					operation.method = method;
					operation.mode = primitive_type;
					operation.first = offs;
					operation.count = GLuint(edge * 2);
					operation.restart_index = restart_index;
					operation.phase = phase;
					this->AddInstruction(instructions, operation);
					offs += edge * 2;
				}
			}
			++phase;
		}
		for(unsigned n=0; n!=4; ++n)
		{
			for(unsigned b=0; b!=_bands; ++b)
			{
				DrawOperation operation;
				operation.method = method;
				operation.mode = primitive_type;
				operation.first = offs;
				operation.count = GLuint(edge * 2);
				operation.restart_index = restart_index;
				operation.phase = phase;
				this->AddInstruction(instructions, operation);
				offs += edge * 2;
			}
		}
		return instructions;
	}
};

} // shapes
} // oglplus

#endif // include guard
