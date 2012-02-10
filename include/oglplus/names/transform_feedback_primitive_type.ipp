/*
 *  .file oglplus/names/transform_feedback_primitive_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/transform_feedback_primitive_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_TRIANGLES
	case GL_TRIANGLES: return "TRIANGLES";
#endif
#if defined GL_LINES
	case GL_LINES: return "LINES";
#endif
#if defined GL_POINTS
	case GL_POINTS: return "POINTS";
#endif
	default:;
}

