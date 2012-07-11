/*
 *  .file oglplus/names/texture_wrap_coord.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_wrap_coord.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_TEXTURE_WRAP_S
	case GL_TEXTURE_WRAP_S: return StrLit("TEXTURE_WRAP_S");
#endif
#if defined GL_TEXTURE_WRAP_T
	case GL_TEXTURE_WRAP_T: return StrLit("TEXTURE_WRAP_T");
#endif
#if defined GL_TEXTURE_WRAP_R
	case GL_TEXTURE_WRAP_R: return StrLit("TEXTURE_WRAP_R");
#endif
	default:;
}

