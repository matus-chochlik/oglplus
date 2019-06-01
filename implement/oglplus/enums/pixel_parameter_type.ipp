//  File implement/oglplus/enums/pixel_parameter_type.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/pixel_parameter.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2019 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

namespace enums {
#if defined GL_PACK_SWAP_BYTES
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackSwapBytes> {
    using Type = bool;
};
#endif
#if defined GL_PACK_LSB_FIRST
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackLSBFirst> {
    using Type = bool;
};
#endif
#if defined GL_PACK_ROW_LENGTH
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackRowLength> {
    using Type = int;
};
#endif
#if defined GL_PACK_SKIP_ROWS
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackSkipRows> {
    using Type = int;
};
#endif
#if defined GL_PACK_SKIP_PIXELS
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackSkipPixels> {
    using Type = int;
};
#endif
#if defined GL_PACK_ALIGNMENT
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackAlignment> {
    using Type = int;
};
#endif
#if defined GL_PACK_IMAGE_HEIGHT
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackImageHeight> {
    using Type = int;
};
#endif
#if defined GL_PACK_SKIP_IMAGES
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackSkipImages> {
    using Type = int;
};
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_WIDTH
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackCompressedBlockWidth> {
    using Type = int;
};
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_HEIGHT
template <>
struct EnumAssocType<
  PixelParameter,
  PixelParameter::PackCompressedBlockHeight> {
    using Type = int;
};
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_DEPTH
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackCompressedBlockDepth> {
    using Type = int;
};
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_SIZE
template <>
struct EnumAssocType<PixelParameter, PixelParameter::PackCompressedBlockSize> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_SWAP_BYTES
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackSwapBytes> {
    using Type = bool;
};
#endif
#if defined GL_UNPACK_LSB_FIRST
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackLSBFirst> {
    using Type = bool;
};
#endif
#if defined GL_UNPACK_ROW_LENGTH
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackRowLength> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_SKIP_ROWS
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackSkipRows> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_SKIP_PIXELS
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackSkipPixels> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_ALIGNMENT
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackAlignment> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_IMAGE_HEIGHT
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackImageHeight> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_SKIP_IMAGES
template <>
struct EnumAssocType<PixelParameter, PixelParameter::UnpackSkipImages> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_WIDTH
template <>
struct EnumAssocType<
  PixelParameter,
  PixelParameter::UnpackCompressedBlockWidth> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
template <>
struct EnumAssocType<
  PixelParameter,
  PixelParameter::UnpackCompressedBlockHeight> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_DEPTH
template <>
struct EnumAssocType<
  PixelParameter,
  PixelParameter::UnpackCompressedBlockDepth> {
    using Type = int;
};
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_SIZE
template <>
struct EnumAssocType<
  PixelParameter,
  PixelParameter::UnpackCompressedBlockSize> {
    using Type = int;
};
#endif
} // namespace enums
