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
EGLPLUS_LIB_FUNC StrLit _ValueName(
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
	default:;
}
EGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

