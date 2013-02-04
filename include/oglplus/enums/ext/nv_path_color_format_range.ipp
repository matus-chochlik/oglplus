/*
 *  .file oglplus/enums/ext/nv_path_color_format_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_color_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	PathNVColorFormat
> EnumValueRange(PathNVColorFormat*)
OGLPLUS_NOEXCEPT(true)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVCOLORFORMAT)
#define OGLPLUS_IMPL_EVN_PATHNVCOLORFORMAT
{
static const GLenum _values[] = {
#if defined GL_LUMINANCE
GL_LUMINANCE,
#endif
#if defined GL_ALPHA
GL_ALPHA,
#endif
#if defined GL_INTENSITY
GL_INTENSITY,
#endif
#if defined GL_LUMINANCE_ALPHA
GL_LUMINANCE_ALPHA,
#endif
#if defined GL_RGB
GL_RGB,
#endif
#if defined GL_RGBA
GL_RGBA,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	PathNVColorFormat
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif

