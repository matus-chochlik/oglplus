/*
 *  .file oalplus/buffer.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/buffer.hpp>

#include <boost/python.hpp>

void oalplus_py_Buffer(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	bpy::class_<BufferOps>("BufferOps", bpy::no_init)
		.def("Data", &BufferOps::Data)
		.def("Frequency", &BufferOps::Frequency)
		.def("Size", &BufferOps::Size)
		.def("Bits", &BufferOps::Bits)
		.def("Channels", &BufferOps::Channels)
		.def("Duration", &BufferOps::Duration)
	;

	bpy::class_<
		Buffer,
		bpy::bases<BufferOps>,
		boost::noncopyable
	>("Buffer", bpy::init<>())
	;
}

