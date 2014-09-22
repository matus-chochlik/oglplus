/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_images_ImageSpec
namespace oglplus {
namespace images {

struct ImageSpec
{
	typedef __OneOf<__DataType, __PixelDataType> PixDataType;

	ImageSpec(void); /*<
	['Nil] image specification.
	>*/

	ImageSpec(
		GLsizei width,
		GLsizei height,
		__PixelDataInternalFormat internal_format
	): /*<
	Specifies a two dimensional image with a particular [^internal_format],
	without any image data.
	Can be used for example to initialize the storage space
	of a __Renderbuffer.
	>*/

	ImageSpec(
		GLsizei width,
		GLsizei height,
		__PixelDataFormat format,
		PixDataType type
	); /*<
	Specifies a two dimensional image with a particular [^format]
	and data [^type], without any image data.
	>*/

	ImageSpec(
		GLsizei width,
		__PixelDataFormat format,
		__PixelDataInternalFormat internal_format,
		PixDataType type
	); /*<
	Specifies a one dimensional image with a particular [^format],
	[^internal_format] and pixel data [^type], without any image
	data.
	>*/

	ImageSpec(
		GLsizei width,
		GLsizei height,
		__PixelDataFormat format,
		__PixelDataInternalFormat internal_format,
		PixDataType type
	); /*<
	Specifies a two dimensional image with a particular [^format],
	[^internal_format] and pixel data [^type], without any image
	data.
	>*/

	ImageSpec(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		__PixelDataFormat format,
		__PixelDataInternalFormat internal_format,
		PixDataType type
	); /*<
	Specifies a three dimensional image with a particular [^format],
	[^internal_format] and pixel data [^type], without any image
	data.
	>*/

	template <typename T>
	ImageSpec(
		GLsizei width,
		__PixelDataFormat format,
		__PixelDataInternalFormat internal_format,
		const T* data
	); /*<
	Specifies a one dimensional image with a particular [^format],
	[^internal_format] and a pointer to pixel [^data]. The data type
	is derived from the type [^T].
	>*/

	template <typename T>
	ImageSpec(
		GLsizei width,
		GLsizei height,
		__PixelDataFormat format,
		const T* data
	); /*<
	Specifies a two dimensional image with a particular [^format],
	and matching internal format and a pointer to pixel [^data].
	The data type is derived from the type [^T].
	>*/

	template <typename T>
	ImageSpec(
		GLsizei w,
		GLsizei h,
		__PixelDataFormat format,
		__PixelDataInternalFormat internal_format,
		const T* data
	); /*<
	Specifies a two dimensional image with a particular [^format],
	[^internal_format] and a pointer to pixel [^data]. The data type
	is derived from the type [^T].
	>*/
};

} // namespace images
} // namespace oglplus
//]

