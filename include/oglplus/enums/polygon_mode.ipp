/*
 *  .file oglplus/enums/polygon_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/polygon_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// POINT
Point,
/// LINE
Line,
/// FILL
Fill

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_POINT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Point = GL_POINT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Line = GL_LINE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FILL
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Fill = GL_FILL
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

