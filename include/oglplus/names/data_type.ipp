/*
 *  .file oglplus/names/data_type.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/data_type.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_BYTE
	case GL_BYTE: return "BYTE";
#endif
#if defined GL_SHORT
	case GL_SHORT: return "SHORT";
#endif
#if defined GL_INT
	case GL_INT: return "INT";
#endif
#if defined GL_FIXED
	case GL_FIXED: return "FIXED";
#endif
#if defined GL_FLOAT
	case GL_FLOAT: return "FLOAT";
#endif
#if defined GL_HALF_FLOAT
	case GL_HALF_FLOAT: return "HALF_FLOAT";
#endif
#if defined GL_DOUBLE
	case GL_DOUBLE: return "DOUBLE";
#endif
#if defined GL_UNSIGNED_BYTE
	case GL_UNSIGNED_BYTE: return "UNSIGNED_BYTE";
#endif
#if defined GL_UNSIGNED_SHORT
	case GL_UNSIGNED_SHORT: return "UNSIGNED_SHORT";
#endif
#if defined GL_UNSIGNED_INT
	case GL_UNSIGNED_INT: return "UNSIGNED_INT";
#endif
	default:;
}

