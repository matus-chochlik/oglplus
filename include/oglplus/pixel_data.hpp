/**
 *  @file oglplus/pixel_data.hpp
 *  @brief Pixel data-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PIXEL_DATA_1107121519_HPP
#define OGLPLUS_PIXEL_DATA_1107121519_HPP

#include <oglplus/config.hpp>

namespace oglplus {

/// OpenGL pixel data type enumeration
enum class PixelDataType : GLenum
{
	UnsignedByte = GL_UNSIGNED_BYTE,
	Byte = GL_BYTE,
	UnsignedShort = GL_UNSIGNED_SHORT,
	Short = GL_SHORT,
	UnsignedInt = GL_UNSIGNED_INT,
	Int = GL_INT,
	HalfFloat = GL_HALF_FLOAT,
	Float = GL_FLOAT,
	UnsignedByte_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
	UnsignedByte_2_3_3_Rev = GL_UNSIGNED_BYTE_2_3_3_REV,
	UnsignedShort_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
	UnsignedShort_5_6_5_Rev = GL_UNSIGNED_SHORT_5_6_5_REV,
	UnsignedShort_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
	UnsignedShort_4_4_4_4_Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,
	UnsignedShort_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
	UnsignedShort_1_5_5_5_Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,
	UnsignedInt_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
	UnsignedInt_8_8_8_8_Rev = GL_UNSIGNED_INT_8_8_8_8_REV,
	UnsignedInt_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
	UnsignedInt_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
	UnsignedInt_24_8 = GL_UNSIGNED_INT_24_8,
	UnsignedInt_10f_11f_11f_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV,
	UnsignedInt_5_9_9_9_Rev = GL_UNSIGNED_INT_5_9_9_9_REV,
	Float_32UnsignedInt_24_8_Rev = GL_FLOAT_32_UNSIGNED_INT_24_8_REV
};

/// OpenGL pixel data format enumeration
enum class PixelDataFormat : GLenum
{
	StencilIndex = GL_STENCIL_INDEX,
	DepthComponent = GL_DEPTH_COMPONENT,
	DepthStencil = GL_DEPTH_STENCIL,
	Red = GL_RED,
	Green = GL_GREEN,
	Blue = GL_BLUE,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	BGR = GL_BGR,
	BGRA = GL_BGRA,
	RedInteger = GL_RED_INTEGER,
	GreenInteger = GL_GREEN_INTEGER,
	BlueInteger = GL_BLUE_INTEGER,
	RGInteger = GL_RG_INTEGER,
	RGBInteger = GL_RGB_INTEGER,
	RGBAInteger = GL_RGBA_INTEGER,
	BGRInteger = GL_BGR_INTEGER,
	BGRAInteger = GL_BGRA_INTEGER
};

/// OpenGL pixel data internal format enumeration
enum class PixelDataInternalFormat : GLenum
{
	DepthComponent = GL_DEPTH_COMPONENT,
	DepthStencil = GL_DEPTH_STENCIL,
	Red = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	R8 = GL_R8,
	R8SNorm = GL_R8_SNORM,
	R16 = GL_R16,
	R16SNorm = GL_R16_SNORM,
	RG8 = GL_RG8,
	RG8SNorm = GL_RG8_SNORM,
	RG16 = GL_RG16,
	RG16SNorm = GL_RG16_SNORM,
	R3G3B2 = GL_R3_G3_B2,
	RGB4 = GL_RGB4,
	RGB5 = GL_RGB5,
	RGB8 = GL_RGB8,
	RGB8SNorm = GL_RGB8_SNORM,
	RGB10 = GL_RGB10,
	RGB12 = GL_RGB12,
	RGB16 = GL_RGB16,
	RGB16SNorm = GL_RGB16_SNORM,
	RGBA2 = GL_RGBA2,
	RGBA4 = GL_RGBA4,
	RGB5A1 = GL_RGB5_A1,
	RGBA8 = GL_RGBA8,
	RGBA8SNorm = GL_RGBA8_SNORM,
	RGB10A2 = GL_RGB10_A2,
	RGB10A2UI = GL_RGB10_A2UI,
	RGBA12 = GL_RGBA12,
	RGBA16 = GL_RGBA16,
	RGBA16SNorm = GL_RGBA16_SNORM,
	SRGB8 = GL_SRGB8,
	SRGB8Alpha8 = GL_SRGB8_ALPHA8,
	R16F = GL_R16F,
	RG16F = GL_RG16F,
	RGB16F = GL_RGB16F,
	RGBA16F = GL_RGBA16F,
	R32F = GL_R32F,
	RG32F = GL_RG32F,
	RGB32F = GL_RGB32F,
	RGBA32F = GL_RGBA32F,
	R11FG11FB10F = GL_R11F_G11F_B10F,
	RGB9E5 = GL_RGB9_E5,
	R8I = GL_R8I,
	R8UI = GL_R8UI,
	R16I = GL_R16I,
	R16UI = GL_R16UI,
	R32I = GL_R32I,
	R32UI = GL_R32UI,
	RG8I = GL_RG8I,
	RG8UI = GL_RG8UI,
	RG16I = GL_RG16I,
	RG16UI = GL_RG16UI,
	RG32I = GL_RG32I,
	RG32UI = GL_RG32UI,
	RGB8I = GL_RGB8I,
	RGB8UI = GL_RGB8UI,
	RGB16I = GL_RGB16I,
	RGB16UI = GL_RGB16UI,
	RGB32I = GL_RGB32I,
	RGB32UI = GL_RGB32UI,
	RGBA8I = GL_RGBA8I,
	RGBA8UI = GL_RGBA8UI,
	RGBA16I = GL_RGBA16I,
	RGBA16UI = GL_RGBA16UI,
	RGBA32I = GL_RGBA32I,
	RGBA32UI = GL_RGBA32UI,
	DepthComponent16  = GL_DEPTH_COMPONENT16,
	DepthComponent24  = GL_DEPTH_COMPONENT24,
	DepthComponent32  = GL_DEPTH_COMPONENT32,
	DepthComponent32F  = GL_DEPTH_COMPONENT32F,
	Depth24Stencil8  = GL_DEPTH24_STENCIL8,
	Depth32fStencil8  = GL_DEPTH32F_STENCIL8,
	CompressedRed  = GL_COMPRESSED_RED,
	CompressedRG  = GL_COMPRESSED_RG,
	CompressedRGB  = GL_COMPRESSED_RGB,
	CompressedRGBA  = GL_COMPRESSED_RGBA,
	CompressedSRGB  = GL_COMPRESSED_SRGB,
	CompressedSRGBAlpha  = GL_COMPRESSED_SRGB_ALPHA,
	CompressedRedRGTC1  = GL_COMPRESSED_RED_RGTC1,
	CompressedSignedRedRGTC1  = GL_COMPRESSED_SIGNED_RED_RGTC1,
	CompressedRGRGTC2  = GL_COMPRESSED_RG_RGTC2,
	CompressedSignedRGRGTC2  = GL_COMPRESSED_SIGNED_RG_RGTC2
};

} // namespace oglplus

#endif // include guard
