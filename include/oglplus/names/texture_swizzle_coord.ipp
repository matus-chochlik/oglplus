/*
 *  .file oglplus/names/texture_swizzle_coord.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_swizzle_coord.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_TEXTURE_SWIZZLE_R
	case GL_TEXTURE_SWIZZLE_R: return "TEXTURE_SWIZZLE_R";
#endif
#if defined GL_TEXTURE_SWIZZLE_G
	case GL_TEXTURE_SWIZZLE_G: return "TEXTURE_SWIZZLE_G";
#endif
#if defined GL_TEXTURE_SWIZZLE_B
	case GL_TEXTURE_SWIZZLE_B: return "TEXTURE_SWIZZLE_B";
#endif
#if defined GL_TEXTURE_SWIZZLE_A
	case GL_TEXTURE_SWIZZLE_A: return "TEXTURE_SWIZZLE_A";
#endif
#if defined GL_TEXTURE_SWIZZLE_RGBA
	case GL_TEXTURE_SWIZZLE_RGBA: return "TEXTURE_SWIZZLE_RGBA";
#endif
	default:;
}

