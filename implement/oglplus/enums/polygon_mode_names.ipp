/*
 *  .file oglplus/enums/polygon_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/polygon_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
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
	case GL_POINT: return StrLit("POINT");
#endif
#if defined GL_LINE
	case GL_LINE: return StrLit("LINE");
#endif
#if defined GL_FILL
	case GL_FILL: return StrLit("FILL");
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

