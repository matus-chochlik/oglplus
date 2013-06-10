/*
 *  .file eglplus/enums/opengl_profile_bit.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/opengl_profile_bit.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/opengl_profile_bit.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void eglplus_py_opengl_profile_bit(void)
{
	boost::python::enum_<eglplus::OpenGLProfileBit>("OpenGLProfileBit")
#if defined EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR
# if defined Core
#  pragma push_macro("Core")
#  undef Core
	.value("Core", eglplus::OpenGLProfileBit::Core)
#  pragma pop_macro("Core")
# else
	.value("Core", eglplus::OpenGLProfileBit::Core)
# endif
#endif
#if defined EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR
# if defined Compatibility
#  pragma push_macro("Compatibility")
#  undef Compatibility
	.value("Compatibility", eglplus::OpenGLProfileBit::Compatibility)
#  pragma pop_macro("Compatibility")
# else
	.value("Compatibility", eglplus::OpenGLProfileBit::Compatibility)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::OpenGLProfileBit) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::OpenGLProfileBit
		>
	>("aux_CastIterRange_OpenGLProfileBit");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::OpenGLProfileBit
	> (*PEnumValueRange)(eglplus::OpenGLProfileBit) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
