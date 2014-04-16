/*
 *  .file eglplus/enums/opengl_profile_bit_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/opengl_profile_bit.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	OpenGLProfileBit*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_OPENGLPROFILEBIT)
#define EGLPLUS_IMPL_EVN_OPENGLPROFILEBIT
{
switch(value)
{
#if defined EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT
	case EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT: return StrLit("CONTEXT_OPENGL_CORE_PROFILE_BIT");
#endif
#if defined EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT
	case EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT: return StrLit("CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT");
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

