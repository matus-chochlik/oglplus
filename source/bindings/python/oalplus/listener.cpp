/*
 *  .file oalplus/listener.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/listener.hpp>

#include <boost/python.hpp>

void oalplus_py_Listener(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	bpy::class_<Listener>("Listener", bpy::init<>())
		.def("Position", (void(*)(const Vec3f&))&Listener::Position)
		.def("Position", (void(*)(ALfloat,ALfloat,ALfloat))&Listener::Position)
		.def("Position", (Vec3f (*)(void))&Listener::Position)
		.staticmethod("Position")
		.def("Velocity", (void(*)(const Vec3f&))&Listener::Velocity)
		.def("Velocity", (void(*)(ALfloat,ALfloat,ALfloat))&Listener::Velocity)
		.def("Velocity", (Vec3f(*)(void))&Listener::Velocity)
		.staticmethod("Velocity")
		.def("Orientation", (void(*)(const Vec3f&, const Vec3f&))&Listener::Orientation)
		.def("Orientation", (void(*)(ALfloat,ALfloat,ALfloat,ALfloat,ALfloat,ALfloat))&Listener::Orientation)
		.staticmethod("Orientation")
		.def("OrientationAt", (Vec3f(*)(void))&Listener::OrientationAt)
		.staticmethod("OrientationAt")
		.def("OrientationUp", (Vec3f(*)(void))&Listener::OrientationUp)
		.staticmethod("OrientationUp")
		.def("Gain", (void(*)(ALfloat))&Listener::Gain)
		.def("Gain", (ALfloat(*)(void))&Listener::Gain)
	;
}

