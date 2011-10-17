/*
 *  .file oglplus/enums/blend_equation.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/blend_equation.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FUNC_ADD
Add,
/// FUNC_SUBTRACT
Subtract,
/// FUNC_REVERSE_SUBTRACT
ReverseSubtract,
/// MIN
Min,
/// MAX
Max

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FUNC_ADD
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Add = GL_FUNC_ADD
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FUNC_SUBTRACT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Subtract = GL_FUNC_SUBTRACT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FUNC_REVERSE_SUBTRACT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MIN
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Min = GL_MIN
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MAX
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Max = GL_MAX
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

