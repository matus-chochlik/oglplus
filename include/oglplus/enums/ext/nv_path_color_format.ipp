/*
 *  .file oglplus/enums/ext/nv_path_color_format.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_color_format.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// LUMINANCE
Luminance,
/// ALPHA
Alpha,
/// INTENSITY
Intensity,
/// LUMINANCE_ALPHA
LuminanceAlpha,
/// RGB
RGB,
/// RGBA
RGBA

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_LUMINANCE
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Luminance = GL_LUMINANCE
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALPHA
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Alpha = GL_ALPHA
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INTENSITY
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
Intensity = GL_INTENSITY
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LUMINANCE_ALPHA
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
LuminanceAlpha = GL_LUMINANCE_ALPHA
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_RGB
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
RGB = GL_RGB
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_RGBA
# if OGLPLUS_LIST_NEEDS_COMMA
,
# endif
RGBA = GL_RGBA
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

