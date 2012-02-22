/*
 *  .file oglplus/names/sync_status.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sync_status.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_SIGNALED
	case GL_SIGNALED: return "SIGNALED";
#endif
#if defined GL_UNSIGNALED
	case GL_UNSIGNALED: return "UNSIGNALED";
#endif
	default:;
}

