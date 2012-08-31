/*
 *  .file oglplus/names/polygon_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/polygon_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(value)
{
#if defined GL_POINT
	case GL_POINT: return StrLit("POINT");
#endif
#if defined GL_LINE
	case GL_LINE: return StrLit("LINE");
#endif
#if defined GL_FILL
	case GL_FILL: return StrLit("FILL");
#endif
	default:;
}

