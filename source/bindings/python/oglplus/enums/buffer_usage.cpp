/*
 *  .file oglplus/enums/buffer_usage.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_usage.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/buffer.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_buffer_usage(void)
{
	boost::python::enum_<oglplus::BufferUsage>("BufferUsage")
#if defined GL_STREAM_DRAW
# if defined StreamDraw
#  pragma push_macro("StreamDraw")
#  undef StreamDraw
	.value("StreamDraw", oglplus::BufferUsage::StreamDraw)
#  pragma pop_macro("StreamDraw")
# else
	.value("StreamDraw", oglplus::BufferUsage::StreamDraw)
# endif
#endif
#if defined GL_STREAM_READ
# if defined StreamRead
#  pragma push_macro("StreamRead")
#  undef StreamRead
	.value("StreamRead", oglplus::BufferUsage::StreamRead)
#  pragma pop_macro("StreamRead")
# else
	.value("StreamRead", oglplus::BufferUsage::StreamRead)
# endif
#endif
#if defined GL_STREAM_COPY
# if defined StreamCopy
#  pragma push_macro("StreamCopy")
#  undef StreamCopy
	.value("StreamCopy", oglplus::BufferUsage::StreamCopy)
#  pragma pop_macro("StreamCopy")
# else
	.value("StreamCopy", oglplus::BufferUsage::StreamCopy)
# endif
#endif
#if defined GL_STATIC_DRAW
# if defined StaticDraw
#  pragma push_macro("StaticDraw")
#  undef StaticDraw
	.value("StaticDraw", oglplus::BufferUsage::StaticDraw)
#  pragma pop_macro("StaticDraw")
# else
	.value("StaticDraw", oglplus::BufferUsage::StaticDraw)
# endif
#endif
#if defined GL_STATIC_READ
# if defined StaticRead
#  pragma push_macro("StaticRead")
#  undef StaticRead
	.value("StaticRead", oglplus::BufferUsage::StaticRead)
#  pragma pop_macro("StaticRead")
# else
	.value("StaticRead", oglplus::BufferUsage::StaticRead)
# endif
#endif
#if defined GL_STATIC_COPY
# if defined StaticCopy
#  pragma push_macro("StaticCopy")
#  undef StaticCopy
	.value("StaticCopy", oglplus::BufferUsage::StaticCopy)
#  pragma pop_macro("StaticCopy")
# else
	.value("StaticCopy", oglplus::BufferUsage::StaticCopy)
# endif
#endif
#if defined GL_DYNAMIC_DRAW
# if defined DynamicDraw
#  pragma push_macro("DynamicDraw")
#  undef DynamicDraw
	.value("DynamicDraw", oglplus::BufferUsage::DynamicDraw)
#  pragma pop_macro("DynamicDraw")
# else
	.value("DynamicDraw", oglplus::BufferUsage::DynamicDraw)
# endif
#endif
#if defined GL_DYNAMIC_READ
# if defined DynamicRead
#  pragma push_macro("DynamicRead")
#  undef DynamicRead
	.value("DynamicRead", oglplus::BufferUsage::DynamicRead)
#  pragma pop_macro("DynamicRead")
# else
	.value("DynamicRead", oglplus::BufferUsage::DynamicRead)
# endif
#endif
#if defined GL_DYNAMIC_COPY
# if defined DynamicCopy
#  pragma push_macro("DynamicCopy")
#  undef DynamicCopy
	.value("DynamicCopy", oglplus::BufferUsage::DynamicCopy)
#  pragma pop_macro("DynamicCopy")
# else
	.value("DynamicCopy", oglplus::BufferUsage::DynamicCopy)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BufferUsage) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::BufferUsage
		>
	>("aux_CastIterRange_BufferUsage");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::BufferUsage
	> (*PEnumValueRange)(oglplus::BufferUsage) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
