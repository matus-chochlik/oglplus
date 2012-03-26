/*
 *  .file oglplus/names/ext/compat_client_attrib_group.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/compat_client_attrib_group.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

switch(GLenum(value))
{
#if defined GL_CLIENT_VERTEX_ARRAY_BIT
	case GL_CLIENT_VERTEX_ARRAY_BIT: return "CLIENT_VERTEX_ARRAY_BIT";
#endif
#if defined GL_CLIENT_PIXEL_STORE_BIT
	case GL_CLIENT_PIXEL_STORE_BIT: return "CLIENT_PIXEL_STORE_BIT";
#endif
#if defined GL_CLIENT_ALL_ATTRIB_BITS
	case GL_CLIENT_ALL_ATTRIB_BITS: return "CLIENT_ALL_ATTRIB_BITS";
#endif
	default:;
}

