//  File implement/oglplus/enums/pixel_data_format_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/pixel_data_format.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	PixelDataFormat*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PIXELDATAFORMAT)
#define OGLPLUS_IMPL_EVN_PIXELDATAFORMAT
{
switch(value)
{
#if defined GL_DEPTH_COMPONENT
	case GL_DEPTH_COMPONENT: return CStrRef("DEPTH_COMPONENT");
#endif
#if defined GL_DEPTH_STENCIL
	case GL_DEPTH_STENCIL: return CStrRef("DEPTH_STENCIL");
#endif
#if defined GL_STENCIL_INDEX
	case GL_STENCIL_INDEX: return CStrRef("STENCIL_INDEX");
#endif
#if defined GL_RED
	case GL_RED: return CStrRef("RED");
#endif
#if defined GL_GREEN
	case GL_GREEN: return CStrRef("GREEN");
#endif
#if defined GL_BLUE
	case GL_BLUE: return CStrRef("BLUE");
#endif
#if defined GL_RG
	case GL_RG: return CStrRef("RG");
#endif
#if defined GL_RGB
	case GL_RGB: return CStrRef("RGB");
#endif
#if defined GL_RGBA
	case GL_RGBA: return CStrRef("RGBA");
#endif
#if defined GL_BGR
	case GL_BGR: return CStrRef("BGR");
#endif
#if defined GL_BGRA
	case GL_BGRA: return CStrRef("BGRA");
#endif
#if defined GL_RED_INTEGER
	case GL_RED_INTEGER: return CStrRef("RED_INTEGER");
#endif
#if defined GL_GREEN_INTEGER
	case GL_GREEN_INTEGER: return CStrRef("GREEN_INTEGER");
#endif
#if defined GL_BLUE_INTEGER
	case GL_BLUE_INTEGER: return CStrRef("BLUE_INTEGER");
#endif
#if defined GL_RG_INTEGER
	case GL_RG_INTEGER: return CStrRef("RG_INTEGER");
#endif
#if defined GL_RGB_INTEGER
	case GL_RGB_INTEGER: return CStrRef("RGB_INTEGER");
#endif
#if defined GL_RGBA_INTEGER
	case GL_RGBA_INTEGER: return CStrRef("RGBA_INTEGER");
#endif
#if defined GL_BGR_INTEGER
	case GL_BGR_INTEGER: return CStrRef("BGR_INTEGER");
#endif
#if defined GL_BGRA_INTEGER
	case GL_BGRA_INTEGER: return CStrRef("BGRA_INTEGER");
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

