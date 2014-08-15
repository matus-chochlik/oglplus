/*
 *  .file oglplus/enums/ext/nv_path_cap_style_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/nv_path_cap_style.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	PathNVCapStyle*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PATHNVCAPSTYLE)
#define OGLPLUS_IMPL_EVN_PATHNVCAPSTYLE
{
switch(value)
{
#if defined GL_FLAT
	case GL_FLAT: return StrCRef("FLAT");
#endif
#if defined GL_SQUARE_NV
	case GL_SQUARE_NV: return StrCRef("SQUARE_NV");
#endif
#if defined GL_ROUND_NV
	case GL_ROUND_NV: return StrCRef("ROUND_NV");
#endif
#if defined GL_TRIANGULAR_NV
	case GL_TRIANGULAR_NV: return StrCRef("TRIANGULAR_NV");
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

