/*
 *  .file oglplus/enums/ext/nv_path_font_style_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_font_style.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	PathNVFontStyle*,
	GLbitfield value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVFONTSTYLE)
#define OGLPLUS_IMPL_EVN_PATHNVFONTSTYLE
{
switch(value)
{
#if defined GL_BOLD_BIT_NV
	case GL_BOLD_BIT_NV: return StrCRef("BOLD_BIT_NV");
#endif
#if defined GL_ITALIC_BIT_NV
	case GL_ITALIC_BIT_NV: return StrCRef("ITALIC_BIT_NV");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

