/*
 *  .file oglplus/enums/tess_gen_primitive_spacing.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/tess_gen_primitive_spacing.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/primitive_type.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_tess_gen_primitive_spacing(void)
{
	boost::python::enum_<oglplus::TessGenPrimitiveSpacing>("TessGenPrimitiveSpacing")
#if defined GL_FRACTIONAL_EVEN
# if defined FractionalEven
#  pragma push_macro("FractionalEven")
#  undef FractionalEven
	.value("FractionalEven", oglplus::TessGenPrimitiveSpacing::FractionalEven)
#  pragma pop_macro("FractionalEven")
# else
	.value("FractionalEven", oglplus::TessGenPrimitiveSpacing::FractionalEven)
# endif
#endif
#if defined GL_FRACTIONAL_ODD
# if defined FractionalOdd
#  pragma push_macro("FractionalOdd")
#  undef FractionalOdd
	.value("FractionalOdd", oglplus::TessGenPrimitiveSpacing::FractionalOdd)
#  pragma pop_macro("FractionalOdd")
# else
	.value("FractionalOdd", oglplus::TessGenPrimitiveSpacing::FractionalOdd)
# endif
#endif
#if defined GL_EQUAL
# if defined Equal
#  pragma push_macro("Equal")
#  undef Equal
	.value("Equal", oglplus::TessGenPrimitiveSpacing::Equal)
#  pragma pop_macro("Equal")
# else
	.value("Equal", oglplus::TessGenPrimitiveSpacing::Equal)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TessGenPrimitiveSpacing) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TessGenPrimitiveSpacing
		>
	>("aux_CastIterRange_TessGenPrimitiveSpacing");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TessGenPrimitiveSpacing
	> (*PEnumValueRange)(oglplus::TessGenPrimitiveSpacing) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
