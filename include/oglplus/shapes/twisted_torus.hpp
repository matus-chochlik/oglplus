/**
 *  @file oglplus/shapes/twisted_torus.hpp
 *  @brief TwistedTorus builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_TWISTED_TORUS_1201021336_HPP
#define OGLPLUS_SHAPES_TWISTED_TORUS_1201021336_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/face_mode.hpp>

#include <oglplus/shapes/vert_attr_info.hpp>

#include <oglplus/math.hpp>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Torus
class TwistedTorus
 : public DrawingInstructionWriter
{
private:
	const GLdouble _radius_out, _radius_in, _thickness;
	const GLdouble _r_slip_coef, _s_slip_coef;
	const unsigned _sections, _rings, _twist;
public:
	/// Creates a torus with unit radius centered at the origin
	TwistedTorus(void)
	 : _radius_out(1.0)
	 , _radius_in(0.5)
	 , _thickness(0.02)
	 , _r_slip_coef(0.25)
	 , _s_slip_coef(0.20)
	 , _sections(12)
	 , _rings(48)
	 , _twist(12)
	{ }

	/// Creates a torus with unit radius centered at the origin
	TwistedTorus(
		GLdouble rad_out,
		GLdouble rad_in,
		GLdouble thickness,
		unsigned sects,
		unsigned rings,
		unsigned twist
	): _radius_out(rad_out)
	 , _radius_in(rad_in)
	 , _thickness(thickness)
	 , _r_slip_coef(0.25)
	 , _s_slip_coef(0.20)
	 , _sections(sects)
	 , _rings(rings)
	 , _twist(twist)
	{
		assert(_sections % 2 == 0);
		assert(_rings % 2 == 0);
		assert(_thickness > 0.0);
		assert(_thickness < _radius_in);
		assert(_radius_in < _radius_out);
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
		dest.resize(2*2*2*_sections*(_rings + 1)*3);
		unsigned k = 0;
		//
		const GLdouble t = _thickness / _radius_in;
		const GLdouble r_twist = GLdouble(_twist) / GLdouble(_rings);
		const GLdouble r_step = (math::TwoPi()) / GLdouble(_rings);
		const GLdouble s_step = (math::TwoPi()) / GLdouble(_sections);
		const GLdouble s_slip = s_step * _s_slip_coef;
		const GLdouble r1 = _radius_in;
		const GLdouble r2 = _radius_out - _radius_in;

		for(unsigned f=0; f!=2; ++f)
		{
			const GLdouble f_sign = (f == 0)? 1.0: -1.0;
			const GLdouble fdt = t*f_sign*0.95;
			for(unsigned s=0; s!=_sections; ++s)
			{
				const GLdouble s_angle = s_step*0.5 + s*s_step;
				const GLdouble sa[2] = {
					s_angle + s_slip*f_sign,
					s_angle - s_slip*f_sign
				};
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					const GLdouble r_angle = r*r_step;
					GLdouble vx = std::cos(r_angle);
					GLdouble vz = std::sin(r_angle);

					const GLdouble ta = s_step*r*r_twist;

					for(unsigned d=0; d!=2; ++d)
					{
						GLdouble vr = std::cos(sa[d]+ta);
						GLdouble vy = std::sin(sa[d]+ta);

						dest[k++] = T(vx*(r1 + r2*(1.0 + vr) + fdt*vr));
						dest[k++] = T(vy*(r2 + fdt));
						dest[k++] = T(vz*(r1 + r2*(1.0 + vr) + fdt*vr));
					}
				}
			}
		}

		for(unsigned d=0; d!=2; ++d)
		{
			const GLdouble d_sign = (d == 0)? 1.0: -1.0;
			for(unsigned s=0; s!=_sections; ++s)
			{
				const GLdouble s_angle = s_step*0.5 + s*s_step;
				const GLdouble sa = s_angle + s_slip*d_sign;
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					const GLdouble r_angle = r*r_step;
					const GLdouble ta = s_step*r*r_twist;
					const GLdouble vr = std::cos(sa+ta);
					const GLdouble vy = std::sin(sa+ta);

					GLdouble vx = std::cos(r_angle);
					GLdouble vz = std::sin(r_angle);

					for(unsigned f=0; f!=2; ++f)
					{
						const GLdouble f_sign = (f == 0)? 1.0: -1.0;
						const GLdouble fdt = -t*d_sign*f_sign*0.95;

						dest[k++] = T(vx*(r1 + r2*(1.0 + vr) + fdt*vr));
						dest[k++] = T(vy*(r2 + fdt));
						dest[k++] = T(vz*(r1 + r2*(1.0 + vr) + fdt*vr));
					}
				}
			}
		}

		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex normals and returns number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize(2*2*2*_sections*(_rings + 1)*3);
		unsigned k = 0;
		//
		const GLdouble r_twist= GLdouble(_twist) / GLdouble(_rings);
		const GLdouble r_step = (math::TwoPi()) / GLdouble(_rings);
		const GLdouble s_step = (math::TwoPi()) / GLdouble(_sections);
		const GLdouble s_slip = s_step * _s_slip_coef;

		for(unsigned f=0; f!=2; ++f)
		{
			const GLdouble f_sign = (f == 0)? 1.0: -1.0;
			for(unsigned s=0; s!=_sections; ++s)
			{
				const GLdouble s_angle = s_step*0.5 + s*s_step;
				const GLdouble sa[2] = {
					s_angle + s_slip*f_sign,
					s_angle - s_slip*f_sign
				};
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					const GLdouble r_angle = r*r_step;
					GLdouble vx = std::cos(r_angle);
					GLdouble vz = std::sin(r_angle);

					const GLdouble ta = s_step*r*r_twist;

					for(unsigned d=0; d!=2; ++d)
					{
						GLdouble vr = std::cos(sa[d]+ta);
						GLdouble vy = std::sin(sa[d]+ta);

						dest[k++] = T(f_sign*vx*vr);
						dest[k++] = T(f_sign*vy);
						dest[k++] = T(f_sign*vz*vr);
					}
				}
			}
		}

		for(unsigned d=0; d!=2; ++d)
		{
			const GLdouble d_sign = (d == 0)? 1.0: -1.0;
			for(unsigned s=0; s!=_sections; ++s)
			{
				const GLdouble s_angle = s_step*0.5 + s*s_step;
				const GLdouble sa = s_angle + s_slip*d_sign;
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					const GLdouble ta = s_step*r*r_twist;
					const GLdouble vr = std::sin(sa+ta);
					const GLdouble vy = std::cos(sa+ta);
					const GLdouble r_angle = r*r_step;
					GLdouble vx = std::cos(r_angle);
					GLdouble vz = std::sin(r_angle);

					for(unsigned f=0; f!=2; ++f)
					{
						dest[k++] = T(d_sign*-vx*vr);
						dest[k++] = T(d_sign*vy);
						dest[k++] = T(d_sign*-vz*vr);
					}
				}
			}
		}

		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex tangents and returns number of values per vertex
	template <typename T>
	GLuint Tangents(std::vector<T>& dest) const
	{
		std::vector<T> poss;
		Positions(poss);

		dest.resize(2*2*2*_sections*(_rings + 1)*3);

		assert(dest.size() == poss.size());
		unsigned k = 0;
		//
		for(unsigned f=0; f!=2; ++f)
		{
			unsigned foff = f*_sections*(_rings+1)*2;
			for(unsigned s=0; s!=_sections; ++s)
			{
				unsigned s0 = s*(_rings+1)*2;
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					unsigned s1 = s0;
					unsigned r0 = r;
					unsigned r1 = r+1;
					if(r == _rings)
					{
						s1 = ((s+_twist)%_sections)*
							(_rings+1)*2;
						r1 = 1;
					}

					for(unsigned d=0; d!=2; ++d)
					{
						std::size_t k0 = foff+s0+r0*2+d;
						std::size_t k1 = foff+s1+r1*2+d;

						T tx = poss[k1*3+0]-poss[k0*3+0];
						T ty = poss[k1*3+1]-poss[k0*3+1];
						T tz = poss[k1*3+2]-poss[k0*3+2];
						T tl = std::sqrt(tx*tx+ty*ty+tz*tz);

						assert(tl > T(0));

						dest[k++] = tx/tl;
						dest[k++] = ty/tl;
						dest[k++] = tz/tl;
					}
				}
			}
		}

		for(unsigned d=0; d!=2; ++d)
		{
			std::size_t doff = d*_sections*(_rings+1)*2;
			for(unsigned s=0; s!=_sections; ++s)
			{
				unsigned s0 = s*(_rings+1)*2;
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					unsigned s1 = s0;
					unsigned r0 = r;
					unsigned r1 = r+1;
					if(r == _rings)
					{
						s1 = ((s+_twist)%_sections)*
							(_rings+1)*2;
						r1 = 1;
					}

					for(unsigned f=0; f!=2; ++f)
					{
						std::size_t k0 = doff+s0+r0*2+f;
						std::size_t k1 = doff+s1+r1*2+f;

						T tx = poss[k1*3+0]-poss[k0*3+0];
						T ty = poss[k1*3+1]-poss[k0*3+1];
						T tz = poss[k1*3+2]-poss[k0*3+2];
						T tl = std::sqrt(tx*tx+ty*ty+tz*tz);

						assert(tl > T(0));

						dest[k++] = tx/tl;
						dest[k++] = ty/tl;
						dest[k++] = tz/tl;
					}
				}
			}
		}

		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex bi-tangents and returns number of values per vertex
	template <typename T>
	GLuint Bitangents(std::vector<T>& dest) const
	{
		std::vector<T> nmls, tgts;
		Normals(nmls);
		Tangents(tgts);
		assert(nmls.size() == tgts.size());
		assert(nmls.size() % 3 == 0);

		dest.resize(nmls.size());

		unsigned k = 0;

		while(k != dest.size())
		{
			T nx = nmls[k+0];
			T ny = nmls[k+1];
			T nz = nmls[k+2];

			T tx = tgts[k+0];
			T ty = tgts[k+1];
			T tz = tgts[k+2];

			dest[k++] = T(ny*tz-nz*ty);
			dest[k++] = T(nz*tx-nx*tz);
			dest[k++] = T(nx*ty-ny*tx);
		}

		assert(k == dest.size());
		return 3;
	}

	/// Makes texture coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize(2*2*2*_sections*(_rings + 1)*2);
		unsigned k = 0;
		//
		GLdouble t = _thickness / _radius_in;
		GLdouble r_step = 0.5 / GLdouble(_rings);
		GLdouble s_step = 1.0 / GLdouble(_sections);
		GLdouble s_slip = s_step * t;

		s_slip = s_step * _s_slip_coef;

		for(unsigned f=0; f!=2; ++f)
		{
			const GLdouble f_sign = (f == 0)? 1.0: -1.0;
			for(unsigned s=0; s!=_sections; ++s)
			{
				const GLdouble s_angle = s_step*0.5 + s*s_step;
				const GLdouble sa[2] = {
					s_angle + s_slip*f_sign,
					s_angle - s_slip*f_sign
				};
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					const GLdouble r_angle = 2*r*r_step;
					GLdouble u = r_angle;
					for(unsigned d=0; d!=2; ++d)
					{
						GLdouble v = sa[d];
						dest[k++] = T(u);
						dest[k++] = T(v);
					}
				}
			}
		}

		for(unsigned d=0; d!=2; ++d)
		{
			const GLdouble d_sign = (d == 0)? 1.0: -1.0;
			for(unsigned s=0; s!=_sections; ++s)
			{
				const GLdouble s_angle = s_step*0.5 + s*s_step;
				const GLdouble v = s_angle + s_slip*d_sign;
				for(unsigned r=0; r!=_rings+1; ++r)
				{
					const GLdouble r_angle = 2*r*r_step;
					GLdouble u = r_angle;
					for(unsigned f=0; f!=2; ++f)
					{
						dest[k++] = T(u);
						dest[k++] = T(v);
					}
				}
			}
		}

		assert(k == dest.size());
		return 2;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** TwistedTorus provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normal" the vertex normal vectors (Normals)
	 *  - "Tangent" the vertex tangent vector (Tangents)
	 *  - "Bitangent" the vertex bi-tangent vector (Bitangents)
	 *  - "TexCoord" the ST texture coordinates (TexCoordinates)
	 */
	typedef VertexAttribsInfo<TwistedTorus> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		TwistedTorus,
		std::tuple<
			VertexPositionsTag,
			VertexNormalsTag,
			VertexTangentsTag,
			VertexBitangentsTag,
			VertexTexCoordinatesTag
		>
	> VertexAttribs;
#endif

	/// Queries the bounding sphere coordinates and dimensions
	template <typename T>
	void BoundingSphere(Vector<T, 4>& center_and_radius) const
	{
		center_and_radius = Vector<T, 4>(
			T(0),
			T(0),
			T(0),
			T(_radius_out + _thickness)
		);
	}

	/// The type of index container returned by Indices()
	typedef std::vector<GLuint> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		return IndexArray();
	}

	/// Returns the instructions for rendering
	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		unsigned strip = 2*(_rings + 1);
		unsigned offs = 0;

		GLuint phase = 0;

		for(unsigned f=0; f!=4; ++f)
		{
			for(unsigned s=0; s!=_sections; ++s)
			{
				DrawOperation operation;
				operation.method = DrawOperation::Method::DrawArrays;
				operation.mode = PrimitiveType::TriangleStrip;
				operation.first = GLuint(offs);
				operation.count = GLuint(strip);
				operation.restart_index = DrawOperation::NoRestartIndex();
				operation.phase = phase;
				this->AddInstruction(instructions, operation);
				offs += strip;
			}
			++phase;
		}
		return instructions;
	}
};

} // shapes
} // oglplus

#endif // include guard
