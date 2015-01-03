//  File implement/oglplus/enums/buffer_map_access_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/buffer_map_access.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2015 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	BufferMapAccess*,
	GLbitfield value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BUFFERMAPACCESS)
#define OGLPLUS_IMPL_EVN_BUFFERMAPACCESS
{
switch(value)
{
#if defined GL_MAP_READ_BIT
	case GL_MAP_READ_BIT: return CStrRef("MAP_READ_BIT");
#endif
#if defined GL_MAP_WRITE_BIT
	case GL_MAP_WRITE_BIT: return CStrRef("MAP_WRITE_BIT");
#endif
#if defined GL_MAP_PERSISTENT_BIT
	case GL_MAP_PERSISTENT_BIT: return CStrRef("MAP_PERSISTENT_BIT");
#endif
#if defined GL_MAP_COHERENT_BIT
	case GL_MAP_COHERENT_BIT: return CStrRef("MAP_COHERENT_BIT");
#endif
#if defined GL_MAP_INVALIDATE_RANGE_BIT
	case GL_MAP_INVALIDATE_RANGE_BIT: return CStrRef("MAP_INVALIDATE_RANGE_BIT");
#endif
#if defined GL_MAP_INVALIDATE_BUFFER_BIT
	case GL_MAP_INVALIDATE_BUFFER_BIT: return CStrRef("MAP_INVALIDATE_BUFFER_BIT");
#endif
#if defined GL_MAP_FLUSH_EXPLICIT_BIT
	case GL_MAP_FLUSH_EXPLICIT_BIT: return CStrRef("MAP_FLUSH_EXPLICIT_BIT");
#endif
#if defined GL_MAP_UNSYNCHRONIZED_BIT
	case GL_MAP_UNSYNCHRONIZED_BIT: return CStrRef("MAP_UNSYNCHRONIZED_BIT");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

