/*
 *  .file oglplus/enums/texture_mag_filter.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_mag_filter.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_texture_mag_filter(void)
{
	boost::python::enum_<oglplus::TextureMagFilter>("TextureMagFilter")
#if defined GL_NEAREST
# if defined Nearest
#  pragma push_macro("Nearest")
#  undef Nearest
	.value("Nearest", oglplus::TextureMagFilter::Nearest)
#  pragma pop_macro("Nearest")
# else
	.value("Nearest", oglplus::TextureMagFilter::Nearest)
# endif
#endif
#if defined GL_LINEAR
# if defined Linear
#  pragma push_macro("Linear")
#  undef Linear
	.value("Linear", oglplus::TextureMagFilter::Linear)
#  pragma pop_macro("Linear")
# else
	.value("Linear", oglplus::TextureMagFilter::Linear)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureMagFilter) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TextureMagFilter
		>
	>("aux_CastIterRange_TextureMagFilter");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TextureMagFilter
	> (*PEnumValueRange)(oglplus::TextureMagFilter) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
