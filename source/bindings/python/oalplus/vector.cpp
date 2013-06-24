/*
 *  .file oalplus/vector.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/vector.hpp>

#include <boost/python.hpp>

#include "../oglplus/vector.hpp"

void oalplus_py_Vector(void)
{
	namespace bpy = ::boost::python;
	using namespace oalplus;

	oglplus_py_export_Vector((Vec3f*)0, "Vec3f");
}

