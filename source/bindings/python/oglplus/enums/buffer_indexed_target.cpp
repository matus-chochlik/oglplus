/*
 *  .file oglplus/enums/buffer_indexed_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_indexed_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/buffer.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_buffer_indexed_target(void)
{
	boost::python::enum_<oglplus::BufferIndexedTarget>("BufferIndexedTarget")
#if defined GL_ATOMIC_COUNTER_BUFFER
# if defined AtomicCounter
#  pragma push_macro("AtomicCounter")
#  undef AtomicCounter
	.value("AtomicCounter", oglplus::BufferIndexedTarget::AtomicCounter)
#  pragma pop_macro("AtomicCounter")
# else
	.value("AtomicCounter", oglplus::BufferIndexedTarget::AtomicCounter)
# endif
#endif
#if defined GL_SHADER_STORAGE_BUFFER
# if defined ShaderStorage
#  pragma push_macro("ShaderStorage")
#  undef ShaderStorage
	.value("ShaderStorage", oglplus::BufferIndexedTarget::ShaderStorage)
#  pragma pop_macro("ShaderStorage")
# else
	.value("ShaderStorage", oglplus::BufferIndexedTarget::ShaderStorage)
# endif
#endif
#if defined GL_TRANSFORM_FEEDBACK_BUFFER
# if defined TransformFeedback
#  pragma push_macro("TransformFeedback")
#  undef TransformFeedback
	.value("TransformFeedback", oglplus::BufferIndexedTarget::TransformFeedback)
#  pragma pop_macro("TransformFeedback")
# else
	.value("TransformFeedback", oglplus::BufferIndexedTarget::TransformFeedback)
# endif
#endif
#if defined GL_UNIFORM_BUFFER
# if defined Uniform
#  pragma push_macro("Uniform")
#  undef Uniform
	.value("Uniform", oglplus::BufferIndexedTarget::Uniform)
#  pragma pop_macro("Uniform")
# else
	.value("Uniform", oglplus::BufferIndexedTarget::Uniform)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BufferIndexedTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::BufferIndexedTarget
		>
	>("aux_CastIterRange_BufferIndexedTarget");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::BufferIndexedTarget
	> (*PEnumValueRange)(oglplus::BufferIndexedTarget) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
