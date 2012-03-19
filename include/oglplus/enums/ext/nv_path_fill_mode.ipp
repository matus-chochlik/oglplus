/*
 *  .file oglplus/enums/ext/nv_path_fill_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_fill_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// INVERT
Invert,
/// COUNT_UP_NV
CountUp,
/// COUNT_DOWN_NV
CountDown,
/// PATH_FILL_MODE_NV
FillMode

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_INVERT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Invert = GL_INVERT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COUNT_UP_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
CountUp = GL_COUNT_UP_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_COUNT_DOWN_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
CountDown = GL_COUNT_DOWN_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_PATH_FILL_MODE_NV
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
FillMode = GL_PATH_FILL_MODE_NV
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

