/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_images_Image
namespace images {

class Image {
public:
    Image(const Image& that);

    Image(Image&& tmp) noexcept;

    Image& operator=(Image&& tmp) noexcept;

    template <typename T>
    Image(
      __SizeType width,
      __SizeType height,
      __SizeType depth,
      __SizeType channels,
      const T* data);

    template <typename T>
    Image(
      __SizeType width,
      __SizeType height,
      __SizeType depth,
      __SizeType channels,
      const T* data,
      __PixelDataFormat format,
      __PixelDataInternalFormat internal);

    GLsizei Dimension(std::size_t i) const
      noexcept; /*<
      Returns the size of the i-th dimension of the image.
      >*/

    GLsizei Width() const noexcept; /*<
                          Returns the width of the image.
                          >*/

    GLsizei Height() const noexcept; /*<
                           Returns the height of the image.
                           >*/

    GLsizei Depth() const noexcept; /*<
                          Returns the depth of the image.
                          >*/

    GLsizei Channels() const noexcept; /*<
                             Returns the number of channels.
                             >*/

    __PixelDataType Type() const noexcept;

    __PixelDataFormat Format() const noexcept;

    __PixelDataInternalFormat InternalFormat() const noexcept;

    template <typename T>
    const T* Data() const noexcept;

    const void* RawData() const noexcept;

    std::size_t DataSize() const noexcept; /*<
                                 Returns the size of data in bytes.
                                 >*/

    // TODO
};

} // namespace images
  //]
