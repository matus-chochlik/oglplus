/**
 *  @file oglplus/shapes/wicker_torus.hpp
 *  @brief WickerTorus builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_WICKER_TORUS_1201021336_HPP
#define OGLPLUS_SHAPES_WICKER_TORUS_1201021336_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/face_mode.hpp>

#include <cmath>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Torus
class WickerTorus
 : public DrawingInstructionWriter
{
private:
	GLdouble _radius_out, _radius_in, _thickness;
	size_t _sections, _rings;
public:
	/// Creates a torus with unit radius centered at the origin
	WickerTorus(void)
	 : _radius_out(1.0)
	 , _radius_in(0.5)
	 , _thickness(0.005)
	 , _sections(32)
	 , _rings(24)
	{ }

	/// Creates a torus with unit radius centered at the origin
	WickerTorus(
		GLdouble rad_out,
		GLdouble rad_in,
		GLdouble thickness,
		size_t sects,
		size_t rings
	): _radius_out(rad_out)
	 , _radius_in(rad_in)
	 , _thickness(thickness)
	 , _sections(sects)
	 , _rings(rings)
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
		dest.resize(
			2*2*2*_rings*(_sections*3 + 1)*3
		);
		size_t k = 0;
		//
		const GLdouble t = _thickness / _radius_in;
		const GLdouble r_step = (2.0 * M_PI) / GLdouble(_rings);
		const GLdouble s_step = (2.0 * M_PI) / GLdouble(_sections);
		const GLdouble r_slip = r_step * 0.25;
		const GLdouble s_slip = s_step * t;
		const GLdouble r1 = _radius_in;
		const GLdouble r2 = _radius_out - _radius_in;

		for(size_t f=0; f!=2; ++f)
		{
			const GLdouble f_sign = (f % 2 == 0)? 1.0: -1.0;
			const GLdouble fdt = t*f_sign*0.5;
			const GLdouble rfs = f_sign * r_slip;
			for(size_t r=0; r!=_rings; ++r)
			{
				const GLdouble r_angle = r*r_step;
				const GLdouble r_sign = (r % 2 == 0)? 1.0: -1.0;
				const double rdt = t*r_sign*2.0;
				for(size_t d=0; d!=2; ++d)
				{
					const GLdouble d_sign = (d % 2 == 0)? 1.0: -1.0;
					for(size_t s=0; s!=_sections; ++s)
					{
						const GLdouble sa[3] = {
							s*s_step,
							(s + t)*s_step,
							(s + 1.0 - 2*t)*s_step
						};
						const GLdouble rd[3] = {
							fdt,
							fdt+((s % 2 == 0)? -rdt : rdt),
							fdt+((s % 2 == 0)? -rdt : rdt)
						};
						for(size_t p=0; p!=3; ++p)
						{
							GLdouble vr = std::cos(sa[p]);
							GLdouble vy = std::sin(sa[p]);
							GLdouble vs = 0.5 + vr*0.5;

							GLdouble rs_angle = r_angle + d_sign*rfs*(1.0 - 0.25*vs);

							GLdouble vx = std::cos(rs_angle);
							GLdouble vz = std::sin(rs_angle);

							dest[k++] = vx*(r1 + r2*(1.0 + vr) + rd[p]*vr);
							dest[k++] = vy*(r2 + rd[p]);
							dest[k++] = vz*(r1 + r2*(1.0 + vr) + rd[p]*vr);
						}
					}

					GLdouble rs_angle = r_angle + d_sign*rfs*0.75;

					GLdouble vx = std::cos(rs_angle);
					GLdouble vz = std::sin(rs_angle);
					dest[k++] = vx*(r1 + r2*(2.0) + fdt);
					dest[k++] = 0.0;
					dest[k++] = vz*(r1 + r2*(2.0) + fdt);
				}
			}
		}

		for(size_t d=0; d!=2; ++d)
		{
			const GLdouble d_sign = (d % 2 == 0)? 1.0: -1.0;
			const GLdouble rds = d_sign * r_slip;
			for(size_t r=0; r!=_rings; ++r)
			{
				const GLdouble r_angle = r*r_step;
				const GLdouble r_sign = (r % 2 == 0)? 1.0: -1.0;
				const double rdt = t*r_sign*2.0;
				for(size_t f=0; f!=2; ++f)
				{
					const GLdouble f_sign = (f % 2 == 0)? 1.0: -1.0;
					const GLdouble fdt = -0.5*t*f_sign*d_sign;
					for(size_t s=0; s!=_sections; ++s)
					{
						const GLdouble sa[3] = {
							s*s_step,
							(s + t)*s_step,
							(s + 1.0 - 2*t)*s_step
						};
						const GLdouble rd[3] = {
							fdt,
							fdt+((s % 2 == 0)? -rdt : rdt),
							fdt+((s % 2 == 0)? -rdt : rdt)
						};
						for(size_t p=0; p!=3; ++p)
						{
							GLdouble vr = std::cos(sa[p]);
							GLdouble vy = std::sin(sa[p]);
							GLdouble vs = 0.5 + vr*0.5;

							GLdouble rs_angle = r_angle + rds*(1.0 - 0.25*vs);

							GLdouble vx = std::cos(rs_angle);
							GLdouble vz = std::sin(rs_angle);

							dest[k++] = vx*(r1 + r2*(1.0 + vr) + rd[p]*vr);
							dest[k++] = vy*(r2 + rd[p]);
							dest[k++] = vz*(r1 + r2*(1.0 + vr) + rd[p]*vr);
						}
					}

					GLdouble rs_angle = r_angle + rds*0.75;

					GLdouble vx = std::cos(rs_angle);
					GLdouble vz = std::sin(rs_angle);
					dest[k++] = vx*(r1 + r2*(2.0) + fdt);
					dest[k++] = 0.0;
					dest[k++] = vz*(r1 + r2*(2.0) + fdt);
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
		dest.resize(
			2*2*2*_rings*(_sections*3 + 1)*3
		);
		size_t k = 0;
		//
		GLdouble r_step = (2.0 * M_PI) / GLdouble(_rings);
		GLdouble s_step = (2.0 * M_PI) / GLdouble(_sections);
		GLdouble s_slop = (1.0 * M_PI) / 4.0;

		for(size_t f=0; f!=2; ++f)
		{
			const GLdouble f_sign = (f % 2 == 0)? 1.0: -1.0;
			for(size_t r=0; r!=_rings; ++r)
			{
				GLdouble r_sign = r % 2 == 0 ? 1.0: -1.0;
				GLdouble vx = std::cos(r*r_step);
				GLdouble vz = std::sin(r*r_step);
				const GLdouble rslp = s_slop*r_sign;
				for(size_t d=0; d!=2; ++d)
				{
					for(size_t s=0; s!=_sections; ++s)
					{
						const GLdouble sa[3] = {
							s*s_step+(s % 2 == 0)?rslp:-rslp,
							s*s_step,
							s*s_step
						};
						for(size_t p=0; p!=3; ++p)
						{
							GLdouble vr = std::cos(sa[p]);
							GLdouble vy = std::sin(sa[p]);
							dest[k++] = f_sign*vx*vr;
							dest[k++] = f_sign*vy;
							dest[k++] = f_sign*vz*vr;
						}
					}
					dest[k++] = f_sign*vx;
					dest[k++] = f_sign*std::sin(rslp);
					dest[k++] = f_sign*vz;
				}
			}
		}

		for(size_t d=0; d!=2; ++d)
		{
			const GLdouble d_sign = (d % 2 == 0)? 1.0: -1.0;
			for(size_t r=0; r!=_rings; ++r)
			{
				GLdouble vx = std::cos(r*r_step);
				GLdouble vz = std::sin(r*r_step);
				for(size_t f=0; f!=2; ++f)
				{
					for(size_t s=0; s!=_sections; ++s)
					{
						for(size_t p=0; p!=3; ++p)
						{
							dest[k++] = +vz*d_sign;
							dest[k++] = T(0);
							dest[k++] = -vx*d_sign;
						}
					}
					dest[k++] = +vz*d_sign;
					dest[k++] = T(0);
					dest[k++] = -vx*d_sign;
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
		dest.resize(
			2*2*2*_rings*(_sections*3 + 1)*3
		);
		size_t k = 0;
		//
		GLdouble r_step = (2.0 * M_PI) / GLdouble(_rings);
		GLdouble s_step = (2.0 * M_PI) / GLdouble(_sections);
		GLdouble s_slop = (1.0 * M_PI) / 4.0;

		for(size_t f=0; f!=2; ++f)
		{
			const GLdouble f_sign = (f % 2 == 0)? 1.0: -1.0;
			for(size_t r=0; r!=_rings; ++r)
			{
				GLdouble vx = std::cos(r*r_step);
				GLdouble vz = std::sin(r*r_step);
				for(size_t d=0; d!=2; ++d)
				{
					for(size_t s=0; s!=_sections; ++s)
					{
						for(size_t p=0; p!=3; ++p)
						{
							dest[k++] = +vz*f_sign;
							dest[k++] = T(0);
							dest[k++] = -vx*f_sign;
						}
					}
					dest[k++] = +vz*f_sign;
					dest[k++] = T(0);
					dest[k++] = -vx*f_sign;
				}
			}
		}

		for(size_t d=0; d!=2; ++d)
		{
			const GLdouble d_sign = (d % 2 == 0)? 1.0: -1.0;
			for(size_t r=0; r!=_rings; ++r)
			{
				GLdouble r_sign = r % 2 == 0 ? 1.0: -1.0;
				GLdouble vx = std::cos(r*r_step);
				GLdouble vz = std::sin(r*r_step);
				const GLdouble rslp = s_slop*r_sign;
				for(size_t f=0; f!=2; ++f)
				{
					for(size_t s=0; s!=_sections; ++s)
					{
						const GLdouble sa[3] = {
							s*s_step+(s % 2 == 0)?rslp:-rslp,
							s*s_step,
							s*s_step
						};
						for(size_t p=0; p!=3; ++p)
						{
							GLdouble vr = std::cos(sa[p]);
							GLdouble vy = std::sin(sa[p]);
							dest[k++] = d_sign*vx*vr;
							dest[k++] = d_sign*vy;
							dest[k++] = d_sign*vz*vr;
						}
					}
					dest[k++] = d_sign*vx;
					dest[k++] = d_sign*std::sin(rslp);
					dest[k++] = d_sign*vz;
				}
			}
		}

		assert(k == dest.size());
		return 3;
	}

	/// Makes texture coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize(
			2*2*2*_rings*(_sections*3 + 1)*2
		);
		size_t k = 0;
		//
		GLdouble t = _thickness / _radius_in;
		GLdouble r_step = 0.5 / GLdouble(_rings);
		GLdouble s_step = 1.0 / GLdouble(_sections);
		GLdouble s_slip = s_step * t;

		for(size_t f=0; f!=2; ++f)
		{
			for(size_t r=0; r!=_rings; ++r)
			{
				GLdouble rv = 2*r*r_step;
				for(size_t d=0; d!=2; ++d)
				{
					GLdouble u = rv + ((d+f)%2)*r_step;
					for(size_t s=0; s!=_sections; ++s)
					{
						const GLdouble sa[3] = {
							s*s_step,
							(s + t)*s_step,
							(s + 1.0 - 2*t)*s_step
						};
						for(size_t p=0; p!=3; ++p)
						{
							GLdouble v = sa[p];
							dest[k++] = u;
							dest[k++] = v;
						}
					}
					dest[k++] = u;
					dest[k++] = 1.0;
				}
			}
		}

		for(size_t d=0; d!=2; ++d)
		{
			for(size_t r=0; r!=_rings; ++r)
			{
				GLdouble rv = 2*r*r_step;
				for(size_t f=0; f!=2; ++f)
				{
					GLdouble u = rv + ((d+f)%2)*r_step;
					for(size_t s=0; s!=_sections; ++s)
					{
						const GLdouble sa[3] = {
							s*s_step,
							(s + t)*s_step,
							(s + 1.0 - 2*t)*s_step
						};
						for(size_t p=0; p!=3; ++p)
						{
							GLdouble v = sa[p];
							dest[k++] = u;
							dest[k++] = v;
						}
					}
					dest[k++] = u;
					dest[k++] = 1.0;
				}
			}
		}

		assert(k == dest.size());
		return 2;
	}

	/// The type of index container returned by Indices()
	typedef std::vector<GLushort> IndexArray;

	/// Returns element indices that are used with the drawing instructions
	IndexArray Indices(void) const
	{
		const size_t n =
			2*2*2*(_rings)*(_sections*3 + 1);
		assert((1<<(sizeof(GLushort)*8)) - 1 >= n);
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t offs = 0;
		size_t strip = _sections*3+1;

		for(size_t f=0; f!=4; ++f)
		{
			for(size_t r=0; r!=_rings; ++r)
			{
				for(size_t s=0; s!=strip; ++s)
				{
					indices[k++] = offs + s + strip;
					indices[k++] = offs + s;
				}
				offs += 2*strip;
			}
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
		size_t strip = _sections*3 + 1;
		size_t offs = 0;

		for(size_t f=0; f!=4; ++f)
		{
			for(size_t r=0; r!=_rings; ++r)
			{
				this->AddInstruction(
					instructions,
					{
						DrawOperation::Method::DrawElements,
						PrimitiveType::TriangleStrip,
						GLuint(offs),
						GLuint(strip * 2)
					}
				);
				offs += strip*2;
			}
		}
		return std::move(instructions);
	}

};

} // shapes
} // oglplus

#endif // include guard
