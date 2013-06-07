/*
 *  .file eglplus/enums/context_attrib.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/context_attrib.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_context_attrib(void)
{
	boost::python::enum_<eglplus::ContextAttrib>("ContextAttrib")
#if defined EGL_CONTEXT_CLIENT_VERSION
# if defined ClientVersion
#  pragma push_macro("ClientVersion")
#  undef ClientVersion
	.value("ClientVersion", eglplus::ContextAttrib::ClientVersion)
#  pragma pop_macro("ClientVersion")
# else
	.value("ClientVersion", eglplus::ContextAttrib::ClientVersion)
# endif
#endif
#if defined EGL_CONTEXT_MINOR_VERSION_KHR
# if defined MinorVersion
#  pragma push_macro("MinorVersion")
#  undef MinorVersion
	.value("MinorVersion", eglplus::ContextAttrib::MinorVersion)
#  pragma pop_macro("MinorVersion")
# else
	.value("MinorVersion", eglplus::ContextAttrib::MinorVersion)
# endif
#endif
#if defined EGL_CONTEXT_FLAGS_KHR
# if defined Flags
#  pragma push_macro("Flags")
#  undef Flags
	.value("Flags", eglplus::ContextAttrib::Flags)
#  pragma pop_macro("Flags")
# else
	.value("Flags", eglplus::ContextAttrib::Flags)
# endif
#endif
#if defined EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR
# if defined OpenGLProfileMask
#  pragma push_macro("OpenGLProfileMask")
#  undef OpenGLProfileMask
	.value("OpenGLProfileMask", eglplus::ContextAttrib::OpenGLProfileMask)
#  pragma pop_macro("OpenGLProfileMask")
# else
	.value("OpenGLProfileMask", eglplus::ContextAttrib::OpenGLProfileMask)
# endif
#endif
#if defined EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR
# if defined OpenGLResetNotificationStrategy
#  pragma push_macro("OpenGLResetNotificationStrategy")
#  undef OpenGLResetNotificationStrategy
	.value("OpenGLResetNotificationStrategy", eglplus::ContextAttrib::OpenGLResetNotificationStrategy)
#  pragma pop_macro("OpenGLResetNotificationStrategy")
# else
	.value("OpenGLResetNotificationStrategy", eglplus::ContextAttrib::OpenGLResetNotificationStrategy)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::ContextAttrib) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::ContextAttrib
		>
	>("aux_CastIterRange_ContextAttrib");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::ContextAttrib
	> (*PEnumValueRange)(eglplus::ContextAttrib) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
