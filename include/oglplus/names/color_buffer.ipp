/*
 *  .file oglplus/names/color_buffer.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/color_buffer.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_NONE
	case GL_NONE: return StrLit("NONE");
#endif
#if defined GL_FRONT_LEFT
	case GL_FRONT_LEFT: return StrLit("FRONT_LEFT");
#endif
#if defined GL_FRONT_RIGHT
	case GL_FRONT_RIGHT: return StrLit("FRONT_RIGHT");
#endif
#if defined GL_BACK_LEFT
	case GL_BACK_LEFT: return StrLit("BACK_LEFT");
#endif
#if defined GL_BACK_RIGHT
	case GL_BACK_RIGHT: return StrLit("BACK_RIGHT");
#endif
#if defined GL_FRONT
	case GL_FRONT: return StrLit("FRONT");
#endif
#if defined GL_BACK
	case GL_BACK: return StrLit("BACK");
#endif
#if defined GL_LEFT
	case GL_LEFT: return StrLit("LEFT");
#endif
#if defined GL_RIGHT
	case GL_RIGHT: return StrLit("RIGHT");
#endif
#if defined GL_FRONT_AND_BACK
	case GL_FRONT_AND_BACK: return StrLit("FRONT_AND_BACK");
#endif
	default:;
}

