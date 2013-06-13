/*
 *  .file oalplus/context.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/context.hpp>

#include <boost/python.hpp>

void oalplus_py_Context(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	bpy::class_<ContextOps>("ContextOps", bpy::no_init)
		.def("Current", &ContextOps::Current).staticmethod("Current")
		.def("GetString", &ContextOps::GetString)
		.def("Vendor", &ContextOps::Vendor)
		.def("Version", &ContextOps::Version)
		.def("Renderer", &ContextOps::Renderer)
		.def("Extensions", &ContextOps::Extensions)
		.def("ContextsDevice", &ContextOps::ContextsDevice)
		.def("MakeCurrent", &ContextOps::MakeCurrent)
		.def("Process", &ContextOps::Process)
		.def("Suspend", &ContextOps::Suspend)
		.def("DistanceModel", (DistanceModel (*)(void))&ContextOps::DistanceModel)
		.def("DistanceModel", (void (*)(DistanceModel))&ContextOps::DistanceModel)
		.def("DopplerFactor", (ALfloat (*)(void))&ContextOps::DopplerFactor)
		.def("DopplerFactor", (void (*)(ALfloat))&ContextOps::DopplerFactor)
		.def("SpeedOfSound", (ALfloat (*)(void))&ContextOps::SpeedOfSound)
		.def("SpeedOfSound", (void (*)(ALfloat))&ContextOps::SpeedOfSound)
	;

	bpy::class_<
		Context,
		bpy::bases<ContextOps>,
		boost::noncopyable
	>("Context", bpy::init<const DeviceOps&>())
	;

	bpy::class_<
		CurrentContext,
		bpy::bases<Context>,
		boost::noncopyable
	>("CurrentContext", bpy::init<const DeviceOps&>())
	;
}

