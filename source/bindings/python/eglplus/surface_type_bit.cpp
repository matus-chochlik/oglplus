/*
 *  .file eglplus/surface_type_bit.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/surface_type_bit.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/surface_type_bit.hpp>

#include <boost/python.hpp>

void eglplus_py_surface_type_bit(void)
{
	boost::python::enum_<eglplus::SurfaceTypeBit>("SurfaceTypeBit")
#if defined EGL_WINDOW_BIT
# if defined Window
#  pragma push_macro("Window")
#  undef Window
	.value("Window", eglplus::SurfaceTypeBit::Window)
#  pragma pop_macro("Window")
# else
	.value("Window", eglplus::SurfaceTypeBit::Window)
# endif
#endif
#if defined EGL_PIXMAP_BIT
# if defined Pixmal
#  pragma push_macro("Pixmal")
#  undef Pixmal
	.value("Pixmal", eglplus::SurfaceTypeBit::Pixmal)
#  pragma pop_macro("Pixmal")
# else
	.value("Pixmal", eglplus::SurfaceTypeBit::Pixmal)
# endif
#endif
#if defined EGL_PBUFFER_BIT
# if defined Pbuffer
#  pragma push_macro("Pbuffer")
#  undef Pbuffer
	.value("Pbuffer", eglplus::SurfaceTypeBit::Pbuffer)
#  pragma pop_macro("Pbuffer")
# else
	.value("Pbuffer", eglplus::SurfaceTypeBit::Pbuffer)
# endif
#endif
#if defined EGL_MULTISAMPLE_RESOLVE_BOX_BIT
# if defined MultisampleResolveBox
#  pragma push_macro("MultisampleResolveBox")
#  undef MultisampleResolveBox
	.value("MultisampleResolveBox", eglplus::SurfaceTypeBit::MultisampleResolveBox)
#  pragma pop_macro("MultisampleResolveBox")
# else
	.value("MultisampleResolveBox", eglplus::SurfaceTypeBit::MultisampleResolveBox)
# endif
#endif
#if defined EGL_SWAP_BEHAVIOR_PRESERVED_BIT
# if defined SwapBehaviorPreserved
#  pragma push_macro("SwapBehaviorPreserved")
#  undef SwapBehaviorPreserved
	.value("SwapBehaviorPreserved", eglplus::SurfaceTypeBit::SwapBehaviorPreserved)
#  pragma pop_macro("SwapBehaviorPreserved")
# else
	.value("SwapBehaviorPreserved", eglplus::SurfaceTypeBit::SwapBehaviorPreserved)
# endif
#endif
#if defined EGL_VG_COLORSPACE_LINEAR_BIT
# if defined VGColorspaceLinear
#  pragma push_macro("VGColorspaceLinear")
#  undef VGColorspaceLinear
	.value("VGColorspaceLinear", eglplus::SurfaceTypeBit::VGColorspaceLinear)
#  pragma pop_macro("VGColorspaceLinear")
# else
	.value("VGColorspaceLinear", eglplus::SurfaceTypeBit::VGColorspaceLinear)
# endif
#endif
#if defined EGL_VG_ALPHA_FORMAT_PRE_BIT
# if defined VGAlphaFormatPre
#  pragma push_macro("VGAlphaFormatPre")
#  undef VGAlphaFormatPre
	.value("VGAlphaFormatPre", eglplus::SurfaceTypeBit::VGAlphaFormatPre)
#  pragma pop_macro("VGAlphaFormatPre")
# else
	.value("VGAlphaFormatPre", eglplus::SurfaceTypeBit::VGAlphaFormatPre)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::SurfaceTypeBit) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
