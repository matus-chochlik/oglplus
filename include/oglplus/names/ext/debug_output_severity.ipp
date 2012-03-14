/*
 *  .file oglplus/names/ext/debug_output_severity.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/debug_output_severity.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_DEBUG_SEVERITY_HIGH_ARB
	case GL_DEBUG_SEVERITY_HIGH_ARB: return "DEBUG_SEVERITY_HIGH_ARB";
#endif
#if defined GL_DEBUG_SEVERITY_MEDIUM_ARB
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: return "DEBUG_SEVERITY_MEDIUM_ARB";
#endif
#if defined GL_DEBUG_SEVERITY_LOW_ARB
	case GL_DEBUG_SEVERITY_LOW_ARB: return "DEBUG_SEVERITY_LOW_ARB";
#endif
	default:;
}

