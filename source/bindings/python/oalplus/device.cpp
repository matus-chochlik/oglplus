/*
 *  .file oalplus/device.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/device.hpp>

#include <boost/python.hpp>

#include "range.hpp"

void oalplus_py_Device(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	oalplus_py_export_range<DeviceSpecRange>("DeviceSpecRange");

	bpy::class_<DeviceOps>("DeviceOps", bpy::no_init)
		.def("Specifiers", &DeviceOps::Specifiers)
		.staticmethod("Specifiers")
		.def("CaptureSpecifiers", &DeviceOps::CaptureSpecifiers)
		.staticmethod("CaptureSpecifiers")
	;

	bpy::class_<
		Device,
		bpy::bases<DeviceOps>, boost::noncopyable
	>("Device", bpy::init<>())
		.def(bpy::init<const char*>())
	;
}

