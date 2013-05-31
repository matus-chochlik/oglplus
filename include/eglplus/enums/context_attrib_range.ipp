/*
 *  .file eglplus/enums/context_attrib_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/context_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC aux::CastIterRange<
	const EGLenum*,
	ContextAttrib
> _ValueRange(ContextAttrib*)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVR_CONTEXTATTRIB)
#define EGLPLUS_IMPL_EVR_CONTEXTATTRIB
{
static const EGLenum _values[] = {
#if defined EGL_CONTEXT_CLIENT_VERSION
EGL_CONTEXT_CLIENT_VERSION,
#endif
0
};
return aux::CastIterRange<
	const EGLenum*,
	ContextAttrib
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums

