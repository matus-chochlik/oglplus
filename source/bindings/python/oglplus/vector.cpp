/*
 *  .file oglplus/vector.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/vector.hpp>

#include <boost/python.hpp>

#include <cstdint>

std::size_t oglplus_py_Vector_adjusted_index(std::size_t N, int index)
{
	if(index < 0) index += N;

	if((index < 0) || (index >= int(N)))
	{
		PyErr_SetString(PyExc_IndexError, "index out of range");
		boost::python::throw_error_already_set();
	}
	return index;
}

template <typename T, std::size_t N>
void oglplus_py_Vector_setitem(oglplus::Vector<T, N>& v, int index, T value)
{
	v[oglplus_py_Vector_adjusted_index(N, index)] = value;
}

template <typename T, std::size_t N>
T oglplus_py_Vector_getitem(oglplus::Vector<T, N>& v, int index)
{
	return v[oglplus_py_Vector_adjusted_index(N, index)];
}

template <typename T, std::size_t N>
boost::python::class_<oglplus::Vector<T, N> >
oglplus_py_export_Vector_base(oglplus::Vector<T, N>*, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Vector<T, N> Vector;

	bpy::class_<Vector> py_vec(name, bpy::init<>());

	py_vec
		.def("Size", &Vector::Size).staticmethod("Size")
		.def("At", (T(Vector::*)(std::size_t)const)&Vector::At)
		.def("At", (T(Vector::*)(std::size_t, T)const)&Vector::At)
		.def(bpy::self == bpy::self)
		.def(bpy::self != bpy::self)
		.def(-bpy::self)
		.def(bpy::self + bpy::self)
		.def(bpy::self - bpy::self)
		.def(T() * bpy::self)
		.def(bpy::self * T())
		.def(bpy::self / T())
		.def("__getitem__", &oglplus_py_Vector_getitem<T, N>)
		.def("__setitem__", &oglplus_py_Vector_setitem<T, N>)
		.def("Add", &Vector::Add)
		.def("Subtract", &Vector::Subtract)
		.def("MultiplyBy", &Vector::MultiplyBy)
		.def("DivideBy", &Vector::DivideBy)
		.def("DotProduct", &Vector::DotProduct).staticmethod("DotProduct")
	;

	std::size_t (*_ptr_oglplus_Vector_Size)(const Vector&) = &Size;
	bpy::def("Size", _ptr_oglplus_Vector_Size);

	T (*_ptr_oglplus_Vector_At)(const Vector&, std::size_t) = &At;
	bpy::def("At", _ptr_oglplus_Vector_At);

	T (*_ptr_oglplus_Vector_At_fb)(const Vector&, std::size_t, T) = &At;
	bpy::def("At", _ptr_oglplus_Vector_At_fb);

	T (*_ptr_oglplus_Vector_Dot)(const Vector&, const Vector&) = &Dot;
	bpy::def("Dot", _ptr_oglplus_Vector_Dot);

	T (*_ptr_oglplus_Vector_Length)(const Vector&) = &Length;
	bpy::def("Length", _ptr_oglplus_Vector_Length);

	T (*_ptr_oglplus_Vector_Distance)(const Vector&, const Vector&) = &Distance;
	bpy::def("Distance", _ptr_oglplus_Vector_Distance);

	Vector (*_ptr_oglplus_Vector_Normalized)(Vector) = &Normalized;
	bpy::def("Normalized", _ptr_oglplus_Vector_Normalized);

	return py_vec;
}

template <typename T>
void oglplus_py_export_Vector(oglplus::Vector<T, 1>* sel, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Vector<T, 1> Vector;

	oglplus_py_export_Vector_base(sel, name)
		.def(bpy::init<T>())
	;
}

template <typename T>
void oglplus_py_export_Vector(oglplus::Vector<T, 2>* sel, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Vector<T, 2> Vector;

	oglplus_py_export_Vector_base(sel, name)
		.def(bpy::init<T, T>())
		.def(bpy::init<oglplus::Vector<T,1>, T>())
	;

	Vector (*_ptr_oglplus_Vector_Perpendicular)(const Vector&) = &Perpendicular;
	bpy::def("Perpendicular", _ptr_oglplus_Vector_Perpendicular);
}

template <typename T>
void oglplus_py_export_Vector(oglplus::Vector<T, 3>* sel, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Vector<T, 3> Vector;

	oglplus_py_export_Vector_base(sel, name)
		.def(bpy::init<T, T, T>())
		.def(bpy::init<oglplus::Vector<T,1>, T, T>())
		.def(bpy::init<oglplus::Vector<T,2>, T>())
	;

	Vector (*_ptr_oglplus_Vector_Cross)(const Vector&, const Vector&) = &Cross;
	bpy::def("Cross", _ptr_oglplus_Vector_Cross);
}

template <typename T>
void oglplus_py_export_Vector(oglplus::Vector<T, 4>* sel, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	typedef oglplus::Vector<T, 4> Vector;

	oglplus_py_export_Vector_base(sel, name)
		.def(bpy::init<T, T, T, T>())
		.def(bpy::init<oglplus::Vector<T,1>, T, T, T>())
		.def(bpy::init<oglplus::Vector<T,2>, T, T>())
		.def(bpy::init<oglplus::Vector<T,3>, T>())
	;
}

void oglplus_py_Vector(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	oglplus_py_export_Vector((Vec1f*)0, "Vec1f");
	oglplus_py_export_Vector((Vec2f*)0, "Vec2f");
	oglplus_py_export_Vector((Vec3f*)0, "Vec3f");
	oglplus_py_export_Vector((Vec4f*)0, "Vec4f");

	oglplus_py_export_Vector((Vec1d*)0, "Vec1d");
	oglplus_py_export_Vector((Vec2d*)0, "Vec2d");
	oglplus_py_export_Vector((Vec3d*)0, "Vec3d");
	oglplus_py_export_Vector((Vec4d*)0, "Vec4d");

}

