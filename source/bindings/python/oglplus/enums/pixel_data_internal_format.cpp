/*
 *  .file oglplus/enums/pixel_data_internal_format.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_data_internal_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/pixel_data.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_pixel_data_internal_format(void)
{
	boost::python::enum_<oglplus::PixelDataInternalFormat>("PixelDataInternalFormat")
#if defined GL_DEPTH_COMPONENT
# if defined DepthComponent
#  pragma push_macro("DepthComponent")
#  undef DepthComponent
	.value("DepthComponent", oglplus::PixelDataInternalFormat::DepthComponent)
#  pragma pop_macro("DepthComponent")
# else
	.value("DepthComponent", oglplus::PixelDataInternalFormat::DepthComponent)
# endif
#endif
#if defined GL_DEPTH_STENCIL
# if defined DepthStencil
#  pragma push_macro("DepthStencil")
#  undef DepthStencil
	.value("DepthStencil", oglplus::PixelDataInternalFormat::DepthStencil)
#  pragma pop_macro("DepthStencil")
# else
	.value("DepthStencil", oglplus::PixelDataInternalFormat::DepthStencil)
# endif
#endif
#if defined GL_RED
# if defined Red
#  pragma push_macro("Red")
#  undef Red
	.value("Red", oglplus::PixelDataInternalFormat::Red)
#  pragma pop_macro("Red")
# else
	.value("Red", oglplus::PixelDataInternalFormat::Red)
# endif
#endif
#if defined GL_RG
# if defined RG
#  pragma push_macro("RG")
#  undef RG
	.value("RG", oglplus::PixelDataInternalFormat::RG)
#  pragma pop_macro("RG")
# else
	.value("RG", oglplus::PixelDataInternalFormat::RG)
# endif
#endif
#if defined GL_RGB
# if defined RGB
#  pragma push_macro("RGB")
#  undef RGB
	.value("RGB", oglplus::PixelDataInternalFormat::RGB)
#  pragma pop_macro("RGB")
# else
	.value("RGB", oglplus::PixelDataInternalFormat::RGB)
# endif
#endif
#if defined GL_RGBA
# if defined RGBA
#  pragma push_macro("RGBA")
#  undef RGBA
	.value("RGBA", oglplus::PixelDataInternalFormat::RGBA)
#  pragma pop_macro("RGBA")
# else
	.value("RGBA", oglplus::PixelDataInternalFormat::RGBA)
# endif
#endif
#if defined GL_R8
# if defined R8
#  pragma push_macro("R8")
#  undef R8
	.value("R8", oglplus::PixelDataInternalFormat::R8)
#  pragma pop_macro("R8")
# else
	.value("R8", oglplus::PixelDataInternalFormat::R8)
# endif
#endif
#if defined GL_R8_SNORM
# if defined R8SNorm
#  pragma push_macro("R8SNorm")
#  undef R8SNorm
	.value("R8SNorm", oglplus::PixelDataInternalFormat::R8SNorm)
#  pragma pop_macro("R8SNorm")
# else
	.value("R8SNorm", oglplus::PixelDataInternalFormat::R8SNorm)
# endif
#endif
#if defined GL_R16
# if defined R16
#  pragma push_macro("R16")
#  undef R16
	.value("R16", oglplus::PixelDataInternalFormat::R16)
#  pragma pop_macro("R16")
# else
	.value("R16", oglplus::PixelDataInternalFormat::R16)
# endif
#endif
#if defined GL_R16_SNORM
# if defined R16SNorm
#  pragma push_macro("R16SNorm")
#  undef R16SNorm
	.value("R16SNorm", oglplus::PixelDataInternalFormat::R16SNorm)
#  pragma pop_macro("R16SNorm")
# else
	.value("R16SNorm", oglplus::PixelDataInternalFormat::R16SNorm)
# endif
#endif
#if defined GL_RG8
# if defined RG8
#  pragma push_macro("RG8")
#  undef RG8
	.value("RG8", oglplus::PixelDataInternalFormat::RG8)
#  pragma pop_macro("RG8")
# else
	.value("RG8", oglplus::PixelDataInternalFormat::RG8)
# endif
#endif
#if defined GL_RG8_SNORM
# if defined RG8SNorm
#  pragma push_macro("RG8SNorm")
#  undef RG8SNorm
	.value("RG8SNorm", oglplus::PixelDataInternalFormat::RG8SNorm)
#  pragma pop_macro("RG8SNorm")
# else
	.value("RG8SNorm", oglplus::PixelDataInternalFormat::RG8SNorm)
# endif
#endif
#if defined GL_RG16
# if defined RG16
#  pragma push_macro("RG16")
#  undef RG16
	.value("RG16", oglplus::PixelDataInternalFormat::RG16)
#  pragma pop_macro("RG16")
# else
	.value("RG16", oglplus::PixelDataInternalFormat::RG16)
# endif
#endif
#if defined GL_RG16_SNORM
# if defined RG16SNorm
#  pragma push_macro("RG16SNorm")
#  undef RG16SNorm
	.value("RG16SNorm", oglplus::PixelDataInternalFormat::RG16SNorm)
#  pragma pop_macro("RG16SNorm")
# else
	.value("RG16SNorm", oglplus::PixelDataInternalFormat::RG16SNorm)
# endif
#endif
#if defined GL_R3_G3_B2
# if defined R3G3B2
#  pragma push_macro("R3G3B2")
#  undef R3G3B2
	.value("R3G3B2", oglplus::PixelDataInternalFormat::R3G3B2)
#  pragma pop_macro("R3G3B2")
# else
	.value("R3G3B2", oglplus::PixelDataInternalFormat::R3G3B2)
# endif
#endif
#if defined GL_RGB4
# if defined RGB4
#  pragma push_macro("RGB4")
#  undef RGB4
	.value("RGB4", oglplus::PixelDataInternalFormat::RGB4)
#  pragma pop_macro("RGB4")
# else
	.value("RGB4", oglplus::PixelDataInternalFormat::RGB4)
# endif
#endif
#if defined GL_RGB5
# if defined RGB5
#  pragma push_macro("RGB5")
#  undef RGB5
	.value("RGB5", oglplus::PixelDataInternalFormat::RGB5)
#  pragma pop_macro("RGB5")
# else
	.value("RGB5", oglplus::PixelDataInternalFormat::RGB5)
# endif
#endif
#if defined GL_RGB8
# if defined RGB8
#  pragma push_macro("RGB8")
#  undef RGB8
	.value("RGB8", oglplus::PixelDataInternalFormat::RGB8)
#  pragma pop_macro("RGB8")
# else
	.value("RGB8", oglplus::PixelDataInternalFormat::RGB8)
# endif
#endif
#if defined GL_RGB8_SNORM
# if defined RGB8SNorm
#  pragma push_macro("RGB8SNorm")
#  undef RGB8SNorm
	.value("RGB8SNorm", oglplus::PixelDataInternalFormat::RGB8SNorm)
#  pragma pop_macro("RGB8SNorm")
# else
	.value("RGB8SNorm", oglplus::PixelDataInternalFormat::RGB8SNorm)
# endif
#endif
#if defined GL_RGB10
# if defined RGB10
#  pragma push_macro("RGB10")
#  undef RGB10
	.value("RGB10", oglplus::PixelDataInternalFormat::RGB10)
#  pragma pop_macro("RGB10")
# else
	.value("RGB10", oglplus::PixelDataInternalFormat::RGB10)
# endif
#endif
#if defined GL_RGB12
# if defined RGB12
#  pragma push_macro("RGB12")
#  undef RGB12
	.value("RGB12", oglplus::PixelDataInternalFormat::RGB12)
#  pragma pop_macro("RGB12")
# else
	.value("RGB12", oglplus::PixelDataInternalFormat::RGB12)
# endif
#endif
#if defined GL_RGB16
# if defined RGB16
#  pragma push_macro("RGB16")
#  undef RGB16
	.value("RGB16", oglplus::PixelDataInternalFormat::RGB16)
#  pragma pop_macro("RGB16")
# else
	.value("RGB16", oglplus::PixelDataInternalFormat::RGB16)
# endif
#endif
#if defined GL_RGB16_SNORM
# if defined RGB16SNorm
#  pragma push_macro("RGB16SNorm")
#  undef RGB16SNorm
	.value("RGB16SNorm", oglplus::PixelDataInternalFormat::RGB16SNorm)
#  pragma pop_macro("RGB16SNorm")
# else
	.value("RGB16SNorm", oglplus::PixelDataInternalFormat::RGB16SNorm)
# endif
#endif
#if defined GL_RGBA2
# if defined RGBA2
#  pragma push_macro("RGBA2")
#  undef RGBA2
	.value("RGBA2", oglplus::PixelDataInternalFormat::RGBA2)
#  pragma pop_macro("RGBA2")
# else
	.value("RGBA2", oglplus::PixelDataInternalFormat::RGBA2)
# endif
#endif
#if defined GL_RGBA4
# if defined RGBA4
#  pragma push_macro("RGBA4")
#  undef RGBA4
	.value("RGBA4", oglplus::PixelDataInternalFormat::RGBA4)
#  pragma pop_macro("RGBA4")
# else
	.value("RGBA4", oglplus::PixelDataInternalFormat::RGBA4)
# endif
#endif
#if defined GL_RGB5_A1
# if defined RGB5A1
#  pragma push_macro("RGB5A1")
#  undef RGB5A1
	.value("RGB5A1", oglplus::PixelDataInternalFormat::RGB5A1)
#  pragma pop_macro("RGB5A1")
# else
	.value("RGB5A1", oglplus::PixelDataInternalFormat::RGB5A1)
# endif
#endif
#if defined GL_RGBA8
# if defined RGBA8
#  pragma push_macro("RGBA8")
#  undef RGBA8
	.value("RGBA8", oglplus::PixelDataInternalFormat::RGBA8)
#  pragma pop_macro("RGBA8")
# else
	.value("RGBA8", oglplus::PixelDataInternalFormat::RGBA8)
# endif
#endif
#if defined GL_RGBA8_SNORM
# if defined RGBA8SNorm
#  pragma push_macro("RGBA8SNorm")
#  undef RGBA8SNorm
	.value("RGBA8SNorm", oglplus::PixelDataInternalFormat::RGBA8SNorm)
#  pragma pop_macro("RGBA8SNorm")
# else
	.value("RGBA8SNorm", oglplus::PixelDataInternalFormat::RGBA8SNorm)
# endif
#endif
#if defined GL_RGB10_A2
# if defined RGB10A2
#  pragma push_macro("RGB10A2")
#  undef RGB10A2
	.value("RGB10A2", oglplus::PixelDataInternalFormat::RGB10A2)
#  pragma pop_macro("RGB10A2")
# else
	.value("RGB10A2", oglplus::PixelDataInternalFormat::RGB10A2)
# endif
#endif
#if defined GL_RGB10_A2UI
# if defined RGB10A2UI
#  pragma push_macro("RGB10A2UI")
#  undef RGB10A2UI
	.value("RGB10A2UI", oglplus::PixelDataInternalFormat::RGB10A2UI)
#  pragma pop_macro("RGB10A2UI")
# else
	.value("RGB10A2UI", oglplus::PixelDataInternalFormat::RGB10A2UI)
# endif
#endif
#if defined GL_RGBA12
# if defined RGBA12
#  pragma push_macro("RGBA12")
#  undef RGBA12
	.value("RGBA12", oglplus::PixelDataInternalFormat::RGBA12)
#  pragma pop_macro("RGBA12")
# else
	.value("RGBA12", oglplus::PixelDataInternalFormat::RGBA12)
# endif
#endif
#if defined GL_RGBA16
# if defined RGBA16
#  pragma push_macro("RGBA16")
#  undef RGBA16
	.value("RGBA16", oglplus::PixelDataInternalFormat::RGBA16)
#  pragma pop_macro("RGBA16")
# else
	.value("RGBA16", oglplus::PixelDataInternalFormat::RGBA16)
# endif
#endif
#if defined GL_RGBA16_SNORM
# if defined RGBA16SNorm
#  pragma push_macro("RGBA16SNorm")
#  undef RGBA16SNorm
	.value("RGBA16SNorm", oglplus::PixelDataInternalFormat::RGBA16SNorm)
#  pragma pop_macro("RGBA16SNorm")
# else
	.value("RGBA16SNorm", oglplus::PixelDataInternalFormat::RGBA16SNorm)
# endif
#endif
#if defined GL_SRGB8
# if defined SRGB8
#  pragma push_macro("SRGB8")
#  undef SRGB8
	.value("SRGB8", oglplus::PixelDataInternalFormat::SRGB8)
#  pragma pop_macro("SRGB8")
# else
	.value("SRGB8", oglplus::PixelDataInternalFormat::SRGB8)
# endif
#endif
#if defined GL_SRGB8_ALPHA8
# if defined SRGB8Alpha8
#  pragma push_macro("SRGB8Alpha8")
#  undef SRGB8Alpha8
	.value("SRGB8Alpha8", oglplus::PixelDataInternalFormat::SRGB8Alpha8)
#  pragma pop_macro("SRGB8Alpha8")
# else
	.value("SRGB8Alpha8", oglplus::PixelDataInternalFormat::SRGB8Alpha8)
# endif
#endif
#if defined GL_R16F
# if defined R16F
#  pragma push_macro("R16F")
#  undef R16F
	.value("R16F", oglplus::PixelDataInternalFormat::R16F)
#  pragma pop_macro("R16F")
# else
	.value("R16F", oglplus::PixelDataInternalFormat::R16F)
# endif
#endif
#if defined GL_RG16F
# if defined RG16F
#  pragma push_macro("RG16F")
#  undef RG16F
	.value("RG16F", oglplus::PixelDataInternalFormat::RG16F)
#  pragma pop_macro("RG16F")
# else
	.value("RG16F", oglplus::PixelDataInternalFormat::RG16F)
# endif
#endif
#if defined GL_RGB16F
# if defined RGB16F
#  pragma push_macro("RGB16F")
#  undef RGB16F
	.value("RGB16F", oglplus::PixelDataInternalFormat::RGB16F)
#  pragma pop_macro("RGB16F")
# else
	.value("RGB16F", oglplus::PixelDataInternalFormat::RGB16F)
# endif
#endif
#if defined GL_RGBA16F
# if defined RGBA16F
#  pragma push_macro("RGBA16F")
#  undef RGBA16F
	.value("RGBA16F", oglplus::PixelDataInternalFormat::RGBA16F)
#  pragma pop_macro("RGBA16F")
# else
	.value("RGBA16F", oglplus::PixelDataInternalFormat::RGBA16F)
# endif
#endif
#if defined GL_R32F
# if defined R32F
#  pragma push_macro("R32F")
#  undef R32F
	.value("R32F", oglplus::PixelDataInternalFormat::R32F)
#  pragma pop_macro("R32F")
# else
	.value("R32F", oglplus::PixelDataInternalFormat::R32F)
# endif
#endif
#if defined GL_RG32F
# if defined RG32F
#  pragma push_macro("RG32F")
#  undef RG32F
	.value("RG32F", oglplus::PixelDataInternalFormat::RG32F)
#  pragma pop_macro("RG32F")
# else
	.value("RG32F", oglplus::PixelDataInternalFormat::RG32F)
# endif
#endif
#if defined GL_RGB32F
# if defined RGB32F
#  pragma push_macro("RGB32F")
#  undef RGB32F
	.value("RGB32F", oglplus::PixelDataInternalFormat::RGB32F)
#  pragma pop_macro("RGB32F")
# else
	.value("RGB32F", oglplus::PixelDataInternalFormat::RGB32F)
# endif
#endif
#if defined GL_RGBA32F
# if defined RGBA32F
#  pragma push_macro("RGBA32F")
#  undef RGBA32F
	.value("RGBA32F", oglplus::PixelDataInternalFormat::RGBA32F)
#  pragma pop_macro("RGBA32F")
# else
	.value("RGBA32F", oglplus::PixelDataInternalFormat::RGBA32F)
# endif
#endif
#if defined GL_R11F_G11F_B10F
# if defined R11FG11FB10F
#  pragma push_macro("R11FG11FB10F")
#  undef R11FG11FB10F
	.value("R11FG11FB10F", oglplus::PixelDataInternalFormat::R11FG11FB10F)
#  pragma pop_macro("R11FG11FB10F")
# else
	.value("R11FG11FB10F", oglplus::PixelDataInternalFormat::R11FG11FB10F)
# endif
#endif
#if defined GL_RGB9_E5
# if defined RGB9E5
#  pragma push_macro("RGB9E5")
#  undef RGB9E5
	.value("RGB9E5", oglplus::PixelDataInternalFormat::RGB9E5)
#  pragma pop_macro("RGB9E5")
# else
	.value("RGB9E5", oglplus::PixelDataInternalFormat::RGB9E5)
# endif
#endif
#if defined GL_R8I
# if defined R8I
#  pragma push_macro("R8I")
#  undef R8I
	.value("R8I", oglplus::PixelDataInternalFormat::R8I)
#  pragma pop_macro("R8I")
# else
	.value("R8I", oglplus::PixelDataInternalFormat::R8I)
# endif
#endif
#if defined GL_R8UI
# if defined R8UI
#  pragma push_macro("R8UI")
#  undef R8UI
	.value("R8UI", oglplus::PixelDataInternalFormat::R8UI)
#  pragma pop_macro("R8UI")
# else
	.value("R8UI", oglplus::PixelDataInternalFormat::R8UI)
# endif
#endif
#if defined GL_R16I
# if defined R16I
#  pragma push_macro("R16I")
#  undef R16I
	.value("R16I", oglplus::PixelDataInternalFormat::R16I)
#  pragma pop_macro("R16I")
# else
	.value("R16I", oglplus::PixelDataInternalFormat::R16I)
# endif
#endif
#if defined GL_R16UI
# if defined R16UI
#  pragma push_macro("R16UI")
#  undef R16UI
	.value("R16UI", oglplus::PixelDataInternalFormat::R16UI)
#  pragma pop_macro("R16UI")
# else
	.value("R16UI", oglplus::PixelDataInternalFormat::R16UI)
# endif
#endif
#if defined GL_R32I
# if defined R32I
#  pragma push_macro("R32I")
#  undef R32I
	.value("R32I", oglplus::PixelDataInternalFormat::R32I)
#  pragma pop_macro("R32I")
# else
	.value("R32I", oglplus::PixelDataInternalFormat::R32I)
# endif
#endif
#if defined GL_R32UI
# if defined R32UI
#  pragma push_macro("R32UI")
#  undef R32UI
	.value("R32UI", oglplus::PixelDataInternalFormat::R32UI)
#  pragma pop_macro("R32UI")
# else
	.value("R32UI", oglplus::PixelDataInternalFormat::R32UI)
# endif
#endif
#if defined GL_RG8I
# if defined RG8I
#  pragma push_macro("RG8I")
#  undef RG8I
	.value("RG8I", oglplus::PixelDataInternalFormat::RG8I)
#  pragma pop_macro("RG8I")
# else
	.value("RG8I", oglplus::PixelDataInternalFormat::RG8I)
# endif
#endif
#if defined GL_RG8UI
# if defined RG8UI
#  pragma push_macro("RG8UI")
#  undef RG8UI
	.value("RG8UI", oglplus::PixelDataInternalFormat::RG8UI)
#  pragma pop_macro("RG8UI")
# else
	.value("RG8UI", oglplus::PixelDataInternalFormat::RG8UI)
# endif
#endif
#if defined GL_RG16I
# if defined RG16I
#  pragma push_macro("RG16I")
#  undef RG16I
	.value("RG16I", oglplus::PixelDataInternalFormat::RG16I)
#  pragma pop_macro("RG16I")
# else
	.value("RG16I", oglplus::PixelDataInternalFormat::RG16I)
# endif
#endif
#if defined GL_RG16UI
# if defined RG16UI
#  pragma push_macro("RG16UI")
#  undef RG16UI
	.value("RG16UI", oglplus::PixelDataInternalFormat::RG16UI)
#  pragma pop_macro("RG16UI")
# else
	.value("RG16UI", oglplus::PixelDataInternalFormat::RG16UI)
# endif
#endif
#if defined GL_RG32I
# if defined RG32I
#  pragma push_macro("RG32I")
#  undef RG32I
	.value("RG32I", oglplus::PixelDataInternalFormat::RG32I)
#  pragma pop_macro("RG32I")
# else
	.value("RG32I", oglplus::PixelDataInternalFormat::RG32I)
# endif
#endif
#if defined GL_RG32UI
# if defined RG32UI
#  pragma push_macro("RG32UI")
#  undef RG32UI
	.value("RG32UI", oglplus::PixelDataInternalFormat::RG32UI)
#  pragma pop_macro("RG32UI")
# else
	.value("RG32UI", oglplus::PixelDataInternalFormat::RG32UI)
# endif
#endif
#if defined GL_RGB8I
# if defined RGB8I
#  pragma push_macro("RGB8I")
#  undef RGB8I
	.value("RGB8I", oglplus::PixelDataInternalFormat::RGB8I)
#  pragma pop_macro("RGB8I")
# else
	.value("RGB8I", oglplus::PixelDataInternalFormat::RGB8I)
# endif
#endif
#if defined GL_RGB8UI
# if defined RGB8UI
#  pragma push_macro("RGB8UI")
#  undef RGB8UI
	.value("RGB8UI", oglplus::PixelDataInternalFormat::RGB8UI)
#  pragma pop_macro("RGB8UI")
# else
	.value("RGB8UI", oglplus::PixelDataInternalFormat::RGB8UI)
# endif
#endif
#if defined GL_RGB16I
# if defined RGB16I
#  pragma push_macro("RGB16I")
#  undef RGB16I
	.value("RGB16I", oglplus::PixelDataInternalFormat::RGB16I)
#  pragma pop_macro("RGB16I")
# else
	.value("RGB16I", oglplus::PixelDataInternalFormat::RGB16I)
# endif
#endif
#if defined GL_RGB16UI
# if defined RGB16UI
#  pragma push_macro("RGB16UI")
#  undef RGB16UI
	.value("RGB16UI", oglplus::PixelDataInternalFormat::RGB16UI)
#  pragma pop_macro("RGB16UI")
# else
	.value("RGB16UI", oglplus::PixelDataInternalFormat::RGB16UI)
# endif
#endif
#if defined GL_RGB32I
# if defined RGB32I
#  pragma push_macro("RGB32I")
#  undef RGB32I
	.value("RGB32I", oglplus::PixelDataInternalFormat::RGB32I)
#  pragma pop_macro("RGB32I")
# else
	.value("RGB32I", oglplus::PixelDataInternalFormat::RGB32I)
# endif
#endif
#if defined GL_RGB32UI
# if defined RGB32UI
#  pragma push_macro("RGB32UI")
#  undef RGB32UI
	.value("RGB32UI", oglplus::PixelDataInternalFormat::RGB32UI)
#  pragma pop_macro("RGB32UI")
# else
	.value("RGB32UI", oglplus::PixelDataInternalFormat::RGB32UI)
# endif
#endif
#if defined GL_RGBA8I
# if defined RGBA8I
#  pragma push_macro("RGBA8I")
#  undef RGBA8I
	.value("RGBA8I", oglplus::PixelDataInternalFormat::RGBA8I)
#  pragma pop_macro("RGBA8I")
# else
	.value("RGBA8I", oglplus::PixelDataInternalFormat::RGBA8I)
# endif
#endif
#if defined GL_RGBA8UI
# if defined RGBA8UI
#  pragma push_macro("RGBA8UI")
#  undef RGBA8UI
	.value("RGBA8UI", oglplus::PixelDataInternalFormat::RGBA8UI)
#  pragma pop_macro("RGBA8UI")
# else
	.value("RGBA8UI", oglplus::PixelDataInternalFormat::RGBA8UI)
# endif
#endif
#if defined GL_RGBA16I
# if defined RGBA16I
#  pragma push_macro("RGBA16I")
#  undef RGBA16I
	.value("RGBA16I", oglplus::PixelDataInternalFormat::RGBA16I)
#  pragma pop_macro("RGBA16I")
# else
	.value("RGBA16I", oglplus::PixelDataInternalFormat::RGBA16I)
# endif
#endif
#if defined GL_RGBA16UI
# if defined RGBA16UI
#  pragma push_macro("RGBA16UI")
#  undef RGBA16UI
	.value("RGBA16UI", oglplus::PixelDataInternalFormat::RGBA16UI)
#  pragma pop_macro("RGBA16UI")
# else
	.value("RGBA16UI", oglplus::PixelDataInternalFormat::RGBA16UI)
# endif
#endif
#if defined GL_RGBA32I
# if defined RGBA32I
#  pragma push_macro("RGBA32I")
#  undef RGBA32I
	.value("RGBA32I", oglplus::PixelDataInternalFormat::RGBA32I)
#  pragma pop_macro("RGBA32I")
# else
	.value("RGBA32I", oglplus::PixelDataInternalFormat::RGBA32I)
# endif
#endif
#if defined GL_RGBA32UI
# if defined RGBA32UI
#  pragma push_macro("RGBA32UI")
#  undef RGBA32UI
	.value("RGBA32UI", oglplus::PixelDataInternalFormat::RGBA32UI)
#  pragma pop_macro("RGBA32UI")
# else
	.value("RGBA32UI", oglplus::PixelDataInternalFormat::RGBA32UI)
# endif
#endif
#if defined GL_DEPTH_COMPONENT16
# if defined DepthComponent16
#  pragma push_macro("DepthComponent16")
#  undef DepthComponent16
	.value("DepthComponent16", oglplus::PixelDataInternalFormat::DepthComponent16)
#  pragma pop_macro("DepthComponent16")
# else
	.value("DepthComponent16", oglplus::PixelDataInternalFormat::DepthComponent16)
# endif
#endif
#if defined GL_DEPTH_COMPONENT24
# if defined DepthComponent24
#  pragma push_macro("DepthComponent24")
#  undef DepthComponent24
	.value("DepthComponent24", oglplus::PixelDataInternalFormat::DepthComponent24)
#  pragma pop_macro("DepthComponent24")
# else
	.value("DepthComponent24", oglplus::PixelDataInternalFormat::DepthComponent24)
# endif
#endif
#if defined GL_DEPTH_COMPONENT32
# if defined DepthComponent32
#  pragma push_macro("DepthComponent32")
#  undef DepthComponent32
	.value("DepthComponent32", oglplus::PixelDataInternalFormat::DepthComponent32)
#  pragma pop_macro("DepthComponent32")
# else
	.value("DepthComponent32", oglplus::PixelDataInternalFormat::DepthComponent32)
# endif
#endif
#if defined GL_DEPTH_COMPONENT32F
# if defined DepthComponent32F
#  pragma push_macro("DepthComponent32F")
#  undef DepthComponent32F
	.value("DepthComponent32F", oglplus::PixelDataInternalFormat::DepthComponent32F)
#  pragma pop_macro("DepthComponent32F")
# else
	.value("DepthComponent32F", oglplus::PixelDataInternalFormat::DepthComponent32F)
# endif
#endif
#if defined GL_DEPTH24_STENCIL8
# if defined Depth24Stencil8
#  pragma push_macro("Depth24Stencil8")
#  undef Depth24Stencil8
	.value("Depth24Stencil8", oglplus::PixelDataInternalFormat::Depth24Stencil8)
#  pragma pop_macro("Depth24Stencil8")
# else
	.value("Depth24Stencil8", oglplus::PixelDataInternalFormat::Depth24Stencil8)
# endif
#endif
#if defined GL_DEPTH32F_STENCIL8
# if defined Depth32fStencil8
#  pragma push_macro("Depth32fStencil8")
#  undef Depth32fStencil8
	.value("Depth32fStencil8", oglplus::PixelDataInternalFormat::Depth32fStencil8)
#  pragma pop_macro("Depth32fStencil8")
# else
	.value("Depth32fStencil8", oglplus::PixelDataInternalFormat::Depth32fStencil8)
# endif
#endif
#if defined GL_COMPRESSED_RED
# if defined CompressedRed
#  pragma push_macro("CompressedRed")
#  undef CompressedRed
	.value("CompressedRed", oglplus::PixelDataInternalFormat::CompressedRed)
#  pragma pop_macro("CompressedRed")
# else
	.value("CompressedRed", oglplus::PixelDataInternalFormat::CompressedRed)
# endif
#endif
#if defined GL_COMPRESSED_RG
# if defined CompressedRG
#  pragma push_macro("CompressedRG")
#  undef CompressedRG
	.value("CompressedRG", oglplus::PixelDataInternalFormat::CompressedRG)
#  pragma pop_macro("CompressedRG")
# else
	.value("CompressedRG", oglplus::PixelDataInternalFormat::CompressedRG)
# endif
#endif
#if defined GL_COMPRESSED_RGB
# if defined CompressedRGB
#  pragma push_macro("CompressedRGB")
#  undef CompressedRGB
	.value("CompressedRGB", oglplus::PixelDataInternalFormat::CompressedRGB)
#  pragma pop_macro("CompressedRGB")
# else
	.value("CompressedRGB", oglplus::PixelDataInternalFormat::CompressedRGB)
# endif
#endif
#if defined GL_COMPRESSED_RGBA
# if defined CompressedRGBA
#  pragma push_macro("CompressedRGBA")
#  undef CompressedRGBA
	.value("CompressedRGBA", oglplus::PixelDataInternalFormat::CompressedRGBA)
#  pragma pop_macro("CompressedRGBA")
# else
	.value("CompressedRGBA", oglplus::PixelDataInternalFormat::CompressedRGBA)
# endif
#endif
#if defined GL_COMPRESSED_SRGB
# if defined CompressedSRGB
#  pragma push_macro("CompressedSRGB")
#  undef CompressedSRGB
	.value("CompressedSRGB", oglplus::PixelDataInternalFormat::CompressedSRGB)
#  pragma pop_macro("CompressedSRGB")
# else
	.value("CompressedSRGB", oglplus::PixelDataInternalFormat::CompressedSRGB)
# endif
#endif
#if defined GL_COMPRESSED_SRGB_ALPHA
# if defined CompressedSRGBAlpha
#  pragma push_macro("CompressedSRGBAlpha")
#  undef CompressedSRGBAlpha
	.value("CompressedSRGBAlpha", oglplus::PixelDataInternalFormat::CompressedSRGBAlpha)
#  pragma pop_macro("CompressedSRGBAlpha")
# else
	.value("CompressedSRGBAlpha", oglplus::PixelDataInternalFormat::CompressedSRGBAlpha)
# endif
#endif
#if defined GL_COMPRESSED_RED_RGTC1
# if defined CompressedRedRGTC1
#  pragma push_macro("CompressedRedRGTC1")
#  undef CompressedRedRGTC1
	.value("CompressedRedRGTC1", oglplus::PixelDataInternalFormat::CompressedRedRGTC1)
#  pragma pop_macro("CompressedRedRGTC1")
# else
	.value("CompressedRedRGTC1", oglplus::PixelDataInternalFormat::CompressedRedRGTC1)
# endif
#endif
#if defined GL_COMPRESSED_SIGNED_RED_RGTC1
# if defined CompressedSignedRedRGTC1
#  pragma push_macro("CompressedSignedRedRGTC1")
#  undef CompressedSignedRedRGTC1
	.value("CompressedSignedRedRGTC1", oglplus::PixelDataInternalFormat::CompressedSignedRedRGTC1)
#  pragma pop_macro("CompressedSignedRedRGTC1")
# else
	.value("CompressedSignedRedRGTC1", oglplus::PixelDataInternalFormat::CompressedSignedRedRGTC1)
# endif
#endif
#if defined GL_COMPRESSED_RG_RGTC2
# if defined CompressedRGRGTC2
#  pragma push_macro("CompressedRGRGTC2")
#  undef CompressedRGRGTC2
	.value("CompressedRGRGTC2", oglplus::PixelDataInternalFormat::CompressedRGRGTC2)
#  pragma pop_macro("CompressedRGRGTC2")
# else
	.value("CompressedRGRGTC2", oglplus::PixelDataInternalFormat::CompressedRGRGTC2)
# endif
#endif
#if defined GL_COMPRESSED_SIGNED_RG_RGTC2
# if defined CompressedSignedRGRGTC2
#  pragma push_macro("CompressedSignedRGRGTC2")
#  undef CompressedSignedRGRGTC2
	.value("CompressedSignedRGRGTC2", oglplus::PixelDataInternalFormat::CompressedSignedRGRGTC2)
#  pragma pop_macro("CompressedSignedRGRGTC2")
# else
	.value("CompressedSignedRGRGTC2", oglplus::PixelDataInternalFormat::CompressedSignedRGRGTC2)
# endif
#endif
#if defined GL_COMPRESSED_RGBA_BPTC_UNORM
# if defined CompressedRGBABPTCUNorm
#  pragma push_macro("CompressedRGBABPTCUNorm")
#  undef CompressedRGBABPTCUNorm
	.value("CompressedRGBABPTCUNorm", oglplus::PixelDataInternalFormat::CompressedRGBABPTCUNorm)
#  pragma pop_macro("CompressedRGBABPTCUNorm")
# else
	.value("CompressedRGBABPTCUNorm", oglplus::PixelDataInternalFormat::CompressedRGBABPTCUNorm)
# endif
#endif
#if defined GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM
# if defined CompressedSRGBAlphaBPTCUNorm
#  pragma push_macro("CompressedSRGBAlphaBPTCUNorm")
#  undef CompressedSRGBAlphaBPTCUNorm
	.value("CompressedSRGBAlphaBPTCUNorm", oglplus::PixelDataInternalFormat::CompressedSRGBAlphaBPTCUNorm)
#  pragma pop_macro("CompressedSRGBAlphaBPTCUNorm")
# else
	.value("CompressedSRGBAlphaBPTCUNorm", oglplus::PixelDataInternalFormat::CompressedSRGBAlphaBPTCUNorm)
# endif
#endif
#if defined GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT
# if defined CompressedRGBBPTCSignedFloat
#  pragma push_macro("CompressedRGBBPTCSignedFloat")
#  undef CompressedRGBBPTCSignedFloat
	.value("CompressedRGBBPTCSignedFloat", oglplus::PixelDataInternalFormat::CompressedRGBBPTCSignedFloat)
#  pragma pop_macro("CompressedRGBBPTCSignedFloat")
# else
	.value("CompressedRGBBPTCSignedFloat", oglplus::PixelDataInternalFormat::CompressedRGBBPTCSignedFloat)
# endif
#endif
#if defined GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
# if defined CompressedRGBBPTCUnsignedFloat
#  pragma push_macro("CompressedRGBBPTCUnsignedFloat")
#  undef CompressedRGBBPTCUnsignedFloat
	.value("CompressedRGBBPTCUnsignedFloat", oglplus::PixelDataInternalFormat::CompressedRGBBPTCUnsignedFloat)
#  pragma pop_macro("CompressedRGBBPTCUnsignedFloat")
# else
	.value("CompressedRGBBPTCUnsignedFloat", oglplus::PixelDataInternalFormat::CompressedRGBBPTCUnsignedFloat)
# endif
#endif
#if defined GL_COMPRESSED_RGB8_ETC2
# if defined CompressedRGB8ETC2
#  pragma push_macro("CompressedRGB8ETC2")
#  undef CompressedRGB8ETC2
	.value("CompressedRGB8ETC2", oglplus::PixelDataInternalFormat::CompressedRGB8ETC2)
#  pragma pop_macro("CompressedRGB8ETC2")
# else
	.value("CompressedRGB8ETC2", oglplus::PixelDataInternalFormat::CompressedRGB8ETC2)
# endif
#endif
#if defined GL_COMPRESSED_SRGB8_ETC2
# if defined CompressedSRGB8ETC2
#  pragma push_macro("CompressedSRGB8ETC2")
#  undef CompressedSRGB8ETC2
	.value("CompressedSRGB8ETC2", oglplus::PixelDataInternalFormat::CompressedSRGB8ETC2)
#  pragma pop_macro("CompressedSRGB8ETC2")
# else
	.value("CompressedSRGB8ETC2", oglplus::PixelDataInternalFormat::CompressedSRGB8ETC2)
# endif
#endif
#if defined GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
# if defined CompressedRGB8PunchthroughAlpha1ETC2
#  pragma push_macro("CompressedRGB8PunchthroughAlpha1ETC2")
#  undef CompressedRGB8PunchthroughAlpha1ETC2
	.value("CompressedRGB8PunchthroughAlpha1ETC2", oglplus::PixelDataInternalFormat::CompressedRGB8PunchthroughAlpha1ETC2)
#  pragma pop_macro("CompressedRGB8PunchthroughAlpha1ETC2")
# else
	.value("CompressedRGB8PunchthroughAlpha1ETC2", oglplus::PixelDataInternalFormat::CompressedRGB8PunchthroughAlpha1ETC2)
# endif
#endif
#if defined GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
# if defined CompressedSRGB8PunchthroughAlpha1ETC2
#  pragma push_macro("CompressedSRGB8PunchthroughAlpha1ETC2")
#  undef CompressedSRGB8PunchthroughAlpha1ETC2
	.value("CompressedSRGB8PunchthroughAlpha1ETC2", oglplus::PixelDataInternalFormat::CompressedSRGB8PunchthroughAlpha1ETC2)
#  pragma pop_macro("CompressedSRGB8PunchthroughAlpha1ETC2")
# else
	.value("CompressedSRGB8PunchthroughAlpha1ETC2", oglplus::PixelDataInternalFormat::CompressedSRGB8PunchthroughAlpha1ETC2)
# endif
#endif
#if defined GL_COMPRESSED_RGBA8_ETC2_EAC
# if defined CompressedETC2EAC
#  pragma push_macro("CompressedETC2EAC")
#  undef CompressedETC2EAC
	.value("CompressedETC2EAC", oglplus::PixelDataInternalFormat::CompressedETC2EAC)
#  pragma pop_macro("CompressedETC2EAC")
# else
	.value("CompressedETC2EAC", oglplus::PixelDataInternalFormat::CompressedETC2EAC)
# endif
#endif
#if defined GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
# if defined CompressedSRGB8Alpha8ETC2EAC
#  pragma push_macro("CompressedSRGB8Alpha8ETC2EAC")
#  undef CompressedSRGB8Alpha8ETC2EAC
	.value("CompressedSRGB8Alpha8ETC2EAC", oglplus::PixelDataInternalFormat::CompressedSRGB8Alpha8ETC2EAC)
#  pragma pop_macro("CompressedSRGB8Alpha8ETC2EAC")
# else
	.value("CompressedSRGB8Alpha8ETC2EAC", oglplus::PixelDataInternalFormat::CompressedSRGB8Alpha8ETC2EAC)
# endif
#endif
#if defined GL_COMPRESSED_R11_EAC
# if defined CompressedR11EAC
#  pragma push_macro("CompressedR11EAC")
#  undef CompressedR11EAC
	.value("CompressedR11EAC", oglplus::PixelDataInternalFormat::CompressedR11EAC)
#  pragma pop_macro("CompressedR11EAC")
# else
	.value("CompressedR11EAC", oglplus::PixelDataInternalFormat::CompressedR11EAC)
# endif
#endif
#if defined GL_COMPRESSED_SIGNED_R11_EAC
# if defined CompressedSignedR11EAC
#  pragma push_macro("CompressedSignedR11EAC")
#  undef CompressedSignedR11EAC
	.value("CompressedSignedR11EAC", oglplus::PixelDataInternalFormat::CompressedSignedR11EAC)
#  pragma pop_macro("CompressedSignedR11EAC")
# else
	.value("CompressedSignedR11EAC", oglplus::PixelDataInternalFormat::CompressedSignedR11EAC)
# endif
#endif
#if defined GL_COMPRESSED_RG11_EAC
# if defined CompressedRG11EAC
#  pragma push_macro("CompressedRG11EAC")
#  undef CompressedRG11EAC
	.value("CompressedRG11EAC", oglplus::PixelDataInternalFormat::CompressedRG11EAC)
#  pragma pop_macro("CompressedRG11EAC")
# else
	.value("CompressedRG11EAC", oglplus::PixelDataInternalFormat::CompressedRG11EAC)
# endif
#endif
#if defined GL_COMPRESSED_SIGNED_RG11_EAC
# if defined CompressedSignedRG11EAC
#  pragma push_macro("CompressedSignedRG11EAC")
#  undef CompressedSignedRG11EAC
	.value("CompressedSignedRG11EAC", oglplus::PixelDataInternalFormat::CompressedSignedRG11EAC)
#  pragma pop_macro("CompressedSignedRG11EAC")
# else
	.value("CompressedSignedRG11EAC", oglplus::PixelDataInternalFormat::CompressedSignedRG11EAC)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PixelDataInternalFormat) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::PixelDataInternalFormat
		>
	>("aux_CastIterRange_PixelDataInternalFormat");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::PixelDataInternalFormat
	> (*PEnumValueRange)(oglplus::PixelDataInternalFormat) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
