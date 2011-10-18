/*
 *  .file oglplus/enums/texture_min_filter.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_min_filter.txt' instead.
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// NEAREST
Nearest,
/// LINEAR
Linear,
/// NEAREST_MIPMAP_NEAREST
NearestMipmapNearest,
/// NEAREST_MIPMAP_LINEAR
NearestMipmapLinear,
/// LINEAR_MIPMAP_NEAREST
LinearMipmapNearest,
/// LINEAR_MIPMAP_LINEAR
LinearMipmapLinear

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_NEAREST
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Nearest = GL_NEAREST
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Linear = GL_LINEAR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_NEAREST_MIPMAP_NEAREST
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_NEAREST_MIPMAP_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINEAR_MIPMAP_NEAREST
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LINEAR_MIPMAP_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

