/*
 *  .file eglplus/bitfield.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_EGLPLUS_BITFIELD_0306061605_HPP
#define OGLPLUS_PYTHON_EGLPLUS_BITFIELD_0306061605_HPP

#include <eglplus/egl.hpp>
#include <eglplus/bitfield.hpp>

#include <boost/python.hpp>

#include <type_traits>

template <typename Bit, typename BF>
inline void eglplus_py_export_Bitfield(
	const char* name,
	eglplus::Bitfield<Bit, BF>*
)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	typedef eglplus::Bitfield<Bit, BF> Bitfield;

	bpy::class_<Bitfield>(name, bpy::no_init)
		.def(bpy::init<Bit>())
		.def(bpy::init<Bit, Bit>())
		.def(bpy::self | Bit())
		.def("Test", &Bitfield::Test)
		.def("__contains__", &Bitfield::Test)
	;

}

template <typename Bitfield>
inline void eglplus_py_export_Bitfield(const char* name)
{
	eglplus_py_export_Bitfield(name, (Bitfield*)nullptr);
}

#endif
