/**
 *  @file oglplus/images/image.hpp
 *  @brief Image data wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_IMAGES_IMAGE_1107121519_HPP
#define OGLPLUS_IMAGES_IMAGE_1107121519_HPP

#include <limits>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <oglplus/math/vector.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/detail/aligned_pod_array.hpp>

namespace oglplus {
namespace images {

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
class Image
{
private:
	GLsizei _width, _height, _depth, _channels;
	PixelDataType _type;
	oglplus::aux::AlignedPODArray _storage;
	double (*_convert)(void*);

	template <typename T>
	static double _do_convert(void* ptr)
	{
		assert(ptr != nullptr);
		const double v = double(*static_cast<T*>(ptr));
		const double n = double(_one((T*)nullptr));
		return v / n;
	}

	bool _is_initialized(void) const;

	static PixelDataFormat _get_def_pdf(unsigned N);
	static PixelDataInternalFormat _get_def_pdif(unsigned N);

protected:
	PixelDataFormat _format;
	PixelDataInternalFormat _internal;

	template <typename T>
	static T _one(T*)
	{
		return std::numeric_limits<T>::max();
	}

	static float _one(float*)
	{
		return 1.0f;
	}

	static double _one(double*)
	{
		return 1.0;
	}

	template <typename T>
	bool _type_ok(void) const
	{
		return _type == PixelDataType(GetDataType<T>());
	}

	template <typename T>
	T* _begin(void)
	{
		assert(_is_initialized());
		assert(_type_ok<T>());
		return static_cast<T*>(_storage.begin());
	}

	unsigned char* _begin_ub(void)
	{
		return _begin<unsigned char>();
	}

	template <typename T>
	T* _end(void)
	{
		assert(_is_initialized());
		assert(_type_ok<T>());
		return static_cast<T*>(_storage.end());
	}

	unsigned char* _end_ub(void)
	{
		return _end<unsigned char>();
	}

	template <typename T>
	T& _at(unsigned x, unsigned y=0, unsigned z=0)
	{
		return *static_cast<T*>(_storage.at(PixelPos(x, y, z)));
	}

	void _bzero(void)
	{
		_storage.fill(0x00);
	}

	Image(void)
	 : _width(0)
	 , _height(0)
	 , _depth(0)
	 , _channels(0)
	 , _convert(nullptr)
	{ }

public:
	Image(const Image& that)
	 : _width(that._width)
	 , _height(that._height)
	 , _depth(that._depth)
	 , _channels(that._channels)
	 , _type(that._type)
	 , _storage(that._storage)
	 , _convert(that._convert)
	 , _format(that._format)
	 , _internal(that._internal)
	{ }

	Image(Image&& tmp)
	 : _width(tmp._width)
	 , _height(tmp._height)
	 , _depth(tmp._depth)
	 , _channels(tmp._channels)
	 , _type(tmp._type)
	 , _storage(std::move(tmp._storage))
	 , _convert(tmp._convert)
	 , _format(tmp._format)
	 , _internal(tmp._internal)
	{ }

	template <typename T>
	Image(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei channels,
		const T* data
	): _width(width)
	 , _height(height)
	 , _depth(depth)
	 , _channels(channels)
	 , _type(PixelDataType(GetDataType<T>()))
	 , _storage(oglplus::aux::AlignedPODArray(data, _width*_height*_depth*_channels))
	 , _convert(&_do_convert<T>)
	 , _format(_get_def_pdf(channels))
	 , _internal(_get_def_pdif(channels))
	{ }

	template <typename T>
	Image(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei channels,
		const T* data,
		PixelDataFormat format,
		PixelDataInternalFormat internal
	): _width(width)
	 , _height(height)
	 , _depth(depth)
	 , _channels(channels)
	 , _type(PixelDataType(GetDataType<T>()))
	 , _storage(oglplus::aux::AlignedPODArray(data, _width*_height*_depth*_channels))
	 , _convert(&_do_convert<T>)
	 , _format(format)
	 , _internal(internal)
	{ }

	Image& operator = (Image&& tmp)
	{
		_width = tmp._width;
		_height = tmp._height;
		_depth = tmp._depth;
		_channels = tmp._channels;
		_type = tmp._type;
		_storage = std::move(tmp._storage);
		_convert = tmp._convert;
		_format = tmp._format;
		_internal = tmp._internal;
		return *this;
	}

	/// Returns the i-th dimension of the image
	/**
	 *  0: Width
	 *  1: Height
	 *  2: Depth
	 *  3: Channels
	 */
	GLsizei Dimension(std::size_t i) const
	{
		if(i == 0) return Width();
		if(i == 1) return Height();
		if(i == 2) return Depth();
		if(i == 3) return Channels();
		assert(!"Invalid image dimension specified");
		return -1;
	}


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

	/// Returns the number of channels
	GLsizei Channels(void) const
	{
		return _channels;
	}

	/// Returns the pixel data type
	PixelDataType Type(void) const
	{
		assert(_is_initialized());
		return _type;
	}

	/// Return the pixel data format
	PixelDataFormat Format(void) const
	{
		assert(_is_initialized());
		return _format;
	}

	/// Return a suitable pixel data internal format
	PixelDataInternalFormat InternalFormat(void) const
	{
		assert(_is_initialized());
		return _internal;
	}

	/// Returns a pointer to the data
	template <typename T>
	const T* Data(void) const
	{
		assert(_is_initialized());
		assert(_type_ok<T>());
		return static_cast<T*>(_storage.begin());
	}

	/// Returns an untyped pointer to the data
	const void* RawData(void) const
	{
		assert(_is_initialized());
		return _storage.begin();
	}

	/// Returns the size of data in bytes
	std::size_t DataSize(void) const
	{
		assert(_is_initialized());
		return _storage.size();
	}

	std::size_t PixelPos(
		GLsizei width,
		GLsizei height,
		GLsizei depth
	) const
	{
		assert(_is_initialized());
		assert(width >= 0);
		assert(height >= 0);
		assert(depth >= 0);
		assert(width < Width());
		assert(height < Height());
		assert(depth < Depth());
		GLsizei ppos = depth*Height()*Width()+height*Width()+width;
		return std::size_t(ppos*Channels());
	}

	/// Returns the pixel at the specified coordinates
	Vector<double, 4> Pixel(
		GLsizei width,
		GLsizei height,
		GLsizei depth
	) const
	{
		assert(_convert);

		std::size_t ppos = PixelPos(width, height, depth);
		return Vector<double, 4>(
			_channels>0?_convert(_storage.at(ppos+0)):0.0,
			_channels>1?_convert(_storage.at(ppos+1)):0.0,
			_channels>2?_convert(_storage.at(ppos+2)):0.0,
			_channels>3?_convert(_storage.at(ppos+3)):0.0
		);
	}

	std::size_t ComponentPos(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei component
	) const
	{
		std::size_t ppos = PixelPos(width, height, depth);
		return std::size_t(ppos+component);
	}

	/// Returns the component of the pixel at the specified coordinates
	double Component(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei component
	) const
	{
		if(component >= Channels()) return 0.0;
		assert(_convert);
		return _convert(_storage.at(ComponentPos(
			width,
			height,
			depth,
			component
		)));
	}

	/// Returns the component of the pixel at the specified coordinates
	template <typename T>
	T ComponentAs(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei component
	) const
	{
		assert(_type_ok<T>());
		if(component >= Channels()) return T(0);
		return *static_cast<T*>(_storage.at(ComponentPos(
			width,
			height,
			depth,
			component
		)));
	}
};

} // namespace images
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/images/image.ipp>
#endif

#endif // include guard
