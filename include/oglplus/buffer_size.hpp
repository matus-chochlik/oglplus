/**
 *  @file oglplus/buffer_size.hpp
 *  @brief Object representing Buffer's storage size in bytes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_SIZE_1310102147_HPP
#define OGLPLUS_BUFFER_SIZE_1310102147_HPP

#include <vector>
#include <array>

namespace oglplus {

/// This class represents the size of a GPU buffer in bytes
class BufferSize
{
private:
	GLsizeiptr _size;
public:
	/// Construction of zero size
	BufferSize(void)
	 : _size(0)
	{ }

	/// Construction of the specified size in bytes
	BufferSize(GLsizeiptr size)
	 : _size(size)
	{ }

	template <typename T>
	BufferSize(unsigned count, const T*)
	 : _size(sizeof(T)*count)
	{ }

	template <typename T, std::size_t N>
	BufferSize(const T (&)[N])
	 : _size(sizeof(T)*N)
	{ }

	template <typename T, std::size_t N>
	BufferSize(const std::array<T, N>& a)
	 : _size(sizeof(T)*a.size())
	{ }

	template <typename T>
	BufferSize(const std::vector<T>& v)
	 : _size(sizeof(T)*v.size())
	{ }

	/// Gets the size in bytes
	GLsizeiptr Get(void) const
	{
		return _size;
	}

	/// Makes the size of count instances of T
	template <typename T>
	static BufferSize Of(unsigned count, const T* data = nullptr)
	{
		return BufferSize(count, data);
	}

	/// Add the size of count instances of T
	template <typename T>
	BufferSize Add(unsigned count, const T* = nullptr) const
	{
		return BufferSize(_size+sizeof(T)*count);
	}

	BufferSize Add(const BufferSize& bs)
	{
		return BufferSize(_size+bs._size);
	}
};

template <typename Type>
class BufferTypedSize
 : public BufferSize
{
public:
	BufferTypedSize(void) { }

	BufferTypedSize(GLsizeiptr count)
	 : BufferSize(count, (Type*)nullptr)
	{ }
};

} // namespace oglplus

#endif // include guard
