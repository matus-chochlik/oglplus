/*
 *  .file eglplus/enums/config_attrib_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/config_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	ConfigAttrib*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_CONFIGATTRIB)
#define EGLPLUS_IMPL_EVN_CONFIGATTRIB
{
switch(value)
{
#if defined EGL_BUFFER_SIZE
	case EGL_BUFFER_SIZE: return StrLit("BUFFER_SIZE");
#endif
#if defined EGL_RED_SIZE
	case EGL_RED_SIZE: return StrLit("RED_SIZE");
#endif
#if defined EGL_GREEN_SIZE
	case EGL_GREEN_SIZE: return StrLit("GREEN_SIZE");
#endif
#if defined EGL_BLUE_SIZE
	case EGL_BLUE_SIZE: return StrLit("BLUE_SIZE");
#endif
#if defined EGL_LUMINANCE_SIZE
	case EGL_LUMINANCE_SIZE: return StrLit("LUMINANCE_SIZE");
#endif
#if defined EGL_ALPHA_SIZE
	case EGL_ALPHA_SIZE: return StrLit("ALPHA_SIZE");
#endif
#if defined EGL_ALPHA_MASK_SIZE
	case EGL_ALPHA_MASK_SIZE: return StrLit("ALPHA_MASK_SIZE");
#endif
#if defined EGL_BIND_TO_TEXTURE_RGB
	case EGL_BIND_TO_TEXTURE_RGB: return StrLit("BIND_TO_TEXTURE_RGB");
#endif
#if defined EGL_BIND_TO_TEXTURE_RGBA
	case EGL_BIND_TO_TEXTURE_RGBA: return StrLit("BIND_TO_TEXTURE_RGBA");
#endif
#if defined EGL_COLOR_BUFFER_TYPE
	case EGL_COLOR_BUFFER_TYPE: return StrLit("COLOR_BUFFER_TYPE");
#endif
#if defined EGL_CONFIG_CAVEAT
	case EGL_CONFIG_CAVEAT: return StrLit("CONFIG_CAVEAT");
#endif
#if defined EGL_CONFIG_ID
	case EGL_CONFIG_ID: return StrLit("CONFIG_ID");
#endif
#if defined EGL_CONFORMANT
	case EGL_CONFORMANT: return StrLit("CONFORMANT");
#endif
#if defined EGL_DEPTH_SIZE
	case EGL_DEPTH_SIZE: return StrLit("DEPTH_SIZE");
#endif
#if defined EGL_LEVEL
	case EGL_LEVEL: return StrLit("LEVEL");
#endif
#if defined EGL_MAX_PBUFFER_WIDTH
	case EGL_MAX_PBUFFER_WIDTH: return StrLit("MAX_PBUFFER_WIDTH");
#endif
#if defined EGL_MAX_PBUFFER_HEIGHT
	case EGL_MAX_PBUFFER_HEIGHT: return StrLit("MAX_PBUFFER_HEIGHT");
#endif
#if defined EGL_MAX_PBUFFER_PIXELS
	case EGL_MAX_PBUFFER_PIXELS: return StrLit("MAX_PBUFFER_PIXELS");
#endif
#if defined EGL_MAX_SWAP_INTERVAL
	case EGL_MAX_SWAP_INTERVAL: return StrLit("MAX_SWAP_INTERVAL");
#endif
#if defined EGL_MIN_SWAP_INTERVAL
	case EGL_MIN_SWAP_INTERVAL: return StrLit("MIN_SWAP_INTERVAL");
#endif
#if defined EGL_NATIVE_RENDERABLE
	case EGL_NATIVE_RENDERABLE: return StrLit("NATIVE_RENDERABLE");
#endif
#if defined EGL_NATIVE_VISUAL_ID
	case EGL_NATIVE_VISUAL_ID: return StrLit("NATIVE_VISUAL_ID");
#endif
#if defined EGL_NATIVE_VISUAL_TYPE
	case EGL_NATIVE_VISUAL_TYPE: return StrLit("NATIVE_VISUAL_TYPE");
#endif
#if defined EGL_RENDERABLE_TYPE
	case EGL_RENDERABLE_TYPE: return StrLit("RENDERABLE_TYPE");
#endif
#if defined EGL_SAMPLE_BUFFERS
	case EGL_SAMPLE_BUFFERS: return StrLit("SAMPLE_BUFFERS");
#endif
#if defined EGL_SAMPLES
	case EGL_SAMPLES: return StrLit("SAMPLES");
#endif
#if defined EGL_STENCIL_SIZE
	case EGL_STENCIL_SIZE: return StrLit("STENCIL_SIZE");
#endif
#if defined EGL_SURFACE_TYPE
	case EGL_SURFACE_TYPE: return StrLit("SURFACE_TYPE");
#endif
#if defined EGL_TRANSPARENT_TYPE
	case EGL_TRANSPARENT_TYPE: return StrLit("TRANSPARENT_TYPE");
#endif
#if defined EGL_TRANSPARENT_RED_VALUE
	case EGL_TRANSPARENT_RED_VALUE: return StrLit("TRANSPARENT_RED_VALUE");
#endif
#if defined EGL_TRANSPARENT_GREEN_VALUE
	case EGL_TRANSPARENT_GREEN_VALUE: return StrLit("TRANSPARENT_GREEN_VALUE");
#endif
#if defined EGL_TRANSPARENT_BLUE_VALUE
	case EGL_TRANSPARENT_BLUE_VALUE: return StrLit("TRANSPARENT_BLUE_VALUE");
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

