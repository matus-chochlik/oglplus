/**
 *  @file oglplus/image.hpp
 *  @brief Image data wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGE_1107121519_HPP
#define OGLPLUS_IMAGE_1107121519_HPP

#include <vector>
#include <cassert>

namespace oglplus {

template <typename T>
class ImageInitializer;

/** @defgroup image_load_gen Image loaders and generators
 *
 *  Classes in this group serve for loading or generating one, two or three
 *  dimensional images in various data formats, that can be used for example
 *  as data source for textures.
 *
 *  The @ref oglplus::Texture "Texture" class can take instances of @c Image
 *  directly in its image loading member functions which makes initializing
 *  textures more convenient.
 */

/// Wrapper for (texture) image data
/** @note Do not use this class directly, use the derived
 *  classes instead.
 *
 *  @ingroup image_load_gen
 */
template <typename T>
class Image
{
protected:
	GLsizei _width, _height, _depth;
	std::vector<T> _data;
	PixelDataType _type;
	PixelDataFormat _format;
	PixelDataInternalFormat _internal;

	friend class ImageInitializer<T>;

	Image(void)
	 : _width(1)
	 , _height(1)
	 , _depth(1)
	{ }

	Image(GLsizei width, GLsizei height, GLsizei depth)
	 : _width(width)
	 , _height(height)
	 , _depth(depth)
	{ }
public:
	Image(Image&& tmp)
	 : _width(tmp._width)
	 , _height(tmp._height)
	 , _depth(tmp._depth)
	 , _data(std::move(tmp._data))
	 , _type(tmp._type)
	 , _format(tmp._format)
	 , _internal(tmp._internal)
	{ }

	/// Returns the width of the image
	GLsizei Width(void) const
	{
		return _width;
	}

	/// Returns the height of the image
	GLsizei Height(void) const
	{
		return _height;
	}

	/// Returns the depth of the image
	GLsizei Depth(void) const
	{
		return _depth;
	}

	/// Returns the pixel data type
	PixelDataType Type(void) const
	{
		return _type;
	}

	/// Return the pixel data format
	PixelDataFormat Format(void) const
	{
		return _format;
	}

	/// Return a suitable pixel data internal format
	PixelDataInternalFormat InternalFormat(void) const
	{
		return _internal;
	}

	/// Returns a pointer to the data
	const T* Data(void) const
	{
		return _data.data();
	}

	/// Returns the count of elements in the data in units of T
	size_t ElementCount(void) const
	{
		return _data.size();
	}

	/// Returns an untyped pointer to the data
	const void* RawData(void) const
	{
		return _data.data();
	}

	/// Returns the size of data in bytes
	size_t DataSize(void) const
	{
		return _data.size() * sizeof(T);
	}

	/// Returns the number of bytes per pixel
	size_t BytesPerPixel(void) const
	{
		return sizeof(T);
	}

	/// Returns the number of elements per pixel in units of T
	size_t ElementsPerPixel(void) const
	{
		if(_data.empty()) return 0;
		assert(_data.size() % (_width * _height * _depth) == 0);
		return _data.size() / (_width * _height * _depth);
	}

	/// Returns the component of the pixel at the specified coordinates
	T Component(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei component
	) const
	{
		assert(width < Width());
		assert(height < Height());
		assert(depth < Depth());
		assert(component < ElementsPerPixel());
		GLsizei offs = depth*Height()*Width()+height*Width()+width;
		return *(Data()+offs*ElementsPerPixel()+component);
	}
};

template <typename T>
class ImageInitializer
{
protected:
	void InitImage(
		Image<T>& image,
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		std::vector<T>&& data,
		PixelDataType type,
		PixelDataFormat format,
		PixelDataInternalFormat internal
	)
	{
		image._width = width;
		image._height = height;
		image._depth = depth;
		image._data = ::std::move(data);
		image._type = type;
		image._format = format;
		image._internal = internal;
	}
};

} // namespace oglplus

#endif // include guard
