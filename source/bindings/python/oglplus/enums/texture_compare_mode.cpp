/*
 *  .file oglplus/enums/texture_compare_mode.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_compare_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_texture_compare_mode(void)
{
	boost::python::enum_<oglplus::TextureCompareMode>("TextureCompareMode")
#if defined GL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", oglplus::TextureCompareMode::None)
#  pragma pop_macro("None")
# else
	.value("None", oglplus::TextureCompareMode::None)
# endif
#endif
#if defined GL_COMPARE_REF_TO_TEXTURE
# if defined CompareRefToTexture
#  pragma push_macro("CompareRefToTexture")
#  undef CompareRefToTexture
	.value("CompareRefToTexture", oglplus::TextureCompareMode::CompareRefToTexture)
#  pragma pop_macro("CompareRefToTexture")
# else
	.value("CompareRefToTexture", oglplus::TextureCompareMode::CompareRefToTexture)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureCompareMode) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TextureCompareMode
		>
	>("aux_CastIterRange_TextureCompareMode");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TextureCompareMode
	> (*PEnumValueRange)(oglplus::TextureCompareMode) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
