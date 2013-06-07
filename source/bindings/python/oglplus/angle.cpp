/*
 *  .file oglplus/angle.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/angle.hpp>

#include <boost/python.hpp>

void oglplus_py_Angle(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	bpy::class_<Anglef>("Anglef")
		.def("Radians", &Anglef::Radians).staticmethod("Radians")
		.def("Degrees", &Anglef::Degrees).staticmethod("Degrees")
		.def("Value", &Anglef::Value)
		.def("ValueInDegrees", &Anglef::ValueInDegrees)
		.def(bpy::self == bpy::self)
		.def(bpy::self != bpy::self)
		.def(bpy::self <  bpy::self)
		.def(bpy::self <= bpy::self)
		.def(bpy::self >  bpy::self)
		.def(bpy::self >= bpy::self)
		.def(-bpy::self)
		.def(bpy::self + bpy::self)
		.def(bpy::self - bpy::self)
		.def(float() * bpy::self)
		.def(bpy::self * float())
		.def(bpy::self / float())
	;

	Anglef (*_ptr_oglplus_Negate_Anglef)(const Anglef&) = &Negate;
	bpy::def("Negate", _ptr_oglplus_Negate_Anglef);
	Anglef (*_ptr_oglplus_Add_Anglef)(const Anglef&, const Anglef&) = &Add;
	bpy::def("Add", _ptr_oglplus_Add_Anglef);
	Anglef (*_ptr_oglplus_Subtract_Anglef)(const Anglef&, const Anglef&) = &Subtract;
	bpy::def("Subtract", _ptr_oglplus_Subtract_Anglef);
	Anglef (*_ptr_oglplus_Multiply_Anglef)(const Anglef&, float) = &Multiply;
	bpy::def("Multiply", _ptr_oglplus_Multiply_Anglef);
	Anglef (*_ptr_oglplus_Divide_Anglef)(const Anglef&, float) = &Divide;
	bpy::def("Divide", _ptr_oglplus_Divide_Anglef);

	float (*_ptr_oglplus_Sin_Anglef)(const Anglef&) = &Sin;
	bpy::def("Sin", _ptr_oglplus_Sin_Anglef);
	float (*_ptr_oglplus_Cos_Anglef)(const Anglef&) = &Cos;
	bpy::def("Cos", _ptr_oglplus_Cos_Anglef);
	float (*_ptr_oglplus_Tan_Anglef)(const Anglef&) = &Tan;
	bpy::def("Tan", _ptr_oglplus_Tan_Anglef);

	bpy::def("Degrees", Degrees);
	bpy::def("Radians", Radians);
	bpy::def("FullCircles", FullCircles);
	bpy::def("FullCircle", FullCircle);
	bpy::def("RightAngles", RightAngles);
	bpy::def("RightAngle", RightAngle);
}

