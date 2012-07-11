/*
 *  .file oglplus/names/hint_option.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/hint_option.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_FASTEST
	case GL_FASTEST: return StrLit("FASTEST");
#endif
#if defined GL_NICEST
	case GL_NICEST: return StrLit("NICEST");
#endif
#if defined GL_DONT_CARE
	case GL_DONT_CARE: return StrLit("DONT_CARE");
#endif
	default:;
}

