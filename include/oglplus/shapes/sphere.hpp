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
#include <oglplus/face_mode.hpp>

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
#include <oglplus/shapes/vert_attr_info.hpp>
#endif

#include <oglplus/math.hpp>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Sphere
class Sphere
 : public DrawingInstructionWriter
{
private:
	GLdouble _radius;
	size_t _sections, _rings;
public:
	/// Creates a sphere with unit radius centered at the origin
	Sphere(void)
	 : _radius(1.0)
	 , _sections(18)
	 , _rings(12)
	{ }

	/// Creates a sphere with unit radius centered at the origin
	Sphere(GLdouble radius, size_t sections, size_t rings)
	 : _radius(radius)
	 , _sections(sections)
	 , _rings(rings)
	{ }

	/// Returns the winding direction of faces
	FaceOrientation FaceWinding(void) const
	{
		return FaceOrientation::CCW;
	}

	/// Makes vertex normals and returns number of values per vertex
	template <typename T>
	GLuint Normals(std::vector<T>& dest) const
	{
		dest.resize(((_rings + 2) * (_sections + 1)) * 3);
		size_t k = 0;
		//
		GLdouble r_step = (1.0 * math::pi()) / GLdouble(_rings + 1);
		GLdouble s_step = (2.0 * math::pi()) / GLdouble(_sections);

		for(size_t r=0; r!=(_rings+2);++r)
		{
			GLdouble r_lat = std::cos(r*r_step);
			GLdouble r_rad = std::sin(r*r_step);
			// the sections
			for(size_t s=0; s!=(_sections+1);++s)
			{
				dest[k++] = r_rad * std::cos(s * s_step);
				dest[k++] = r_lat;
				dest[k++] = r_rad * -std::sin(s * s_step);
			}
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
		dest.resize(((_rings + 2) * (_sections + 1)) * 3);
		size_t k = 0;
		//
		GLdouble s_step = (2.0 * math::pi()) / GLdouble(_sections);

		for(size_t r=0; r!=(_rings+2);++r)
		{
			for(size_t s=0; s!=(_sections+1);++s)
			{
				GLdouble vx = std::cos(s*s_step);
				GLdouble vz = std::sin(s*s_step);
				dest[k++] = +vz;
				dest[k++] = T(0);
				dest[k++] = -vx;
			}
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
		GLuint n = Normals(dest);
		if(_radius != 1.0)
			for(auto i=dest.begin(),e=dest.end(); i!= e; ++i)
				*i *= _radius;
		return n;
	}

	/// Makes texture-coorinates and returns number of values per vertex
	template <typename T>
	GLuint TexCoordinates(std::vector<T>& dest) const
	{
		dest.resize(((_rings + 2) * (_sections + 1)) * 2);
		size_t k = 0;
		//
		GLdouble r_step = 1.0 / GLdouble(_rings + 1);
		GLdouble s_step = 1.0 / GLdouble(_sections);
		for(size_t r=0; r!=(_rings+2);++r)
		{
			GLdouble r_lat = 1.0 - r*r_step;
			// the sections
			for(size_t s=0; s!=(_sections+1);++s)
			{
				dest[k++] = s * s_step;
				dest[k++] = r_lat;
			}
		}
		assert(k == dest.size());
		// 2 values per vertex
		return 2;
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Vertex attribute information for this shape builder
	/** Sphere provides build functions for the following named
	 *  vertex attributes:
	 *  - "Position" the vertex positions (Positions)
	 *  - "Normal" the vertex normal vectors (Normals)
	 *  - "Tangent" the vertex tangent vector (Tangents)
	 *  - "TexCoord" the ST texture coordinates (TexCoordinates)
	 */
	typedef VertexAttribsInfo<Sphere> VertexAttribs;
#elif !OGLPLUS_NO_VARIADIC_TEMPLATES
	typedef VertexAttribsInfo<
		Sphere,
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
		assert((1<<(sizeof(GLushort)*8))-1>=((_rings+2)*(_sections+1)));
		//
		const size_t n =
			2 * (_rings + 1)*(_sections + 1);
		//
		IndexArray indices(n);
		size_t k = 0;
		size_t offs = 0;
		// the triangle strips
		for(size_t r=0; r!=(_rings+1); ++r)
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
		return indices;
	}

	/// Returns the instructions for rendering
	DrawingInstructions Instructions(void) const
	{
		auto instructions = this->MakeInstructions();
		for(size_t r=0; r!=(_rings+1); ++r)
		{
			DrawOperation operation;
			operation.method = DrawOperation::Method::DrawElements;
			operation.mode = PrimitiveType::TriangleStrip;
			operation.first =  GLuint(r * (_sections + 1) * 2);
			operation.count = GLuint((_sections + 1) * 2);
			operation.phase = 0;
			this->AddInstruction(instructions, operation);
		}
		return instructions;
	}
};

} // shapes
} // oglplus

#endif // include guard
