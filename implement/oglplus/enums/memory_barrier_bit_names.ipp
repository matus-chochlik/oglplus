/*
 *  .file oglplus/enums/memory_barrier_bit_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/memory_barrier_bit.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	MemoryBarrierBit*,
	GLbitfield value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_MEMORYBARRIERBIT)
#define OGLPLUS_IMPL_EVN_MEMORYBARRIERBIT
{
switch(value)
{
#if defined GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
	case GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT: return StrLit("VERTEX_ATTRIB_ARRAY_BARRIER_BIT");
#endif
#if defined GL_ELEMENT_ARRAY_BARRIER_BIT
	case GL_ELEMENT_ARRAY_BARRIER_BIT: return StrLit("ELEMENT_ARRAY_BARRIER_BIT");
#endif
#if defined GL_UNIFORM_BARRIER_BIT
	case GL_UNIFORM_BARRIER_BIT: return StrLit("UNIFORM_BARRIER_BIT");
#endif
#if defined GL_TEXTURE_FETCH_BARRIER_BIT
	case GL_TEXTURE_FETCH_BARRIER_BIT: return StrLit("TEXTURE_FETCH_BARRIER_BIT");
#endif
#if defined GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
	case GL_SHADER_IMAGE_ACCESS_BARRIER_BIT: return StrLit("SHADER_IMAGE_ACCESS_BARRIER_BIT");
#endif
#if defined GL_COMMAND_BARRIER_BIT
	case GL_COMMAND_BARRIER_BIT: return StrLit("COMMAND_BARRIER_BIT");
#endif
#if defined GL_PIXEL_BUFFER_BARRIER_BIT
	case GL_PIXEL_BUFFER_BARRIER_BIT: return StrLit("PIXEL_BUFFER_BARRIER_BIT");
#endif
#if defined GL_TEXTURE_UPDATE_BARRIER_BIT
	case GL_TEXTURE_UPDATE_BARRIER_BIT: return StrLit("TEXTURE_UPDATE_BARRIER_BIT");
#endif
#if defined GL_BUFFER_UPDATE_BARRIER_BIT
	case GL_BUFFER_UPDATE_BARRIER_BIT: return StrLit("BUFFER_UPDATE_BARRIER_BIT");
#endif
#if defined GL_FRAMEBUFFER_BARRIER_BIT
	case GL_FRAMEBUFFER_BARRIER_BIT: return StrLit("FRAMEBUFFER_BARRIER_BIT");
#endif
#if defined GL_TRANSFORM_FEEDBACK_BARRIER_BIT
	case GL_TRANSFORM_FEEDBACK_BARRIER_BIT: return StrLit("TRANSFORM_FEEDBACK_BARRIER_BIT");
#endif
#if defined GL_ATOMIC_COUNTER_BARRIER_BIT
	case GL_ATOMIC_COUNTER_BARRIER_BIT: return StrLit("ATOMIC_COUNTER_BARRIER_BIT");
#endif
#if defined GL_SHADER_STORAGE_BARRIER_BIT
	case GL_SHADER_STORAGE_BARRIER_BIT: return StrLit("SHADER_STORAGE_BARRIER_BIT");
#endif
#if defined GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT
	case GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT: return StrLit("CLIENT_MAPPED_BUFFER_BARRIER_BIT");
#endif
#if defined GL_ALL_BARRIER_BITS
	case GL_ALL_BARRIER_BITS: return StrLit("ALL_BARRIER_BITS");
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

