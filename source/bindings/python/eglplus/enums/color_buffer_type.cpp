/*
 *  .file eglplus/enums/color_buffer_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/eglplus/color_buffer_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eglplus/egl.hpp>
#include <eglplus/color_buffer_type.hpp>

#include <boost/python.hpp>

void eglplus_py_color_buffer_type(void)
{
	boost::python::enum_<eglplus::ColorBufferType>("ColorBufferType")
#if defined EGL_RGB_BUFFER
# if defined RGBBuffer
#  pragma push_macro("RGBBuffer")
#  undef RGBBuffer
	.value("RGBBuffer", eglplus::ColorBufferType::RGBBuffer)
#  pragma pop_macro("RGBBuffer")
# else
	.value("RGBBuffer", eglplus::ColorBufferType::RGBBuffer)
# endif
#endif
#if defined EGL_LUMINANCE_BUFFER
# if defined LuminanceBuffer
#  pragma push_macro("LuminanceBuffer")
#  undef LuminanceBuffer
	.value("LuminanceBuffer", eglplus::ColorBufferType::LuminanceBuffer)
#  pragma pop_macro("LuminanceBuffer")
# else
	.value("LuminanceBuffer", eglplus::ColorBufferType::LuminanceBuffer)
# endif
#endif
	;

	eglplus::StrLit (*PEnumValueName)(eglplus::ColorBufferType) =
		&eglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
