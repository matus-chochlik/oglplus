/*
 *  .file oglplus/enums/pixel_data_format_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_data_format.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PixelDataFormat*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PIXELDATAFORMAT)
#define OGLPLUS_IMPL_EVN_PIXELDATAFORMAT
{
switch(value)
{
#if defined GL_DEPTH_COMPONENT
	case GL_DEPTH_COMPONENT: return StrLit("DEPTH_COMPONENT");
#endif
#if defined GL_DEPTH_STENCIL
	case GL_DEPTH_STENCIL: return StrLit("DEPTH_STENCIL");
#endif
#if defined GL_STENCIL_INDEX
	case GL_STENCIL_INDEX: return StrLit("STENCIL_INDEX");
#endif
#if defined GL_RED
	case GL_RED: return StrLit("RED");
#endif
#if defined GL_GREEN
	case GL_GREEN: return StrLit("GREEN");
#endif
#if defined GL_BLUE
	case GL_BLUE: return StrLit("BLUE");
#endif
#if defined GL_RG
	case GL_RG: return StrLit("RG");
#endif
#if defined GL_RGB
	case GL_RGB: return StrLit("RGB");
#endif
#if defined GL_RGBA
	case GL_RGBA: return StrLit("RGBA");
#endif
#if defined GL_BGR
	case GL_BGR: return StrLit("BGR");
#endif
#if defined GL_BGRA
	case GL_BGRA: return StrLit("BGRA");
#endif
#if defined GL_RED_INTEGER
	case GL_RED_INTEGER: return StrLit("RED_INTEGER");
#endif
#if defined GL_GREEN_INTEGER
	case GL_GREEN_INTEGER: return StrLit("GREEN_INTEGER");
#endif
#if defined GL_BLUE_INTEGER
	case GL_BLUE_INTEGER: return StrLit("BLUE_INTEGER");
#endif
#if defined GL_RG_INTEGER
	case GL_RG_INTEGER: return StrLit("RG_INTEGER");
#endif
#if defined GL_RGB_INTEGER
	case GL_RGB_INTEGER: return StrLit("RGB_INTEGER");
#endif
#if defined GL_RGBA_INTEGER
	case GL_RGBA_INTEGER: return StrLit("RGBA_INTEGER");
#endif
#if defined GL_BGR_INTEGER
	case GL_BGR_INTEGER: return StrLit("BGR_INTEGER");
#endif
#if defined GL_BGRA_INTEGER
	case GL_BGRA_INTEGER: return StrLit("BGRA_INTEGER");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrLit();
}
#else
;
#endif
} // namespace enums

