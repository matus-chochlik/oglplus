/*
 *  .file oglplus/string.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/string.hpp>

#include <boost/python.hpp>

struct oglplus_String_to_python_str
{
	static PyObject* convert(oglplus::String const& s)
	{
		return boost::python::incref(
			boost::python::object(s.c_str()).ptr()
		);
	}
};

struct oglplus_String_from_python_str
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
			(bpy::converter::rvalue_from_python_storage<oglplus::String>*)
			data
		)->storage.bytes;
		new (storage) oglplus::String(value);
		data->convertible = storage;
	}
};

struct oglplus_StrLit_to_python_str
{
	static PyObject* convert(oglplus::StrLit const& s)
	{
		return boost::python::incref(
			boost::python::object(s.c_str()).ptr()
		);
	}
};

void oglplus_py_String(void)
{
	namespace bpy = ::boost::python;

	// String
	bpy::to_python_converter<
		oglplus::String,
		oglplus_String_to_python_str
	>();

	bpy::converter::registry::push_back(
		&oglplus_String_from_python_str::convertible,
		&oglplus_String_from_python_str::construct,
		bpy::type_id<oglplus::String>()
	);

	// StrLit
	bpy::to_python_converter<
		oglplus::StrLit,
		oglplus_StrLit_to_python_str
	>();
}

