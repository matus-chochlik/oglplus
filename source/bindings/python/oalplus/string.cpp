/*
 *  .file oalplus/string.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/string.hpp>

#include <boost/python.hpp>

struct oalplus_String_to_python_str
{
	static PyObject* convert(oalplus::String const& s)
	{
		return boost::python::incref(
			boost::python::object(s.c_str()).ptr()
		);
	}
};

struct oalplus_String_from_python_str
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
			(bpy::converter::rvalue_from_python_storage<oalplus::String>*)
			data
		)->storage.bytes;
		new (storage) oalplus::String(value);
		data->convertible = storage;
	}
};

struct oalplus_StrLit_to_python_str
{
	static PyObject* convert(oalplus::StrLit const& s)
	{
		return boost::python::incref(
			boost::python::object(s.c_str()).ptr()
		);
	}
};

void oalplus_py_String(void)
{
	namespace bpy = ::boost::python;

	// String
	bpy::to_python_converter<
		oalplus::String,
		oalplus_String_to_python_str
	>();

	bpy::converter::registry::push_back(
		&oalplus_String_from_python_str::convertible,
		&oalplus_String_from_python_str::construct,
		bpy::type_id<oalplus::String>()
	);

	// StrLit
	bpy::to_python_converter<
		oalplus::StrLit,
		oalplus_StrLit_to_python_str
	>();
}

