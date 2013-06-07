/*
 *  .file oglplus/enums/hint_option.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/hint_option.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/hint.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_hint_option(void)
{
	boost::python::enum_<oglplus::HintOption>("HintOption")
#if defined GL_FASTEST
# if defined Fastest
#  pragma push_macro("Fastest")
#  undef Fastest
	.value("Fastest", oglplus::HintOption::Fastest)
#  pragma pop_macro("Fastest")
# else
	.value("Fastest", oglplus::HintOption::Fastest)
# endif
#endif
#if defined GL_NICEST
# if defined Nicest
#  pragma push_macro("Nicest")
#  undef Nicest
	.value("Nicest", oglplus::HintOption::Nicest)
#  pragma pop_macro("Nicest")
# else
	.value("Nicest", oglplus::HintOption::Nicest)
# endif
#endif
#if defined GL_DONT_CARE
# if defined DontCare
#  pragma push_macro("DontCare")
#  undef DontCare
	.value("DontCare", oglplus::HintOption::DontCare)
#  pragma pop_macro("DontCare")
# else
	.value("DontCare", oglplus::HintOption::DontCare)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::HintOption) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::HintOption
		>
	>("aux_CastIterRange_HintOption");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::HintOption
	> (*PEnumValueRange)(oglplus::HintOption) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
