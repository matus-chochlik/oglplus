/*
 *  .file eglplus/enums/opengl_rns.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/opengl_rns.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/opengl_rns.hpp>

#include <boost/python.hpp>

void eglplus_py_opengl_rns(void)
{
	boost::python::enum_<eglplus::OpenGLResetNotificationStrategy>("OpenGLResetNotificationStrategy")
#if defined EGL_NO_RESET_NOTIFICATION_KHR
# if defined NoResetNotification
#  pragma push_macro("NoResetNotification")
#  undef NoResetNotification
	.value("NoResetNotification", eglplus::OpenGLResetNotificationStrategy::NoResetNotification)
#  pragma pop_macro("NoResetNotification")
# else
	.value("NoResetNotification", eglplus::OpenGLResetNotificationStrategy::NoResetNotification)
# endif
#endif
#if defined EGL_LOSE_CONTEXT_ON_RESET_KHR
# if defined LoseContextOnReset
#  pragma push_macro("LoseContextOnReset")
#  undef LoseContextOnReset
	.value("LoseContextOnReset", eglplus::OpenGLResetNotificationStrategy::LoseContextOnReset)
#  pragma pop_macro("LoseContextOnReset")
# else
	.value("LoseContextOnReset", eglplus::OpenGLResetNotificationStrategy::LoseContextOnReset)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::OpenGLResetNotificationStrategy) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
