/*
 *  .file eglplus/enums/vg_colorspace.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/vg_colorspace.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/vg_colorspace.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_vg_colorspace(void)
{
	boost::python::enum_<eglplus::VGColorspace>("VGColorspace")
#if defined EGL_VG_COLORSPACE_sRGB
# if defined sRGB
#  pragma push_macro("sRGB")
#  undef sRGB
	.value("sRGB", eglplus::VGColorspace::sRGB)
#  pragma pop_macro("sRGB")
# else
	.value("sRGB", eglplus::VGColorspace::sRGB)
# endif
#endif
#if defined EGL_VG_COLORSPACE_LINEAR
# if defined Linear
#  pragma push_macro("Linear")
#  undef Linear
	.value("Linear", eglplus::VGColorspace::Linear)
#  pragma pop_macro("Linear")
# else
	.value("Linear", eglplus::VGColorspace::Linear)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::VGColorspace) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::VGColorspace
		>
	>("aux_CastIterRange_VGColorspace");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::VGColorspace
	> (*PEnumValueRange)(eglplus::VGColorspace) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
