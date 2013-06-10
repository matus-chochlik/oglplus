/*
 *  .file oglplus/enums/memory_barrier_bit.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/memory_barrier_bit.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/memory_barrier.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_memory_barrier_bit(void)
{
	boost::python::enum_<oglplus::MemoryBarrierBit>("MemoryBarrierBit")
#if defined GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
# if defined VertexAttribArray
#  pragma push_macro("VertexAttribArray")
#  undef VertexAttribArray
	.value("VertexAttribArray", oglplus::MemoryBarrierBit::VertexAttribArray)
#  pragma pop_macro("VertexAttribArray")
# else
	.value("VertexAttribArray", oglplus::MemoryBarrierBit::VertexAttribArray)
# endif
#endif
#if defined GL_ELEMENT_ARRAY_BARRIER_BIT
# if defined ElementArray
#  pragma push_macro("ElementArray")
#  undef ElementArray
	.value("ElementArray", oglplus::MemoryBarrierBit::ElementArray)
#  pragma pop_macro("ElementArray")
# else
	.value("ElementArray", oglplus::MemoryBarrierBit::ElementArray)
# endif
#endif
#if defined GL_UNIFORM_BARRIER_BIT
# if defined Uniform
#  pragma push_macro("Uniform")
#  undef Uniform
	.value("Uniform", oglplus::MemoryBarrierBit::Uniform)
#  pragma pop_macro("Uniform")
# else
	.value("Uniform", oglplus::MemoryBarrierBit::Uniform)
# endif
#endif
#if defined GL_TEXTURE_FETCH_BARRIER_BIT
# if defined TextureFetch
#  pragma push_macro("TextureFetch")
#  undef TextureFetch
	.value("TextureFetch", oglplus::MemoryBarrierBit::TextureFetch)
#  pragma pop_macro("TextureFetch")
# else
	.value("TextureFetch", oglplus::MemoryBarrierBit::TextureFetch)
# endif
#endif
#if defined GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
# if defined ShaderImageAccess
#  pragma push_macro("ShaderImageAccess")
#  undef ShaderImageAccess
	.value("ShaderImageAccess", oglplus::MemoryBarrierBit::ShaderImageAccess)
#  pragma pop_macro("ShaderImageAccess")
# else
	.value("ShaderImageAccess", oglplus::MemoryBarrierBit::ShaderImageAccess)
# endif
#endif
#if defined GL_COMMAND_BARRIER_BIT
# if defined Command
#  pragma push_macro("Command")
#  undef Command
	.value("Command", oglplus::MemoryBarrierBit::Command)
#  pragma pop_macro("Command")
# else
	.value("Command", oglplus::MemoryBarrierBit::Command)
# endif
#endif
#if defined GL_PIXEL_BUFFER_BARRIER_BIT
# if defined PixelBuffer
#  pragma push_macro("PixelBuffer")
#  undef PixelBuffer
	.value("PixelBuffer", oglplus::MemoryBarrierBit::PixelBuffer)
#  pragma pop_macro("PixelBuffer")
# else
	.value("PixelBuffer", oglplus::MemoryBarrierBit::PixelBuffer)
# endif
#endif
#if defined GL_TEXTURE_UPDATE_BARRIER_BIT
# if defined TextureUpdate
#  pragma push_macro("TextureUpdate")
#  undef TextureUpdate
	.value("TextureUpdate", oglplus::MemoryBarrierBit::TextureUpdate)
#  pragma pop_macro("TextureUpdate")
# else
	.value("TextureUpdate", oglplus::MemoryBarrierBit::TextureUpdate)
# endif
#endif
#if defined GL_BUFFER_UPDATE_BARRIER_BIT
# if defined BufferUpdate
#  pragma push_macro("BufferUpdate")
#  undef BufferUpdate
	.value("BufferUpdate", oglplus::MemoryBarrierBit::BufferUpdate)
#  pragma pop_macro("BufferUpdate")
# else
	.value("BufferUpdate", oglplus::MemoryBarrierBit::BufferUpdate)
# endif
#endif
#if defined GL_FRAMEBUFFER_BARRIER_BIT
# if defined Framebuffer
#  pragma push_macro("Framebuffer")
#  undef Framebuffer
	.value("Framebuffer", oglplus::MemoryBarrierBit::Framebuffer)
#  pragma pop_macro("Framebuffer")
# else
	.value("Framebuffer", oglplus::MemoryBarrierBit::Framebuffer)
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BARRIER_BIT
# if defined TransformFeedback
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
	.value("TransformFeedback", oglplus::MemoryBarrierBit::TransformFeedback)
#  pragma pop_macro("TransformFeedback")
# else
	.value("TransformFeedback", oglplus::MemoryBarrierBit::TransformFeedback)
# endif
#endif
#if defined GL_ATOMIC_COUNTER_BARRIER_BIT
# if defined AtomicCounter
#  pragma push_macro("AtomicCounter")
#  undef AtomicCounter
	.value("AtomicCounter", oglplus::MemoryBarrierBit::AtomicCounter)
#  pragma pop_macro("AtomicCounter")
# else
	.value("AtomicCounter", oglplus::MemoryBarrierBit::AtomicCounter)
# endif
#endif
#if defined GL_SHADER_STORAGE_BARRIER_BIT
# if defined ShaderStorage
#  pragma push_macro("ShaderStorage")
#  undef ShaderStorage
	.value("ShaderStorage", oglplus::MemoryBarrierBit::ShaderStorage)
#  pragma pop_macro("ShaderStorage")
# else
	.value("ShaderStorage", oglplus::MemoryBarrierBit::ShaderStorage)
# endif
#endif
#if defined GL_ALL_BARRIER_BITS
# if defined All
#  pragma push_macro("All")
#  undef All
	.value("All", oglplus::MemoryBarrierBit::All)
#  pragma pop_macro("All")
# else
	.value("All", oglplus::MemoryBarrierBit::All)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::MemoryBarrierBit) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLbitfield*,
			oglplus::MemoryBarrierBit
		>
	>("aux_CastIterRange_MemoryBarrierBit");

	oglplus::aux::CastIterRange<
		const GLbitfield*,
		oglplus::MemoryBarrierBit
	> (*PEnumValueRange)(oglplus::MemoryBarrierBit) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
