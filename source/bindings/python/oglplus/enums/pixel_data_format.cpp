/*
 *  .file oglplus/enums/pixel_data_format.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_data_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/pixel_data.hpp>

#include <boost/python.hpp>

void oglplus_py_pixel_data_format(void)
{
	boost::python::enum_<oglplus::PixelDataFormat>("PixelDataFormat")
#if defined GL_STENCIL_INDEX
# if defined StencilIndex
#  pragma push_macro("StencilIndex")
#  undef StencilIndex
	.value("StencilIndex", oglplus::PixelDataFormat::StencilIndex)
#  pragma pop_macro("StencilIndex")
# else
	.value("StencilIndex", oglplus::PixelDataFormat::StencilIndex)
# endif
#endif
#if defined GL_DEPTH_COMPONENT
# if defined DepthComponent
#  pragma push_macro("DepthComponent")
#  undef DepthComponent
	.value("DepthComponent", oglplus::PixelDataFormat::DepthComponent)
#  pragma pop_macro("DepthComponent")
# else
	.value("DepthComponent", oglplus::PixelDataFormat::DepthComponent)
# endif
#endif
#if defined GL_DEPTH_STENCIL
# if defined DepthStencil
#  pragma push_macro("DepthStencil")
#  undef DepthStencil
	.value("DepthStencil", oglplus::PixelDataFormat::DepthStencil)
#  pragma pop_macro("DepthStencil")
# else
	.value("DepthStencil", oglplus::PixelDataFormat::DepthStencil)
# endif
#endif
#if defined GL_RED
# if defined Red
#  pragma push_macro("Red")
#  undef Red
	.value("Red", oglplus::PixelDataFormat::Red)
#  pragma pop_macro("Red")
# else
	.value("Red", oglplus::PixelDataFormat::Red)
# endif
#endif
#if defined GL_GREEN
# if defined Green
#  pragma push_macro("Green")
#  undef Green
	.value("Green", oglplus::PixelDataFormat::Green)
#  pragma pop_macro("Green")
# else
	.value("Green", oglplus::PixelDataFormat::Green)
# endif
#endif
#if defined GL_BLUE
# if defined Blue
#  pragma push_macro("Blue")
#  undef Blue
	.value("Blue", oglplus::PixelDataFormat::Blue)
#  pragma pop_macro("Blue")
# else
	.value("Blue", oglplus::PixelDataFormat::Blue)
# endif
#endif
#if defined GL_RG
# if defined RG
#  pragma push_macro("RG")
#  undef RG
	.value("RG", oglplus::PixelDataFormat::RG)
#  pragma pop_macro("RG")
# else
	.value("RG", oglplus::PixelDataFormat::RG)
# endif
#endif
#if defined GL_RGB
# if defined RGB
#  pragma push_macro("RGB")
#  undef RGB
	.value("RGB", oglplus::PixelDataFormat::RGB)
#  pragma pop_macro("RGB")
# else
	.value("RGB", oglplus::PixelDataFormat::RGB)
# endif
#endif
#if defined GL_RGBA
# if defined RGBA
#  pragma push_macro("RGBA")
#  undef RGBA
	.value("RGBA", oglplus::PixelDataFormat::RGBA)
#  pragma pop_macro("RGBA")
# else
	.value("RGBA", oglplus::PixelDataFormat::RGBA)
# endif
#endif
#if defined GL_BGR
# if defined BGR
#  pragma push_macro("BGR")
#  undef BGR
	.value("BGR", oglplus::PixelDataFormat::BGR)
#  pragma pop_macro("BGR")
# else
	.value("BGR", oglplus::PixelDataFormat::BGR)
# endif
#endif
#if defined GL_BGRA
# if defined BGRA
#  pragma push_macro("BGRA")
#  undef BGRA
	.value("BGRA", oglplus::PixelDataFormat::BGRA)
#  pragma pop_macro("BGRA")
# else
	.value("BGRA", oglplus::PixelDataFormat::BGRA)
# endif
#endif
#if defined GL_RED_INTEGER
# if defined RedInteger
#  pragma push_macro("RedInteger")
#  undef RedInteger
	.value("RedInteger", oglplus::PixelDataFormat::RedInteger)
#  pragma pop_macro("RedInteger")
# else
	.value("RedInteger", oglplus::PixelDataFormat::RedInteger)
# endif
#endif
#if defined GL_GREEN_INTEGER
# if defined GreenInteger
#  pragma push_macro("GreenInteger")
#  undef GreenInteger
	.value("GreenInteger", oglplus::PixelDataFormat::GreenInteger)
#  pragma pop_macro("GreenInteger")
# else
	.value("GreenInteger", oglplus::PixelDataFormat::GreenInteger)
# endif
#endif
#if defined GL_BLUE_INTEGER
# if defined BlueInteger
#  pragma push_macro("BlueInteger")
#  undef BlueInteger
	.value("BlueInteger", oglplus::PixelDataFormat::BlueInteger)
#  pragma pop_macro("BlueInteger")
# else
	.value("BlueInteger", oglplus::PixelDataFormat::BlueInteger)
# endif
#endif
#if defined GL_RG_INTEGER
# if defined RGInteger
#  pragma push_macro("RGInteger")
#  undef RGInteger
	.value("RGInteger", oglplus::PixelDataFormat::RGInteger)
#  pragma pop_macro("RGInteger")
# else
	.value("RGInteger", oglplus::PixelDataFormat::RGInteger)
# endif
#endif
#if defined GL_RGB_INTEGER
# if defined RGBInteger
#  pragma push_macro("RGBInteger")
#  undef RGBInteger
	.value("RGBInteger", oglplus::PixelDataFormat::RGBInteger)
#  pragma pop_macro("RGBInteger")
# else
	.value("RGBInteger", oglplus::PixelDataFormat::RGBInteger)
# endif
#endif
#if defined GL_RGBA_INTEGER
# if defined RGBAInteger
#  pragma push_macro("RGBAInteger")
#  undef RGBAInteger
	.value("RGBAInteger", oglplus::PixelDataFormat::RGBAInteger)
#  pragma pop_macro("RGBAInteger")
# else
	.value("RGBAInteger", oglplus::PixelDataFormat::RGBAInteger)
# endif
#endif
#if defined GL_BGR_INTEGER
# if defined BGRInteger
#  pragma push_macro("BGRInteger")
#  undef BGRInteger
	.value("BGRInteger", oglplus::PixelDataFormat::BGRInteger)
#  pragma pop_macro("BGRInteger")
# else
	.value("BGRInteger", oglplus::PixelDataFormat::BGRInteger)
# endif
#endif
#if defined GL_BGRA_INTEGER
# if defined BGRAInteger
#  pragma push_macro("BGRAInteger")
#  undef BGRAInteger
	.value("BGRAInteger", oglplus::PixelDataFormat::BGRAInteger)
#  pragma pop_macro("BGRAInteger")
# else
	.value("BGRAInteger", oglplus::PixelDataFormat::BGRAInteger)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PixelDataFormat) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
