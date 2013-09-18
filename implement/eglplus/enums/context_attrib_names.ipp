/*
 *  .file eglplus/enums/context_attrib_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	ContextAttrib*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_CONTEXTATTRIB)
#define EGLPLUS_IMPL_EVN_CONTEXTATTRIB
{
switch(value)
{
#if defined EGL_CONTEXT_CLIENT_VERSION
	case EGL_CONTEXT_CLIENT_VERSION: return StrLit("CONTEXT_CLIENT_VERSION");
#endif
#if defined EGL_CONTEXT_MINOR_VERSION_KHR
	case EGL_CONTEXT_MINOR_VERSION_KHR: return StrLit("CONTEXT_MINOR_VERSION_KHR");
#endif
#if defined EGL_CONTEXT_FLAGS_KHR
	case EGL_CONTEXT_FLAGS_KHR: return StrLit("CONTEXT_FLAGS_KHR");
#endif
#if defined EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR
	case EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR: return StrLit("CONTEXT_OPENGL_PROFILE_MASK_KHR");
#endif
#if defined EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR
	case EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR: return StrLit("CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR");
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

