/*
 *  .file oglplus/names/texture_min_filter.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/texture_min_filter.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_NEAREST
	case GL_NEAREST: return "NEAREST";
#endif
#if defined GL_LINEAR
	case GL_LINEAR: return "LINEAR";
#endif
#if defined GL_NEAREST_MIPMAP_NEAREST
	case GL_NEAREST_MIPMAP_NEAREST: return "NEAREST_MIPMAP_NEAREST";
#endif
#if defined GL_NEAREST_MIPMAP_LINEAR
	case GL_NEAREST_MIPMAP_LINEAR: return "NEAREST_MIPMAP_LINEAR";
#endif
#if defined GL_LINEAR_MIPMAP_NEAREST
	case GL_LINEAR_MIPMAP_NEAREST: return "LINEAR_MIPMAP_NEAREST";
#endif
#if defined GL_LINEAR_MIPMAP_LINEAR
	case GL_LINEAR_MIPMAP_LINEAR: return "LINEAR_MIPMAP_LINEAR";
#endif
	default:;
}

