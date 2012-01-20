/*
 *  .file oglplus/enums/compare_function.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/compare_function.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// LEQUAL: Less-than or equal
LEqual,
/// GEQUAL: Greater-than or equal
GEqual,
/// LESS: Less-than
Less,
/// GREATER: Greater-than
Greater,
/// EQUAL: Equality
Equal,
/// NOTEQUAL: Nonequality
NotEqual,
/// ALWAYS: Always true
Always,
/// NEVER: Always false
Never

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_LEQUAL
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LEqual = GL_LEQUAL
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_GEQUAL
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
GEqual = GL_GEQUAL
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LESS
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Less = GL_LESS
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_GREATER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Greater = GL_GREATER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_EQUAL
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Equal = GL_EQUAL
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_NOTEQUAL
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
NotEqual = GL_NOTEQUAL
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALWAYS
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Always = GL_ALWAYS
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_NEVER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Never = GL_NEVER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

