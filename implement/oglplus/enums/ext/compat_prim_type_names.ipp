/*
 *  .file oglplus/enums/ext/compat_prim_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/compat_prim_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	CompatibilityPrimitiveType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPATIBILITYPRIMITIVETYPE)
#define OGLPLUS_IMPL_EVN_COMPATIBILITYPRIMITIVETYPE
{
switch(value)
{
#if defined GL_POINTS
	case GL_POINTS: return StrLit("POINTS");
#endif
#if defined GL_LINE_STRIP
	case GL_LINE_STRIP: return StrLit("LINE_STRIP");
#endif
#if defined GL_LINE_LOOP
	case GL_LINE_LOOP: return StrLit("LINE_LOOP");
#endif
#if defined GL_LINES
	case GL_LINES: return StrLit("LINES");
#endif
#if defined GL_TRIANGLE_STRIP
	case GL_TRIANGLE_STRIP: return StrLit("TRIANGLE_STRIP");
#endif
#if defined GL_TRIANGLE_FAN
	case GL_TRIANGLE_FAN: return StrLit("TRIANGLE_FAN");
#endif
#if defined GL_TRIANGLES
	case GL_TRIANGLES: return StrLit("TRIANGLES");
#endif
#if defined GL_QUADS
	case GL_QUADS: return StrLit("QUADS");
#endif
#if defined GL_QUAD_STRIP
	case GL_QUAD_STRIP: return StrLit("QUAD_STRIP");
#endif
#if defined GL_POLYGON
	case GL_POLYGON: return StrLit("POLYGON");
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

