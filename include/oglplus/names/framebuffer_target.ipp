/*
 *  .file oglplus/names/framebuffer_target.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/framebuffer_target.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(value)
{
#if defined GL_DRAW_FRAMEBUFFER
	case GL_DRAW_FRAMEBUFFER: return StrLit("DRAW_FRAMEBUFFER");
#endif
#if defined GL_READ_FRAMEBUFFER
	case GL_READ_FRAMEBUFFER: return StrLit("READ_FRAMEBUFFER");
#endif
	default:;
}

