/*
 *  .file eglplus/enums/vg_alpha_format.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/vg_alpha_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/vg_alpha_format.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_vg_alpha_format(void)
{
	boost::python::enum_<eglplus::VGAlphaFormat>("VGAlphaFormat")
#if defined EGL_VG_ALPHA_FORMAT_PRE
# if defined Pre
#  pragma push_macro("Pre")
#  undef Pre
	.value("Pre", eglplus::VGAlphaFormat::Pre)
#  pragma pop_macro("Pre")
# else
	.value("Pre", eglplus::VGAlphaFormat::Pre)
# endif
#endif
#if defined EGL_VG_ALPHA_FORMAT_NONPRE
# if defined NonPre
#  pragma push_macro("NonPre")
#  undef NonPre
	.value("NonPre", eglplus::VGAlphaFormat::NonPre)
#  pragma pop_macro("NonPre")
# else
	.value("NonPre", eglplus::VGAlphaFormat::NonPre)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::VGAlphaFormat) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::VGAlphaFormat
		>
	>("aux_CastIterRange_VGAlphaFormat");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::VGAlphaFormat
	> (*PEnumValueRange)(eglplus::VGAlphaFormat) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
