/*
 *  .file oglplus/names/ext/compat_matrix_mode.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/compat_matrix_mode.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(value)
{
#if defined GL_PROJECTION
	case GL_PROJECTION: return StrLit("PROJECTION");
#endif
#if defined GL_MODELVIEW
	case GL_MODELVIEW: return StrLit("MODELVIEW");
#endif
	default:;
}

