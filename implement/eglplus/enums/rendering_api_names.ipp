/*
 *  .file eglplus/enums/rendering_api_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/rendering_api.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	RenderingAPI*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_RENDERINGAPI)
#define EGLPLUS_IMPL_EVN_RENDERINGAPI
{
switch(value)
{
#if defined EGL_OPENGL_API
	case EGL_OPENGL_API: return StrLit("OPENGL_API");
#endif
#if defined EGL_OPENGL_ES_API
	case EGL_OPENGL_ES_API: return StrLit("OPENGL_ES_API");
#endif
#if defined EGL_OPENVG_API
	case EGL_OPENVG_API: return StrLit("OPENVG_API");
#endif
#if defined EGL_NONE
	case EGL_NONE: return StrLit("NONE");
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

