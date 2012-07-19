/*
 *  .file oglplus/enums/ext/compat_client_attrib_group.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/compat_client_attrib_group.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// CLIENT_VERTEX_ARRAY_BIT
VertexArray,
/// CLIENT_PIXEL_STORE_BIT
PixelStore,
/// CLIENT_ALL_ATTRIB_BITS
AllAttribs

#else // !OGLPLUS_DOCUMENTATION_ONLY

#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#if defined GL_CLIENT_VERTEX_ARRAY_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(VertexArray, GL_CLIENT_VERTEX_ARRAY_BIT)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_CLIENT_PIXEL_STORE_BIT
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(PixelStore, GL_CLIENT_PIXEL_STORE_BIT)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#if defined GL_CLIENT_ALL_ATTRIB_BITS
# if OGLPLUS_LIST_NEEDS_COMMA
OGLPLUS_ENUM_CLASS_COMMA
# endif
OGLPLUS_ENUM_CLASS_VALUE(AllAttribs, GL_CLIENT_ALL_ATTRIB_BITS)
# ifndef OGLPLUS_LIST_NEEDS_COMMA
#  define OGLPLUS_LIST_NEEDS_COMMA 1
# endif
#endif
#ifdef OGLPLUS_LIST_NEEDS_COMMA
# undef OGLPLUS_LIST_NEEDS_COMMA
#endif

#endif // !OGLPLUS_DOCUMENTATION_ONLY

