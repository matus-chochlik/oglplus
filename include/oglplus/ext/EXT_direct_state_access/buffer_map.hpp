/**
 *  @file oglplus/ext/EXT_direct_state_access/buffer_map.hpp
 *  @brief BufferMap wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_MAP_DSA_1309301821_HPP
#define OGLPLUS_BUFFER_MAP_DSA_1309301821_HPP

#include <oglplus/buffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

class DSABufferRawMapEXT
 : public FriendOf<DSABufferEXTOps>
{
private:
	const GLintptr _offset;
	GLsizeiptr _size;
	GLvoid* _ptr;
	const GLuint _name;

	static GLsizeiptr _get_size(GLuint name)
	{
		GLint value = 0;
		OGLPLUS_GLFUNC(GetNamedBufferParameterivEXT)(
			name,
			GL_BUFFER_SIZE,
			&value
		);
		OGLPLUS_CHECK(
			OGLPLUS_ERROR_INFO(GetNamedBufferParameterivEXT)
		);
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
	 *  @param target use the buffer bound to the target specified
	 *  @param offset map offset in units of Type
	 *  @param size map size in units of Type
	 *  @param access the access specifier for the buffer mapping
	 *
	 *  @throws Error
	 */
	DSABufferRawMapEXT(
		const DSABufferEXTOps& buffer,
		GLintptr offset_bytes,
		GLsizeiptr size_bytes,
		Bitfield<BufferMapAccess> access
	): _offset(offset_bytes)
	 , _size(size_bytes)
	 , _ptr(
		OGLPLUS_GLFUNC(MapNamedBufferRangeEXT)(
			FriendOf<DSABufferEXTOps>::GetName(buffer),
			offset_bytes,
			size_bytes,
			GLbitfield(access)
		)
	), _name(FriendOf<DSABufferEXTOps>::GetName(buffer))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MapNamedBufferRangeEXT));
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
	DSABufferRawMapEXT(
		const DSABufferEXTOps& buffer,
		Bitfield<BufferMapAccess> access
	): _offset(0)
	 , _size(_get_size(FriendOf<DSABufferEXTOps>::GetName(buffer)))
	 , _ptr(
		OGLPLUS_GLFUNC(MapNamedBufferEXT)(
			FriendOf<DSABufferEXTOps>::GetName(buffer),
			_translate(GLbitfield(access))
		)
	), _name(FriendOf<DSABufferEXTOps>::GetName(buffer))
	{
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(MapNamedBufferEXT));
	}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	DSABufferRawMapEXT(const DSABufferRawMapEXT&) = delete;
#else
private:
	DSABufferRawMapEXT(const DSABufferRawMapEXT&);
public:
#endif

	/// Move construction is enabled
	DSABufferRawMapEXT(DSABufferRawMapEXT&& temp)
	 : _offset(temp._offset)
	 , _size(temp._size)
	 , _ptr(temp._ptr)
	 , _name(temp._name)
	{
		temp._ptr = nullptr;
	}

	~DSABufferRawMapEXT(void)
	{
		try { Unmap(); }
		catch(...) { }
	}

	/// Unmaps the buffer from client address space
	/**
	 *  @glsymbols
	 *  @glfunref{UnmapNamedBufferEXT}
	 *
	 *  @throws Error
	 */
	void Unmap(void)
	{
		if(_ptr != nullptr)
		{
			OGLPLUS_GLFUNC(UnmapNamedBufferEXT)(_name);
			OGLPLUS_IGNORE(
				OGLPLUS_ERROR_INFO(UnmapNamedBufferEXT)
			);
			_ptr = nullptr;
		}
	}

	/// Returns true if the buffer is mapped
	bool Mapped(void) const
	{
		return _ptr != nullptr;
	}

	/// Returns the size (in bytes) of the mapped buffer
	GLsizeiptr Size(void) const
	{
		return _size;
	}

	/// Returns a const pointer to the mapped data
	/**
	 *  @pre Mapped()
	 */
	const GLvoid* RawData(void) const
	{
		assert(Mapped());
		return _ptr;
	}

	/// Returns a pointer to the mapped data
	/**
	 *  @pre Mapped()
	 */
	GLvoid* RawData(void)
	{
		assert(Mapped());
		return _ptr;
	}
};

/// Untyped mapping of the buffer to the client address space
template <typename Type>
class DSABufferTypedMapEXT
 : public DSABufferRawMapEXT
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
	DSABufferTypedMapEXT(
		const DSABufferEXTOps& buffer,
		GLintptr offset,
		GLsizeiptr size,
		Bitfield<BufferMapAccess> access
	): DSABufferRawMapEXT(
		buffer,
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
	DSABufferTypedMapEXT(
		const DSABufferEXTOps& buffer,
		Bitfield<BufferMapAccess> access
	): DSABufferRawMapEXT(buffer, access)
	{ }

	/// Move construction is enabled
	DSABufferTypedMapEXT(DSABufferTypedMapEXT&& temp)
	 : DSABufferRawMapEXT(static_cast<DSABufferRawMapEXT&&>(temp))
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

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#endif // include guard
