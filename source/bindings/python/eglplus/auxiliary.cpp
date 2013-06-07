/*
 *  .file eglplus/auxiliary.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/all.hpp>

#include <boost/python.hpp>

#include "_py_range_adapt.hpp"

void eglplus_py_Auxiliary(void)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	eglplus_py_export_range<aux::SepStrRange>("aux_SepStrRange");
}

