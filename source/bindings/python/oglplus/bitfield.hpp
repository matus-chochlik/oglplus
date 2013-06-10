/*
 *  .file oglplus/bitfield.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_OGLPLUS_BITFIELD_0306061605_HPP
#define OGLPLUS_PYTHON_OGLPLUS_BITFIELD_0306061605_HPP

#include <oglplus/gl.hpp>
#include <oglplus/bitfield.hpp>

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include <type_traits>

template <typename Bitfield>
struct oglplus_Bitfield_from_python_list;

template <typename Bit>
struct oglplus_Bitfield_from_python_list<oglplus::Bitfield<Bit> >
{
	typedef oglplus::Bitfield<Bit> Bitfield;

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

		bpy::handle<> handle(bpy::borrowed(obj_ptr));

		typedef bpy::converter::rvalue_from_python_storage<Bitfield> storage_type;
		void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

		typedef bpy::stl_input_iterator<Bit> iterator;

		data->convertible = new (storage) Bitfield(
			iterator(bpy::object(handle)),
			iterator()
		);
	}

	static void do_export(void)
	{
		namespace bpy = ::boost::python;

		bpy::converter::registry::push_back(
			&oglplus_Bitfield_from_python_list::convertible,
			&oglplus_Bitfield_from_python_list::construct,
			bpy::type_id<Bitfield>()
		);
	}
};

template <typename Bit>
inline oglplus::Bitfield<Bit> oglplus_py_BF_bit(Bit bit)
{
	return oglplus::Bitfield<Bit>(bit);
}

template <typename Bit>
inline void oglplus_py_export_Bitfield(
	const char* name,
	oglplus::Bitfield<Bit>*
)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Bitfield<Bit> Bitfield;

	//oglplus_Bitfield_from_python_list<Bitfield>::do_export();

	bpy::class_<Bitfield>(name, bpy::init<>())
		.def(bpy::init<Bit>())
		.def(bpy::init<Bit, Bit>())
		.def(bpy::self | Bit())
		.def("Test", &Bitfield::Test)
		.def("__contains__", &Bitfield::Test)
	;

	bpy::def("Bits", &oglplus_py_BF_bit<Bit>);
}

template <typename Bitfield>
inline void oglplus_py_export_Bitfield(const char* name)
{
	oglplus_py_export_Bitfield(name, (Bitfield*)nullptr);
}

#endif
