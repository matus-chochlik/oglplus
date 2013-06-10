/*
 *  .file oglplus/range.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_OGLPLUS_RANGE_0306061605_HPP
#define OGLPLUS_PYTHON_OGLPLUS_RANGE_0306061605_HPP

#include <boost/python.hpp>

template <typename Range>
struct oglplus_aux_py_range_wrapper
{
	static Range copy(const Range& range)
	{
		return range;
	}

	static typename Range::ValueType next(Range& range)
	{
		if(range.Empty())
			boost::python::objects::stop_iteration_error();
		typename Range::ValueType result = range.Front();
		range.Next();
		return result;
	}
};

template <typename Range>
inline void oglplus_py_export_range(const char* name)
{
	boost::python::class_<Range>(name, boost::python::no_init)
		.def("__iter__", &oglplus_aux_py_range_wrapper<Range>::copy)
		.def("self", &oglplus_aux_py_range_wrapper<Range>::copy)
		.def("next", &oglplus_aux_py_range_wrapper<Range>::next)
	;
}

#endif
