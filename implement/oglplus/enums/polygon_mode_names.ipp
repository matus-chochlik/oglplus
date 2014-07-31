/*
 *  .file oglplus/enums/polygon_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/polygon_mode.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	PolygonMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_POLYGONMODE)
#define OGLPLUS_IMPL_EVN_POLYGONMODE
{
switch(value)
{
#if defined GL_POINT
	case GL_POINT: return StrCRef("POINT");
#endif
#if defined GL_LINE
	case GL_LINE: return StrCRef("LINE");
#endif
#if defined GL_FILL
	case GL_FILL: return StrCRef("FILL");
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

