/*
 *  .file oglplus/names/sync_wait_result.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/sync_wait_result.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_CONDITION_SATISFIED
	case GL_CONDITION_SATISFIED: return StrLit("CONDITION_SATISFIED");
#endif
#if defined GL_ALREADY_SIGNALED
	case GL_ALREADY_SIGNALED: return StrLit("ALREADY_SIGNALED");
#endif
#if defined GL_TIMEOUT_EXPIRED
	case GL_TIMEOUT_EXPIRED: return StrLit("TIMEOUT_EXPIRED");
#endif
#if defined GL_WAIT_FAILED
	case GL_WAIT_FAILED: return StrLit("WAIT_FAILED");
#endif
	default:;
}

