/*
 *  .file eglplus/enums/surface_type_bit_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/surface_type_bit.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	SurfaceTypeBit*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_SURFACETYPEBIT)
#define EGLPLUS_IMPL_EVN_SURFACETYPEBIT
{
switch(value)
{
#if defined EGL_WINDOW_BIT
	case EGL_WINDOW_BIT: return StrLit("WINDOW_BIT");
#endif
#if defined EGL_PIXMAP_BIT
	case EGL_PIXMAP_BIT: return StrLit("PIXMAP_BIT");
#endif
#if defined EGL_PBUFFER_BIT
	case EGL_PBUFFER_BIT: return StrLit("PBUFFER_BIT");
#endif
#if defined EGL_MULTISAMPLE_RESOLVE_BOX_BIT
	case EGL_MULTISAMPLE_RESOLVE_BOX_BIT: return StrLit("MULTISAMPLE_RESOLVE_BOX_BIT");
#endif
#if defined EGL_SWAP_BEHAVIOR_PRESERVED_BIT
	case EGL_SWAP_BEHAVIOR_PRESERVED_BIT: return StrLit("SWAP_BEHAVIOR_PRESERVED_BIT");
#endif
#if defined EGL_VG_COLORSPACE_LINEAR_BIT
	case EGL_VG_COLORSPACE_LINEAR_BIT: return StrLit("VG_COLORSPACE_LINEAR_BIT");
#endif
#if defined EGL_VG_ALPHA_FORMAT_PRE_BIT
	case EGL_VG_ALPHA_FORMAT_PRE_BIT: return StrLit("VG_ALPHA_FORMAT_PRE_BIT");
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

