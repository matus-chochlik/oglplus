//  File implement/eglplus/enums/error_code_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/eglplus/error_code.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
EGLPLUS_LIB_FUNC CStrRef ValueName_(
	ErrorCode*,
	EGLenum value
) noexcept
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_ERRORCODE)
#define EGLPLUS_IMPL_EVN_ERRORCODE
{
switch(value)
{
#if defined EGL_NOT_INITIALIZED
	case EGL_NOT_INITIALIZED: return CStrRef("NOT_INITIALIZED");
#endif
#if defined EGL_BAD_ACCESS
	case EGL_BAD_ACCESS: return CStrRef("BAD_ACCESS");
#endif
#if defined EGL_BAD_ALLOC
	case EGL_BAD_ALLOC: return CStrRef("BAD_ALLOC");
#endif
#if defined EGL_BAD_ATTRIBUTE
	case EGL_BAD_ATTRIBUTE: return CStrRef("BAD_ATTRIBUTE");
#endif
#if defined EGL_BAD_CONTEXT
	case EGL_BAD_CONTEXT: return CStrRef("BAD_CONTEXT");
#endif
#if defined EGL_BAD_CONFIG
	case EGL_BAD_CONFIG: return CStrRef("BAD_CONFIG");
#endif
#if defined EGL_BAD_CURRENT_SURFACE
	case EGL_BAD_CURRENT_SURFACE: return CStrRef("BAD_CURRENT_SURFACE");
#endif
#if defined EGL_BAD_DISPLAY
	case EGL_BAD_DISPLAY: return CStrRef("BAD_DISPLAY");
#endif
#if defined EGL_BAD_SURFACE
	case EGL_BAD_SURFACE: return CStrRef("BAD_SURFACE");
#endif
#if defined EGL_BAD_MATCH
	case EGL_BAD_MATCH: return CStrRef("BAD_MATCH");
#endif
#if defined EGL_BAD_PARAMETER
	case EGL_BAD_PARAMETER: return CStrRef("BAD_PARAMETER");
#endif
#if defined EGL_BAD_NATIVE_PIXMAP
	case EGL_BAD_NATIVE_PIXMAP: return CStrRef("BAD_NATIVE_PIXMAP");
#endif
#if defined EGL_BAD_NATIVE_WINDOW
	case EGL_BAD_NATIVE_WINDOW: return CStrRef("BAD_NATIVE_WINDOW");
#endif
#if defined EGL_CONTEXT_LOST
	case EGL_CONTEXT_LOST: return CStrRef("CONTEXT_LOST");
#endif
	default:;
}
EGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

