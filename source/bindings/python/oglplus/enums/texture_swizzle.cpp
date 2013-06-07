/*
 *  .file oglplus/enums/texture_swizzle.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_swizzle.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_texture_swizzle(void)
{
	boost::python::enum_<oglplus::TextureSwizzle>("TextureSwizzle")
#if defined GL_RED
# if defined Red
#  pragma push_macro("Red")
#  undef Red
	.value("Red", oglplus::TextureSwizzle::Red)
#  pragma pop_macro("Red")
# else
	.value("Red", oglplus::TextureSwizzle::Red)
# endif
#endif
#if defined GL_GREEN
# if defined Green
#  pragma push_macro("Green")
#  undef Green
	.value("Green", oglplus::TextureSwizzle::Green)
#  pragma pop_macro("Green")
# else
	.value("Green", oglplus::TextureSwizzle::Green)
# endif
#endif
#if defined GL_BLUE
# if defined Blue
#  pragma push_macro("Blue")
#  undef Blue
	.value("Blue", oglplus::TextureSwizzle::Blue)
#  pragma pop_macro("Blue")
# else
	.value("Blue", oglplus::TextureSwizzle::Blue)
# endif
#endif
#if defined GL_ALPHA
# if defined Alpha
#  pragma push_macro("Alpha")
#  undef Alpha
	.value("Alpha", oglplus::TextureSwizzle::Alpha)
#  pragma pop_macro("Alpha")
# else
	.value("Alpha", oglplus::TextureSwizzle::Alpha)
# endif
#endif
#if defined GL_ZERO
# if defined Zero
#  pragma push_macro("Zero")
#  undef Zero
	.value("Zero", oglplus::TextureSwizzle::Zero)
#  pragma pop_macro("Zero")
# else
	.value("Zero", oglplus::TextureSwizzle::Zero)
# endif
#endif
#if defined GL_ONE
# if defined One
#  pragma push_macro("One")
#  undef One
	.value("One", oglplus::TextureSwizzle::One)
#  pragma pop_macro("One")
# else
	.value("One", oglplus::TextureSwizzle::One)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureSwizzle) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::TextureSwizzle
		>
	>("aux_CastIterRange_TextureSwizzle");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::TextureSwizzle
	> (*PEnumValueRange)(oglplus::TextureSwizzle) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
