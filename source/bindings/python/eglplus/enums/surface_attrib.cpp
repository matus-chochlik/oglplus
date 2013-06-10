/*
 *  .file eglplus/enums/surface_attrib.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/surface_attrib.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/surface_attrib.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void eglplus_py_surface_attrib(void)
{
	boost::python::enum_<eglplus::SurfaceAttrib>("SurfaceAttrib")
#if defined EGL_WIDTH
# if defined Width
#  pragma push_macro("Width")
#  undef Width
	.value("Width", eglplus::SurfaceAttrib::Width)
#  pragma pop_macro("Width")
# else
	.value("Width", eglplus::SurfaceAttrib::Width)
# endif
#endif
#if defined EGL_HEIGHT
# if defined Height
#  pragma push_macro("Height")
#  undef Height
	.value("Height", eglplus::SurfaceAttrib::Height)
#  pragma pop_macro("Height")
# else
	.value("Height", eglplus::SurfaceAttrib::Height)
# endif
#endif
#if defined EGL_CONFIG_ID
# if defined ConfigId
#  pragma push_macro("ConfigId")
#  undef ConfigId
	.value("ConfigId", eglplus::SurfaceAttrib::ConfigId)
#  pragma pop_macro("ConfigId")
# else
	.value("ConfigId", eglplus::SurfaceAttrib::ConfigId)
# endif
#endif
#if defined EGL_VG_ALPHA_FORMAT
# if defined VGAlphaFormat
#  pragma push_macro("VGAlphaFormat")
#  undef VGAlphaFormat
	.value("VGAlphaFormat", eglplus::SurfaceAttrib::VGAlphaFormat)
#  pragma pop_macro("VGAlphaFormat")
# else
	.value("VGAlphaFormat", eglplus::SurfaceAttrib::VGAlphaFormat)
# endif
#endif
#if defined EGL_VG_COLORSPACE
# if defined VGColorspace
#  pragma push_macro("VGColorspace")
#  undef VGColorspace
	.value("VGColorspace", eglplus::SurfaceAttrib::VGColorspace)
#  pragma pop_macro("VGColorspace")
# else
	.value("VGColorspace", eglplus::SurfaceAttrib::VGColorspace)
# endif
#endif
#if defined EGL_HORIZONTAL_RESOLUTION
# if defined HorizontalResolution
#  pragma push_macro("HorizontalResolution")
#  undef HorizontalResolution
	.value("HorizontalResolution", eglplus::SurfaceAttrib::HorizontalResolution)
#  pragma pop_macro("HorizontalResolution")
# else
	.value("HorizontalResolution", eglplus::SurfaceAttrib::HorizontalResolution)
# endif
#endif
#if defined EGL_VERTICAL_RESOLUTION
# if defined VerticalResolution
#  pragma push_macro("VerticalResolution")
#  undef VerticalResolution
	.value("VerticalResolution", eglplus::SurfaceAttrib::VerticalResolution)
#  pragma pop_macro("VerticalResolution")
# else
	.value("VerticalResolution", eglplus::SurfaceAttrib::VerticalResolution)
# endif
#endif
#if defined EGL_LARGEST_PBUFFER
# if defined LargestPbuffer
#  pragma push_macro("LargestPbuffer")
#  undef LargestPbuffer
	.value("LargestPbuffer", eglplus::SurfaceAttrib::LargestPbuffer)
#  pragma pop_macro("LargestPbuffer")
# else
	.value("LargestPbuffer", eglplus::SurfaceAttrib::LargestPbuffer)
# endif
#endif
#if defined EGL_MIPMAP_TEXTURE
# if defined MipmapTexture
#  pragma push_macro("MipmapTexture")
#  undef MipmapTexture
	.value("MipmapTexture", eglplus::SurfaceAttrib::MipmapTexture)
#  pragma pop_macro("MipmapTexture")
# else
	.value("MipmapTexture", eglplus::SurfaceAttrib::MipmapTexture)
# endif
#endif
#if defined EGL_MIPMAP_LEVEL
# if defined MipmapLevel
#  pragma push_macro("MipmapLevel")
#  undef MipmapLevel
	.value("MipmapLevel", eglplus::SurfaceAttrib::MipmapLevel)
#  pragma pop_macro("MipmapLevel")
# else
	.value("MipmapLevel", eglplus::SurfaceAttrib::MipmapLevel)
# endif
#endif
#if defined EGL_MULTISAMPLE_RESOLVE
# if defined MultisampleResolve
#  pragma push_macro("MultisampleResolve")
#  undef MultisampleResolve
	.value("MultisampleResolve", eglplus::SurfaceAttrib::MultisampleResolve)
#  pragma pop_macro("MultisampleResolve")
# else
	.value("MultisampleResolve", eglplus::SurfaceAttrib::MultisampleResolve)
# endif
#endif
#if defined EGL_PIXEL_ASPECT_RATIO
# if defined PixelAspectRatio
#  pragma push_macro("PixelAspectRatio")
#  undef PixelAspectRatio
	.value("PixelAspectRatio", eglplus::SurfaceAttrib::PixelAspectRatio)
#  pragma pop_macro("PixelAspectRatio")
# else
	.value("PixelAspectRatio", eglplus::SurfaceAttrib::PixelAspectRatio)
# endif
#endif
#if defined EGL_RENDER_BUFFER
# if defined RenderBuffer
#  pragma push_macro("RenderBuffer")
#  undef RenderBuffer
	.value("RenderBuffer", eglplus::SurfaceAttrib::RenderBuffer)
#  pragma pop_macro("RenderBuffer")
# else
	.value("RenderBuffer", eglplus::SurfaceAttrib::RenderBuffer)
# endif
#endif
#if defined EGL_SWAP_BEHAVIOR
# if defined SwapBehavior
#  pragma push_macro("SwapBehavior")
#  undef SwapBehavior
	.value("SwapBehavior", eglplus::SurfaceAttrib::SwapBehavior)
#  pragma pop_macro("SwapBehavior")
# else
	.value("SwapBehavior", eglplus::SurfaceAttrib::SwapBehavior)
# endif
#endif
#if defined EGL_TEXTURE_FORMAT
# if defined TextureFormat
#  pragma push_macro("TextureFormat")
#  undef TextureFormat
	.value("TextureFormat", eglplus::SurfaceAttrib::TextureFormat)
#  pragma pop_macro("TextureFormat")
# else
	.value("TextureFormat", eglplus::SurfaceAttrib::TextureFormat)
# endif
#endif
#if defined EGL_TEXTURE_TARGET
# if defined TextureTarget
#  pragma push_macro("TextureTarget")
#  undef TextureTarget
	.value("TextureTarget", eglplus::SurfaceAttrib::TextureTarget)
#  pragma pop_macro("TextureTarget")
# else
	.value("TextureTarget", eglplus::SurfaceAttrib::TextureTarget)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::SurfaceAttrib) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	eglplus_py_export_range<
		eglplus::aux::CastIterRange<
			const EGLenum*,
			eglplus::SurfaceAttrib
		>
	>("aux_CastIterRange_SurfaceAttrib");

	eglplus::aux::CastIterRange<
		const EGLenum*,
		eglplus::SurfaceAttrib
	> (*PEnumValueRange)(eglplus::SurfaceAttrib) =
		&eglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
