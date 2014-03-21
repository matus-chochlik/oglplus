/*
 *  .file eglplus/enums/context_attrib_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
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
#if defined EGL_CONTEXT_MAJOR_VERSION
	case EGL_CONTEXT_MAJOR_VERSION: return StrLit("CONTEXT_MAJOR_VERSION");
#endif
#if defined EGL_CONTEXT_MINOR_VERSION
	case EGL_CONTEXT_MINOR_VERSION: return StrLit("CONTEXT_MINOR_VERSION");
#endif
#if defined EGL_CONTEXT_FLAGS
	case EGL_CONTEXT_FLAGS: return StrLit("CONTEXT_FLAGS");
#endif
#if defined EGL_CONTEXT_OPENGL_PROFILE_MASK
	case EGL_CONTEXT_OPENGL_PROFILE_MASK: return StrLit("CONTEXT_OPENGL_PROFILE_MASK");
#endif
#if defined EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY
	case EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY: return StrLit("CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY");
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

