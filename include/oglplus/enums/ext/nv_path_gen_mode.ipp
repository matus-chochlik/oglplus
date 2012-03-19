/*
 *  .file oglplus/enums/ext/nv_path_gen_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_gen_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// NONE
None,
/// EYE_LINEAR
EyeLinear,
/// OBJECT_LINEAR
ObjectLinear,
/// PATH_OBJECT_BOUNDING_BOX_NV
ObjectBoundingBox

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_NONE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
None = GL_NONE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_EYE_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
EyeLinear = GL_EYE_LINEAR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_OBJECT_LINEAR
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ObjectLinear = GL_OBJECT_LINEAR
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_OBJECT_BOUNDING_BOX_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ObjectBoundingBox = GL_PATH_OBJECT_BOUNDING_BOX_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

