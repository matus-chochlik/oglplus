/*
 *  .file oglplus/enums/ext/nv_path_color_format_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_color_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVColorFormat*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVCOLORFORMAT)
#define OGLPLUS_IMPL_EVN_PATHNVCOLORFORMAT
{
switch(value)
{
#if defined GL_LUMINANCE
	case GL_LUMINANCE: return StrLit("LUMINANCE");
#endif
#if defined GL_ALPHA
	case GL_ALPHA: return StrLit("ALPHA");
#endif
#if defined GL_INTENSITY
	case GL_INTENSITY: return StrLit("INTENSITY");
#endif
#if defined GL_LUMINANCE_ALPHA
	case GL_LUMINANCE_ALPHA: return StrLit("LUMINANCE_ALPHA");
#endif
#if defined GL_RGB
	case GL_RGB: return StrLit("RGB");
#endif
#if defined GL_RGBA
	case GL_RGBA: return StrLit("RGBA");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

