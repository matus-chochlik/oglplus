/*
 *  .file oglplus/enums/pixel_storage_mode_names.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/pixel_storage_mode.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace enums {
OGLPLUS_LIB_FUNC StrLit ValueName_(
	PixelStorageMode*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_PIXELSTORAGEMODE)
#define OGLPLUS_IMPL_EVN_PIXELSTORAGEMODE
{
switch(value)
{
#if defined GL_PACK_SWAP_BYTES
	case GL_PACK_SWAP_BYTES: return StrLit("PACK_SWAP_BYTES");
#endif
#if defined GL_PACK_LSB_FIRST
	case GL_PACK_LSB_FIRST: return StrLit("PACK_LSB_FIRST");
#endif
#if defined GL_PACK_ROW_LENGTH
	case GL_PACK_ROW_LENGTH: return StrLit("PACK_ROW_LENGTH");
#endif
#if defined GL_PACK_SKIP_ROWS
	case GL_PACK_SKIP_ROWS: return StrLit("PACK_SKIP_ROWS");
#endif
#if defined GL_PACK_SKIP_PIXELS
	case GL_PACK_SKIP_PIXELS: return StrLit("PACK_SKIP_PIXELS");
#endif
#if defined GL_PACK_ALIGNMENT
	case GL_PACK_ALIGNMENT: return StrLit("PACK_ALIGNMENT");
#endif
#if defined GL_PACK_IMAGE_HEIGHT
	case GL_PACK_IMAGE_HEIGHT: return StrLit("PACK_IMAGE_HEIGHT");
#endif
#if defined GL_PACK_SKIP_IMAGES
	case GL_PACK_SKIP_IMAGES: return StrLit("PACK_SKIP_IMAGES");
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_WIDTH
	case GL_PACK_COMPRESSED_BLOCK_WIDTH: return StrLit("PACK_COMPRESSED_BLOCK_WIDTH");
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_HEIGHT
	case GL_PACK_COMPRESSED_BLOCK_HEIGHT: return StrLit("PACK_COMPRESSED_BLOCK_HEIGHT");
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_DEPTH
	case GL_PACK_COMPRESSED_BLOCK_DEPTH: return StrLit("PACK_COMPRESSED_BLOCK_DEPTH");
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_SIZE
	case GL_PACK_COMPRESSED_BLOCK_SIZE: return StrLit("PACK_COMPRESSED_BLOCK_SIZE");
#endif
#if defined GL_UNPACK_SWAP_BYTES
	case GL_UNPACK_SWAP_BYTES: return StrLit("UNPACK_SWAP_BYTES");
#endif
#if defined GL_UNPACK_LSB_FIRST
	case GL_UNPACK_LSB_FIRST: return StrLit("UNPACK_LSB_FIRST");
#endif
#if defined GL_UNPACK_ROW_LENGTH
	case GL_UNPACK_ROW_LENGTH: return StrLit("UNPACK_ROW_LENGTH");
#endif
#if defined GL_UNPACK_SKIP_ROWS
	case GL_UNPACK_SKIP_ROWS: return StrLit("UNPACK_SKIP_ROWS");
#endif
#if defined GL_UNPACK_SKIP_PIXELS
	case GL_UNPACK_SKIP_PIXELS: return StrLit("UNPACK_SKIP_PIXELS");
#endif
#if defined GL_UNPACK_ALIGNMENT
	case GL_UNPACK_ALIGNMENT: return StrLit("UNPACK_ALIGNMENT");
#endif
#if defined GL_UNPACK_IMAGE_HEIGHT
	case GL_UNPACK_IMAGE_HEIGHT: return StrLit("UNPACK_IMAGE_HEIGHT");
#endif
#if defined GL_UNPACK_SKIP_IMAGES
	case GL_UNPACK_SKIP_IMAGES: return StrLit("UNPACK_SKIP_IMAGES");
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_WIDTH
	case GL_UNPACK_COMPRESSED_BLOCK_WIDTH: return StrLit("UNPACK_COMPRESSED_BLOCK_WIDTH");
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
	case GL_UNPACK_COMPRESSED_BLOCK_HEIGHT: return StrLit("UNPACK_COMPRESSED_BLOCK_HEIGHT");
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_DEPTH
	case GL_UNPACK_COMPRESSED_BLOCK_DEPTH: return StrLit("UNPACK_COMPRESSED_BLOCK_DEPTH");
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_SIZE
	case GL_UNPACK_COMPRESSED_BLOCK_SIZE: return StrLit("UNPACK_COMPRESSED_BLOCK_SIZE");
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

