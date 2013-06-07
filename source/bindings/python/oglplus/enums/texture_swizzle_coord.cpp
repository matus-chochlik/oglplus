/*
 *  .file oglplus/enums/texture_swizzle_coord.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_swizzle_coord.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_texture_swizzle_coord(void)
{
	boost::python::enum_<oglplus::TextureSwizzleCoord>("TextureSwizzleCoord")
#if defined GL_TEXTURE_SWIZZLE_R
# if defined R
#  pragma push_macro("R")
#  undef R
	.value("R", oglplus::TextureSwizzleCoord::R)
#  pragma pop_macro("R")
# else
	.value("R", oglplus::TextureSwizzleCoord::R)
# endif
#endif
#if defined GL_TEXTURE_SWIZZLE_G
# if defined G
#  pragma push_macro("G")
#  undef G
	.value("G", oglplus::TextureSwizzleCoord::G)
#  pragma pop_macro("G")
# else
	.value("G", oglplus::TextureSwizzleCoord::G)
# endif
#endif
#if defined GL_TEXTURE_SWIZZLE_B
# if defined B
#  pragma push_macro("B")
#  undef B
	.value("B", oglplus::TextureSwizzleCoord::B)
#  pragma pop_macro("B")
# else
	.value("B", oglplus::TextureSwizzleCoord::B)
# endif
#endif
#if defined GL_TEXTURE_SWIZZLE_A
# if defined A
#  pragma push_macro("A")
#  undef A
	.value("A", oglplus::TextureSwizzleCoord::A)
#  pragma pop_macro("A")
# else
	.value("A", oglplus::TextureSwizzleCoord::A)
# endif
#endif
#if defined GL_TEXTURE_SWIZZLE_RGBA
# if defined RGBA
#  pragma push_macro("RGBA")
#  undef RGBA
	.value("RGBA", oglplus::TextureSwizzleCoord::RGBA)
#  pragma pop_macro("RGBA")
# else
	.value("RGBA", oglplus::TextureSwizzleCoord::RGBA)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureSwizzleCoord) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TextureSwizzleCoord
		>
	>("aux_CastIterRange_TextureSwizzleCoord");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TextureSwizzleCoord
	> (*PEnumValueRange)(oglplus::TextureSwizzleCoord) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
