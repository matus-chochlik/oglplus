/*
 *  .file oglplus/enums/pixel_storage_mode.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_storage_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/pixel_storage_mode.hpp>

#include <boost/python.hpp>

#include "../_py_range_adapt.hpp"

void oglplus_py_pixel_storage_mode(void)
{
	boost::python::enum_<oglplus::PixelStorageMode>("PixelStorageMode")
#if defined GL_PACK_SWAP_BYTES
# if defined PackSwapBytes
#  pragma push_macro("PackSwapBytes")
#  undef PackSwapBytes
	.value("PackSwapBytes", oglplus::PixelStorageMode::PackSwapBytes)
#  pragma pop_macro("PackSwapBytes")
# else
	.value("PackSwapBytes", oglplus::PixelStorageMode::PackSwapBytes)
# endif
#endif
#if defined GL_PACK_LSB_FIRST
# if defined PackLsbFirst
#  pragma push_macro("PackLsbFirst")
#  undef PackLsbFirst
	.value("PackLsbFirst", oglplus::PixelStorageMode::PackLsbFirst)
#  pragma pop_macro("PackLsbFirst")
# else
	.value("PackLsbFirst", oglplus::PixelStorageMode::PackLsbFirst)
# endif
#endif
#if defined GL_PACK_ROW_LENGTH
# if defined PackRowLength
#  pragma push_macro("PackRowLength")
#  undef PackRowLength
	.value("PackRowLength", oglplus::PixelStorageMode::PackRowLength)
#  pragma pop_macro("PackRowLength")
# else
	.value("PackRowLength", oglplus::PixelStorageMode::PackRowLength)
# endif
#endif
#if defined GL_PACK_SKIP_ROWS
# if defined PackSkipRows
#  pragma push_macro("PackSkipRows")
#  undef PackSkipRows
	.value("PackSkipRows", oglplus::PixelStorageMode::PackSkipRows)
#  pragma pop_macro("PackSkipRows")
# else
	.value("PackSkipRows", oglplus::PixelStorageMode::PackSkipRows)
# endif
#endif
#if defined GL_PACK_SKIP_PIXELS
# if defined PackSkipPixels
#  pragma push_macro("PackSkipPixels")
#  undef PackSkipPixels
	.value("PackSkipPixels", oglplus::PixelStorageMode::PackSkipPixels)
#  pragma pop_macro("PackSkipPixels")
# else
	.value("PackSkipPixels", oglplus::PixelStorageMode::PackSkipPixels)
# endif
#endif
#if defined GL_PACK_ALIGNMENT
# if defined PackAlignment
#  pragma push_macro("PackAlignment")
#  undef PackAlignment
	.value("PackAlignment", oglplus::PixelStorageMode::PackAlignment)
#  pragma pop_macro("PackAlignment")
# else
	.value("PackAlignment", oglplus::PixelStorageMode::PackAlignment)
# endif
#endif
#if defined GL_PACK_IMAGE_HEIGHT
# if defined PackImageHeight
#  pragma push_macro("PackImageHeight")
#  undef PackImageHeight
	.value("PackImageHeight", oglplus::PixelStorageMode::PackImageHeight)
#  pragma pop_macro("PackImageHeight")
# else
	.value("PackImageHeight", oglplus::PixelStorageMode::PackImageHeight)
# endif
#endif
#if defined GL_PACK_SKIP_IMAGES
# if defined PackSkipImages
#  pragma push_macro("PackSkipImages")
#  undef PackSkipImages
	.value("PackSkipImages", oglplus::PixelStorageMode::PackSkipImages)
#  pragma pop_macro("PackSkipImages")
# else
	.value("PackSkipImages", oglplus::PixelStorageMode::PackSkipImages)
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_WIDTH
# if defined PackCompressedBlockWidth
#  pragma push_macro("PackCompressedBlockWidth")
#  undef PackCompressedBlockWidth
	.value("PackCompressedBlockWidth", oglplus::PixelStorageMode::PackCompressedBlockWidth)
#  pragma pop_macro("PackCompressedBlockWidth")
# else
	.value("PackCompressedBlockWidth", oglplus::PixelStorageMode::PackCompressedBlockWidth)
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_HEIGHT
# if defined PackCompressedBlockHeight
#  pragma push_macro("PackCompressedBlockHeight")
#  undef PackCompressedBlockHeight
	.value("PackCompressedBlockHeight", oglplus::PixelStorageMode::PackCompressedBlockHeight)
#  pragma pop_macro("PackCompressedBlockHeight")
# else
	.value("PackCompressedBlockHeight", oglplus::PixelStorageMode::PackCompressedBlockHeight)
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_DEPTH
# if defined PackCompressedBlockDepth
#  pragma push_macro("PackCompressedBlockDepth")
#  undef PackCompressedBlockDepth
	.value("PackCompressedBlockDepth", oglplus::PixelStorageMode::PackCompressedBlockDepth)
#  pragma pop_macro("PackCompressedBlockDepth")
# else
	.value("PackCompressedBlockDepth", oglplus::PixelStorageMode::PackCompressedBlockDepth)
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_SIZE
# if defined PackCompressedBlockSize
#  pragma push_macro("PackCompressedBlockSize")
#  undef PackCompressedBlockSize
	.value("PackCompressedBlockSize", oglplus::PixelStorageMode::PackCompressedBlockSize)
#  pragma pop_macro("PackCompressedBlockSize")
# else
	.value("PackCompressedBlockSize", oglplus::PixelStorageMode::PackCompressedBlockSize)
# endif
#endif
#if defined GL_UNPACK_SWAP_BYTES
# if defined UnpackSwapBytes
#  pragma push_macro("UnpackSwapBytes")
#  undef UnpackSwapBytes
	.value("UnpackSwapBytes", oglplus::PixelStorageMode::UnpackSwapBytes)
#  pragma pop_macro("UnpackSwapBytes")
# else
	.value("UnpackSwapBytes", oglplus::PixelStorageMode::UnpackSwapBytes)
# endif
#endif
#if defined GL_UNPACK_LSB_FIRST
# if defined UnpackLsbFirst
#  pragma push_macro("UnpackLsbFirst")
#  undef UnpackLsbFirst
	.value("UnpackLsbFirst", oglplus::PixelStorageMode::UnpackLsbFirst)
#  pragma pop_macro("UnpackLsbFirst")
# else
	.value("UnpackLsbFirst", oglplus::PixelStorageMode::UnpackLsbFirst)
# endif
#endif
#if defined GL_UNPACK_ROW_LENGTH
# if defined UnpackRowLength
#  pragma push_macro("UnpackRowLength")
#  undef UnpackRowLength
	.value("UnpackRowLength", oglplus::PixelStorageMode::UnpackRowLength)
#  pragma pop_macro("UnpackRowLength")
# else
	.value("UnpackRowLength", oglplus::PixelStorageMode::UnpackRowLength)
# endif
#endif
#if defined GL_UNPACK_SKIP_ROWS
# if defined UnpackSkipRows
#  pragma push_macro("UnpackSkipRows")
#  undef UnpackSkipRows
	.value("UnpackSkipRows", oglplus::PixelStorageMode::UnpackSkipRows)
#  pragma pop_macro("UnpackSkipRows")
# else
	.value("UnpackSkipRows", oglplus::PixelStorageMode::UnpackSkipRows)
# endif
#endif
#if defined GL_UNPACK_SKIP_PIXELS
# if defined UnpackSkipPixels
#  pragma push_macro("UnpackSkipPixels")
#  undef UnpackSkipPixels
	.value("UnpackSkipPixels", oglplus::PixelStorageMode::UnpackSkipPixels)
#  pragma pop_macro("UnpackSkipPixels")
# else
	.value("UnpackSkipPixels", oglplus::PixelStorageMode::UnpackSkipPixels)
# endif
#endif
#if defined GL_UNPACK_ALIGNMENT
# if defined UnpackAlignment
#  pragma push_macro("UnpackAlignment")
#  undef UnpackAlignment
	.value("UnpackAlignment", oglplus::PixelStorageMode::UnpackAlignment)
#  pragma pop_macro("UnpackAlignment")
# else
	.value("UnpackAlignment", oglplus::PixelStorageMode::UnpackAlignment)
# endif
#endif
#if defined GL_UNPACK_IMAGE_HEIGHT
# if defined UnpackImageHeight
#  pragma push_macro("UnpackImageHeight")
#  undef UnpackImageHeight
	.value("UnpackImageHeight", oglplus::PixelStorageMode::UnpackImageHeight)
#  pragma pop_macro("UnpackImageHeight")
# else
	.value("UnpackImageHeight", oglplus::PixelStorageMode::UnpackImageHeight)
# endif
#endif
#if defined GL_UNPACK_SKIP_IMAGES
# if defined UnpackSkipImages
#  pragma push_macro("UnpackSkipImages")
#  undef UnpackSkipImages
	.value("UnpackSkipImages", oglplus::PixelStorageMode::UnpackSkipImages)
#  pragma pop_macro("UnpackSkipImages")
# else
	.value("UnpackSkipImages", oglplus::PixelStorageMode::UnpackSkipImages)
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_WIDTH
# if defined UnpackCompressedBlockWidth
#  pragma push_macro("UnpackCompressedBlockWidth")
#  undef UnpackCompressedBlockWidth
	.value("UnpackCompressedBlockWidth", oglplus::PixelStorageMode::UnpackCompressedBlockWidth)
#  pragma pop_macro("UnpackCompressedBlockWidth")
# else
	.value("UnpackCompressedBlockWidth", oglplus::PixelStorageMode::UnpackCompressedBlockWidth)
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
# if defined UnpackCompressedBlockHeight
#  pragma push_macro("UnpackCompressedBlockHeight")
#  undef UnpackCompressedBlockHeight
	.value("UnpackCompressedBlockHeight", oglplus::PixelStorageMode::UnpackCompressedBlockHeight)
#  pragma pop_macro("UnpackCompressedBlockHeight")
# else
	.value("UnpackCompressedBlockHeight", oglplus::PixelStorageMode::UnpackCompressedBlockHeight)
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_DEPTH
# if defined UnpackCompressedBlockDepth
#  pragma push_macro("UnpackCompressedBlockDepth")
#  undef UnpackCompressedBlockDepth
	.value("UnpackCompressedBlockDepth", oglplus::PixelStorageMode::UnpackCompressedBlockDepth)
#  pragma pop_macro("UnpackCompressedBlockDepth")
# else
	.value("UnpackCompressedBlockDepth", oglplus::PixelStorageMode::UnpackCompressedBlockDepth)
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_SIZE
# if defined UnpackCompressedBlockSize
#  pragma push_macro("UnpackCompressedBlockSize")
#  undef UnpackCompressedBlockSize
	.value("UnpackCompressedBlockSize", oglplus::PixelStorageMode::UnpackCompressedBlockSize)
#  pragma pop_macro("UnpackCompressedBlockSize")
# else
	.value("UnpackCompressedBlockSize", oglplus::PixelStorageMode::UnpackCompressedBlockSize)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::PixelStorageMode) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::PixelStorageMode
		>
	>("aux_CastIterRange_PixelStorageMode");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::PixelStorageMode
	> (*PEnumValueRange)(oglplus::PixelStorageMode) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
