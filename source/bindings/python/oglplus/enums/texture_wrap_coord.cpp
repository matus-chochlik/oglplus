/*
 *  .file oglplus/enums/texture_wrap_coord.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_wrap_coord.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_texture_wrap_coord(void)
{
	boost::python::enum_<oglplus::TextureWrapCoord>("TextureWrapCoord")
#if defined GL_TEXTURE_WRAP_S
# if defined S
#  pragma push_macro("S")
#  undef S
	.value("S", oglplus::TextureWrapCoord::S)
#  pragma pop_macro("S")
# else
	.value("S", oglplus::TextureWrapCoord::S)
# endif
#endif
#if defined GL_TEXTURE_WRAP_T
# if defined T
#  pragma push_macro("T")
#  undef T
	.value("T", oglplus::TextureWrapCoord::T)
#  pragma pop_macro("T")
# else
	.value("T", oglplus::TextureWrapCoord::T)
# endif
#endif
#if defined GL_TEXTURE_WRAP_R
# if defined R
#  pragma push_macro("R")
#  undef R
	.value("R", oglplus::TextureWrapCoord::R)
#  pragma pop_macro("R")
# else
	.value("R", oglplus::TextureWrapCoord::R)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureWrapCoord) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TextureWrapCoord
		>
	>("aux_CastIterRange_TextureWrapCoord");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TextureWrapCoord
	> (*PEnumValueRange)(oglplus::TextureWrapCoord) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
