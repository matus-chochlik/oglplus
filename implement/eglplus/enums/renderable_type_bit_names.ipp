/*
 *  .file eglplus/enums/renderable_type_bit_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/renderable_type_bit.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	RenderableTypeBit*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_RENDERABLETYPEBIT)
#define EGLPLUS_IMPL_EVN_RENDERABLETYPEBIT
{
switch(value)
{
#if defined EGL_OPENGL_BIT
	case EGL_OPENGL_BIT: return StrLit("OPENGL_BIT");
#endif
#if defined EGL_OPENGL_ES_BIT
	case EGL_OPENGL_ES_BIT: return StrLit("OPENGL_ES_BIT");
#endif
#if defined EGL_OPENGL_ES2_BIT
	case EGL_OPENGL_ES2_BIT: return StrLit("OPENGL_ES2_BIT");
#endif
#if defined EGL_OPENGL_ES3_BIT
	case EGL_OPENGL_ES3_BIT: return StrLit("OPENGL_ES3_BIT");
#endif
#if defined EGL_OPENVG_BIT
	case EGL_OPENVG_BIT: return StrLit("OPENVG_BIT");
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

