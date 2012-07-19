/*
 *  .file oglplus/enums/face_orientation.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/face_orientation.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// CW: Clockwise
CW,
/// CCW: Counter-clockwise
CCW

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CW
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(CW, GL_CW)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_CCW
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(CCW, GL_CCW)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

