/*
 *  .file oglplus/enums/texture_swizzle.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_swizzle.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// RED
Red,
/// GREEN
Green,
/// BLUE
Blue,
/// ALPHA
Alpha,
/// ZERO
Zero,
/// ONE
One

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_RED
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Red = GL_RED
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_GREEN
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Green = GL_GREEN
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BLUE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Blue = GL_BLUE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALPHA
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Alpha = GL_ALPHA
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ZERO
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Zero = GL_ZERO
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ONE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
One = GL_ONE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

