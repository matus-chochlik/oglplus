/*
 *  .file oglplus/enums/capability.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/capability.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// DEPTH_TEST
DepthTest,
/// STENCIL_TEST
StencilTest,
/// CULL_FACE
CullFace,
/// POLYGON_OFFSET_POINT
PolygonOffsetPoint,
/// POLYGON_OFFSET_LINE
PolygonOffsetLine,
/// POLYGON_OFFSET_FILL
PolygonOffsetFill,
/// BLEND
Blend,
/// COLOR_LOGIC_OP
ColorLogicOp

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_DEPTH_TEST
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
DepthTest = GL_DEPTH_TEST
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_STENCIL_TEST
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
StencilTest = GL_STENCIL_TEST
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_CULL_FACE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
CullFace = GL_CULL_FACE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_OFFSET_POINT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_OFFSET_LINE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PolygonOffsetLine = GL_POLYGON_OFFSET_LINE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_POLYGON_OFFSET_FILL
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
PolygonOffsetFill = GL_POLYGON_OFFSET_FILL
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BLEND
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Blend = GL_BLEND
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COLOR_LOGIC_OP
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ColorLogicOp = GL_COLOR_LOGIC_OP
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

