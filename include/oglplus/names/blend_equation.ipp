/*
 *  .file oglplus/names/blend_equation.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/blend_equation.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_FUNC_ADD
	case GL_FUNC_ADD: return "FUNC_ADD";
#endif
#if defined GL_FUNC_SUBTRACT
	case GL_FUNC_SUBTRACT: return "FUNC_SUBTRACT";
#endif
#if defined GL_FUNC_REVERSE_SUBTRACT
	case GL_FUNC_REVERSE_SUBTRACT: return "FUNC_REVERSE_SUBTRACT";
#endif
#if defined GL_MIN
	case GL_MIN: return "MIN";
#endif
#if defined GL_MAX
	case GL_MAX: return "MAX";
#endif
	default:;
}

