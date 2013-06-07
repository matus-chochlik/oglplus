/*
 *  .file eglplus/enums/transparent_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/transparent_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/transparent_type.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_transparent_type(void)
{
	boost::python::enum_<eglplus::TransparentType>("TransparentType")
#if defined EGL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", eglplus::TransparentType::None)
#  pragma pop_macro("None")
# else
	.value("None", eglplus::TransparentType::None)
# endif
#endif
#if defined EGL_TRANSPARENT_RGB
# if defined TransparentRGB
#  pragma push_macro("TransparentRGB")
#  undef TransparentRGB
	.value("TransparentRGB", eglplus::TransparentType::TransparentRGB)
#  pragma pop_macro("TransparentRGB")
# else
	.value("TransparentRGB", eglplus::TransparentType::TransparentRGB)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::TransparentType) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::TransparentType
		>
	>("aux_CastIterRange_TransparentType");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::TransparentType
	> (*PEnumValueRange)(eglplus::TransparentType) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
