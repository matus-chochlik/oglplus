/*
 *  .file oglplus/enums/data_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/data_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/data_type.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_data_type(void)
{
	boost::python::enum_<oglplus::DataType>("DataType")
#if defined GL_BYTE
# if defined Byte
#  pragma push_macro("Byte")
#  undef Byte
	.value("Byte", oglplus::DataType::Byte)
#  pragma pop_macro("Byte")
# else
	.value("Byte", oglplus::DataType::Byte)
# endif
#endif
#if defined GL_SHORT
# if defined Short
#  pragma push_macro("Short")
#  undef Short
	.value("Short", oglplus::DataType::Short)
#  pragma pop_macro("Short")
# else
	.value("Short", oglplus::DataType::Short)
# endif
#endif
#if defined GL_INT
# if defined Int
#  pragma push_macro("Int")
#  undef Int
	.value("Int", oglplus::DataType::Int)
#  pragma pop_macro("Int")
# else
	.value("Int", oglplus::DataType::Int)
# endif
#endif
#if defined GL_FIXED
# if defined Fixed
#  pragma push_macro("Fixed")
#  undef Fixed
	.value("Fixed", oglplus::DataType::Fixed)
#  pragma pop_macro("Fixed")
# else
	.value("Fixed", oglplus::DataType::Fixed)
# endif
#endif
#if defined GL_FLOAT
# if defined Float
#  pragma push_macro("Float")
#  undef Float
	.value("Float", oglplus::DataType::Float)
#  pragma pop_macro("Float")
# else
	.value("Float", oglplus::DataType::Float)
# endif
#endif
#if defined GL_HALF_FLOAT
# if defined HalfFloat
#  pragma push_macro("HalfFloat")
#  undef HalfFloat
	.value("HalfFloat", oglplus::DataType::HalfFloat)
#  pragma pop_macro("HalfFloat")
# else
	.value("HalfFloat", oglplus::DataType::HalfFloat)
# endif
#endif
#if defined GL_DOUBLE
# if defined Double
#  pragma push_macro("Double")
#  undef Double
	.value("Double", oglplus::DataType::Double)
#  pragma pop_macro("Double")
# else
	.value("Double", oglplus::DataType::Double)
# endif
#endif
#if defined GL_UNSIGNED_BYTE
# if defined UnsignedByte
#  pragma push_macro("UnsignedByte")
#  undef UnsignedByte
	.value("UnsignedByte", oglplus::DataType::UnsignedByte)
#  pragma pop_macro("UnsignedByte")
# else
	.value("UnsignedByte", oglplus::DataType::UnsignedByte)
# endif
#endif
#if defined GL_UNSIGNED_SHORT
# if defined UnsignedShort
#  pragma push_macro("UnsignedShort")
#  undef UnsignedShort
	.value("UnsignedShort", oglplus::DataType::UnsignedShort)
#  pragma pop_macro("UnsignedShort")
# else
	.value("UnsignedShort", oglplus::DataType::UnsignedShort)
# endif
#endif
#if defined GL_UNSIGNED_INT
# if defined UnsignedInt
#  pragma push_macro("UnsignedInt")
#  undef UnsignedInt
	.value("UnsignedInt", oglplus::DataType::UnsignedInt)
#  pragma pop_macro("UnsignedInt")
# else
	.value("UnsignedInt", oglplus::DataType::UnsignedInt)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::DataType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::DataType
		>
	>("aux_CastIterRange_DataType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::DataType
	> (*PEnumValueRange)(oglplus::DataType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
