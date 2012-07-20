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
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Luminance)
#  pragma push_macro("Luminance")
#  undef Luminance
   OGLPLUS_ENUM_CLASS_VALUE(Luminance, GL_LUMINANCE)
#  pragma pop_macro("Luminance")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Luminance, GL_LUMINANCE)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_ALPHA
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Alpha)
#  pragma push_macro("Alpha")
#  undef Alpha
   OGLPLUS_ENUM_CLASS_VALUE(Alpha, GL_ALPHA)
#  pragma pop_macro("Alpha")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Alpha, GL_ALPHA)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_INTENSITY
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(Intensity)
#  pragma push_macro("Intensity")
#  undef Intensity
   OGLPLUS_ENUM_CLASS_VALUE(Intensity, GL_INTENSITY)
#  pragma pop_macro("Intensity")
# else
   OGLPLUS_ENUM_CLASS_VALUE(Intensity, GL_INTENSITY)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_LUMINANCE_ALPHA
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(LuminanceAlpha)
#  pragma push_macro("LuminanceAlpha")
#  undef LuminanceAlpha
   OGLPLUS_ENUM_CLASS_VALUE(LuminanceAlpha, GL_LUMINANCE_ALPHA)
#  pragma pop_macro("LuminanceAlpha")
# else
   OGLPLUS_ENUM_CLASS_VALUE(LuminanceAlpha, GL_LUMINANCE_ALPHA)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_RGB
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(RGB)
#  pragma push_macro("RGB")
#  undef RGB
   OGLPLUS_ENUM_CLASS_VALUE(RGB, GL_RGB)
#  pragma pop_macro("RGB")
# else
   OGLPLUS_ENUM_CLASS_VALUE(RGB, GL_RGB)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_RGBA
# if OGLPLUS_LIST_NEEDS_COMMA
    OGLPLUS_ENUM_CLASS_COMMA
# endif
# if OGLPLUS_NO_SCOPED_ENUMS && defined(RGBA)
#  pragma push_macro("RGBA")
#  undef RGBA
   OGLPLUS_ENUM_CLASS_VALUE(RGBA, GL_RGBA)
#  pragma pop_macro("RGBA")
# else
   OGLPLUS_ENUM_CLASS_VALUE(RGBA, GL_RGBA)
# endif
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

