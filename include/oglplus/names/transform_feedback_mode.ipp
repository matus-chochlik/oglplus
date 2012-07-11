/*
 *  .file oglplus/names/transform_feedback_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/transform_feedback_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_INTERLEAVED_ATTRIBS
	case GL_INTERLEAVED_ATTRIBS: return StrLit("INTERLEAVED_ATTRIBS");
#endif
#if defined GL_SEPARATE_ATTRIBS
	case GL_SEPARATE_ATTRIBS: return StrLit("SEPARATE_ATTRIBS");
#endif
	default:;
}

