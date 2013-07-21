/*
 *  .file eglplus/attrib_list.hpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_PYTHON_EGLPLUS_ATTRIB_LIST_0306061605_HPP
#define OGLPLUS_PYTHON_EGLPLUS_ATTRIB_LIST_0306061605_HPP

#include <eglplus/egl.hpp>
#include <eglplus/attrib_list.hpp>
#include <eglplus/bitfield.hpp>

#include <boost/python.hpp>

#include <type_traits>

template <typename AK, typename VTAM, typename Traits>
inline boost::python::class_<eglplus::AttributeList<AK, VTAM, Traits> >&
eglplus_py_export_AttributeList_Add(
	boost::python::class_<eglplus::AttributeList<AK, VTAM, Traits> >& al_class,
	...
)
{
	return al_class;
}

template <typename VT, typename AttribList>
inline boost::python::class_<AttribList>&
eglplus_py_do_export_AttributeList_Add(
	boost::python::class_<AttribList>& al_class,
	std::false_type
)
{
	boost::python::return_internal_reference<1> bpy_rvp;

	AttribList& (AttribList::*PAdd)(VT) = &AttribList::Add;

	return al_class.def("Add", PAdd, bpy_rvp);
}


template <typename VT, typename AttribList>
inline boost::python::class_<AttribList>&
eglplus_py_do_export_AttributeList_Add(
	boost::python::class_<AttribList>& al_class,
	std::true_type
)
{
	boost::python::return_internal_reference<1> bpy_rvp;

	AttribList& (AttribList::*PAdd)(eglplus::Bitfield<VT>) = &AttribList::Add;

	return eglplus_py_do_export_AttributeList_Add<VT>(
		al_class,
		std::false_type()
	).def("Add", PAdd, bpy_rvp);
}


template <typename AK, typename VTAM, typename Traits, int I>
boost::python::class_<eglplus::AttributeList<AK, VTAM, Traits> >&
eglplus_py_export_AttributeList_Add(
	boost::python::class_<eglplus::AttributeList<AK, VTAM, Traits> >& al_class,
	std::integral_constant<int, I>,
	AK (VTAM::*)(
		decltype(VTAM::ValueType(std::integral_constant<int, I>()))
	) const = &VTAM::operator()
)
{
	typedef decltype(VTAM::ValueType(std::integral_constant<int, I>())) VT;

	return eglplus_py_export_AttributeList_Add(
		eglplus_py_do_export_AttributeList_Add<VT>(
			al_class,
			typename oglplus::enums::IsBitfieldBit<VT>::Type()
		),
		std::integral_constant<int, I+1>()
	);
}

template <typename AttribKind, class ValueToAttribMap, typename Traits>
inline void eglplus_py_export_AttributeList(
	const std::string& name,
	eglplus::AttributeList<AttribKind, ValueToAttribMap, Traits>*
)
{
	namespace bpy = ::boost::python;
	using namespace eglplus;

	typedef eglplus::FinishedAttributeList<AttribKind, Traits>
		FinishedAttribList;

	bpy::class_<FinishedAttribList>(
		("Finished"+name).c_str(),
		bpy::no_init
	);

	typedef eglplus::AttributeList<AttribKind, ValueToAttribMap, Traits>
		AttribList;

	AttribList& (AttribList::*PAdd1)(AttribKind, EGLint) =
		&AttribList::Add;
	AttribList& (AttribList::*PAdd2)(AttribKind, bool) =
		&AttribList::Add;

	bpy::return_internal_reference<1> bpy_rvp;

	bpy::class_<AttribList> cls(name.c_str(), bpy::init<>());
	std::integral_constant<int, 0> zero;


	eglplus_py_export_AttributeList_Add(cls, zero)
		.def("Add", PAdd1, bpy_rvp)
		.def("Add", PAdd2, bpy_rvp)
		.def("DontCare", &AttribList::DontCare, bpy_rvp)
		.def("Finish", &AttribList::Finish, bpy_rvp)
		.def("Finished", &AttribList::Finished)
		.def("Get", &AttribList::Get)
	;
}

template <typename AttribList>
inline void eglplus_py_export_AttributeList(const char* name)
{
	eglplus_py_export_AttributeList(name, (AttribList*)nullptr);
}

#endif
