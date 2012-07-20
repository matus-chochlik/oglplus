/*
 *  .file oglplus/enums/ext/compat_client_attrib_group_ese.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/ext/compat_client_attrib_group.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined GL_CLIENT_VERTEX_ARRAY_BIT
# if defined VertexArray
#  pragma push_macro("VertexArray")
#  undef VertexArray
   OGLPLUS_ENUM_CLASS_VALUE(VertexArray, GL_CLIENT_VERTEX_ARRAY_BIT)
#  pragma pop_macro("VertexArray")
# else
   OGLPLUS_ENUM_CLASS_VALUE(VertexArray, GL_CLIENT_VERTEX_ARRAY_BIT)
# endif
#endif
#if defined GL_CLIENT_PIXEL_STORE_BIT
# if defined PixelStore
#  pragma push_macro("PixelStore")
#  undef PixelStore
   OGLPLUS_ENUM_CLASS_VALUE(PixelStore, GL_CLIENT_PIXEL_STORE_BIT)
#  pragma pop_macro("PixelStore")
# else
   OGLPLUS_ENUM_CLASS_VALUE(PixelStore, GL_CLIENT_PIXEL_STORE_BIT)
# endif
#endif
#if defined GL_CLIENT_ALL_ATTRIB_BITS
# if defined AllAttribs
#  pragma push_macro("AllAttribs")
#  undef AllAttribs
   OGLPLUS_ENUM_CLASS_VALUE(AllAttribs, GL_CLIENT_ALL_ATTRIB_BITS)
#  pragma pop_macro("AllAttribs")
# else
   OGLPLUS_ENUM_CLASS_VALUE(AllAttribs, GL_CLIENT_ALL_ATTRIB_BITS)
# endif
#endif
