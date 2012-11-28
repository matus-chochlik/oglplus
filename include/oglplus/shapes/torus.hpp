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

#include <oglplus/shapes/vert_attr_info.hpp>

#include <oglplus/math.hpp>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Torus
class Torus
 : public DrawingInstructionWriter
{
private:
	GLdouble _radius_out, _radius_in;
	unsigned _sections, _rings;
public:
	/// Creates a torus with unit radius centered at the origin
	Torus(void)
	 : _radius_out(1.0)
	 , _radius_in(0.5)
	 , _sections(36)
	 , _rings(24)
	{ }

	/// Creates a torus with unit radius centered at the origin
	Torus(GLdouble rad_out, GLdouble rad_in, unsigned sects, unsigned rings)
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
	GLuint Positions(std::vector<T>& dest) const
	{
		dest.resize((_rings + 1) * (_sections + 1) * 3);
		unsigned k = 0;
		//
		GLdouble r_step = (2.0 * math::pi()) / GLdouble(_rings);
		GLdouble s_step = (2.0 * math::pi()) / GLdouble(_sections);
		GLdouble r1 = _radius_in;
		GLdouble r2 = _radius_out - _radius_in;

		for(unsigned r=0; r!=(_rings+1); ++r)
		{
			GLdouble vx = std::cos(r*r_step);
			GLdouble vz = std::sin(r*r_step);
			for(unsigned s=0; s!=(_sections+1); ++s)
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
		unsigned k = 0;
		//
		GLdouble r_step = (2.0 * math::pi()) / GLdouble(_rings);
		GLdouble s_step = (2.0 * math::pi()) / GLdouble(_sections);

		for(unsigned r=0; r!=(_rings+1); ++r)
		{
			GLdouble vx = std::cos(r*r_step);
			GLdouble vz = std::sin(r*r_step);
			for(unsigned s=0; s!=(_sections+1); ++s)
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

	/// Makes vertex tangents and returns number of values per vertex
	template <typename T>
	GLuint Tangents(std::vector<T>& dest) const
	{
		dest.resize((_rings + 1) * (_sections + 1) * 3);
		unsigned k = 0;
		//
		GLdouble r_step = (2.0 * math::pi()) / GLdouble(_rings);

		for(unsigned r=0; r!=(_rings+1); ++r)
		{
			GLdouble vx = std::cos(r*r_step);
			GLdouble vz = std::sin(r*r_step);
			for(unsigned s=0; s!=(_sections+1); ++s)
			{
				dest[k++] = +vz;
				dest[k++] = T(0);
				dest[k++] = -vx;
			}
		}
		assert(k == dest.size());
		return 3;
	}

	/// Makes texture coordinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize((_rings + 1) * (_sections + 1) * 2);
		unsigned k = 0;
		//
		GLdouble r_step = 1.0 / GLdouble(_rings);
		GLdouble s_step = 1.0 / GLdouble(_sections);

		for(unsigned r=0; r!=(_rings+1); ++r)
		{
			GLdouble u = r*r_step;
			for(unsigned s=0; s!=(_sections+1); ++s)
			{
				GLdouble v = s*s_step;
				dest[k++] = u;
				dest[k++] = v;
			}
		}
		assert(k == dest.size());
		return 2;
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
	typedef VertexAttribsInfo<Torus> VertexAttribs;
#else
	typedef VertexAttribsInfo<
		Torus,
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
		const unsigned n = _rings * (2 * (_sections + 1) + 1);
		assert((1<<(sizeof(GLushort)*8)) - 1 >= n);
		//
		IndexArray indices(n);
		unsigned k = 0;
		unsigned offs = 0;
		// the triangle strips
		for(unsigned r=0; r!=(_rings); ++r)
		{
			for(unsigned s=0; s!=(_sections+1); ++s)
			{
				indices[k++] = offs + s;
				indices[k++] = offs + s + (_sections+1);
			}
			indices[k++] = n;
			offs += _sections + 1;
		}
		assert(k == indices.size());
		//
		// return the indices
		return indices;
	}

	/// Returns element indices that are used with the drawing instructions
	IndexArray IndicesWithAdjacency(void) const
	{
		const unsigned m = _rings*(_sections + 1);
		const unsigned n = _rings*(4 * (_sections + 1) + 1);
		assert((1<<(sizeof(GLushort)*8)) - 1 >= n);
		//
		IndexArray indices(n);
		unsigned k = 0;
		unsigned offs = 0;

		for(unsigned r=0; r!=(_rings); ++r)
		{
			indices[k++] = offs;
			indices[k++] = offs + (2*_sections);
			indices[k++] = offs + (_sections+1);
			for(unsigned s=0; s!=_sections; ++s)
			{
				indices[k++] = (offs + m-(_sections+1))%m + s+1;
				indices[k++] = offs + s + 1;
				indices[k++] = (offs + 2*(_sections+1)) % m + s;
				indices[k++] = offs + (_sections+1) + s + 1;
			}
			indices[k++] = offs + 1;
			indices[k++] = n;
			offs += _sections + 1;
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

		const GLuint n = _rings * (2 * (_sections + 1) + 1);
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawElements;
		operation.mode = PrimitiveType::TriangleStrip;
		operation.first = GLuint(0);
		operation.count = n;
		operation.restart_index = n;
		operation.phase = 0;

		this->AddInstruction(instructions, operation);

		return instructions;
	}

	/// Returns the instructions for rendering
	DrawingInstructions InstructionsWithAdjacency(void) const
	{
		auto instructions = this->MakeInstructions();

		const unsigned n = _rings*(4 * (_sections + 1) + 1);
		DrawOperation operation;
		operation.method = DrawOperation::Method::DrawElements;
		operation.mode = PrimitiveType::TriangleStripAdjacency;
		operation.first = GLuint(0);
		operation.count = n;
		operation.restart_index = n;
		operation.phase = 0;

		this->AddInstruction(instructions, operation);

		return instructions;
	}
};

} // shapes
} // oglplus

#endif // include guard
