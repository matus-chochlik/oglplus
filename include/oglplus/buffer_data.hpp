/**
 *  @file oglplus/buffer_data.hpp
 *  @brief Object wrapping data to be stores in a Buffer
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_DATA_1310102147_HPP
#define OGLPLUS_BUFFER_DATA_1310102147_HPP

#include <oglplus/buffer_size.hpp>

namespace oglplus {

class BufferData
{
private:
	BufferSize _size;
	const GLvoid* _data;
public:
	BufferData(BufferSize size, const GLvoid* data)
	 : _size(size)
	 , _data(data)
	{ }

	template <typename T>
	BufferData(GLsizei count, const T* data)
	 : _size(count, data)
	 , _data(data)
	{ }

	template <typename T, std::size_t N>
	BufferData(const T (&data)[N])
	 : _size(data)
	 , _data(data)
	{ }

	template <typename T, std::size_t N>
	BufferData(const std::array<T, N>& a)
	 : _size(a)
	 , _data(a.data())
	{ }

	template <typename T>
	BufferData(const std::vector<T>& v)
	 : _size(v)
	 , _data(v.data())
	{ }

	GLsizeiptr Size(void) const
	{
		return _size.Get();
	}

	const GLvoid* Data(void) const
	{
		return _data;
	}
};

} // namespace oglplus

#endif // include guard
