/*
 *  .file oglplus/enums/texture_wrap.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_wrap.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

void oglplus_py_texture_wrap(void)
{
	boost::python::enum_<oglplus::TextureWrap>("TextureWrap")
#if defined GL_CLAMP_TO_EDGE
# if defined ClampToEdge
#  pragma push_macro("ClampToEdge")
#  undef ClampToEdge
	.value("ClampToEdge", oglplus::TextureWrap::ClampToEdge)
#  pragma pop_macro("ClampToEdge")
# else
	.value("ClampToEdge", oglplus::TextureWrap::ClampToEdge)
# endif
#endif
#if defined GL_REPEAT
# if defined Repeat
#  pragma push_macro("Repeat")
#  undef Repeat
	.value("Repeat", oglplus::TextureWrap::Repeat)
#  pragma pop_macro("Repeat")
# else
	.value("Repeat", oglplus::TextureWrap::Repeat)
# endif
#endif
#if defined GL_CLAMP_TO_BORDER
# if defined ClampToBorder
#  pragma push_macro("ClampToBorder")
#  undef ClampToBorder
	.value("ClampToBorder", oglplus::TextureWrap::ClampToBorder)
#  pragma pop_macro("ClampToBorder")
# else
	.value("ClampToBorder", oglplus::TextureWrap::ClampToBorder)
# endif
#endif
#if defined GL_MIRRORED_REPEAT
# if defined MirroredRepeat
#  pragma push_macro("MirroredRepeat")
#  undef MirroredRepeat
	.value("MirroredRepeat", oglplus::TextureWrap::MirroredRepeat)
#  pragma pop_macro("MirroredRepeat")
# else
	.value("MirroredRepeat", oglplus::TextureWrap::MirroredRepeat)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureWrap) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
