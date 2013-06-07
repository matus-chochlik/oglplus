/*
 *  .file oglplus/enums/color_buffer.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/color_buffer.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/color_buffer.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_color_buffer(void)
{
	boost::python::enum_<oglplus::ColorBuffer>("ColorBuffer")
#if defined GL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", oglplus::ColorBuffer::None)
#  pragma pop_macro("None")
# else
	.value("None", oglplus::ColorBuffer::None)
# endif
#endif
#if defined GL_FRONT_LEFT
# if defined FrontLeft
#  pragma push_macro("FrontLeft")
#  undef FrontLeft
	.value("FrontLeft", oglplus::ColorBuffer::FrontLeft)
#  pragma pop_macro("FrontLeft")
# else
	.value("FrontLeft", oglplus::ColorBuffer::FrontLeft)
# endif
#endif
#if defined GL_FRONT_RIGHT
# if defined FrontRight
#  pragma push_macro("FrontRight")
#  undef FrontRight
	.value("FrontRight", oglplus::ColorBuffer::FrontRight)
#  pragma pop_macro("FrontRight")
# else
	.value("FrontRight", oglplus::ColorBuffer::FrontRight)
# endif
#endif
#if defined GL_BACK_LEFT
# if defined BackLeft
#  pragma push_macro("BackLeft")
#  undef BackLeft
	.value("BackLeft", oglplus::ColorBuffer::BackLeft)
#  pragma pop_macro("BackLeft")
# else
	.value("BackLeft", oglplus::ColorBuffer::BackLeft)
# endif
#endif
#if defined GL_BACK_RIGHT
# if defined BackRight
#  pragma push_macro("BackRight")
#  undef BackRight
	.value("BackRight", oglplus::ColorBuffer::BackRight)
#  pragma pop_macro("BackRight")
# else
	.value("BackRight", oglplus::ColorBuffer::BackRight)
# endif
#endif
#if defined GL_FRONT
# if defined Front
#  pragma push_macro("Front")
#  undef Front
	.value("Front", oglplus::ColorBuffer::Front)
#  pragma pop_macro("Front")
# else
	.value("Front", oglplus::ColorBuffer::Front)
# endif
#endif
#if defined GL_BACK
# if defined Back
#  pragma push_macro("Back")
#  undef Back
	.value("Back", oglplus::ColorBuffer::Back)
#  pragma pop_macro("Back")
# else
	.value("Back", oglplus::ColorBuffer::Back)
# endif
#endif
#if defined GL_LEFT
# if defined Left
#  pragma push_macro("Left")
#  undef Left
	.value("Left", oglplus::ColorBuffer::Left)
#  pragma pop_macro("Left")
# else
	.value("Left", oglplus::ColorBuffer::Left)
# endif
#endif
#if defined GL_RIGHT
# if defined Right
#  pragma push_macro("Right")
#  undef Right
	.value("Right", oglplus::ColorBuffer::Right)
#  pragma pop_macro("Right")
# else
	.value("Right", oglplus::ColorBuffer::Right)
# endif
#endif
#if defined GL_FRONT_AND_BACK
# if defined FrontAndBack
#  pragma push_macro("FrontAndBack")
#  undef FrontAndBack
	.value("FrontAndBack", oglplus::ColorBuffer::FrontAndBack)
#  pragma pop_macro("FrontAndBack")
# else
	.value("FrontAndBack", oglplus::ColorBuffer::FrontAndBack)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::ColorBuffer) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::ColorBuffer
		>
	>("aux_CastIterRange_ColorBuffer");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::ColorBuffer
	> (*PEnumValueRange)(oglplus::ColorBuffer) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
