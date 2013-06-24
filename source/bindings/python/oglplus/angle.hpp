/*
 *  .file oglplus/angle.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_OGLPLUS_ANGLE_0306061605_HPP
#define OGLPLUS_PYTHON_OGLPLUS_ANGLE_0306061605_HPP


#include <oglplus/gl.hpp>
#include <oglplus/angle.hpp>

#include <boost/python.hpp>

template <typename T>
void oglplus_py_export_Angle(oglplus::Angle<T>*, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Angle<T> Angle;

	bpy::class_<Angle>(name)
		.def("Radians", &Angle::Radians).staticmethod("Radians")
		.def("Degrees", &Angle::Degrees).staticmethod("Degrees")
		.def("Value", &Angle::Value)
		.def("ValueInDegrees", &Angle::ValueInDegrees)
		.def(bpy::self == bpy::self)
		.def(bpy::self != bpy::self)
		.def(bpy::self <  bpy::self)
		.def(bpy::self <= bpy::self)
		.def(bpy::self >  bpy::self)
		.def(bpy::self >= bpy::self)
		.def(-bpy::self)
		.def(bpy::self + bpy::self)
		.def(bpy::self - bpy::self)
		.def(T() * bpy::self)
		.def(bpy::self * T())
		.def(bpy::self / T())
	;

	Angle (*_ptr_oglplus_Negate_Angle)(const Angle&) = &Negate;
	bpy::def("Negate", _ptr_oglplus_Negate_Angle);
	Angle (*_ptr_oglplus_Add_Angle)(const Angle&, const Angle&) = &Add;
	bpy::def("Add", _ptr_oglplus_Add_Angle);
	Angle (*_ptr_oglplus_Subtract_Angle)(const Angle&, const Angle&) = &Subtract;
	bpy::def("Subtract", _ptr_oglplus_Subtract_Angle);
	Angle (*_ptr_oglplus_Multiply_Angle)(const Angle&, T) = &Multiply;
	bpy::def("Multiply", _ptr_oglplus_Multiply_Angle);
	Angle (*_ptr_oglplus_Divide_Angle)(const Angle&, T) = &Divide;
	bpy::def("Divide", _ptr_oglplus_Divide_Angle);

	T (*_ptr_oglplus_Sin_Angle)(const Angle&) = &Sin;
	bpy::def("Sin", _ptr_oglplus_Sin_Angle);
	T (*_ptr_oglplus_Cos_Angle)(const Angle&) = &Cos;
	bpy::def("Cos", _ptr_oglplus_Cos_Angle);
	T (*_ptr_oglplus_Tan_Angle)(const Angle&) = &Tan;
	bpy::def("Tan", _ptr_oglplus_Tan_Angle);
}

#endif
