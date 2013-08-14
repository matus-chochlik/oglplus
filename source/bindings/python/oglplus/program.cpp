/*
 *  .file oglplus/program.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/program.hpp>

#include <boost/python.hpp>


void oglplus_py_Program(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	bpy::return_internal_reference<1> bpy_rvp;

	bpy::class_<ProgramOps>("ProgramOps", bpy::no_init)
		.def("AttachShader", &ProgramOps::AttachShader, bpy_rvp)
		.def("DetachShader", &ProgramOps::DetachShader, bpy_rvp)
		.def("IsLinked", &ProgramOps::IsLinked)
		.def("GetInfoLog", &ProgramOps::GetInfoLog)
		.def("Link", &ProgramOps::Link, bpy_rvp)
		.def("IsValid", &ProgramOps::IsValid)
		.def("Validate", &ProgramOps::Validate, bpy_rvp)
		.def("Use", &ProgramOps::Use, bpy_rvp)
		.def("UseNone", &ProgramOps::UseNone).staticmethod("UseNone")
	;

	bpy::class_<
		Program,
		bpy::bases<ProgramOps>,
		boost::noncopyable
	>("Program", bpy::init<>())
	;
}

