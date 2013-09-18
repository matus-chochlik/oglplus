/*
 *  .file oglplus/enums/image_unit_format_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/image_unit_format.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	ImageUnitFormat*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_IMAGEUNITFORMAT)
#define OGLPLUS_IMPL_EVN_IMAGEUNITFORMAT
{
switch(value)
{
#if defined GL_RGBA32F
	case GL_RGBA32F: return StrLit("RGBA32F");
#endif
#if defined GL_RGBA16F
	case GL_RGBA16F: return StrLit("RGBA16F");
#endif
#if defined GL_RG32F
	case GL_RG32F: return StrLit("RG32F");
#endif
#if defined GL_RG16F
	case GL_RG16F: return StrLit("RG16F");
#endif
#if defined GL_R11F_G11F_B10F
	case GL_R11F_G11F_B10F: return StrLit("R11F_G11F_B10F");
#endif
#if defined GL_R32F
	case GL_R32F: return StrLit("R32F");
#endif
#if defined GL_R16F
	case GL_R16F: return StrLit("R16F");
#endif
#if defined GL_RGBA32UI
	case GL_RGBA32UI: return StrLit("RGBA32UI");
#endif
#if defined GL_RGBA16UI
	case GL_RGBA16UI: return StrLit("RGBA16UI");
#endif
#if defined GL_RGB10_A2UI
	case GL_RGB10_A2UI: return StrLit("RGB10_A2UI");
#endif
#if defined GL_RGBA8UI
	case GL_RGBA8UI: return StrLit("RGBA8UI");
#endif
#if defined GL_RG32UI
	case GL_RG32UI: return StrLit("RG32UI");
#endif
#if defined GL_RG16UI
	case GL_RG16UI: return StrLit("RG16UI");
#endif
#if defined GL_RG8UI
	case GL_RG8UI: return StrLit("RG8UI");
#endif
#if defined GL_R32UI
	case GL_R32UI: return StrLit("R32UI");
#endif
#if defined GL_R16UI
	case GL_R16UI: return StrLit("R16UI");
#endif
#if defined GL_R8UI
	case GL_R8UI: return StrLit("R8UI");
#endif
#if defined GL_RGBA32I
	case GL_RGBA32I: return StrLit("RGBA32I");
#endif
#if defined GL_RGBA16I
	case GL_RGBA16I: return StrLit("RGBA16I");
#endif
#if defined GL_RGBA8I
	case GL_RGBA8I: return StrLit("RGBA8I");
#endif
#if defined GL_RG32I
	case GL_RG32I: return StrLit("RG32I");
#endif
#if defined GL_RG16I
	case GL_RG16I: return StrLit("RG16I");
#endif
#if defined GL_RG8I
	case GL_RG8I: return StrLit("RG8I");
#endif
#if defined GL_R32I
	case GL_R32I: return StrLit("R32I");
#endif
#if defined GL_R16I
	case GL_R16I: return StrLit("R16I");
#endif
#if defined GL_R8I
	case GL_R8I: return StrLit("R8I");
#endif
#if defined GL_RGBA16
	case GL_RGBA16: return StrLit("RGBA16");
#endif
#if defined GL_RGB10_A2
	case GL_RGB10_A2: return StrLit("RGB10_A2");
#endif
#if defined GL_RGBA8
	case GL_RGBA8: return StrLit("RGBA8");
#endif
#if defined GL_RG16
	case GL_RG16: return StrLit("RG16");
#endif
#if defined GL_RG8
	case GL_RG8: return StrLit("RG8");
#endif
#if defined GL_R16
	case GL_R16: return StrLit("R16");
#endif
#if defined GL_R8
	case GL_R8: return StrLit("R8");
#endif
#if defined GL_RGBA16_SNORM
	case GL_RGBA16_SNORM: return StrLit("RGBA16_SNORM");
#endif
#if defined GL_RGBA8_SNORM
	case GL_RGBA8_SNORM: return StrLit("RGBA8_SNORM");
#endif
#if defined GL_RG16_SNORM
	case GL_RG16_SNORM: return StrLit("RG16_SNORM");
#endif
#if defined GL_RG8_SNORM
	case GL_RG8_SNORM: return StrLit("RG8_SNORM");
#endif
#if defined GL_R16_SNORM
	case GL_R16_SNORM: return StrLit("R16_SNORM");
#endif
#if defined GL_R8_SNORM
	case GL_R8_SNORM: return StrLit("R8_SNORM");
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

