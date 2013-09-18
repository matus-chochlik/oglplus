/*
 *  .file eglplus/enums/opengl_rns_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/opengl_rns.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	OpenGLResetNotificationStrategy*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_OPENGLRESETNOTIFICATIONSTRATEGY)
#define EGLPLUS_IMPL_EVN_OPENGLRESETNOTIFICATIONSTRATEGY
{
switch(value)
{
#if defined EGL_NO_RESET_NOTIFICATION_KHR
	case EGL_NO_RESET_NOTIFICATION_KHR: return StrLit("NO_RESET_NOTIFICATION_KHR");
#endif
#if defined EGL_LOSE_CONTEXT_ON_RESET_KHR
	case EGL_LOSE_CONTEXT_ON_RESET_KHR: return StrLit("LOSE_CONTEXT_ON_RESET_KHR");
#endif
	default:;
}
EGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

