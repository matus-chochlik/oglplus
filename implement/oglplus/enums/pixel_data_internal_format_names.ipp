/*
 *  .file oglplus/enums/pixel_data_internal_format_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_data_internal_format.txt' instead.
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PixelDataInternalFormat*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PIXELDATAINTERNALFORMAT)
#define OGLPLUS_IMPL_EVN_PIXELDATAINTERNALFORMAT
{
switch(value)
{
#if defined GL_DEPTH_COMPONENT
	case GL_DEPTH_COMPONENT: return StrLit("DEPTH_COMPONENT");
#endif
#if defined GL_DEPTH_STENCIL
	case GL_DEPTH_STENCIL: return StrLit("DEPTH_STENCIL");
#endif
#if defined GL_STENCIL_INDEX8
	case GL_STENCIL_INDEX8: return StrLit("STENCIL_INDEX8");
#endif
#if defined GL_RED
	case GL_RED: return StrLit("RED");
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
#if defined GL_R8
	case GL_R8: return StrLit("R8");
#endif
#if defined GL_R8_SNORM
	case GL_R8_SNORM: return StrLit("R8_SNORM");
#endif
#if defined GL_R16
	case GL_R16: return StrLit("R16");
#endif
#if defined GL_R16_SNORM
	case GL_R16_SNORM: return StrLit("R16_SNORM");
#endif
#if defined GL_RG8
	case GL_RG8: return StrLit("RG8");
#endif
#if defined GL_RG8_SNORM
	case GL_RG8_SNORM: return StrLit("RG8_SNORM");
#endif
#if defined GL_RG16
	case GL_RG16: return StrLit("RG16");
#endif
#if defined GL_RG16_SNORM
	case GL_RG16_SNORM: return StrLit("RG16_SNORM");
#endif
#if defined GL_R3_G3_B2
	case GL_R3_G3_B2: return StrLit("R3_G3_B2");
#endif
#if defined GL_RGB4
	case GL_RGB4: return StrLit("RGB4");
#endif
#if defined GL_RGB5
	case GL_RGB5: return StrLit("RGB5");
#endif
#if defined GL_RGB8
	case GL_RGB8: return StrLit("RGB8");
#endif
#if defined GL_RGB8_SNORM
	case GL_RGB8_SNORM: return StrLit("RGB8_SNORM");
#endif
#if defined GL_RGB10
	case GL_RGB10: return StrLit("RGB10");
#endif
#if defined GL_RGB12
	case GL_RGB12: return StrLit("RGB12");
#endif
#if defined GL_RGB16
	case GL_RGB16: return StrLit("RGB16");
#endif
#if defined GL_RGB16_SNORM
	case GL_RGB16_SNORM: return StrLit("RGB16_SNORM");
#endif
#if defined GL_RGBA2
	case GL_RGBA2: return StrLit("RGBA2");
#endif
#if defined GL_RGBA4
	case GL_RGBA4: return StrLit("RGBA4");
#endif
#if defined GL_RGB5_A1
	case GL_RGB5_A1: return StrLit("RGB5_A1");
#endif
#if defined GL_RGBA8
	case GL_RGBA8: return StrLit("RGBA8");
#endif
#if defined GL_RGBA8_SNORM
	case GL_RGBA8_SNORM: return StrLit("RGBA8_SNORM");
#endif
#if defined GL_RGB10_A2
	case GL_RGB10_A2: return StrLit("RGB10_A2");
#endif
#if defined GL_RGB10_A2UI
	case GL_RGB10_A2UI: return StrLit("RGB10_A2UI");
#endif
#if defined GL_RGBA12
	case GL_RGBA12: return StrLit("RGBA12");
#endif
#if defined GL_RGBA16
	case GL_RGBA16: return StrLit("RGBA16");
#endif
#if defined GL_RGBA16_SNORM
	case GL_RGBA16_SNORM: return StrLit("RGBA16_SNORM");
#endif
#if defined GL_SRGB8
	case GL_SRGB8: return StrLit("SRGB8");
#endif
#if defined GL_SRGB8_ALPHA8
	case GL_SRGB8_ALPHA8: return StrLit("SRGB8_ALPHA8");
#endif
#if defined GL_R16F
	case GL_R16F: return StrLit("R16F");
#endif
#if defined GL_RG16F
	case GL_RG16F: return StrLit("RG16F");
#endif
#if defined GL_RGB16F
	case GL_RGB16F: return StrLit("RGB16F");
#endif
#if defined GL_RGBA16F
	case GL_RGBA16F: return StrLit("RGBA16F");
#endif
#if defined GL_R32F
	case GL_R32F: return StrLit("R32F");
#endif
#if defined GL_RG32F
	case GL_RG32F: return StrLit("RG32F");
#endif
#if defined GL_RGB32F
	case GL_RGB32F: return StrLit("RGB32F");
#endif
#if defined GL_RGBA32F
	case GL_RGBA32F: return StrLit("RGBA32F");
#endif
#if defined GL_R11F_G11F_B10F
	case GL_R11F_G11F_B10F: return StrLit("R11F_G11F_B10F");
#endif
#if defined GL_RGB9_E5
	case GL_RGB9_E5: return StrLit("RGB9_E5");
#endif
#if defined GL_R8I
	case GL_R8I: return StrLit("R8I");
#endif
#if defined GL_R8UI
	case GL_R8UI: return StrLit("R8UI");
#endif
#if defined GL_R16I
	case GL_R16I: return StrLit("R16I");
#endif
#if defined GL_R16UI
	case GL_R16UI: return StrLit("R16UI");
#endif
#if defined GL_R32I
	case GL_R32I: return StrLit("R32I");
#endif
#if defined GL_R32UI
	case GL_R32UI: return StrLit("R32UI");
#endif
#if defined GL_RG8I
	case GL_RG8I: return StrLit("RG8I");
#endif
#if defined GL_RG8UI
	case GL_RG8UI: return StrLit("RG8UI");
#endif
#if defined GL_RG16I
	case GL_RG16I: return StrLit("RG16I");
#endif
#if defined GL_RG16UI
	case GL_RG16UI: return StrLit("RG16UI");
#endif
#if defined GL_RG32I
	case GL_RG32I: return StrLit("RG32I");
#endif
#if defined GL_RG32UI
	case GL_RG32UI: return StrLit("RG32UI");
#endif
#if defined GL_RGB8I
	case GL_RGB8I: return StrLit("RGB8I");
#endif
#if defined GL_RGB8UI
	case GL_RGB8UI: return StrLit("RGB8UI");
#endif
#if defined GL_RGB16I
	case GL_RGB16I: return StrLit("RGB16I");
#endif
#if defined GL_RGB16UI
	case GL_RGB16UI: return StrLit("RGB16UI");
#endif
#if defined GL_RGB32I
	case GL_RGB32I: return StrLit("RGB32I");
#endif
#if defined GL_RGB32UI
	case GL_RGB32UI: return StrLit("RGB32UI");
#endif
#if defined GL_RGBA8I
	case GL_RGBA8I: return StrLit("RGBA8I");
#endif
#if defined GL_RGBA8UI
	case GL_RGBA8UI: return StrLit("RGBA8UI");
#endif
#if defined GL_RGBA16I
	case GL_RGBA16I: return StrLit("RGBA16I");
#endif
#if defined GL_RGBA16UI
	case GL_RGBA16UI: return StrLit("RGBA16UI");
#endif
#if defined GL_RGBA32I
	case GL_RGBA32I: return StrLit("RGBA32I");
#endif
#if defined GL_RGBA32UI
	case GL_RGBA32UI: return StrLit("RGBA32UI");
#endif
#if defined GL_DEPTH_COMPONENT16
	case GL_DEPTH_COMPONENT16: return StrLit("DEPTH_COMPONENT16");
#endif
#if defined GL_DEPTH_COMPONENT24
	case GL_DEPTH_COMPONENT24: return StrLit("DEPTH_COMPONENT24");
#endif
#if defined GL_DEPTH_COMPONENT32
	case GL_DEPTH_COMPONENT32: return StrLit("DEPTH_COMPONENT32");
#endif
#if defined GL_DEPTH_COMPONENT32F
	case GL_DEPTH_COMPONENT32F: return StrLit("DEPTH_COMPONENT32F");
#endif
#if defined GL_DEPTH24_STENCIL8
	case GL_DEPTH24_STENCIL8: return StrLit("DEPTH24_STENCIL8");
#endif
#if defined GL_DEPTH32F_STENCIL8
	case GL_DEPTH32F_STENCIL8: return StrLit("DEPTH32F_STENCIL8");
#endif
#if defined GL_COMPRESSED_RED
	case GL_COMPRESSED_RED: return StrLit("COMPRESSED_RED");
#endif
#if defined GL_COMPRESSED_RG
	case GL_COMPRESSED_RG: return StrLit("COMPRESSED_RG");
#endif
#if defined GL_COMPRESSED_RGB
	case GL_COMPRESSED_RGB: return StrLit("COMPRESSED_RGB");
#endif
#if defined GL_COMPRESSED_RGBA
	case GL_COMPRESSED_RGBA: return StrLit("COMPRESSED_RGBA");
#endif
#if defined GL_COMPRESSED_SRGB
	case GL_COMPRESSED_SRGB: return StrLit("COMPRESSED_SRGB");
#endif
#if defined GL_COMPRESSED_SRGB_ALPHA
	case GL_COMPRESSED_SRGB_ALPHA: return StrLit("COMPRESSED_SRGB_ALPHA");
#endif
#if defined GL_COMPRESSED_RED_RGTC1
	case GL_COMPRESSED_RED_RGTC1: return StrLit("COMPRESSED_RED_RGTC1");
#endif
#if defined GL_COMPRESSED_SIGNED_RED_RGTC1
	case GL_COMPRESSED_SIGNED_RED_RGTC1: return StrLit("COMPRESSED_SIGNED_RED_RGTC1");
#endif
#if defined GL_COMPRESSED_RG_RGTC2
	case GL_COMPRESSED_RG_RGTC2: return StrLit("COMPRESSED_RG_RGTC2");
#endif
#if defined GL_COMPRESSED_SIGNED_RG_RGTC2
	case GL_COMPRESSED_SIGNED_RG_RGTC2: return StrLit("COMPRESSED_SIGNED_RG_RGTC2");
#endif
#if defined GL_COMPRESSED_RGBA_BPTC_UNORM
	case GL_COMPRESSED_RGBA_BPTC_UNORM: return StrLit("COMPRESSED_RGBA_BPTC_UNORM");
#endif
#if defined GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM
	case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM: return StrLit("COMPRESSED_SRGB_ALPHA_BPTC_UNORM");
#endif
#if defined GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT
	case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT: return StrLit("COMPRESSED_RGB_BPTC_SIGNED_FLOAT");
#endif
#if defined GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
	case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT: return StrLit("COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT");
#endif
#if defined GL_COMPRESSED_RGB8_ETC2
	case GL_COMPRESSED_RGB8_ETC2: return StrLit("COMPRESSED_RGB8_ETC2");
#endif
#if defined GL_COMPRESSED_SRGB8_ETC2
	case GL_COMPRESSED_SRGB8_ETC2: return StrLit("COMPRESSED_SRGB8_ETC2");
#endif
#if defined GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
	case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2: return StrLit("COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2");
#endif
#if defined GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
	case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2: return StrLit("COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2");
#endif
#if defined GL_COMPRESSED_RGBA8_ETC2_EAC
	case GL_COMPRESSED_RGBA8_ETC2_EAC: return StrLit("COMPRESSED_RGBA8_ETC2_EAC");
#endif
#if defined GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
	case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC: return StrLit("COMPRESSED_SRGB8_ALPHA8_ETC2_EAC");
#endif
#if defined GL_COMPRESSED_R11_EAC
	case GL_COMPRESSED_R11_EAC: return StrLit("COMPRESSED_R11_EAC");
#endif
#if defined GL_COMPRESSED_SIGNED_R11_EAC
	case GL_COMPRESSED_SIGNED_R11_EAC: return StrLit("COMPRESSED_SIGNED_R11_EAC");
#endif
#if defined GL_COMPRESSED_RG11_EAC
	case GL_COMPRESSED_RG11_EAC: return StrLit("COMPRESSED_RG11_EAC");
#endif
#if defined GL_COMPRESSED_SIGNED_RG11_EAC
	case GL_COMPRESSED_SIGNED_RG11_EAC: return StrLit("COMPRESSED_SIGNED_RG11_EAC");
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

