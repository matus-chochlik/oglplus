/*
 *  .file oglplus/enums/buffer_storage_bit_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_storage_bit.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	BufferStorageBit*,
	GLbitfield value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_BUFFERSTORAGEBIT)
#define OGLPLUS_IMPL_EVN_BUFFERSTORAGEBIT
{
switch(value)
{
#if defined GL_MAP_READ_BIT
	case GL_MAP_READ_BIT: return StrLit("MAP_READ_BIT");
#endif
#if defined GL_MAP_WRITE_BIT
	case GL_MAP_WRITE_BIT: return StrLit("MAP_WRITE_BIT");
#endif
#if defined GL_MAP_PERSISTENT_BIT
	case GL_MAP_PERSISTENT_BIT: return StrLit("MAP_PERSISTENT_BIT");
#endif
#if defined GL_MAP_COHERENT_BIT
	case GL_MAP_COHERENT_BIT: return StrLit("MAP_COHERENT_BIT");
#endif
#if defined GL_DYNAMIC_STORAGE_BIT
	case GL_DYNAMIC_STORAGE_BIT: return StrLit("DYNAMIC_STORAGE_BIT");
#endif
#if defined GL_CLIENT_STORAGE_BIT
	case GL_CLIENT_STORAGE_BIT: return StrLit("CLIENT_STORAGE_BIT");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

