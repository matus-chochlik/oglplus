/*
 *  .file oalplus/auxiliary.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/auxiliary/sep_str_range.hpp>

#include <boost/python.hpp>

#include "range.hpp"

void oalplus_py_Auxiliary(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	oalplus_py_export_range<aux::SepStrRange>("aux_SepStrRange");
}

