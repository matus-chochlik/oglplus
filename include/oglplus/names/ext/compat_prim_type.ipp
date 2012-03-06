/*
 *  .file oglplus/names/ext/compat_prim_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/compat_prim_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_POINTS
	case GL_POINTS: return "POINTS";
#endif
#if defined GL_LINE_STRIP
	case GL_LINE_STRIP: return "LINE_STRIP";
#endif
#if defined GL_LINE_LOOP
	case GL_LINE_LOOP: return "LINE_LOOP";
#endif
#if defined GL_LINES
	case GL_LINES: return "LINES";
#endif
#if defined GL_TRIANGLE_STRIP
	case GL_TRIANGLE_STRIP: return "TRIANGLE_STRIP";
#endif
#if defined GL_TRIANGLE_FAN
	case GL_TRIANGLE_FAN: return "TRIANGLE_FAN";
#endif
#if defined GL_TRIANGLES
	case GL_TRIANGLES: return "TRIANGLES";
#endif
#if defined GL_QUADS
	case GL_QUADS: return "QUADS";
#endif
#if defined GL_QUAD_STRIP
	case GL_QUAD_STRIP: return "QUAD_STRIP";
#endif
#if defined GL_POLYGON
	case GL_POLYGON: return "POLYGON";
#endif
	default:;
}

