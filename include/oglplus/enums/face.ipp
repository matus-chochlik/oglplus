/*
 *  .file oglplus/enums/face.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/face.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// FRONT
Front,
/// BACK
Back,
/// FRONT_AND_BACK
FrontAndBack

#else // OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_FRONT
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Front = GL_FRONT
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_BACK
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Back = GL_BACK
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_FRONT_AND_BACK
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
FrontAndBack = GL_FRONT_AND_BACK
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // OGLPLUS_DOCUMENTATION_ONLY

