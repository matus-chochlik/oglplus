/*
 *  .file oglplus/names/error_code.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/error_code.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_NO_ERROR
	case GL_NO_ERROR: return "NO_ERROR";
#endif
#if defined GL_OUT_OF_MEMORY
	case GL_OUT_OF_MEMORY: return "OUT_OF_MEMORY";
#endif
#if defined GL_INVALID_ENUM
	case GL_INVALID_ENUM: return "INVALID_ENUM";
#endif
#if defined GL_INVALID_VALUE
	case GL_INVALID_VALUE: return "INVALID_VALUE";
#endif
#if defined GL_INVALID_OPERATION
	case GL_INVALID_OPERATION: return "INVALID_OPERATION";
#endif
#if defined GL_INVALID_FRAMEBUFFER_OPERATION
	case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
#endif
#if defined GL_STACK_OVERFLOW
	case GL_STACK_OVERFLOW: return "STACK_OVERFLOW";
#endif
#if defined GL_STACK_UNDERFLOW
	case GL_STACK_UNDERFLOW: return "STACK_UNDERFLOW";
#endif
#if defined GL_TABLE_TOO_LARGE
	case GL_TABLE_TOO_LARGE: return "TABLE_TOO_LARGE";
#endif
	default:;
}

