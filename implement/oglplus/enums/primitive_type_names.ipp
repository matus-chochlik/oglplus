/*
 *  .file oglplus/enums/primitive_type_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/primitive_type.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	PrimitiveType*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PRIMITIVETYPE)
#define OGLPLUS_IMPL_EVN_PRIMITIVETYPE
{
switch(value)
{
#if defined GL_POINTS
	case GL_POINTS: return StrCRef("POINTS");
#endif
#if defined GL_LINE_STRIP
	case GL_LINE_STRIP: return StrCRef("LINE_STRIP");
#endif
#if defined GL_LINE_LOOP
	case GL_LINE_LOOP: return StrCRef("LINE_LOOP");
#endif
#if defined GL_LINES
	case GL_LINES: return StrCRef("LINES");
#endif
#if defined GL_TRIANGLE_STRIP
	case GL_TRIANGLE_STRIP: return StrCRef("TRIANGLE_STRIP");
#endif
#if defined GL_TRIANGLE_FAN
	case GL_TRIANGLE_FAN: return StrCRef("TRIANGLE_FAN");
#endif
#if defined GL_TRIANGLES
	case GL_TRIANGLES: return StrCRef("TRIANGLES");
#endif
#if defined GL_LINES_ADJACENCY
	case GL_LINES_ADJACENCY: return StrCRef("LINES_ADJACENCY");
#endif
#if defined GL_LINE_STRIP_ADJACENCY
	case GL_LINE_STRIP_ADJACENCY: return StrCRef("LINE_STRIP_ADJACENCY");
#endif
#if defined GL_TRIANGLES_ADJACENCY
	case GL_TRIANGLES_ADJACENCY: return StrCRef("TRIANGLES_ADJACENCY");
#endif
#if defined GL_TRIANGLE_STRIP_ADJACENCY
	case GL_TRIANGLE_STRIP_ADJACENCY: return StrCRef("TRIANGLE_STRIP_ADJACENCY");
#endif
#if defined GL_PATCHES
	case GL_PATCHES: return StrCRef("PATCHES");
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

