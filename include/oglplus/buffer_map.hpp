/**
 *  @file oglplus/buffer_map.hpp
 *  @brief Buffer map wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_MAP_1107121519_HPP
#define OGLPLUS_BUFFER_MAP_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/buffer_map_access.hpp>
#include <oglplus/buffer_target.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
/// Untyped mapping of the buffer to the client address space
class BufferRawMap
{
private:
	const GLintptr _offset;
	GLsizeiptr _size;
	GLvoid* _ptr;
	const BufferTarget _target;

	static GLsizeiptr _get_size(BufferTarget target)
	{
		GLint value = 0;
		OGLPLUS_GLFUNC(GetBufferParameteriv)(
			GLenum(target),
			GL_BUFFER_SIZE,
			&value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetBufferParameteriv));
		return GLsizeiptr(value);
	}

	static GLenum _translate(GLbitfield access)
	{
		switch(access)
		{
			case GL_MAP_READ_BIT:
				return GL_READ_ONLY;
			case GL_MAP_WRITE_BIT:
				return GL_WRITE_ONLY;
			case GL_MAP_READ_BIT|GL_MAP_WRITE_BIT:
				return GL_READ_WRITE;
		}
		return GL_READ_ONLY;
	}
public:
	/// Maps a range of the buffer
	/**
	 *  @param target use the buffer bound to the specified target
	 *  @param byte_offset map offset in machine bytes
	 *  @param size map size in machine bytes
	 *  @param access the access specifier for the buffer mapping
	 *
	 *  @throws Error
	 */
	BufferRawMap(
		BufferTarget target,
		GLintptr byte_offset,
		GLsizeiptr size_bytes,
		Bitfield<BufferMapAccess> access
	): _offset(byte_offset)
	 , _size(size_bytes)
	 , _ptr(
		OGLPLUS_GLFUNC(MapBufferRange)(
			GLenum(target),
			byte_offset,
			size_bytes,
			GLbitfield(access)
		)
	), _target(target)
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MapBufferRange));
	}

	/// Maps the whole buffer
	/**
	 *  @param target use the buffer bound to the target specified
	 *  @param access the access specifier for the buffer mapping
	 *
	 * This class is non-copyable.
	 *
	 *  @throws Error
	 */
	BufferRawMap(BufferTarget target, Bitfield<BufferMapAccess> access)
	 : _offset(0)
	 , _size(_get_size(target))
	 , _ptr(
		OGLPLUS_GLFUNC(MapBuffer)(
			GLenum(target),
			_translate(GLbitfield(access))
		)
	), _target(target)
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MapBuffer));
	}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	BufferRawMap(const BufferRawMap&) = delete;
#else
private:
	BufferRawMap(const BufferRawMap&);
public:
#endif
	/// Move construction is enabled
	BufferRawMap(BufferRawMap&& temp)
	 : _offset(temp._offset)
	 , _size(temp._size)
	 , _ptr(temp._ptr)
	 , _target(temp._target)
	{
		temp._ptr = nullptr;
	}

	/// Unmaps the buffer from client address space
	~BufferRawMap(void)
	{
		if(_ptr != nullptr)
		{
			OGLPLUS_GLFUNC(UnmapBuffer)(GLenum(_target));
			OGLPLUS_IGNORE(OGLPLUS_ERROR_INFO(UnmapBuffer));
		}
	}

	/// Returns the size (in bytes) of the mapped buffer
	GLsizeiptr Size(void) const
	{
		return _size;
	}

	/// Returns a const pointer to the mapped data
	const GLvoid* RawData(void) const
	{
		return _ptr;
	}

	/// Returns a pointer to the mapped data
	GLvoid* RawData(void)
	{
		return _ptr;
	}
};

/// Typed mapping of the buffer to the client address space
template <typename Type>
class BufferTypedMap
 : public BufferRawMap
{
public:
	/// Maps a range of the buffer
	/**
	 *  @param target use the buffer bound to the target specified
	 *  @param offset map offset in units of Type
	 *  @param size map size in units of Type
	 *  @param access the access specifier for the buffer mapping
	 *
	 *  @throws Error
	 */
	BufferTypedMap(
		BufferTarget target,
		GLintptr offset,
		GLsizeiptr size,
		Bitfield<BufferMapAccess> access
	): BufferRawMap(
		target,
		offset * sizeof(Type),
	 	size * sizeof(Type),
		access
	){ }

	/// Maps the whole buffer
	/**
	 *  @param target use the buffer bound to the target specified
	 *  @param access the access specifier for the buffer mapping
	 *
	 * This class is non-copyable.
	 *
	 *  @throws Error
	 */
	BufferTypedMap(BufferTarget target, Bitfield<BufferMapAccess> access)
	 : BufferRawMap(target, access)
	{ }

	/// Move construction is enabled
	BufferTypedMap(BufferTypedMap&& temp)
	 : BufferRawMap(static_cast<BufferRawMap&&>(temp))
	{ }

	/// Returns the count of elements of Type in the mapped buffer
	GLsizeiptr Count(void) const
	{
		assert(this->Size() % sizeof(Type) == 0);
		return this->Size() / sizeof(Type);
	}

	/// Returns a const pointer to the mapped data
	const Type* Data(void) const
	{
		return static_cast<const Type*>(this->RawData());
	}

	/// Returns a pointer to the mapped data
	Type* Data(void)
	{
		return static_cast<Type*>(this->RawData());
	}

	/// Returns a const reference to the element at the specified index
	const Type& At(GLuint index) const
	{
		assert(Data() != nullptr);
		assert(((index+1)*sizeof(Type)) <= std::size_t(this->Size()));
		return Data()[index];
	}

	/// Returns a reference to the element at the specified index
	Type& At(GLuint index)
	{
		assert(Data() != nullptr);
		assert(((index+1)*sizeof(Type)) <= std::size_t(this->Size()));
		return Data()[index];
	}
};
#endif // GL_VERSION_3_0

} // namespace oglplus

#endif // include guard
