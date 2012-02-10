/*
 *  .file oglplus/enums/primitive_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/primitive_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// POINTS
Points,
/// LINE_STRIP
LineStrip,
/// LINE_LOOP
LineLoop,
/// LINES
Lines,
/// TRIANGLE_STRIP
TriangleStrip,
/// TRIANGLE_FAN
TriangleFan,
/// TRIANGLES
Triangles,
/// LINES_ADJACENCY
LinesAdjacency,
/// LINE_STRIP_ADJACENCY
LineStripAdjacency,
/// TRIANGLES_ADJACENCY
TrianglesAdjacency,
/// TRIANGLE_STRIP_ADJACENCY
TriangleStripAdjacency,
/// PATCHES
Patches

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_POINTS
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Points = GL_POINTS
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINE_STRIP
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LineStrip = GL_LINE_STRIP
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINE_LOOP
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LineLoop = GL_LINE_LOOP
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINES
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Lines = GL_LINES
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRIANGLE_STRIP
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TriangleStrip = GL_TRIANGLE_STRIP
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRIANGLE_FAN
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TriangleFan = GL_TRIANGLE_FAN
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRIANGLES
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Triangles = GL_TRIANGLES
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINES_ADJACENCY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LinesAdjacency = GL_LINES_ADJACENCY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINE_STRIP_ADJACENCY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LineStripAdjacency = GL_LINE_STRIP_ADJACENCY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRIANGLES_ADJACENCY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TrianglesAdjacency = GL_TRIANGLES_ADJACENCY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TRIANGLE_STRIP_ADJACENCY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATCHES
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Patches = GL_PATCHES
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

