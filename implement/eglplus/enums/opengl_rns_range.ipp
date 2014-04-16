/*
 *  .file eglplus/enums/opengl_rns_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/opengl_rns.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC aux::CastIterRange<
	const EGLenum*,
	OpenGLResetNotificationStrategy
> ValueRange_(OpenGLResetNotificationStrategy*)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVR_OPENGLRESETNOTIFICATIONSTRATEGY)
#define EGLPLUS_IMPL_EVR_OPENGLRESETNOTIFICATIONSTRATEGY
{
static const EGLenum _values[] = {
#if defined EGL_NO_RESET_NOTIFICATION
EGL_NO_RESET_NOTIFICATION,
#endif
#if defined EGL_LOSE_CONTEXT_ON_RESET
EGL_LOSE_CONTEXT_ON_RESET,
#endif
0
};
return aux::CastIterRange<
	const EGLenum*,
	OpenGLResetNotificationStrategy
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

