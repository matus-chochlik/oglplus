/*
 *  .file oglplus/enums/transform_feedback_primitive_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/transform_feedback_primitive_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// TRIANGLES
Triangles,
/// LINES
Lines,
/// POINTS
Points

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
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
#if defined GL_LINES
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Lines = GL_LINES
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
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
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

