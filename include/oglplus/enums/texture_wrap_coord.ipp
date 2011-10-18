/*
 *  .file oglplus/enums/texture_wrap_coord.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_wrap_coord.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// TEXTURE_WRAP_S
S,
/// TEXTURE_WRAP_T
T,
/// TEXTURE_WRAP_R
R

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_TEXTURE_WRAP_S
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
S = GL_TEXTURE_WRAP_S
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_WRAP_T
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
T = GL_TEXTURE_WRAP_T
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_TEXTURE_WRAP_R
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
R = GL_TEXTURE_WRAP_R
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

