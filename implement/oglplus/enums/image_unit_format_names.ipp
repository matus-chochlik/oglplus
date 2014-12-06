//  File implement/oglplus/enums/image_unit_format_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/image_unit_format.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC CStrRef ValueName_(
	ImageUnitFormat*,
	GLenum value
) noexcept
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_IMAGEUNITFORMAT)
#define OGLPLUS_IMPL_EVN_IMAGEUNITFORMAT
{
switch(value)
{
#if defined GL_RGBA32F
	case GL_RGBA32F: return CStrRef("RGBA32F");
#endif
#if defined GL_RGBA16F
	case GL_RGBA16F: return CStrRef("RGBA16F");
#endif
#if defined GL_RG32F
	case GL_RG32F: return CStrRef("RG32F");
#endif
#if defined GL_RG16F
	case GL_RG16F: return CStrRef("RG16F");
#endif
#if defined GL_R11F_G11F_B10F
	case GL_R11F_G11F_B10F: return CStrRef("R11F_G11F_B10F");
#endif
#if defined GL_R32F
	case GL_R32F: return CStrRef("R32F");
#endif
#if defined GL_R16F
	case GL_R16F: return CStrRef("R16F");
#endif
#if defined GL_RGBA32UI
	case GL_RGBA32UI: return CStrRef("RGBA32UI");
#endif
#if defined GL_RGBA16UI
	case GL_RGBA16UI: return CStrRef("RGBA16UI");
#endif
#if defined GL_RGB10_A2UI
	case GL_RGB10_A2UI: return CStrRef("RGB10_A2UI");
#endif
#if defined GL_RGBA8UI
	case GL_RGBA8UI: return CStrRef("RGBA8UI");
#endif
#if defined GL_RG32UI
	case GL_RG32UI: return CStrRef("RG32UI");
#endif
#if defined GL_RG16UI
	case GL_RG16UI: return CStrRef("RG16UI");
#endif
#if defined GL_RG8UI
	case GL_RG8UI: return CStrRef("RG8UI");
#endif
#if defined GL_R32UI
	case GL_R32UI: return CStrRef("R32UI");
#endif
#if defined GL_R16UI
	case GL_R16UI: return CStrRef("R16UI");
#endif
#if defined GL_R8UI
	case GL_R8UI: return CStrRef("R8UI");
#endif
#if defined GL_RGBA32I
	case GL_RGBA32I: return CStrRef("RGBA32I");
#endif
#if defined GL_RGBA16I
	case GL_RGBA16I: return CStrRef("RGBA16I");
#endif
#if defined GL_RGBA8I
	case GL_RGBA8I: return CStrRef("RGBA8I");
#endif
#if defined GL_RG32I
	case GL_RG32I: return CStrRef("RG32I");
#endif
#if defined GL_RG16I
	case GL_RG16I: return CStrRef("RG16I");
#endif
#if defined GL_RG8I
	case GL_RG8I: return CStrRef("RG8I");
#endif
#if defined GL_R32I
	case GL_R32I: return CStrRef("R32I");
#endif
#if defined GL_R16I
	case GL_R16I: return CStrRef("R16I");
#endif
#if defined GL_R8I
	case GL_R8I: return CStrRef("R8I");
#endif
#if defined GL_RGBA16
	case GL_RGBA16: return CStrRef("RGBA16");
#endif
#if defined GL_RGB10_A2
	case GL_RGB10_A2: return CStrRef("RGB10_A2");
#endif
#if defined GL_RGBA8
	case GL_RGBA8: return CStrRef("RGBA8");
#endif
#if defined GL_RG16
	case GL_RG16: return CStrRef("RG16");
#endif
#if defined GL_RG8
	case GL_RG8: return CStrRef("RG8");
#endif
#if defined GL_R16
	case GL_R16: return CStrRef("R16");
#endif
#if defined GL_R8
	case GL_R8: return CStrRef("R8");
#endif
#if defined GL_RGBA16_SNORM
	case GL_RGBA16_SNORM: return CStrRef("RGBA16_SNORM");
#endif
#if defined GL_RGBA8_SNORM
	case GL_RGBA8_SNORM: return CStrRef("RGBA8_SNORM");
#endif
#if defined GL_RG16_SNORM
	case GL_RG16_SNORM: return CStrRef("RG16_SNORM");
#endif
#if defined GL_RG8_SNORM
	case GL_RG8_SNORM: return CStrRef("RG8_SNORM");
#endif
#if defined GL_R16_SNORM
	case GL_R16_SNORM: return CStrRef("R16_SNORM");
#endif
#if defined GL_R8_SNORM
	case GL_R8_SNORM: return CStrRef("R8_SNORM");
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

