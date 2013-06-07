/*
 *  .file oglplus/enums/buffer_select_bit.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/buffer_select_bit.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/buffer_select_bit.hpp>

#include <boost/python.hpp>

void oglplus_py_buffer_select_bit(void)
{
	boost::python::enum_<oglplus::BufferSelectBit>("BufferSelectBit")
#if defined GL_COLOR_BUFFER_BIT
# if defined ColorBuffer
#  pragma push_macro("ColorBuffer")
#  undef ColorBuffer
	.value("ColorBuffer", oglplus::BufferSelectBit::ColorBuffer)
#  pragma pop_macro("ColorBuffer")
# else
	.value("ColorBuffer", oglplus::BufferSelectBit::ColorBuffer)
# endif
#endif
#if defined GL_DEPTH_BUFFER_BIT
# if defined DepthBuffer
#  pragma push_macro("DepthBuffer")
#  undef DepthBuffer
	.value("DepthBuffer", oglplus::BufferSelectBit::DepthBuffer)
#  pragma pop_macro("DepthBuffer")
# else
	.value("DepthBuffer", oglplus::BufferSelectBit::DepthBuffer)
# endif
#endif
#if defined GL_STENCIL_BUFFER_BIT
# if defined StencilBuffer
#  pragma push_macro("StencilBuffer")
#  undef StencilBuffer
	.value("StencilBuffer", oglplus::BufferSelectBit::StencilBuffer)
#  pragma pop_macro("StencilBuffer")
# else
	.value("StencilBuffer", oglplus::BufferSelectBit::StencilBuffer)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BufferSelectBit) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
