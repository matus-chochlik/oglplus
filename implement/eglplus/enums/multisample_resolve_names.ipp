/*
 *  .file eglplus/enums/multisample_resolve_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/multisample_resolve.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	MultisampleResolve*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_MULTISAMPLERESOLVE)
#define EGLPLUS_IMPL_EVN_MULTISAMPLERESOLVE
{
switch(value)
{
#if defined EGL_MULTISAMPLE_RESOLVE_DEFAULT
	case EGL_MULTISAMPLE_RESOLVE_DEFAULT: return StrLit("MULTISAMPLE_RESOLVE_DEFAULT");
#endif
#if defined EGL_MULTISAMPLE_RESOLVE_BOX
	case EGL_MULTISAMPLE_RESOLVE_BOX: return StrLit("MULTISAMPLE_RESOLVE_BOX");
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

