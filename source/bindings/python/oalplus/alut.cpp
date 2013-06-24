/*
 *  .file oalplus/alut.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/alut.hpp>

#include <boost/python.hpp>

void oalplus_py_ALUT(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	bpy::class_<ALUtilityToolkit, boost::noncopyable>("ALUtilityToolkit", bpy::init<bool>())
		.def("CreateBufferHelloWorld", &ALUtilityToolkit::CreateBufferHelloWorld)
		.def("CreateBufferFromFile", &ALUtilityToolkit::CreateBufferFromFile)
	;
}

