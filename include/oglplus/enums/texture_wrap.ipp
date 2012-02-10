/*
 *  .file oglplus/enums/texture_wrap.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_wrap.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// CLAMP_TO_EDGE
ClampToEdge,
/// REPEAT
Repeat,
/// CLAMP_TO_BORDER
ClampToBorder,
/// MIRRORED_REPEAT
MirroredRepeat

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CLAMP_TO_EDGE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ClampToEdge = GL_CLAMP_TO_EDGE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_REPEAT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Repeat = GL_REPEAT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_CLAMP_TO_BORDER
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
ClampToBorder = GL_CLAMP_TO_BORDER
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_MIRRORED_REPEAT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
MirroredRepeat = GL_MIRRORED_REPEAT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

