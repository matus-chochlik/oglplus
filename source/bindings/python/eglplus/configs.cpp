/*
 *  .file eglplus/configs.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/configs.hpp>

#include <boost/python.hpp>

#include "attrib_list.hpp"

void eglplus_py_Configs(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	eglplus_py_export_AttributeList<eglplus::ConfigAttribs>("ConfigAttribs");

	bpy::class_<eglplus::Config>("Config", bpy::no_init)
	;
}

