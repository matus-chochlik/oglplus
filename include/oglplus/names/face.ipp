/*
 *  .file oglplus/names/face.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/face.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_FRONT
	case GL_FRONT: return StrLit("FRONT");
#endif
#if defined GL_BACK
	case GL_BACK: return StrLit("BACK");
#endif
#if defined GL_FRONT_AND_BACK
	case GL_FRONT_AND_BACK: return StrLit("FRONT_AND_BACK");
#endif
	default:;
}

