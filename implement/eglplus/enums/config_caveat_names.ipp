/*
 *  .file eglplus/enums/config_caveat_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/config_caveat.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	ConfigCaveat*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_CONFIGCAVEAT)
#define EGLPLUS_IMPL_EVN_CONFIGCAVEAT
{
switch(value)
{
#if defined EGL_NONE
	case EGL_NONE: return StrLit("NONE");
#endif
#if defined EGL_SLOW_CONFIG
	case EGL_SLOW_CONFIG: return StrLit("SLOW_CONFIG");
#endif
#if defined EGL_NON_CONFORMANT_CONFIG
	case EGL_NON_CONFORMANT_CONFIG: return StrLit("NON_CONFORMANT_CONFIG");
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

