/*
 *  .file oglplus/names/face_orientation.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/face_orientation.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_CW
	case GL_CW: return "CW";
#endif
#if defined GL_CCW
	case GL_CCW: return "CCW";
#endif
	default:;
}

