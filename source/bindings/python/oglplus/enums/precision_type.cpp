/*
 *  .file oglplus/enums/precision_type.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/precision_type.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/precision_type.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_precision_type(void)
{
	boost::python::enum_<oglplus::PrecisionType>("PrecisionType")
#if defined GL_LOW_FLOAT
# if defined LowFloat
#  pragma push_macro("LowFloat")
#  undef LowFloat
	.value("LowFloat", oglplus::PrecisionType::LowFloat)
#  pragma pop_macro("LowFloat")
# else
	.value("LowFloat", oglplus::PrecisionType::LowFloat)
# endif
#endif
#if defined GL_MEDIUM_FLOAT
# if defined MediumFloat
#  pragma push_macro("MediumFloat")
#  undef MediumFloat
	.value("MediumFloat", oglplus::PrecisionType::MediumFloat)
#  pragma pop_macro("MediumFloat")
# else
	.value("MediumFloat", oglplus::PrecisionType::MediumFloat)
# endif
#endif
#if defined GL_HIGH_FLOAT
# if defined HighFloat
#  pragma push_macro("HighFloat")
#  undef HighFloat
	.value("HighFloat", oglplus::PrecisionType::HighFloat)
#  pragma pop_macro("HighFloat")
# else
	.value("HighFloat", oglplus::PrecisionType::HighFloat)
# endif
#endif
#if defined GL_LOW_INT
# if defined LowInt
#  pragma push_macro("LowInt")
#  undef LowInt
	.value("LowInt", oglplus::PrecisionType::LowInt)
#  pragma pop_macro("LowInt")
# else
	.value("LowInt", oglplus::PrecisionType::LowInt)
# endif
#endif
#if defined GL_MEDIUM_INT
# if defined MediumInt
#  pragma push_macro("MediumInt")
#  undef MediumInt
	.value("MediumInt", oglplus::PrecisionType::MediumInt)
#  pragma pop_macro("MediumInt")
# else
	.value("MediumInt", oglplus::PrecisionType::MediumInt)
# endif
#endif
#if defined GL_HIGH_INT
# if defined HighInt
#  pragma push_macro("HighInt")
#  undef HighInt
	.value("HighInt", oglplus::PrecisionType::HighInt)
#  pragma pop_macro("HighInt")
# else
	.value("HighInt", oglplus::PrecisionType::HighInt)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PrecisionType) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::PrecisionType
		>
	>("aux_CastIterRange_PrecisionType");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::PrecisionType
	> (*PEnumValueRange)(oglplus::PrecisionType) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
