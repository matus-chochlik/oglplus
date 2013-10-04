/*
 *  .file eglplus/enums/render_buffer_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/render_buffer.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	RenderBuffer*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_RENDERBUFFER)
#define EGLPLUS_IMPL_EVN_RENDERBUFFER
{
switch(value)
{
#if defined EGL_SINGLE_BUFFER
	case EGL_SINGLE_BUFFER: return StrLit("SINGLE_BUFFER");
#endif
#if defined EGL_BACK_BUFFER
	case EGL_BACK_BUFFER: return StrLit("BACK_BUFFER");
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

