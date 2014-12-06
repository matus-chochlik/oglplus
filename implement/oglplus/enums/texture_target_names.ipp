//  File implement/oglplus/enums/texture_target_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/texture_target.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	TextureTarget*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_TEXTURETARGET)
#define OGLPLUS_IMPL_EVN_TEXTURETARGET
{
switch(value)
{
#if defined GL_TEXTURE_1D
	case GL_TEXTURE_1D: return CStrRef("TEXTURE_1D");
#endif
#if defined GL_TEXTURE_2D
	case GL_TEXTURE_2D: return CStrRef("TEXTURE_2D");
#endif
#if defined GL_TEXTURE_3D
	case GL_TEXTURE_3D: return CStrRef("TEXTURE_3D");
#endif
#if defined GL_TEXTURE_1D_ARRAY
	case GL_TEXTURE_1D_ARRAY: return CStrRef("TEXTURE_1D_ARRAY");
#endif
#if defined GL_TEXTURE_2D_ARRAY
	case GL_TEXTURE_2D_ARRAY: return CStrRef("TEXTURE_2D_ARRAY");
#endif
#if defined GL_TEXTURE_RECTANGLE
	case GL_TEXTURE_RECTANGLE: return CStrRef("TEXTURE_RECTANGLE");
#endif
#if defined GL_TEXTURE_BUFFER
	case GL_TEXTURE_BUFFER: return CStrRef("TEXTURE_BUFFER");
#endif
#if defined GL_TEXTURE_CUBE_MAP
	case GL_TEXTURE_CUBE_MAP: return CStrRef("TEXTURE_CUBE_MAP");
#endif
#if defined GL_TEXTURE_CUBE_MAP_ARRAY
	case GL_TEXTURE_CUBE_MAP_ARRAY: return CStrRef("TEXTURE_CUBE_MAP_ARRAY");
#endif
#if defined GL_TEXTURE_2D_MULTISAMPLE
	case GL_TEXTURE_2D_MULTISAMPLE: return CStrRef("TEXTURE_2D_MULTISAMPLE");
#endif
#if defined GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	case GL_TEXTURE_2D_MULTISAMPLE_ARRAY: return CStrRef("TEXTURE_2D_MULTISAMPLE_ARRAY");
#endif
#if defined GL_TEXTURE_CUBE_MAP_POSITIVE_X
	case GL_TEXTURE_CUBE_MAP_POSITIVE_X: return CStrRef("TEXTURE_CUBE_MAP_POSITIVE_X");
#endif
#if defined GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_X: return CStrRef("TEXTURE_CUBE_MAP_NEGATIVE_X");
#endif
#if defined GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Y: return CStrRef("TEXTURE_CUBE_MAP_POSITIVE_Y");
#endif
#if defined GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y: return CStrRef("TEXTURE_CUBE_MAP_NEGATIVE_Y");
#endif
#if defined GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Z: return CStrRef("TEXTURE_CUBE_MAP_POSITIVE_Z");
#endif
#if defined GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z: return CStrRef("TEXTURE_CUBE_MAP_NEGATIVE_Z");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return CStrRef();
}
#else
;
#endif
} // namespace enums

