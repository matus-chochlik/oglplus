/*
 *  .file eglplus/string.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/string.hpp>

#include <boost/python.hpp>

struct eglplus_String_to_python_str
{
	static PyObject* convert(eglplus::String const& s)
	{
		return boost::python::incref(
			boost::python::object(s.c_str()).ptr()
		);
	}
};

struct eglplus_String_from_python_str
{
	static void* convertible(PyObject* obj_ptr)
	{
		if (!PyString_Check(obj_ptr)) return 0;
		return obj_ptr;
	}

	static void construct(
		PyObject* obj_ptr,
		boost::python::converter::rvalue_from_python_stage1_data* data
	)
	{
		namespace bpy = ::boost::python;

		const char* value = PyString_AsString(obj_ptr);
		if (value == 0) bpy::throw_error_already_set();
		void* storage = (
			(bpy::converter::rvalue_from_python_storage<eglplus::String>*)
			data
		)->storage.bytes;
		new (storage) eglplus::String(value);
		data->convertible = storage;
	}
};

struct eglplus_StrLit_to_python_str
{
	static PyObject* convert(eglplus::StrLit const& s)
	{
		return boost::python::incref(
			boost::python::object(s.c_str()).ptr()
		);
	}
};

void eglplus_py_String(void)
{
	namespace bpy = ::boost::python;

	// String
	bpy::to_python_converter<
		eglplus::String,
		eglplus_String_to_python_str
	>();

	bpy::converter::registry::push_back(
		&eglplus_String_from_python_str::convertible,
		&eglplus_String_from_python_str::construct,
		bpy::type_id<eglplus::String>()
	);

	// StrLit
	bpy::to_python_converter<
		eglplus::StrLit,
		eglplus_StrLit_to_python_str
	>();
}

