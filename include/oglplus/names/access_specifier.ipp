/*
 *  .file oglplus/names/access_specifier.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/access_specifier.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_READ_ONLY
	case GL_READ_ONLY: return "READ_ONLY";
#endif
#if defined GL_WRITE_ONLY
	case GL_WRITE_ONLY: return "WRITE_ONLY";
#endif
#if defined GL_READ_WRITE
	case GL_READ_WRITE: return "READ_WRITE";
#endif
	default:;
}

