/*
 *  .file oglplus/enums/buffer_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/buffer.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_buffer_target(void)
{
	boost::python::enum_<oglplus::BufferTarget>("BufferTarget")
#if defined GL_ARRAY_BUFFER
# if defined Array
#  pragma push_macro("Array")
#  undef Array
	.value("Array", oglplus::BufferTarget::Array)
#  pragma pop_macro("Array")
# else
	.value("Array", oglplus::BufferTarget::Array)
# endif
#endif
#if defined GL_ATOMIC_COUNTER_BUFFER
# if defined AtomicCounter
#  pragma push_macro("AtomicCounter")
#  undef AtomicCounter
	.value("AtomicCounter", oglplus::BufferTarget::AtomicCounter)
#  pragma pop_macro("AtomicCounter")
# else
	.value("AtomicCounter", oglplus::BufferTarget::AtomicCounter)
# endif
#endif
#if defined GL_COPY_READ_BUFFER
# if defined CopyRead
#  pragma push_macro("CopyRead")
#  undef CopyRead
	.value("CopyRead", oglplus::BufferTarget::CopyRead)
#  pragma pop_macro("CopyRead")
# else
	.value("CopyRead", oglplus::BufferTarget::CopyRead)
# endif
#endif
#if defined GL_COPY_WRITE_BUFFER
# if defined CopyWrite
#  pragma push_macro("CopyWrite")
#  undef CopyWrite
	.value("CopyWrite", oglplus::BufferTarget::CopyWrite)
#  pragma pop_macro("CopyWrite")
# else
	.value("CopyWrite", oglplus::BufferTarget::CopyWrite)
# endif
#endif
#if defined GL_DISPATCH_INDIRECT_BUFFER
# if defined DispatchIndirect
#  pragma push_macro("DispatchIndirect")
#  undef DispatchIndirect
	.value("DispatchIndirect", oglplus::BufferTarget::DispatchIndirect)
#  pragma pop_macro("DispatchIndirect")
# else
	.value("DispatchIndirect", oglplus::BufferTarget::DispatchIndirect)
# endif
#endif
#if defined GL_DRAW_INDIRECT_BUFFER
# if defined DrawIndirect
#  pragma push_macro("DrawIndirect")
#  undef DrawIndirect
	.value("DrawIndirect", oglplus::BufferTarget::DrawIndirect)
#  pragma pop_macro("DrawIndirect")
# else
	.value("DrawIndirect", oglplus::BufferTarget::DrawIndirect)
# endif
#endif
#if defined GL_ELEMENT_ARRAY_BUFFER
# if defined ElementArray
#  pragma push_macro("ElementArray")
#  undef ElementArray
	.value("ElementArray", oglplus::BufferTarget::ElementArray)
#  pragma pop_macro("ElementArray")
# else
	.value("ElementArray", oglplus::BufferTarget::ElementArray)
# endif
#endif
#if defined GL_PIXEL_PACK_BUFFER
# if defined PixelPack
#  pragma push_macro("PixelPack")
#  undef PixelPack
	.value("PixelPack", oglplus::BufferTarget::PixelPack)
#  pragma pop_macro("PixelPack")
# else
	.value("PixelPack", oglplus::BufferTarget::PixelPack)
# endif
#endif
#if defined GL_PIXEL_UNPACK_BUFFER
# if defined PixelUnpack
#  pragma push_macro("PixelUnpack")
#  undef PixelUnpack
	.value("PixelUnpack", oglplus::BufferTarget::PixelUnpack)
#  pragma pop_macro("PixelUnpack")
# else
	.value("PixelUnpack", oglplus::BufferTarget::PixelUnpack)
# endif
#endif
#if defined GL_SHADER_STORAGE_BUFFER
# if defined ShaderStorage
#  pragma push_macro("ShaderStorage")
#  undef ShaderStorage
	.value("ShaderStorage", oglplus::BufferTarget::ShaderStorage)
#  pragma pop_macro("ShaderStorage")
# else
	.value("ShaderStorage", oglplus::BufferTarget::ShaderStorage)
# endif
#endif
#if defined GL_TEXTURE_BUFFER
# if defined Texture
#  pragma push_macro("Texture")
#  undef Texture
	.value("Texture", oglplus::BufferTarget::Texture)
#  pragma pop_macro("Texture")
# else
	.value("Texture", oglplus::BufferTarget::Texture)
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER
# if defined TransformFeedback
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
	.value("TransformFeedback", oglplus::BufferTarget::TransformFeedback)
#  pragma pop_macro("TransformFeedback")
# else
	.value("TransformFeedback", oglplus::BufferTarget::TransformFeedback)
# endif
#endif
#if defined GL_UNIFORM_BUFFER
# if defined Uniform
#  pragma push_macro("Uniform")
#  undef Uniform
	.value("Uniform", oglplus::BufferTarget::Uniform)
#  pragma pop_macro("Uniform")
# else
	.value("Uniform", oglplus::BufferTarget::Uniform)
# endif
#endif
#if defined GL_QUERY_BUFFER_AMD
# if defined Query
#  pragma push_macro("Query")
#  undef Query
	.value("Query", oglplus::BufferTarget::Query)
#  pragma pop_macro("Query")
# else
	.value("Query", oglplus::BufferTarget::Query)
# endif
#endif
#if defined GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD
# if defined ExternalVirtualMemory
#  pragma push_macro("ExternalVirtualMemory")
#  undef ExternalVirtualMemory
	.value("ExternalVirtualMemory", oglplus::BufferTarget::ExternalVirtualMemory)
#  pragma pop_macro("ExternalVirtualMemory")
# else
	.value("ExternalVirtualMemory", oglplus::BufferTarget::ExternalVirtualMemory)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BufferTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::BufferTarget
		>
	>("aux_CastIterRange_BufferTarget");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::BufferTarget
	> (*PEnumValueRange)(oglplus::BufferTarget) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
