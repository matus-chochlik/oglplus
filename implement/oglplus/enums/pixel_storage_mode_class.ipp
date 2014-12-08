//  File implement/oglplus/enums/pixel_storage_mode_class.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/pixel_storage_mode.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
template <typename Base, template<PixelStorageMode> class Transform>
class EnumToClass<Base, PixelStorageMode, Transform>
 : public Base
{
private:
	Base& _base(void) { return *this; }
public:

#if defined GL_PACK_SWAP_BYTES
# if defined PackSwapBytes
#  pragma push_macro("PackSwapBytes")
#  undef PackSwapBytes
	Transform<PixelStorageMode::PackSwapBytes> PackSwapBytes;
#  pragma pop_macro("PackSwapBytes")
# else
	Transform<PixelStorageMode::PackSwapBytes> PackSwapBytes;
# endif
#endif
#if defined GL_PACK_LSB_FIRST
# if defined PackLsbFirst
#  pragma push_macro("PackLsbFirst")
#  undef PackLsbFirst
	Transform<PixelStorageMode::PackLsbFirst> PackLsbFirst;
#  pragma pop_macro("PackLsbFirst")
# else
	Transform<PixelStorageMode::PackLsbFirst> PackLsbFirst;
# endif
#endif
#if defined GL_PACK_ROW_LENGTH
# if defined PackRowLength
#  pragma push_macro("PackRowLength")
#  undef PackRowLength
	Transform<PixelStorageMode::PackRowLength> PackRowLength;
#  pragma pop_macro("PackRowLength")
# else
	Transform<PixelStorageMode::PackRowLength> PackRowLength;
# endif
#endif
#if defined GL_PACK_SKIP_ROWS
# if defined PackSkipRows
#  pragma push_macro("PackSkipRows")
#  undef PackSkipRows
	Transform<PixelStorageMode::PackSkipRows> PackSkipRows;
#  pragma pop_macro("PackSkipRows")
# else
	Transform<PixelStorageMode::PackSkipRows> PackSkipRows;
# endif
#endif
#if defined GL_PACK_SKIP_PIXELS
# if defined PackSkipPixels
#  pragma push_macro("PackSkipPixels")
#  undef PackSkipPixels
	Transform<PixelStorageMode::PackSkipPixels> PackSkipPixels;
#  pragma pop_macro("PackSkipPixels")
# else
	Transform<PixelStorageMode::PackSkipPixels> PackSkipPixels;
# endif
#endif
#if defined GL_PACK_ALIGNMENT
# if defined PackAlignment
#  pragma push_macro("PackAlignment")
#  undef PackAlignment
	Transform<PixelStorageMode::PackAlignment> PackAlignment;
#  pragma pop_macro("PackAlignment")
# else
	Transform<PixelStorageMode::PackAlignment> PackAlignment;
# endif
#endif
#if defined GL_PACK_IMAGE_HEIGHT
# if defined PackImageHeight
#  pragma push_macro("PackImageHeight")
#  undef PackImageHeight
	Transform<PixelStorageMode::PackImageHeight> PackImageHeight;
#  pragma pop_macro("PackImageHeight")
# else
	Transform<PixelStorageMode::PackImageHeight> PackImageHeight;
# endif
#endif
#if defined GL_PACK_SKIP_IMAGES
# if defined PackSkipImages
#  pragma push_macro("PackSkipImages")
#  undef PackSkipImages
	Transform<PixelStorageMode::PackSkipImages> PackSkipImages;
#  pragma pop_macro("PackSkipImages")
# else
	Transform<PixelStorageMode::PackSkipImages> PackSkipImages;
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_WIDTH
# if defined PackCompressedBlockWidth
#  pragma push_macro("PackCompressedBlockWidth")
#  undef PackCompressedBlockWidth
	Transform<PixelStorageMode::PackCompressedBlockWidth> PackCompressedBlockWidth;
#  pragma pop_macro("PackCompressedBlockWidth")
# else
	Transform<PixelStorageMode::PackCompressedBlockWidth> PackCompressedBlockWidth;
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_HEIGHT
# if defined PackCompressedBlockHeight
#  pragma push_macro("PackCompressedBlockHeight")
#  undef PackCompressedBlockHeight
	Transform<PixelStorageMode::PackCompressedBlockHeight> PackCompressedBlockHeight;
#  pragma pop_macro("PackCompressedBlockHeight")
# else
	Transform<PixelStorageMode::PackCompressedBlockHeight> PackCompressedBlockHeight;
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_DEPTH
# if defined PackCompressedBlockDepth
#  pragma push_macro("PackCompressedBlockDepth")
#  undef PackCompressedBlockDepth
	Transform<PixelStorageMode::PackCompressedBlockDepth> PackCompressedBlockDepth;
#  pragma pop_macro("PackCompressedBlockDepth")
# else
	Transform<PixelStorageMode::PackCompressedBlockDepth> PackCompressedBlockDepth;
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_SIZE
# if defined PackCompressedBlockSize
#  pragma push_macro("PackCompressedBlockSize")
#  undef PackCompressedBlockSize
	Transform<PixelStorageMode::PackCompressedBlockSize> PackCompressedBlockSize;
#  pragma pop_macro("PackCompressedBlockSize")
# else
	Transform<PixelStorageMode::PackCompressedBlockSize> PackCompressedBlockSize;
# endif
#endif
#if defined GL_UNPACK_SWAP_BYTES
# if defined UnpackSwapBytes
#  pragma push_macro("UnpackSwapBytes")
#  undef UnpackSwapBytes
	Transform<PixelStorageMode::UnpackSwapBytes> UnpackSwapBytes;
#  pragma pop_macro("UnpackSwapBytes")
# else
	Transform<PixelStorageMode::UnpackSwapBytes> UnpackSwapBytes;
# endif
#endif
#if defined GL_UNPACK_LSB_FIRST
# if defined UnpackLsbFirst
#  pragma push_macro("UnpackLsbFirst")
#  undef UnpackLsbFirst
	Transform<PixelStorageMode::UnpackLsbFirst> UnpackLsbFirst;
#  pragma pop_macro("UnpackLsbFirst")
# else
	Transform<PixelStorageMode::UnpackLsbFirst> UnpackLsbFirst;
# endif
#endif
#if defined GL_UNPACK_ROW_LENGTH
# if defined UnpackRowLength
#  pragma push_macro("UnpackRowLength")
#  undef UnpackRowLength
	Transform<PixelStorageMode::UnpackRowLength> UnpackRowLength;
#  pragma pop_macro("UnpackRowLength")
# else
	Transform<PixelStorageMode::UnpackRowLength> UnpackRowLength;
# endif
#endif
#if defined GL_UNPACK_SKIP_ROWS
# if defined UnpackSkipRows
#  pragma push_macro("UnpackSkipRows")
#  undef UnpackSkipRows
	Transform<PixelStorageMode::UnpackSkipRows> UnpackSkipRows;
#  pragma pop_macro("UnpackSkipRows")
# else
	Transform<PixelStorageMode::UnpackSkipRows> UnpackSkipRows;
# endif
#endif
#if defined GL_UNPACK_SKIP_PIXELS
# if defined UnpackSkipPixels
#  pragma push_macro("UnpackSkipPixels")
#  undef UnpackSkipPixels
	Transform<PixelStorageMode::UnpackSkipPixels> UnpackSkipPixels;
#  pragma pop_macro("UnpackSkipPixels")
# else
	Transform<PixelStorageMode::UnpackSkipPixels> UnpackSkipPixels;
# endif
#endif
#if defined GL_UNPACK_ALIGNMENT
# if defined UnpackAlignment
#  pragma push_macro("UnpackAlignment")
#  undef UnpackAlignment
	Transform<PixelStorageMode::UnpackAlignment> UnpackAlignment;
#  pragma pop_macro("UnpackAlignment")
# else
	Transform<PixelStorageMode::UnpackAlignment> UnpackAlignment;
# endif
#endif
#if defined GL_UNPACK_IMAGE_HEIGHT
# if defined UnpackImageHeight
#  pragma push_macro("UnpackImageHeight")
#  undef UnpackImageHeight
	Transform<PixelStorageMode::UnpackImageHeight> UnpackImageHeight;
#  pragma pop_macro("UnpackImageHeight")
# else
	Transform<PixelStorageMode::UnpackImageHeight> UnpackImageHeight;
# endif
#endif
#if defined GL_UNPACK_SKIP_IMAGES
# if defined UnpackSkipImages
#  pragma push_macro("UnpackSkipImages")
#  undef UnpackSkipImages
	Transform<PixelStorageMode::UnpackSkipImages> UnpackSkipImages;
#  pragma pop_macro("UnpackSkipImages")
# else
	Transform<PixelStorageMode::UnpackSkipImages> UnpackSkipImages;
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_WIDTH
# if defined UnpackCompressedBlockWidth
#  pragma push_macro("UnpackCompressedBlockWidth")
#  undef UnpackCompressedBlockWidth
	Transform<PixelStorageMode::UnpackCompressedBlockWidth> UnpackCompressedBlockWidth;
#  pragma pop_macro("UnpackCompressedBlockWidth")
# else
	Transform<PixelStorageMode::UnpackCompressedBlockWidth> UnpackCompressedBlockWidth;
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
# if defined UnpackCompressedBlockHeight
#  pragma push_macro("UnpackCompressedBlockHeight")
#  undef UnpackCompressedBlockHeight
	Transform<PixelStorageMode::UnpackCompressedBlockHeight> UnpackCompressedBlockHeight;
#  pragma pop_macro("UnpackCompressedBlockHeight")
# else
	Transform<PixelStorageMode::UnpackCompressedBlockHeight> UnpackCompressedBlockHeight;
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_DEPTH
# if defined UnpackCompressedBlockDepth
#  pragma push_macro("UnpackCompressedBlockDepth")
#  undef UnpackCompressedBlockDepth
	Transform<PixelStorageMode::UnpackCompressedBlockDepth> UnpackCompressedBlockDepth;
#  pragma pop_macro("UnpackCompressedBlockDepth")
# else
	Transform<PixelStorageMode::UnpackCompressedBlockDepth> UnpackCompressedBlockDepth;
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_SIZE
# if defined UnpackCompressedBlockSize
#  pragma push_macro("UnpackCompressedBlockSize")
#  undef UnpackCompressedBlockSize
	Transform<PixelStorageMode::UnpackCompressedBlockSize> UnpackCompressedBlockSize;
#  pragma pop_macro("UnpackCompressedBlockSize")
# else
	Transform<PixelStorageMode::UnpackCompressedBlockSize> UnpackCompressedBlockSize;
# endif
#endif

	EnumToClass(void) { }
	EnumToClass(Base&& base)
	 : Base(std::move(base))
#if defined GL_PACK_SWAP_BYTES
# if defined PackSwapBytes
#  pragma push_macro("PackSwapBytes")
#  undef PackSwapBytes
	 , PackSwapBytes(_base())
#  pragma pop_macro("PackSwapBytes")
# else
	 , PackSwapBytes(_base())
# endif
#endif
#if defined GL_PACK_LSB_FIRST
# if defined PackLsbFirst
#  pragma push_macro("PackLsbFirst")
#  undef PackLsbFirst
	 , PackLsbFirst(_base())
#  pragma pop_macro("PackLsbFirst")
# else
	 , PackLsbFirst(_base())
# endif
#endif
#if defined GL_PACK_ROW_LENGTH
# if defined PackRowLength
#  pragma push_macro("PackRowLength")
#  undef PackRowLength
	 , PackRowLength(_base())
#  pragma pop_macro("PackRowLength")
# else
	 , PackRowLength(_base())
# endif
#endif
#if defined GL_PACK_SKIP_ROWS
# if defined PackSkipRows
#  pragma push_macro("PackSkipRows")
#  undef PackSkipRows
	 , PackSkipRows(_base())
#  pragma pop_macro("PackSkipRows")
# else
	 , PackSkipRows(_base())
# endif
#endif
#if defined GL_PACK_SKIP_PIXELS
# if defined PackSkipPixels
#  pragma push_macro("PackSkipPixels")
#  undef PackSkipPixels
	 , PackSkipPixels(_base())
#  pragma pop_macro("PackSkipPixels")
# else
	 , PackSkipPixels(_base())
# endif
#endif
#if defined GL_PACK_ALIGNMENT
# if defined PackAlignment
#  pragma push_macro("PackAlignment")
#  undef PackAlignment
	 , PackAlignment(_base())
#  pragma pop_macro("PackAlignment")
# else
	 , PackAlignment(_base())
# endif
#endif
#if defined GL_PACK_IMAGE_HEIGHT
# if defined PackImageHeight
#  pragma push_macro("PackImageHeight")
#  undef PackImageHeight
	 , PackImageHeight(_base())
#  pragma pop_macro("PackImageHeight")
# else
	 , PackImageHeight(_base())
# endif
#endif
#if defined GL_PACK_SKIP_IMAGES
# if defined PackSkipImages
#  pragma push_macro("PackSkipImages")
#  undef PackSkipImages
	 , PackSkipImages(_base())
#  pragma pop_macro("PackSkipImages")
# else
	 , PackSkipImages(_base())
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_WIDTH
# if defined PackCompressedBlockWidth
#  pragma push_macro("PackCompressedBlockWidth")
#  undef PackCompressedBlockWidth
	 , PackCompressedBlockWidth(_base())
#  pragma pop_macro("PackCompressedBlockWidth")
# else
	 , PackCompressedBlockWidth(_base())
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_HEIGHT
# if defined PackCompressedBlockHeight
#  pragma push_macro("PackCompressedBlockHeight")
#  undef PackCompressedBlockHeight
	 , PackCompressedBlockHeight(_base())
#  pragma pop_macro("PackCompressedBlockHeight")
# else
	 , PackCompressedBlockHeight(_base())
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_DEPTH
# if defined PackCompressedBlockDepth
#  pragma push_macro("PackCompressedBlockDepth")
#  undef PackCompressedBlockDepth
	 , PackCompressedBlockDepth(_base())
#  pragma pop_macro("PackCompressedBlockDepth")
# else
	 , PackCompressedBlockDepth(_base())
# endif
#endif
#if defined GL_PACK_COMPRESSED_BLOCK_SIZE
# if defined PackCompressedBlockSize
#  pragma push_macro("PackCompressedBlockSize")
#  undef PackCompressedBlockSize
	 , PackCompressedBlockSize(_base())
#  pragma pop_macro("PackCompressedBlockSize")
# else
	 , PackCompressedBlockSize(_base())
# endif
#endif
#if defined GL_UNPACK_SWAP_BYTES
# if defined UnpackSwapBytes
#  pragma push_macro("UnpackSwapBytes")
#  undef UnpackSwapBytes
	 , UnpackSwapBytes(_base())
#  pragma pop_macro("UnpackSwapBytes")
# else
	 , UnpackSwapBytes(_base())
# endif
#endif
#if defined GL_UNPACK_LSB_FIRST
# if defined UnpackLsbFirst
#  pragma push_macro("UnpackLsbFirst")
#  undef UnpackLsbFirst
	 , UnpackLsbFirst(_base())
#  pragma pop_macro("UnpackLsbFirst")
# else
	 , UnpackLsbFirst(_base())
# endif
#endif
#if defined GL_UNPACK_ROW_LENGTH
# if defined UnpackRowLength
#  pragma push_macro("UnpackRowLength")
#  undef UnpackRowLength
	 , UnpackRowLength(_base())
#  pragma pop_macro("UnpackRowLength")
# else
	 , UnpackRowLength(_base())
# endif
#endif
#if defined GL_UNPACK_SKIP_ROWS
# if defined UnpackSkipRows
#  pragma push_macro("UnpackSkipRows")
#  undef UnpackSkipRows
	 , UnpackSkipRows(_base())
#  pragma pop_macro("UnpackSkipRows")
# else
	 , UnpackSkipRows(_base())
# endif
#endif
#if defined GL_UNPACK_SKIP_PIXELS
# if defined UnpackSkipPixels
#  pragma push_macro("UnpackSkipPixels")
#  undef UnpackSkipPixels
	 , UnpackSkipPixels(_base())
#  pragma pop_macro("UnpackSkipPixels")
# else
	 , UnpackSkipPixels(_base())
# endif
#endif
#if defined GL_UNPACK_ALIGNMENT
# if defined UnpackAlignment
#  pragma push_macro("UnpackAlignment")
#  undef UnpackAlignment
	 , UnpackAlignment(_base())
#  pragma pop_macro("UnpackAlignment")
# else
	 , UnpackAlignment(_base())
# endif
#endif
#if defined GL_UNPACK_IMAGE_HEIGHT
# if defined UnpackImageHeight
#  pragma push_macro("UnpackImageHeight")
#  undef UnpackImageHeight
	 , UnpackImageHeight(_base())
#  pragma pop_macro("UnpackImageHeight")
# else
	 , UnpackImageHeight(_base())
# endif
#endif
#if defined GL_UNPACK_SKIP_IMAGES
# if defined UnpackSkipImages
#  pragma push_macro("UnpackSkipImages")
#  undef UnpackSkipImages
	 , UnpackSkipImages(_base())
#  pragma pop_macro("UnpackSkipImages")
# else
	 , UnpackSkipImages(_base())
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_WIDTH
# if defined UnpackCompressedBlockWidth
#  pragma push_macro("UnpackCompressedBlockWidth")
#  undef UnpackCompressedBlockWidth
	 , UnpackCompressedBlockWidth(_base())
#  pragma pop_macro("UnpackCompressedBlockWidth")
# else
	 , UnpackCompressedBlockWidth(_base())
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
# if defined UnpackCompressedBlockHeight
#  pragma push_macro("UnpackCompressedBlockHeight")
#  undef UnpackCompressedBlockHeight
	 , UnpackCompressedBlockHeight(_base())
#  pragma pop_macro("UnpackCompressedBlockHeight")
# else
	 , UnpackCompressedBlockHeight(_base())
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_DEPTH
# if defined UnpackCompressedBlockDepth
#  pragma push_macro("UnpackCompressedBlockDepth")
#  undef UnpackCompressedBlockDepth
	 , UnpackCompressedBlockDepth(_base())
#  pragma pop_macro("UnpackCompressedBlockDepth")
# else
	 , UnpackCompressedBlockDepth(_base())
# endif
#endif
#if defined GL_UNPACK_COMPRESSED_BLOCK_SIZE
# if defined UnpackCompressedBlockSize
#  pragma push_macro("UnpackCompressedBlockSize")
#  undef UnpackCompressedBlockSize
	 , UnpackCompressedBlockSize(_base())
#  pragma pop_macro("UnpackCompressedBlockSize")
# else
	 , UnpackCompressedBlockSize(_base())
# endif
#endif
	{ }
};

} // namespace enums

