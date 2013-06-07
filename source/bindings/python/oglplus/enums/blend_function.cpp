/*
 *  .file oglplus/enums/blend_function.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/blend_function.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/blend_func.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_blend_function(void)
{
	boost::python::enum_<oglplus::BlendFunction>("BlendFunction")
#if defined GL_ZERO
# if defined Zero
#  pragma push_macro("Zero")
#  undef Zero
	.value("Zero", oglplus::BlendFunction::Zero)
#  pragma pop_macro("Zero")
# else
	.value("Zero", oglplus::BlendFunction::Zero)
# endif
#endif
#if defined GL_ONE
# if defined One
#  pragma push_macro("One")
#  undef One
	.value("One", oglplus::BlendFunction::One)
#  pragma pop_macro("One")
# else
	.value("One", oglplus::BlendFunction::One)
# endif
#endif
#if defined GL_SRC_COLOR
# if defined SrcColor
#  pragma push_macro("SrcColor")
#  undef SrcColor
	.value("SrcColor", oglplus::BlendFunction::SrcColor)
#  pragma pop_macro("SrcColor")
# else
	.value("SrcColor", oglplus::BlendFunction::SrcColor)
# endif
#endif
#if defined GL_ONE_MINUS_SRC_COLOR
# if defined OneMinusSrcColor
#  pragma push_macro("OneMinusSrcColor")
#  undef OneMinusSrcColor
	.value("OneMinusSrcColor", oglplus::BlendFunction::OneMinusSrcColor)
#  pragma pop_macro("OneMinusSrcColor")
# else
	.value("OneMinusSrcColor", oglplus::BlendFunction::OneMinusSrcColor)
# endif
#endif
#if defined GL_DST_COLOR
# if defined DstColor
#  pragma push_macro("DstColor")
#  undef DstColor
	.value("DstColor", oglplus::BlendFunction::DstColor)
#  pragma pop_macro("DstColor")
# else
	.value("DstColor", oglplus::BlendFunction::DstColor)
# endif
#endif
#if defined GL_ONE_MINUS_DST_COLOR
# if defined OneMinusDstColor
#  pragma push_macro("OneMinusDstColor")
#  undef OneMinusDstColor
	.value("OneMinusDstColor", oglplus::BlendFunction::OneMinusDstColor)
#  pragma pop_macro("OneMinusDstColor")
# else
	.value("OneMinusDstColor", oglplus::BlendFunction::OneMinusDstColor)
# endif
#endif
#if defined GL_SRC_ALPHA
# if defined SrcAlpha
#  pragma push_macro("SrcAlpha")
#  undef SrcAlpha
	.value("SrcAlpha", oglplus::BlendFunction::SrcAlpha)
#  pragma pop_macro("SrcAlpha")
# else
	.value("SrcAlpha", oglplus::BlendFunction::SrcAlpha)
# endif
#endif
#if defined GL_ONE_MINUS_SRC_ALPHA
# if defined OneMinusSrcAlpha
#  pragma push_macro("OneMinusSrcAlpha")
#  undef OneMinusSrcAlpha
	.value("OneMinusSrcAlpha", oglplus::BlendFunction::OneMinusSrcAlpha)
#  pragma pop_macro("OneMinusSrcAlpha")
# else
	.value("OneMinusSrcAlpha", oglplus::BlendFunction::OneMinusSrcAlpha)
# endif
#endif
#if defined GL_DST_ALPHA
# if defined DstAlpha
#  pragma push_macro("DstAlpha")
#  undef DstAlpha
	.value("DstAlpha", oglplus::BlendFunction::DstAlpha)
#  pragma pop_macro("DstAlpha")
# else
	.value("DstAlpha", oglplus::BlendFunction::DstAlpha)
# endif
#endif
#if defined GL_ONE_MINUS_DST_ALPHA
# if defined OneMinusDstAlpha
#  pragma push_macro("OneMinusDstAlpha")
#  undef OneMinusDstAlpha
	.value("OneMinusDstAlpha", oglplus::BlendFunction::OneMinusDstAlpha)
#  pragma pop_macro("OneMinusDstAlpha")
# else
	.value("OneMinusDstAlpha", oglplus::BlendFunction::OneMinusDstAlpha)
# endif
#endif
#if defined GL_CONSTANT_COLOR
# if defined ConstantColor
#  pragma push_macro("ConstantColor")
#  undef ConstantColor
	.value("ConstantColor", oglplus::BlendFunction::ConstantColor)
#  pragma pop_macro("ConstantColor")
# else
	.value("ConstantColor", oglplus::BlendFunction::ConstantColor)
# endif
#endif
#if defined GL_ONE_MINUS_CONSTANT_COLOR
# if defined OneMinusConstantColor
#  pragma push_macro("OneMinusConstantColor")
#  undef OneMinusConstantColor
	.value("OneMinusConstantColor", oglplus::BlendFunction::OneMinusConstantColor)
#  pragma pop_macro("OneMinusConstantColor")
# else
	.value("OneMinusConstantColor", oglplus::BlendFunction::OneMinusConstantColor)
# endif
#endif
#if defined GL_CONSTANT_ALPHA
# if defined ConstantAlpha
#  pragma push_macro("ConstantAlpha")
#  undef ConstantAlpha
	.value("ConstantAlpha", oglplus::BlendFunction::ConstantAlpha)
#  pragma pop_macro("ConstantAlpha")
# else
	.value("ConstantAlpha", oglplus::BlendFunction::ConstantAlpha)
# endif
#endif
#if defined GL_ONE_MINUS_CONSTANT_ALPHA
# if defined OneMinusConstantAlpha
#  pragma push_macro("OneMinusConstantAlpha")
#  undef OneMinusConstantAlpha
	.value("OneMinusConstantAlpha", oglplus::BlendFunction::OneMinusConstantAlpha)
#  pragma pop_macro("OneMinusConstantAlpha")
# else
	.value("OneMinusConstantAlpha", oglplus::BlendFunction::OneMinusConstantAlpha)
# endif
#endif
#if defined GL_SRC_ALPHA_SATURATE
# if defined SrcAlphaSaturate
#  pragma push_macro("SrcAlphaSaturate")
#  undef SrcAlphaSaturate
	.value("SrcAlphaSaturate", oglplus::BlendFunction::SrcAlphaSaturate)
#  pragma pop_macro("SrcAlphaSaturate")
# else
	.value("SrcAlphaSaturate", oglplus::BlendFunction::SrcAlphaSaturate)
# endif
#endif
#if defined GL_SRC1_COLOR
# if defined Src1Color
#  pragma push_macro("Src1Color")
#  undef Src1Color
	.value("Src1Color", oglplus::BlendFunction::Src1Color)
#  pragma pop_macro("Src1Color")
# else
	.value("Src1Color", oglplus::BlendFunction::Src1Color)
# endif
#endif
#if defined GL_ONE_MINUS_SRC1_COLOR
# if defined OneMinusSrc1Color
#  pragma push_macro("OneMinusSrc1Color")
#  undef OneMinusSrc1Color
	.value("OneMinusSrc1Color", oglplus::BlendFunction::OneMinusSrc1Color)
#  pragma pop_macro("OneMinusSrc1Color")
# else
	.value("OneMinusSrc1Color", oglplus::BlendFunction::OneMinusSrc1Color)
# endif
#endif
#if defined GL_SRC1_ALPHA
# if defined Src1Alpha
#  pragma push_macro("Src1Alpha")
#  undef Src1Alpha
	.value("Src1Alpha", oglplus::BlendFunction::Src1Alpha)
#  pragma pop_macro("Src1Alpha")
# else
	.value("Src1Alpha", oglplus::BlendFunction::Src1Alpha)
# endif
#endif
#if defined GL_ONE_MINUS_SRC1_ALPHA
# if defined OneMinusSrc1Alpha
#  pragma push_macro("OneMinusSrc1Alpha")
#  undef OneMinusSrc1Alpha
	.value("OneMinusSrc1Alpha", oglplus::BlendFunction::OneMinusSrc1Alpha)
#  pragma pop_macro("OneMinusSrc1Alpha")
# else
	.value("OneMinusSrc1Alpha", oglplus::BlendFunction::OneMinusSrc1Alpha)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::BlendFunction) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::BlendFunction
		>
	>("aux_CastIterRange_BlendFunction");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::BlendFunction
	> (*PEnumValueRange)(oglplus::BlendFunction) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
