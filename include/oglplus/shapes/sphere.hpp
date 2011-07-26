/**
 *  @file oglplus/shapes/sphere.hpp
 *  @brief Sphere builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_SPHERE_1107121519_HPP
#define OGLPLUS_SHAPES_SPHERE_1107121519_HPP

#include <oglplus/shapes/draw.hpp>

#include <cmath>

namespace oglplus {
namespace shapes {

class Sphere
 : public DrawingInstructionWriter
{
private:
	GLdouble _radius;
	size_t _sections, _rings;
public:
	Sphere(void)
	 : _radius(1.0)
	 , _sections(18)
	 , _rings(12)
	{ }

	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize((1 + _rings * _sections + 1) * 3);
		size_t k = 0;
		// the north pole
		dest[k++] = T(0), dest[k++] =  T(1), dest[k++] = T(0);
		//
		GLdouble r_step = (1.0 * M_PI) / GLdouble(_rings + 1);
		GLdouble s_step = (2.0 * M_PI) / GLdouble(_sections);
		// the rings of latitude
		for(size_t r=0; r!=_rings;++r)
		{
			GLdouble r_lat = std::cos((r+1)*r_step);
			GLdouble r_rad = std::sin((r+1)*r_step);
			// the sections
			for(size_t s=0; s!=_sections;++s)
			{
				dest[k++] = r_rad * std::cos(s * s_step);
				dest[k++] = r_lat;
				dest[k++] = r_rad * std::sin(s * s_step);
			}
		}
		// the south pole
		dest[k++] = T(0), dest[k++] = -T(1), dest[k++] = T(0);
		//
		assert(k == dest.size());
		// 3 values per vertex
		return 3;
	}

	template <typename T>
	GLuint Vertices(std::vector<T>& dest) const
	{
		GLuint n = Normals(dest);
		if(_radius != 1.0)
			for(auto i=dest.begin(),e=dest.end(); i!= e; ++i)
				*i *= _radius;
		return n;
	}

	std::vector<GLushort> Indices(void) const
	{
		// TODO: check if ushort range is enough for all indices
		//
		// 1 fan at the north pole +
		// (rings - 1) triangle strips +
		// 1 fan at the south pole
		const size_t n =
			2 * (1 + _sections + 1) +  // 2 fans at the poles
			2 * (_rings - 1)*(_sections + 1); // the strips between
		//
		std::vector<GLushort> indices(n);
		size_t k = 0;
		// the north pole fan
		indices[k++] = 0;
		for(size_t i=0; i!=_sections; ++i)
			indices[k++] = i+1;
		indices[k++] = 1;
		assert(k == _sections + 2);
		//
		size_t offs = 1;
		// the triangle strips
		for(size_t r=0; r!=(_rings-1); ++r)
		{
			for(size_t s=0; s!=_sections; ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = offs + s + _sections;
			}
			indices[k++] = offs;
			indices[k++] = offs + _sections;
			offs += _sections;
		}
		// the south pole fan
		indices[k++] = 1 + (_rings * _sections);
		indices[k++] = offs;
		for(size_t s=0; s!=_sections; ++s)
			indices[k++] = offs + (_sections - s - 1);
		//
		// return the indices
		return std::move(indices);
	}

	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		this->AddInstruction(
			instructions,
			{
				DrawOperation::Method::DrawElements,
				PrimitiveType::TriangleFan,
				0, _sections + 2
			}
		);
		for(size_t r=0; r!=(_rings-1); ++r)
		{
			this->AddInstruction(
				instructions,
				{
					DrawOperation::Method::DrawElements,
					PrimitiveType::TriangleStrip,
					(_sections + 2) +
					r * (_sections + 1) * 2,
					(_sections + 1) * 2
				}
			);
		}
		this->AddInstruction(
			instructions,
			{
				DrawOperation::Method::DrawElements,
				PrimitiveType::TriangleFan,
				(_sections + 2) +
				(_rings - 1) * (_sections + 1) * 2, _sections + 2
			}
		);
		return std::move(instructions);
	}
};

} // shapes
} // oglplus

#endif // include guard
