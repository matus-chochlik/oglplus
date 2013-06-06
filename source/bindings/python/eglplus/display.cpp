/*
 *  .file eglplus/display.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/all.hpp>

#include <boost/python.hpp>

void eglplus_py_Display(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	bpy::class_<eglplus::Display>("Display")
		.def(bpy::init<>())
	;
}

