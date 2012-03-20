/*
 *  .file oglplus/enums/ext/nv_path_list_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_list_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// ACCUM_ADJACENT_PAIRS_NV
AccumAdjacentPairs,
/// ADJACENT_PAIRS_NV
AdjacentPairs,
/// FIRST_TO_REST_NV
FirstToRest

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_ACCUM_ADJACENT_PAIRS_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
AccumAdjacentPairs = GL_ACCUM_ADJACENT_PAIRS_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ADJACENT_PAIRS_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
AdjacentPairs = GL_ADJACENT_PAIRS_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FIRST_TO_REST_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
FirstToRest = GL_FIRST_TO_REST_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

