/*
 *  .file oglplus/enums/pixel_data_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_data_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/pixel_data.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_pixel_data_type(void)
{
	boost::python::enum_<oglplus::PixelDataType>("PixelDataType")
#if defined GL_UNSIGNED_BYTE
# if defined UnsignedByte
#  pragma push_macro("UnsignedByte")
#  undef UnsignedByte
	.value("UnsignedByte", oglplus::PixelDataType::UnsignedByte)
#  pragma pop_macro("UnsignedByte")
# else
	.value("UnsignedByte", oglplus::PixelDataType::UnsignedByte)
# endif
#endif
#if defined GL_BYTE
# if defined Byte
#  pragma push_macro("Byte")
#  undef Byte
	.value("Byte", oglplus::PixelDataType::Byte)
#  pragma pop_macro("Byte")
# else
	.value("Byte", oglplus::PixelDataType::Byte)
# endif
#endif
#if defined GL_UNSIGNED_SHORT
# if defined UnsignedShort
#  pragma push_macro("UnsignedShort")
#  undef UnsignedShort
	.value("UnsignedShort", oglplus::PixelDataType::UnsignedShort)
#  pragma pop_macro("UnsignedShort")
# else
	.value("UnsignedShort", oglplus::PixelDataType::UnsignedShort)
# endif
#endif
#if defined GL_SHORT
# if defined Short
#  pragma push_macro("Short")
#  undef Short
	.value("Short", oglplus::PixelDataType::Short)
#  pragma pop_macro("Short")
# else
	.value("Short", oglplus::PixelDataType::Short)
# endif
#endif
#if defined GL_UNSIGNED_INT
# if defined UnsignedInt
#  pragma push_macro("UnsignedInt")
#  undef UnsignedInt
	.value("UnsignedInt", oglplus::PixelDataType::UnsignedInt)
#  pragma pop_macro("UnsignedInt")
# else
	.value("UnsignedInt", oglplus::PixelDataType::UnsignedInt)
# endif
#endif
#if defined GL_INT
# if defined Int
#  pragma push_macro("Int")
#  undef Int
	.value("Int", oglplus::PixelDataType::Int)
#  pragma pop_macro("Int")
# else
	.value("Int", oglplus::PixelDataType::Int)
# endif
#endif
#if defined GL_HALF_FLOAT
# if defined HalfFloat
#  pragma push_macro("HalfFloat")
#  undef HalfFloat
	.value("HalfFloat", oglplus::PixelDataType::HalfFloat)
#  pragma pop_macro("HalfFloat")
# else
	.value("HalfFloat", oglplus::PixelDataType::HalfFloat)
# endif
#endif
#if defined GL_FLOAT
# if defined Float
#  pragma push_macro("Float")
#  undef Float
	.value("Float", oglplus::PixelDataType::Float)
#  pragma pop_macro("Float")
# else
	.value("Float", oglplus::PixelDataType::Float)
# endif
#endif
#if defined GL_UNSIGNED_BYTE_3_3_2
# if defined UnsignedByte_3_3_2
#  pragma push_macro("UnsignedByte_3_3_2")
#  undef UnsignedByte_3_3_2
	.value("UnsignedByte_3_3_2", oglplus::PixelDataType::UnsignedByte_3_3_2)
#  pragma pop_macro("UnsignedByte_3_3_2")
# else
	.value("UnsignedByte_3_3_2", oglplus::PixelDataType::UnsignedByte_3_3_2)
# endif
#endif
#if defined GL_UNSIGNED_BYTE_2_3_3_REV
# if defined UnsignedByte_2_3_3_Rev
#  pragma push_macro("UnsignedByte_2_3_3_Rev")
#  undef UnsignedByte_2_3_3_Rev
	.value("UnsignedByte_2_3_3_Rev", oglplus::PixelDataType::UnsignedByte_2_3_3_Rev)
#  pragma pop_macro("UnsignedByte_2_3_3_Rev")
# else
	.value("UnsignedByte_2_3_3_Rev", oglplus::PixelDataType::UnsignedByte_2_3_3_Rev)
# endif
#endif
#if defined GL_UNSIGNED_SHORT_5_6_5
# if defined UnsignedShort_5_6_5
#  pragma push_macro("UnsignedShort_5_6_5")
#  undef UnsignedShort_5_6_5
	.value("UnsignedShort_5_6_5", oglplus::PixelDataType::UnsignedShort_5_6_5)
#  pragma pop_macro("UnsignedShort_5_6_5")
# else
	.value("UnsignedShort_5_6_5", oglplus::PixelDataType::UnsignedShort_5_6_5)
# endif
#endif
#if defined GL_UNSIGNED_SHORT_5_6_5_REV
# if defined UnsignedShort_5_6_5_Rev
#  pragma push_macro("UnsignedShort_5_6_5_Rev")
#  undef UnsignedShort_5_6_5_Rev
	.value("UnsignedShort_5_6_5_Rev", oglplus::PixelDataType::UnsignedShort_5_6_5_Rev)
#  pragma pop_macro("UnsignedShort_5_6_5_Rev")
# else
	.value("UnsignedShort_5_6_5_Rev", oglplus::PixelDataType::UnsignedShort_5_6_5_Rev)
# endif
#endif
#if defined GL_UNSIGNED_SHORT_4_4_4_4
# if defined UnsignedShort_4_4_4_4
#  pragma push_macro("UnsignedShort_4_4_4_4")
#  undef UnsignedShort_4_4_4_4
	.value("UnsignedShort_4_4_4_4", oglplus::PixelDataType::UnsignedShort_4_4_4_4)
#  pragma pop_macro("UnsignedShort_4_4_4_4")
# else
	.value("UnsignedShort_4_4_4_4", oglplus::PixelDataType::UnsignedShort_4_4_4_4)
# endif
#endif
#if defined GL_UNSIGNED_SHORT_4_4_4_4_REV
# if defined UnsignedShort_4_4_4_4_Rev
#  pragma push_macro("UnsignedShort_4_4_4_4_Rev")
#  undef UnsignedShort_4_4_4_4_Rev
	.value("UnsignedShort_4_4_4_4_Rev", oglplus::PixelDataType::UnsignedShort_4_4_4_4_Rev)
#  pragma pop_macro("UnsignedShort_4_4_4_4_Rev")
# else
	.value("UnsignedShort_4_4_4_4_Rev", oglplus::PixelDataType::UnsignedShort_4_4_4_4_Rev)
# endif
#endif
#if defined GL_UNSIGNED_SHORT_5_5_5_1
# if defined UnsignedShort_5_5_5_1
#  pragma push_macro("UnsignedShort_5_5_5_1")
#  undef UnsignedShort_5_5_5_1
	.value("UnsignedShort_5_5_5_1", oglplus::PixelDataType::UnsignedShort_5_5_5_1)
#  pragma pop_macro("UnsignedShort_5_5_5_1")
# else
	.value("UnsignedShort_5_5_5_1", oglplus::PixelDataType::UnsignedShort_5_5_5_1)
# endif
#endif
#if defined GL_UNSIGNED_SHORT_1_5_5_5_REV
# if defined UnsignedShort_1_5_5_5_Rev
#  pragma push_macro("UnsignedShort_1_5_5_5_Rev")
#  undef UnsignedShort_1_5_5_5_Rev
	.value("UnsignedShort_1_5_5_5_Rev", oglplus::PixelDataType::UnsignedShort_1_5_5_5_Rev)
#  pragma pop_macro("UnsignedShort_1_5_5_5_Rev")
# else
	.value("UnsignedShort_1_5_5_5_Rev", oglplus::PixelDataType::UnsignedShort_1_5_5_5_Rev)
# endif
#endif
#if defined GL_UNSIGNED_INT_8_8_8_8
# if defined UnsignedInt_8_8_8_8
#  pragma push_macro("UnsignedInt_8_8_8_8")
#  undef UnsignedInt_8_8_8_8
	.value("UnsignedInt_8_8_8_8", oglplus::PixelDataType::UnsignedInt_8_8_8_8)
#  pragma pop_macro("UnsignedInt_8_8_8_8")
# else
	.value("UnsignedInt_8_8_8_8", oglplus::PixelDataType::UnsignedInt_8_8_8_8)
# endif
#endif
#if defined GL_UNSIGNED_INT_8_8_8_8_REV
# if defined UnsignedInt_8_8_8_8_Rev
#  pragma push_macro("UnsignedInt_8_8_8_8_Rev")
#  undef UnsignedInt_8_8_8_8_Rev
	.value("UnsignedInt_8_8_8_8_Rev", oglplus::PixelDataType::UnsignedInt_8_8_8_8_Rev)
#  pragma pop_macro("UnsignedInt_8_8_8_8_Rev")
# else
	.value("UnsignedInt_8_8_8_8_Rev", oglplus::PixelDataType::UnsignedInt_8_8_8_8_Rev)
# endif
#endif
#if defined GL_UNSIGNED_INT_10_10_10_2
# if defined UnsignedInt_10_10_10_2
#  pragma push_macro("UnsignedInt_10_10_10_2")
#  undef UnsignedInt_10_10_10_2
	.value("UnsignedInt_10_10_10_2", oglplus::PixelDataType::UnsignedInt_10_10_10_2)
#  pragma pop_macro("UnsignedInt_10_10_10_2")
# else
	.value("UnsignedInt_10_10_10_2", oglplus::PixelDataType::UnsignedInt_10_10_10_2)
# endif
#endif
#if defined GL_UNSIGNED_INT_2_10_10_10_REV
# if defined UnsignedInt_2_10_10_10_Rev
#  pragma push_macro("UnsignedInt_2_10_10_10_Rev")
#  undef UnsignedInt_2_10_10_10_Rev
	.value("UnsignedInt_2_10_10_10_Rev", oglplus::PixelDataType::UnsignedInt_2_10_10_10_Rev)
#  pragma pop_macro("UnsignedInt_2_10_10_10_Rev")
# else
	.value("UnsignedInt_2_10_10_10_Rev", oglplus::PixelDataType::UnsignedInt_2_10_10_10_Rev)
# endif
#endif
#if defined GL_UNSIGNED_INT_24_8
# if defined UnsignedInt_24_8
#  pragma push_macro("UnsignedInt_24_8")
#  undef UnsignedInt_24_8
	.value("UnsignedInt_24_8", oglplus::PixelDataType::UnsignedInt_24_8)
#  pragma pop_macro("UnsignedInt_24_8")
# else
	.value("UnsignedInt_24_8", oglplus::PixelDataType::UnsignedInt_24_8)
# endif
#endif
#if defined GL_UNSIGNED_INT_10F_11F_11F_REV
# if defined UnsignedInt_10f_11f_11f_Rev
#  pragma push_macro("UnsignedInt_10f_11f_11f_Rev")
#  undef UnsignedInt_10f_11f_11f_Rev
	.value("UnsignedInt_10f_11f_11f_Rev", oglplus::PixelDataType::UnsignedInt_10f_11f_11f_Rev)
#  pragma pop_macro("UnsignedInt_10f_11f_11f_Rev")
# else
	.value("UnsignedInt_10f_11f_11f_Rev", oglplus::PixelDataType::UnsignedInt_10f_11f_11f_Rev)
# endif
#endif
#if defined GL_UNSIGNED_INT_5_9_9_9_REV
# if defined UnsignedInt_5_9_9_9_Rev
#  pragma push_macro("UnsignedInt_5_9_9_9_Rev")
#  undef UnsignedInt_5_9_9_9_Rev
	.value("UnsignedInt_5_9_9_9_Rev", oglplus::PixelDataType::UnsignedInt_5_9_9_9_Rev)
#  pragma pop_macro("UnsignedInt_5_9_9_9_Rev")
# else
	.value("UnsignedInt_5_9_9_9_Rev", oglplus::PixelDataType::UnsignedInt_5_9_9_9_Rev)
# endif
#endif
#if defined GL_FLOAT_32_UNSIGNED_INT_24_8_REV
# if defined Float_32UnsignedInt_24_8_Rev
#  pragma push_macro("Float_32UnsignedInt_24_8_Rev")
#  undef Float_32UnsignedInt_24_8_Rev
	.value("Float_32UnsignedInt_24_8_Rev", oglplus::PixelDataType::Float_32UnsignedInt_24_8_Rev)
#  pragma pop_macro("Float_32UnsignedInt_24_8_Rev")
# else
	.value("Float_32UnsignedInt_24_8_Rev", oglplus::PixelDataType::Float_32UnsignedInt_24_8_Rev)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PixelDataType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::PixelDataType
		>
	>("aux_CastIterRange_PixelDataType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::PixelDataType
	> (*PEnumValueRange)(oglplus::PixelDataType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
