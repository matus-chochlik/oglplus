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

} // namespace oglplus

#endif // include guard
