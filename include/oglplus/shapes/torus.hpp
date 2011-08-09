/**
 *  @file oglplus/shapes/torus.hpp
 *  @brief Torus builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_TORUS_1107121519_HPP
#define OGLPLUS_SHAPES_TORUS_1107121519_HPP

#include <oglplus/shapes/draw.hpp>
#include <oglplus/face_mode.hpp>

#include <cmath>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Torus
class Torus
 : public DrawingInstructionWriter
{
private:
	GLdouble _radius_out, _radius_in;
	size_t _sections, _rings;
public:
	/// Creates a torus with unit radius centered at the origin
	Torus(void)
	 : _radius_out(1.0)
	 , _radius_in(0.5)
	 , _sections(36)
	 , _rings(24)
	{ }

	/// Creates a torus with unit radius centered at the origin
	Torus(GLdouble rad_out, GLdouble rad_in, size_t sects, size_t rings)
	 : _radius_out(rad_out)
	 , _radius_in(rad_in)
	 , _sections(sects)
	 , _rings(rings)
	{ }

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CW;
	}

	/// Makes vertex coordinates and returns number of values per vertex
	template <typename T>
	GLuint Vertices(std::vector<T>& dest) const
	{
		dest.resize((_rings + 1) * (_sections + 1) * 3);
		size_t k = 0;
		//
		GLdouble r_step = (2.0 * M_PI) / GLdouble(_rings);
		GLdouble s_step = (2.0 * M_PI) / GLdouble(_sections);
		GLdouble r1 = _radius_in;
		GLdouble r2 = _radius_out - _radius_in;

		for(size_t r=0; r!=(_rings+1); ++r)
		{
			GLdouble vx = std::cos(r*r_step);
			GLdouble vz = std::sin(r*r_step);
			for(size_t s=0; s!=(_sections+1); ++s)
			{
				GLdouble vr = std::cos(s*s_step);
				GLdouble vy = std::sin(s*s_step);
				dest[k++] = vx*(r1 + r2 * (1.0 + vr));
				dest[k++] = vy*r2;
				dest[k++] = vz*(r1 + r2 * (1.0 + vr));
			}
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes vertex normals and returns number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize((_rings + 1) * (_sections + 1) * 3);
		size_t k = 0;
		//
		GLdouble r_step = (2.0 * M_PI) / GLdouble(_rings);
		GLdouble s_step = (2.0 * M_PI) / GLdouble(_sections);

		for(size_t r=0; r!=(_rings+1); ++r)
		{
			GLdouble vx = std::cos(r*r_step);
			GLdouble vz = std::sin(r*r_step);
			for(size_t s=0; s!=(_sections+1); ++s)
			{
				GLdouble vr = std::cos(s*s_step);
				GLdouble vy = std::sin(s*s_step);
				dest[k++] = vx*vr;
				dest[k++] = vy;
				dest[k++] = vz*vr;
			}
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes texture coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize((_rings + 1) * (_sections + 1) * 2);
		size_t k = 0;
		//
		GLdouble r_step = 1.0 / GLdouble(_rings);
		GLdouble s_step = 1.0 / GLdouble(_sections);

		for(size_t r=0; r!=(_rings+1); ++r)
		{
			GLdouble v = r*r_step;
			for(size_t s=0; s!=(_sections+1); ++s)
			{
				GLdouble u = s*s_step;
				dest[k++] = u;
				dest[k++] = v;
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
		assert((1<<(sizeof(GLushort)*8)) - 1 >= (_rings*(_sections+1)));
		//
		const size_t n =
			2 * (_rings)*(_sections + 1);
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t offs = 0;
		// the triangle strips
		for(size_t r=0; r!=(_rings); ++r)
		{
			for(size_t s=0; s!=(_sections+1); ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = offs + s + (_sections+1);
			}
			offs += _sections + 1;
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
		for(size_t r=0; r!=_rings; ++r)
		{
			this->AddInstruction(
				instructions,
				{
					DrawOperation::Method::DrawElements,
					PrimitiveType::TriangleStrip,
					GLuint(r * (_sections + 1) * 2),
					GLuint((_sections + 1) * 2)
				}
			);
		}
		return std::move(instructions);
	}
};

} // shapes
} // oglplus

#endif // include guard
