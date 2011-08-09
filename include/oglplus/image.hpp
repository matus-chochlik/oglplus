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

namespace oglplus {

/// Wrapper for image data
/** @note Do not use this class directly, use the derived
 *  classes instead.
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
};

} // namespace oglplus

#endif // include guard
