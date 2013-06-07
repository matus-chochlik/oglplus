/*
 *  .file oglplus/enums/texture_target.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/texture_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/texture.hpp>

#include <boost/python.hpp>

void oglplus_py_texture_target(void)
{
	boost::python::enum_<oglplus::TextureTarget>("TextureTarget")
#if defined GL_TEXTURE_1D
# if defined _1D
#  pragma push_macro("_1D")
#  undef _1D
	.value("_1D", oglplus::TextureTarget::_1D)
#  pragma pop_macro("_1D")
# else
	.value("_1D", oglplus::TextureTarget::_1D)
# endif
#endif
#if defined GL_TEXTURE_2D
# if defined _2D
#  pragma push_macro("_2D")
#  undef _2D
	.value("_2D", oglplus::TextureTarget::_2D)
#  pragma pop_macro("_2D")
# else
	.value("_2D", oglplus::TextureTarget::_2D)
# endif
#endif
#if defined GL_TEXTURE_3D
# if defined _3D
#  pragma push_macro("_3D")
#  undef _3D
	.value("_3D", oglplus::TextureTarget::_3D)
#  pragma pop_macro("_3D")
# else
	.value("_3D", oglplus::TextureTarget::_3D)
# endif
#endif
#if defined GL_TEXTURE_1D_ARRAY
# if defined _1DArray
#  pragma push_macro("_1DArray")
#  undef _1DArray
	.value("_1DArray", oglplus::TextureTarget::_1DArray)
#  pragma pop_macro("_1DArray")
# else
	.value("_1DArray", oglplus::TextureTarget::_1DArray)
# endif
#endif
#if defined GL_TEXTURE_2D_ARRAY
# if defined _2DArray
#  pragma push_macro("_2DArray")
#  undef _2DArray
	.value("_2DArray", oglplus::TextureTarget::_2DArray)
#  pragma pop_macro("_2DArray")
# else
	.value("_2DArray", oglplus::TextureTarget::_2DArray)
# endif
#endif
#if defined GL_TEXTURE_RECTANGLE
# if defined Rectangle
#  pragma push_macro("Rectangle")
#  undef Rectangle
	.value("Rectangle", oglplus::TextureTarget::Rectangle)
#  pragma pop_macro("Rectangle")
# else
	.value("Rectangle", oglplus::TextureTarget::Rectangle)
# endif
#endif
#if defined GL_TEXTURE_BUFFER
# if defined Buffer
#  pragma push_macro("Buffer")
#  undef Buffer
	.value("Buffer", oglplus::TextureTarget::Buffer)
#  pragma pop_macro("Buffer")
# else
	.value("Buffer", oglplus::TextureTarget::Buffer)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP
# if defined CubeMap
#  pragma push_macro("CubeMap")
#  undef CubeMap
	.value("CubeMap", oglplus::TextureTarget::CubeMap)
#  pragma pop_macro("CubeMap")
# else
	.value("CubeMap", oglplus::TextureTarget::CubeMap)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_ARRAY
# if defined CubeMapArray
#  pragma push_macro("CubeMapArray")
#  undef CubeMapArray
	.value("CubeMapArray", oglplus::TextureTarget::CubeMapArray)
#  pragma pop_macro("CubeMapArray")
# else
	.value("CubeMapArray", oglplus::TextureTarget::CubeMapArray)
# endif
#endif
#if defined GL_TEXTURE_2D_MULTISAMPLE
# if defined _2DMultisample
#  pragma push_macro("_2DMultisample")
#  undef _2DMultisample
	.value("_2DMultisample", oglplus::TextureTarget::_2DMultisample)
#  pragma pop_macro("_2DMultisample")
# else
	.value("_2DMultisample", oglplus::TextureTarget::_2DMultisample)
# endif
#endif
#if defined GL_TEXTURE_2D_MULTISAMPLE_ARRAY
# if defined _2DMultisampleArray
#  pragma push_macro("_2DMultisampleArray")
#  undef _2DMultisampleArray
	.value("_2DMultisampleArray", oglplus::TextureTarget::_2DMultisampleArray)
#  pragma pop_macro("_2DMultisampleArray")
# else
	.value("_2DMultisampleArray", oglplus::TextureTarget::_2DMultisampleArray)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_POSITIVE_X
# if defined CubeMapPositiveX
#  pragma push_macro("CubeMapPositiveX")
#  undef CubeMapPositiveX
	.value("CubeMapPositiveX", oglplus::TextureTarget::CubeMapPositiveX)
#  pragma pop_macro("CubeMapPositiveX")
# else
	.value("CubeMapPositiveX", oglplus::TextureTarget::CubeMapPositiveX)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_NEGATIVE_X
# if defined CubeMapNegativeX
#  pragma push_macro("CubeMapNegativeX")
#  undef CubeMapNegativeX
	.value("CubeMapNegativeX", oglplus::TextureTarget::CubeMapNegativeX)
#  pragma pop_macro("CubeMapNegativeX")
# else
	.value("CubeMapNegativeX", oglplus::TextureTarget::CubeMapNegativeX)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_POSITIVE_Y
# if defined CubeMapPositiveY
#  pragma push_macro("CubeMapPositiveY")
#  undef CubeMapPositiveY
	.value("CubeMapPositiveY", oglplus::TextureTarget::CubeMapPositiveY)
#  pragma pop_macro("CubeMapPositiveY")
# else
	.value("CubeMapPositiveY", oglplus::TextureTarget::CubeMapPositiveY)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
# if defined CubeMapNegativeY
#  pragma push_macro("CubeMapNegativeY")
#  undef CubeMapNegativeY
	.value("CubeMapNegativeY", oglplus::TextureTarget::CubeMapNegativeY)
#  pragma pop_macro("CubeMapNegativeY")
# else
	.value("CubeMapNegativeY", oglplus::TextureTarget::CubeMapNegativeY)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_POSITIVE_Z
# if defined CubeMapPositiveZ
#  pragma push_macro("CubeMapPositiveZ")
#  undef CubeMapPositiveZ
	.value("CubeMapPositiveZ", oglplus::TextureTarget::CubeMapPositiveZ)
#  pragma pop_macro("CubeMapPositiveZ")
# else
	.value("CubeMapPositiveZ", oglplus::TextureTarget::CubeMapPositiveZ)
# endif
#endif
#if defined GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
# if defined CubeMapNegativeZ
#  pragma push_macro("CubeMapNegativeZ")
#  undef CubeMapNegativeZ
	.value("CubeMapNegativeZ", oglplus::TextureTarget::CubeMapNegativeZ)
#  pragma pop_macro("CubeMapNegativeZ")
# else
	.value("CubeMapNegativeZ", oglplus::TextureTarget::CubeMapNegativeZ)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::TextureTarget) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);
}
