/**
 *  @file oglplus/buffer_size.hpp
 *  @brief Object representing Buffer's storage size in bytes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_SIZE_1310102147_HPP
#define OGLPLUS_BUFFER_SIZE_1310102147_HPP

#include <oglplus/size_type.hpp>
#include <vector>
#include <array>

namespace oglplus {

/// This class represents the size of a GPU buffer in bytes
class BufferSize
 : public BigSizeType
{
public:
	/// Construction of zero size
	BufferSize(void)
	 : BigSizeType(0)
	{ }

	/// Construction of the specified size in bytes
	BufferSize(GLsizeiptr size)
	 : BigSizeType(size)
	{ }

	BufferSize(BigSizeType size)
	 : BigSizeType(size)
	{ }

	template <typename T>
	BufferSize(std::size_t count, const T*)
	 : BigSizeType(GLsizeiptr(sizeof(T)*count))
	{ }

	template <typename T, std::size_t N>
	BufferSize(const T (&)[N])
	 : BigSizeType(GLsizeiptr(sizeof(T)*N))
	{ }

	template <typename T, std::size_t N>
	BufferSize(const std::array<T, N>& a)
	 : BigSizeType(GLsizeiptr(sizeof(T)*a.size()))
	{ }

	template <typename T>
	BufferSize(const std::vector<T>& v)
	 : BigSizeType(GLsizeiptr(sizeof(T)*v.size()))
	{ }

	/// Gets the size in bytes
	GLsizeiptr Get(void) const
	{
		return GLsizeiptr(*this);
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
		return BufferSize(Get()+sizeof(T)*count);
	}

	BufferSize Add(const BufferSize& bs) const
	{
		return BufferSize(Get()+bs.Get());
	}
};

template <typename Type>
class BufferTypedSize
 : public BufferSize
{
public:
	BufferTypedSize(void) { }

	BufferTypedSize(BigSizeType count)
	 : BufferSize(std::size_t(count), &TypeTag<Type>())
	{ }
};

} // namespace oglplus

#endif // include guard
