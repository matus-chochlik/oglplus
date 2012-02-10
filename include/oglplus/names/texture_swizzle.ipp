/*
 *  .file oglplus/names/texture_swizzle.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_swizzle.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_RED
	case GL_RED: return "RED";
#endif
#if defined GL_GREEN
	case GL_GREEN: return "GREEN";
#endif
#if defined GL_BLUE
	case GL_BLUE: return "BLUE";
#endif
#if defined GL_ALPHA
	case GL_ALPHA: return "ALPHA";
#endif
#if defined GL_ZERO
	case GL_ZERO: return "ZERO";
#endif
#if defined GL_ONE
	case GL_ONE: return "ONE";
#endif
	default:;
}

