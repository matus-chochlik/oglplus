/*
 *  .file eglplus/enums/surface_attrib_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/surface_attrib.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	SurfaceAttrib*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_SURFACEATTRIB)
#define EGLPLUS_IMPL_EVN_SURFACEATTRIB
{
switch(value)
{
#if defined EGL_WIDTH
	case EGL_WIDTH: return StrLit("WIDTH");
#endif
#if defined EGL_HEIGHT
	case EGL_HEIGHT: return StrLit("HEIGHT");
#endif
#if defined EGL_CONFIG_ID
	case EGL_CONFIG_ID: return StrLit("CONFIG_ID");
#endif
#if defined EGL_VG_ALPHA_FORMAT
	case EGL_VG_ALPHA_FORMAT: return StrLit("VG_ALPHA_FORMAT");
#endif
#if defined EGL_VG_COLORSPACE
	case EGL_VG_COLORSPACE: return StrLit("VG_COLORSPACE");
#endif
#if defined EGL_GL_COLORSPACE
	case EGL_GL_COLORSPACE: return StrLit("GL_COLORSPACE");
#endif
#if defined EGL_HORIZONTAL_RESOLUTION
	case EGL_HORIZONTAL_RESOLUTION: return StrLit("HORIZONTAL_RESOLUTION");
#endif
#if defined EGL_VERTICAL_RESOLUTION
	case EGL_VERTICAL_RESOLUTION: return StrLit("VERTICAL_RESOLUTION");
#endif
#if defined EGL_LARGEST_PBUFFER
	case EGL_LARGEST_PBUFFER: return StrLit("LARGEST_PBUFFER");
#endif
#if defined EGL_MIPMAP_TEXTURE
	case EGL_MIPMAP_TEXTURE: return StrLit("MIPMAP_TEXTURE");
#endif
#if defined EGL_MIPMAP_LEVEL
	case EGL_MIPMAP_LEVEL: return StrLit("MIPMAP_LEVEL");
#endif
#if defined EGL_MULTISAMPLE_RESOLVE
	case EGL_MULTISAMPLE_RESOLVE: return StrLit("MULTISAMPLE_RESOLVE");
#endif
#if defined EGL_PIXEL_ASPECT_RATIO
	case EGL_PIXEL_ASPECT_RATIO: return StrLit("PIXEL_ASPECT_RATIO");
#endif
#if defined EGL_RENDER_BUFFER
	case EGL_RENDER_BUFFER: return StrLit("RENDER_BUFFER");
#endif
#if defined EGL_SWAP_BEHAVIOR
	case EGL_SWAP_BEHAVIOR: return StrLit("SWAP_BEHAVIOR");
#endif
#if defined EGL_TEXTURE_FORMAT
	case EGL_TEXTURE_FORMAT: return StrLit("TEXTURE_FORMAT");
#endif
#if defined EGL_TEXTURE_TARGET
	case EGL_TEXTURE_TARGET: return StrLit("TEXTURE_TARGET");
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

