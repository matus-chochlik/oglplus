/*
 *  .file eglplus/enums/context_flag.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_flag.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/context_flag.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void eglplus_py_context_flag(void)
{
	boost::python::enum_<eglplus::ContextFlag>("ContextFlag")
#if defined EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR
# if defined OpenGLDebug
#  pragma push_macro("OpenGLDebug")
#  undef OpenGLDebug
	.value("OpenGLDebug", eglplus::ContextFlag::OpenGLDebug)
#  pragma pop_macro("OpenGLDebug")
# else
	.value("OpenGLDebug", eglplus::ContextFlag::OpenGLDebug)
# endif
#endif
#if defined EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR
# if defined OpenGLForwardCompatible
#  pragma push_macro("OpenGLForwardCompatible")
#  undef OpenGLForwardCompatible
	.value("OpenGLForwardCompatible", eglplus::ContextFlag::OpenGLForwardCompatible)
#  pragma pop_macro("OpenGLForwardCompatible")
# else
	.value("OpenGLForwardCompatible", eglplus::ContextFlag::OpenGLForwardCompatible)
# endif
#endif
#if defined EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR
# if defined OpenGLRobustAccess
#  pragma push_macro("OpenGLRobustAccess")
#  undef OpenGLRobustAccess
	.value("OpenGLRobustAccess", eglplus::ContextFlag::OpenGLRobustAccess)
#  pragma pop_macro("OpenGLRobustAccess")
# else
	.value("OpenGLRobustAccess", eglplus::ContextFlag::OpenGLRobustAccess)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::ContextFlag) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::ContextFlag
		>
	>("aux_CastIterRange_ContextFlag");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::ContextFlag
	> (*PEnumValueRange)(eglplus::ContextFlag) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
