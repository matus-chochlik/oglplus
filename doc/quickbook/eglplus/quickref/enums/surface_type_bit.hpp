//  File doc/quickbook/eglplus/quickref/enums/surface_type_bit.hpp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/eglplus/surface_type_bit.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//[oglplus_enums_surface_type_bit
namespace eglplus {

enum class SurfaceTypeBit : EGLenum
{
	Window                = EGL_WINDOW_BIT,
	Pixmap                = EGL_PIXMAP_BIT,
	Pbuffer               = EGL_PBUFFER_BIT,
	MultisampleResolveBox = EGL_MULTISAMPLE_RESOLVE_BOX_BIT,
	SwapBehaviorPreserved = EGL_SWAP_BEHAVIOR_PRESERVED_BIT,
	VGColorspaceLinear    = EGL_VG_COLORSPACE_LINEAR_BIT,
	VGAlphaFormatPre      = EGL_VG_ALPHA_FORMAT_PRE_BIT
};

#if !__OGLPLUS_NO_ENUM_VALUE_RANGES
template <>
__Range<SurfaceTypeBit> __EnumValueName<SurfaceTypeBit>(void);
#endif

#if !__OGLPLUS_NO_ENUM_VALUE_NAMES
__StrCRef __EnumValueName(SurfaceTypeBit);
#endif

} // namespace eglplus
//]
