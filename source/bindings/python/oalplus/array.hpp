/*
 *  .file oalplus/array.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_OALPLUS_ARRAY_0306061605_HPP
#define OGLPLUS_PYTHON_OALPLUS_ARRAY_0306061605_HPP

#include <boost/python.hpp>

#include <string>

#include "./range.hpp"

template <typename ObjectOps>
inline void oalplus_py_do_export_Array(
	oalplus::Array<oalplus::Object<ObjectOps> >*,
	const char* name
)
{
	namespace bpy = boost::python;
	using namespace oalplus;

	oalplus_py_export_range<aux::ArrayRange<Managed<ObjectOps> > >(
		(std::string(name)+"Range").c_str()
	);

	typedef Array<Object<ObjectOps> > Array;

	bpy::class_<Array, boost::noncopyable>(name, bpy::init<ALsizei>())
		.def("all", &Array::all)
	;
}

template <typename Array>
inline void oalplus_py_export_Array(const char* name)
{
	oalplus_py_do_export_Array((Array*)nullptr, name);
}

#endif
