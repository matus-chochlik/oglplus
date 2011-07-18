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
	Points = GL_POINTS,
	LineStrip = GL_LINE_STRIP,
	LineLoop = GL_LINE_LOOP,
	Lines = GL_LINES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Triangles = GL_TRIANGLES,
	LinesAdjcacency = GL_LINES_ADJACENCY,
	LineStripAdjcacency = GL_LINE_STRIP_ADJACENCY,
	TrianglesAdjcacency = GL_LINES_ADJACENCY,
	TriangleStripAdjcacency = GL_LINE_STRIP_ADJACENCY,
	Patches = GL_PATCHES
};

} // namespace oglplus

#endif // include guard
