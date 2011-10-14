/**
 *  @file oglplus/primitive_type.hpp
 *  @brief OpenGL primitive type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PRIMITIVE_TYPE_1107121519_HPP
#define OGLPLUS_PRIMITIVE_TYPE_1107121519_HPP

namespace oglplus {

/// Primitive type enumeration
/**
 *  @ingroup enumerations
 */
enum class PrimitiveType : GLenum
{
	/// POINTS
	Points = GL_POINTS,
	/// LINE_STRIP
	LineStrip = GL_LINE_STRIP,
	/// LINE_LOOP
	LineLoop = GL_LINE_LOOP,
	/// LINES
	Lines = GL_LINES,
	/// TRIANGLE_STRIP
	TriangleStrip = GL_TRIANGLE_STRIP,
	/// TRIANGLE_FAN
	TriangleFan = GL_TRIANGLE_FAN,
	/// TRIANGLES
	Triangles = GL_TRIANGLES,
	/// LINES_ADJACENCY
	LinesAdjacency = GL_LINES_ADJACENCY,
	/// LINE_STRIP_ADJACENCY
	LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
	/// TRIANGLES_ADJACENCY
	TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
	/// TRIANGLE_STRIP_ADJACENCY
	TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	/// PATCHES
	Patches = GL_PATCHES
};

/// Tesselation generation stage primitive type
/**
 * @ingroup enumerations
 */
enum class TessGenPrimitiveType : GLenum
{
	/// QUADS
	//TODO: Quads = GL_QUADS,
	/// TRIANGLES
	Triangles = GL_TRIANGLES,
	/// ISOLINES
	Isolines = GL_ISOLINES
};

/// Tesselation primitive spacing
/**
 * @ingroup enumerations
 */
enum class TessGenPrimitiveSpacing : GLenum
{
	/// FRACTIONAL_EVEN
	FractionalEven = GL_FRACTIONAL_EVEN,
	/// FRACTIONAL_ODD
	FractionalOdd = GL_FRACTIONAL_ODD,
	/// EQUAL
	Equal = GL_EQUAL
};

} // namespace oglplus

#endif // include guard
