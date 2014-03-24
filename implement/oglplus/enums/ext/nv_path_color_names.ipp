/*
 *  .file oglplus/enums/ext/nv_path_color_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_color.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PathNVColor*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVCOLOR)
#define OGLPLUS_IMPL_EVN_PATHNVCOLOR
{
switch(value)
{
#if defined GL_PRIMARY_COLOR_NV
	case GL_PRIMARY_COLOR_NV: return StrLit("PRIMARY_COLOR_NV");
#endif
#if defined GL_SECONDARY_COLOR_NV
	case GL_SECONDARY_COLOR_NV: return StrLit("SECONDARY_COLOR_NV");
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

