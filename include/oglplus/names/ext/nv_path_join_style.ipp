/*
 *  .file oglplus/names/ext/nv_path_join_style.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/nv_path_join_style.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_NONE
	case GL_NONE: return StrLit("NONE");
#endif
#if defined GL_ROUND_NV
	case GL_ROUND_NV: return StrLit("ROUND_NV");
#endif
#if defined GL_BEVEL_NV
	case GL_BEVEL_NV: return StrLit("BEVEL_NV");
#endif
#if defined GL_MITER_REVERT_NV
	case GL_MITER_REVERT_NV: return StrLit("MITER_REVERT_NV");
#endif
#if defined GL_MITER_TRUNCATE_NV
	case GL_MITER_TRUNCATE_NV: return StrLit("MITER_TRUNCATE_NV");
#endif
	default:;
}

