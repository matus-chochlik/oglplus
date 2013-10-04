/*
 *  .file eglplus/enums/vg_colorspace_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/vg_colorspace.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
EGLPLUS_LIB_FUNC StrLit ValueName_(
	VGColorspace*,
	EGLenum value
)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVN_VGCOLORSPACE)
#define EGLPLUS_IMPL_EVN_VGCOLORSPACE
{
switch(value)
{
#if defined EGL_VG_COLORSPACE_sRGB
	case EGL_VG_COLORSPACE_sRGB: return StrLit("VG_COLORSPACE_sRGB");
#endif
#if defined EGL_VG_COLORSPACE_LINEAR
	case EGL_VG_COLORSPACE_LINEAR: return StrLit("VG_COLORSPACE_LINEAR");
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

