/*
 *  .file oglplus/plane.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/plane.hpp>

#include <boost/python.hpp>

template <typename T>
void oglplus_py_export_Plane(oglplus::Plane<T>*, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Plane<T> Plane;

	bpy::return_internal_reference<1> bpy_rvp;

	bpy::class_<Plane>(name, bpy::init<T,T,T,T>())
		.def("FromTriangle", &Plane::FromTriangle)
			.staticmethod("FromTriangle")
		.def("FromPointAndVectors", &Plane::FromPointAndVectors)
			.staticmethod("FromPointAndVectors")
		.def("FromNormal", &Plane::FromNormal)
			.staticmethod("FromNormal")
		.def("FromPointAndNormal", &Plane::FromPointAndNormal)
			.staticmethod("FromPointAndNormal")
		.def("Equation", &Plane::Equation, bpy_rvp)
	;
}

void oglplus_py_Plane(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	oglplus_py_export_Plane((Planef*)0, "Planef");
}

