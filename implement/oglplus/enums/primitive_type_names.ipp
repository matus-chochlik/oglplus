//  File implement/oglplus/enums/primitive_type_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/primitive_type.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	PrimitiveType*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PRIMITIVETYPE)
#define OGLPLUS_IMPL_EVN_PRIMITIVETYPE
{
switch(value)
{
#if defined GL_POINTS
	case GL_POINTS: return CStrRef("POINTS");
#endif
#if defined GL_LINE_STRIP
	case GL_LINE_STRIP: return CStrRef("LINE_STRIP");
#endif
#if defined GL_LINE_LOOP
	case GL_LINE_LOOP: return CStrRef("LINE_LOOP");
#endif
#if defined GL_LINES
	case GL_LINES: return CStrRef("LINES");
#endif
#if defined GL_TRIANGLE_STRIP
	case GL_TRIANGLE_STRIP: return CStrRef("TRIANGLE_STRIP");
#endif
#if defined GL_TRIANGLE_FAN
	case GL_TRIANGLE_FAN: return CStrRef("TRIANGLE_FAN");
#endif
#if defined GL_TRIANGLES
	case GL_TRIANGLES: return CStrRef("TRIANGLES");
#endif
#if defined GL_LINES_ADJACENCY
	case GL_LINES_ADJACENCY: return CStrRef("LINES_ADJACENCY");
#endif
#if defined GL_LINE_STRIP_ADJACENCY
	case GL_LINE_STRIP_ADJACENCY: return CStrRef("LINE_STRIP_ADJACENCY");
#endif
#if defined GL_TRIANGLES_ADJACENCY
	case GL_TRIANGLES_ADJACENCY: return CStrRef("TRIANGLES_ADJACENCY");
#endif
#if defined GL_TRIANGLE_STRIP_ADJACENCY
	case GL_TRIANGLE_STRIP_ADJACENCY: return CStrRef("TRIANGLE_STRIP_ADJACENCY");
#endif
#if defined GL_PATCHES
	case GL_PATCHES: return CStrRef("PATCHES");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

