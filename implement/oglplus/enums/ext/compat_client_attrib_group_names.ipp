/*
 *  .file oglplus/enums/ext/compat_client_attrib_group_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/ext/compat_client_attrib_group.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	CompatibilityClientAttributeGroup*,
	GLbitfield value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_COMPATIBILITYCLIENTATTRIBUTEGROUP)
#define OGLPLUS_IMPL_EVN_COMPATIBILITYCLIENTATTRIBUTEGROUP
{
switch(value)
{
#if defined GL_CLIENT_VERTEX_ARRAY_BIT
	case GL_CLIENT_VERTEX_ARRAY_BIT: return StrCRef("CLIENT_VERTEX_ARRAY_BIT");
#endif
#if defined GL_CLIENT_PIXEL_STORE_BIT
	case GL_CLIENT_PIXEL_STORE_BIT: return StrCRef("CLIENT_PIXEL_STORE_BIT");
#endif
#if defined GL_CLIENT_ALL_ATTRIB_BITS
	case GL_CLIENT_ALL_ATTRIB_BITS: return StrCRef("CLIENT_ALL_ATTRIB_BITS");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums

