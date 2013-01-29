/**
 *  @file oglplus/image.hpp
 *  @brief Image data wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_IMAGE_1107121519_HPP
#define OGLPLUS_IMAGES_IMAGE_1107121519_HPP
#include <limits>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <oglplus/data_type.hpp>

namespace oglplus {
namespace images {

// Helper class for storing (image) PO data
class AlignedPODArray
{
private:
	std::size_t _count;
	std::size_t _sizeof;

	void* _data;

	void (*_delete)(void*);
	void* (*_dup)(const void*, std::size_t);

	template <typename T>
	static void _do_delete(void* ptr)
	{
		delete[] static_cast<T*>(ptr);
	}

	template <typename T>
	static void* _do_dup(const void* src, std::size_t count)
	{
		T* dst = new T[count];
		if(src != nullptr) std::memcpy(dst, src, count*sizeof(T));
		return static_cast<void*>(dst);
	}

	void* _data_copy(void) const
	{
		if(_dup) return _dup(_data, _count);
		assert(!_data && !_count);
		return nullptr;
	}

	void* _release_data(void)
	{
		void* result = _data;
		_data = nullptr;
		_count = 0;
		return result;
	}

	void _cleanup(void)
	{
		if(_data)
		{
			assert(_delete);
			_delete(_data);
		}
	}
public:
	AlignedPODArray(void)
	 : _count(0)
	 , _sizeof(0)
	 , _data(nullptr)
	 , _delete(nullptr)
	 , _dup(nullptr)
	{ }

	template <typename T>
	AlignedPODArray(const T* data, std::size_t count)
	 : _count(count)
	 , _sizeof(sizeof(T))
	 , _data(_do_dup<T>(static_cast<const void*>(data), count))
	 , _delete(&_do_delete<T>)
	 , _dup(&_do_dup<T>)
	{ }

	AlignedPODArray(AlignedPODArray&& tmp)
	 : _count(tmp._count)
	 , _sizeof(tmp._sizeof)
	 , _data(tmp._release_data())
	 , _delete(tmp._delete)
	 , _dup(tmp._dup)
	{ }

	AlignedPODArray(const AlignedPODArray& that)
	 : _count(that._count)
	 , _sizeof(that._sizeof)
	 , _data(that._data_copy())
	 , _delete(that._delete)
	 , _dup(that._dup)
	{ }

	~AlignedPODArray(void)
	{
		_cleanup();
	}

	AlignedPODArray& operator = (AlignedPODArray&& tmp)
	{
		_cleanup();
		_count = tmp._count;
		_sizeof = tmp._sizeof;
		_data = tmp._release_data();
		_delete = tmp._delete;
		_dup = tmp._dup;
		return *this;
	}

	AlignedPODArray& operator = (const AlignedPODArray& that)
	{
		void* tmp_data = that._data_copy();
		_cleanup();
		_count = that._count;
		_sizeof = that._sizeof;
		_data = tmp_data;
		_delete = that._delete;
		_dup = that._dup;
		return *this;
	}

	void* Begin(void) const
	{
		return const_cast<void*>(_data);
	}

	void* End(void) const
	{
		typedef unsigned char byte;
		return static_cast<void*>(static_cast<byte*>(Begin())+Size());
	}

	void* At(std::size_t offs) const
	{
		assert(!Empty());
		typedef unsigned char byte;
		std::size_t boffs = offs*_sizeof;
		return static_cast<void*>(static_cast<byte*>(Begin())+boffs);
	}

	std::size_t Count(void) const
	{
		return _count;
	}

	std::size_t ElemSize(void) const
	{
		return _sizeof;
	}

	std::size_t Size(void) const
	{
		return Count()*ElemSize();
	}

	bool Empty(void) const
	{
		return _data == nullptr;
	}
};

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
	AlignedPODArray _storage;
	GLdouble (*_convert)(void*);

	template <typename T>
	static GLdouble _do_convert(GLvoid* ptr)
	{
		assert(ptr != nullptr);
		const GLdouble v = GLdouble(*static_cast<T*>(ptr));
		const GLdouble n = GLdouble(_one((T*)nullptr));
		return v / n;
	}

	bool _is_initialized(void) const
	{
		return (!_storage.Empty()) && (_convert != nullptr);
	}

	static PixelDataFormat _get_def_pdf(std::size_t N)
	{
		if(N == 1) return PixelDataFormat::Red;
		else if(N == 2) return PixelDataFormat::RG;
		else if(N == 3) return PixelDataFormat::RGB;
		else if(N == 4) return PixelDataFormat::RGBA;
		else assert(!"Too many color channels!");
		return PixelDataFormat::Red;
	}

	static PixelDataInternalFormat _get_def_pdif(std::size_t N)
	{
		if(N == 1) return PixelDataInternalFormat::Red;
		else if(N == 2) return PixelDataInternalFormat::RG;
		else if(N == 3) return PixelDataInternalFormat::RGB;
		else if(N == 4) return PixelDataInternalFormat::RGBA;
		else assert(!"Too many color channels!");
		return PixelDataInternalFormat::Red;
	}

protected:
	PixelDataFormat _format;
	PixelDataInternalFormat _internal;

	template <typename T>
	static T _one(T*)
	{
		return std::numeric_limits<T>::max();
	}

	static GLfloat _one(GLfloat*)
	{
		return 1.0f;
	}

	static GLdouble _one(GLdouble*)
	{
		return 1.0;
	}

	template <typename T>
	bool _type_ok(void) const
	{
		return _type == PixelDataType(oglplus::GetDataType<T>());
	}

	template <typename T>
	T* _begin(void)
	{
		assert(_is_initialized());
		assert(_type_ok<T>());
		return static_cast<T*>(_storage.Begin());
	}

	GLubyte* _begin_ub(void)
	{
		return _begin<GLubyte>();
	}

	template <typename T>
	T* _end(void)
	{
		assert(_is_initialized());
		assert(_type_ok<T>());
		return static_cast<T*>(_storage.End());
	}

	GLubyte* _end_ub(void)
	{
		return _end<GLubyte>();
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
	 , _storage(AlignedPODArray(data, _width*_height*_depth*_channels))
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
	 , _storage(AlignedPODArray(data, _width*_height*_depth*_channels))
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
		return static_cast<T*>(_storage.Begin());
	}

	/// Returns an untyped pointer to the data
	const void* RawData(void) const
	{
		assert(_is_initialized());
		return _storage.Begin();
	}

	/// Returns the size of data in bytes
	std::size_t DataSize(void) const
	{
		assert(_is_initialized());
		return _storage.Size();
	}

	std::size_t PixelPos(
		GLsizei width,
		GLsizei height,
		GLsizei depth
	) const
	{
		assert(_is_initialized());
		assert(width < Width());
		assert(height < Height());
		assert(depth < Depth());
		GLsizei ppos = depth*Height()*Width()+height*Width()+width;
		return std::size_t(ppos*Channels());
	}

	/// Returns the pixel at the specified coordinates
	Vector<GLdouble, 4> Pixel(
		GLsizei width,
		GLsizei height,
		GLsizei depth
	) const
	{
		assert(_convert);
		std::size_t ppos = PixelPos(width, height, depth);
		return Vector<GLdouble, 4>(
			_convert(_storage.At(ppos+0)),
			_convert(_storage.At(ppos+1)),
			_convert(_storage.At(ppos+2)),
			_convert(_storage.At(ppos+3))
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
	GLdouble Component(
		GLsizei width,
		GLsizei height,
		GLsizei depth,
		GLsizei component
	) const
	{
		if(component >= Channels()) return 0.0;
		assert(_convert);
		return _convert(_storage.At(ComponentPos(
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
		return *static_cast<T*>(_storage.At(ComponentPos(
			width,
			height,
			depth,
			component
		)));
	}
};

} // namespace images
} // namespace oglplus

#endif // include guard
