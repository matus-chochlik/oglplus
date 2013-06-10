/*
 *  .file eglplus/context.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/context.hpp>

#include <boost/python.hpp>

#include "range.hpp"
#include "attrib_list.hpp"

void eglplus_py_Context(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	eglplus_py_export_AttributeList<eglplus::ContextAttribs>("ContextAttribs");

	bpy::class_<Context, boost::noncopyable>("Context", bpy::no_init)
		.def(bpy::init<const eglplus::Display&, const Config&>())
		.def(bpy::init<const eglplus::Display&, const Config&, const Context&>())
		.def(bpy::init<const eglplus::Display&, const Config&, const FinishedContextAttribs&>())
		.def(bpy::init<const eglplus::Display&, const Config&, const Context&, const FinishedContextAttribs&>())
		.def("MakeCurrent",  (bool (Context::*)(const Surface&))&Context::MakeCurrent)
		.def("MakeCurrent",  (bool (Context::*)(const Surface&, const Surface&))&Context::MakeCurrent)
		.def("WaitClient", &Context::WaitClient)
		.def("WaitGL", &Context::WaitGL)
		.def("WaitNative", &Context::WaitNative)
	;
}

