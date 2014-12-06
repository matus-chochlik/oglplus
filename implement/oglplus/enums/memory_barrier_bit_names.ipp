//  File implement/oglplus/enums/memory_barrier_bit_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/memory_barrier_bit.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	MemoryBarrierBit*,
	GLbitfield value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_MEMORYBARRIERBIT)
#define OGLPLUS_IMPL_EVN_MEMORYBARRIERBIT
{
switch(value)
{
#if defined GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
	case GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT: return CStrRef("VERTEX_ATTRIB_ARRAY_BARRIER_BIT");
#endif
#if defined GL_ELEMENT_ARRAY_BARRIER_BIT
	case GL_ELEMENT_ARRAY_BARRIER_BIT: return CStrRef("ELEMENT_ARRAY_BARRIER_BIT");
#endif
#if defined GL_UNIFORM_BARRIER_BIT
	case GL_UNIFORM_BARRIER_BIT: return CStrRef("UNIFORM_BARRIER_BIT");
#endif
#if defined GL_TEXTURE_FETCH_BARRIER_BIT
	case GL_TEXTURE_FETCH_BARRIER_BIT: return CStrRef("TEXTURE_FETCH_BARRIER_BIT");
#endif
#if defined GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
	case GL_SHADER_IMAGE_ACCESS_BARRIER_BIT: return CStrRef("SHADER_IMAGE_ACCESS_BARRIER_BIT");
#endif
#if defined GL_COMMAND_BARRIER_BIT
	case GL_COMMAND_BARRIER_BIT: return CStrRef("COMMAND_BARRIER_BIT");
#endif
#if defined GL_PIXEL_BUFFER_BARRIER_BIT
	case GL_PIXEL_BUFFER_BARRIER_BIT: return CStrRef("PIXEL_BUFFER_BARRIER_BIT");
#endif
#if defined GL_TEXTURE_UPDATE_BARRIER_BIT
	case GL_TEXTURE_UPDATE_BARRIER_BIT: return CStrRef("TEXTURE_UPDATE_BARRIER_BIT");
#endif
#if defined GL_BUFFER_UPDATE_BARRIER_BIT
	case GL_BUFFER_UPDATE_BARRIER_BIT: return CStrRef("BUFFER_UPDATE_BARRIER_BIT");
#endif
#if defined GL_FRAMEBUFFER_BARRIER_BIT
	case GL_FRAMEBUFFER_BARRIER_BIT: return CStrRef("FRAMEBUFFER_BARRIER_BIT");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BARRIER_BIT
	case GL_TRANSFORM_FEEDBACK_BARRIER_BIT: return CStrRef("TRANSFORM_FEEDBACK_BARRIER_BIT");
#endif
#if defined GL_ATOMIC_COUNTER_BARRIER_BIT
	case GL_ATOMIC_COUNTER_BARRIER_BIT: return CStrRef("ATOMIC_COUNTER_BARRIER_BIT");
#endif
#if defined GL_SHADER_STORAGE_BARRIER_BIT
	case GL_SHADER_STORAGE_BARRIER_BIT: return CStrRef("SHADER_STORAGE_BARRIER_BIT");
#endif
#if defined GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT
	case GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT: return CStrRef("CLIENT_MAPPED_BUFFER_BARRIER_BIT");
#endif
#if defined GL_ALL_BARRIER_BITS
	case GL_ALL_BARRIER_BITS: return CStrRef("ALL_BARRIER_BITS");
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

