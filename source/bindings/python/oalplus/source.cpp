/*
 *  .file oalplus/source.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/source.hpp>

#include <boost/python.hpp>

#include "./array.hpp"

void oalplus_py_Source(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	oalplus_py_export_Array<Array<Buffer> >("BufferArray");

	bpy::class_<SourceOps>("SourceOps", bpy::no_init)
		.def("Play", &SourceOps::Play)
		.def("Pause", &SourceOps::Pause)
		.def("Stop", &SourceOps::Stop)
		.def("Rewind", &SourceOps::Rewind)
		.def("State", &SourceOps::State)
		.def("Relative", (void (SourceOps::*)(bool))&SourceOps::Relative)
		.def("Relative", (bool (SourceOps::*)(void) const)&SourceOps::Relative)
		.def("Type", (void (SourceOps::*)(SourceType))&SourceOps::Type)
		.def("Type", (SourceType (SourceOps::*)(void) const)&SourceOps::Type)
		.def("Looping", (void (SourceOps::*)(bool))&SourceOps::Looping)
		.def("Looping", (bool (SourceOps::*)(void) const)&SourceOps::Looping)
		.def("Buffer", &SourceOps::Buffer)
		.def("DetachBuffers", &SourceOps::DetachBuffers)
		.def("QueueBuffers", &SourceOps::QueueBuffers)
		.def("UnqueueBuffers", &SourceOps::UnqueueBuffers)
		.def("Gain", (void (SourceOps::*)(ALfloat))&SourceOps::Gain)
		.def("Gain", (ALfloat (SourceOps::*)(void) const)&SourceOps::Gain)
		.def("MinGain", (void (SourceOps::*)(ALfloat))&SourceOps::MinGain)
		.def("MinGain", (ALfloat (SourceOps::*)(void) const)&SourceOps::MinGain)
		.def("MaxGain", (void (SourceOps::*)(ALfloat))&SourceOps::MaxGain)
		.def("MaxGain", (ALfloat (SourceOps::*)(void) const)&SourceOps::MaxGain)
		.def("ReferenceDistance", (void (SourceOps::*)(ALfloat))&SourceOps::ReferenceDistance)
		.def("ReferenceDistance", (ALfloat (SourceOps::*)(void) const)&SourceOps::ReferenceDistance)
		.def("RolloffFactor", (void (SourceOps::*)(ALfloat))&SourceOps::RolloffFactor)
		.def("RolloffFactor", (ALfloat (SourceOps::*)(void) const)&SourceOps::RolloffFactor)
		.def("MaxDistance", (void (SourceOps::*)(ALfloat))&SourceOps::MaxDistance)
		.def("MaxDistance", (ALfloat (SourceOps::*)(void) const)&SourceOps::MaxDistance)
		.def("Pitch", (void (SourceOps::*)(ALfloat))&SourceOps::Pitch)
		.def("Pitch", (ALfloat (SourceOps::*)(void) const)&SourceOps::Pitch)
	;

	bpy::class_<
		Source,
		bpy::bases<SourceOps>,
		boost::noncopyable
	>("Source", bpy::init<>())
	;
}

