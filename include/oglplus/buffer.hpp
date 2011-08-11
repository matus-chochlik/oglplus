/**
 *  @file oglplus/buffer.hpp
 *  @brief Buffer wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BUFFER_1107121519_HPP
#define OGLPLUS_BUFFER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/limited_value.hpp>
#include <cassert>

namespace oglplus {

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Type for the uniform buffer binding point index
class UniformBufferBindingPoint
 : public LimitedCount
{
public:
	UniformBufferBindingPoint(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	UniformBufferBindingPoint,
	MAX_UNIFORM_BUFFER_BINDINGS
)
#endif

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Type for the transform feedback buffer binding point index
class TransformFeedbackBufferBindingPoint
 : public LimitedCount
{
public:
	TransformFeedbackBufferBindingPoint(GLuint count);
};
#else
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	TransformFeedbackBufferBindingPoint,
	MAX_TRANSFORM_FEEDBACK_BUFFERS
)
#endif

/// Wrapper for OpenGL buffer operations
/**
 *  @note Do not use this class directly, use Buffer instead
 *
 *  @see Buffer
 */
class BufferOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenBuffers(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(GenBuffers));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteBuffers(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsBuffer(_name);
	}

	friend class FriendOf<BufferOps>;
public:
	/// Buffer bind targets
	enum class Target : GLenum {
		Array = GL_ARRAY_BUFFER,
		CopyRead = GL_COPY_READ_BUFFER,
		CopyWrite = GL_COPY_WRITE_BUFFER,
		DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
		ElementArray = GL_ELEMENT_ARRAY_BUFFER,
		PixelPack = GL_PIXEL_PACK_BUFFER,
		PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
		TextureBuffer = GL_TEXTURE_BUFFER,
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
		Uniform = GL_UNIFORM_BUFFER
	};

	/// Buffer indexed bind targets
	enum class IndexedTarget : GLenum {
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
		Uniform = GL_UNIFORM_BUFFER
	};

	/// Buffer usage
	enum class Usage : GLenum {
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY
	};

	/// Mapped data access types
	enum class MapAccess : GLbitfield {
		Read = GL_MAP_READ_BIT,
		Write = GL_MAP_WRITE_BIT,
		ReadWrite = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT
	};

	/// Typed mapping of the buffer to the client address space
	template <typename Type>
	class TypedMap
	{
	private:
		const GLintptr _offset;
		GLsizeiptr _size;
		GLvoid* _ptr;
		const Target _target;

		static GLsizeiptr _get_size(Target target)
		{
			GLint value = 0;
			::glGetBufferParameteriv(
				GLenum(target),
				GL_BUFFER_SIZE,
				&value
			);
			ThrowOnError(OGLPLUS_ERROR_INFO(GetBufferParameteriv));
			return GLsizeiptr(value);
		}

		static GLenum _translate(MapAccess access)
		{
			switch(access)
			{
				case MapAccess::Read: return GL_READ_ONLY;
				case MapAccess::Write: return GL_WRITE_ONLY;
				case MapAccess::ReadWrite: return GL_READ_WRITE;
			}
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
		TypedMap(
			Target target,
			GLintptr offset,
			GLsizeiptr size,
			MapAccess access
		): _offset(offset * sizeof(Type))
		 , _size(size * sizeof(Type))
		 , _ptr(
			::glMapBufferRange(
				GLenum(target),
				offset,
				size,
				GLbitfield(access)
			)
		), _target(target)
		{
			ThrowOnError(OGLPLUS_ERROR_INFO(MapBufferRange));
		}

		/// Maps the whole buffer
		/**
		 *  @param target use the buffer bound to the target specified
		 *  @param access the access specifier for the buffer mapping
		 *
		 *  @throws Error
		 */
		TypedMap(Target target, MapAccess access)
		 : _offset(0)
		 , _size(_get_size(target))
		 , _ptr(::glMapBuffer(GLenum(target), _translate(access)))
		 , _target(target)
		{
			ThrowOnError(OGLPLUS_ERROR_INFO(MapBuffer));
		}

		/// Copying is disabled
		TypedMap(const TypedMap&) = delete;

		/// Move construction is enabled
		TypedMap(TypedMap&& temp)
		 : _offset(temp._offset)
		 , _size(temp._size)
		 , _ptr(temp._ptr)
		 , _target(temp._target)
		{
			temp._ptr = nullptr;
		}

		~TypedMap(void)
		{
			if(_ptr != nullptr) ::glUnmapBuffer(GLenum(_target));
		}

		/// Returns the size (in bytes) of the mapped buffer
		GLsizeiptr Size(void) const
		{
			return _size;
		}

		/// Returns the count of elements of Type in the mapped buffer
		GLsizeiptr Count(void) const
		{
			assert(_size % sizeof(Type) == 0);
			return _size / sizeof(Type);
		}

		/// Returns the pointer to the mapped data
		Type* Data(void) const
		{
			return (Type*)_ptr;
		}

		/// Returns the element at the specified index
		Type& At(GLuint index) const
		{
			assert(_ptr != nullptr);
			assert(((index + 1) * sizeof(Type)) <= _size);
			return ((Type*)_ptr)[index];
		}
	};

	/// Mapping of the buffer to the client address space
	typedef TypedMap<GLubyte> Map;

	/// Bind this buffer to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target target) const
	{
		assert(_name != 0);
		::glBindBuffer(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindBuffer));
	}

	/// Unbind the current buffer from the specified target
	/**
	 *  @throws Error
	 */
	static void Unbind(Target target)
	{
		::glBindBuffer(GLenum(target), 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindBuffer));
	}

	/// Bind this buffer to the specified indexed target
	/**
	 *  @throws Error
	 */
	void BindBase(IndexedTarget target, GLuint index) const
	{
		assert(_name != 0);
		::glBindBufferBase(GLenum(target), index, _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindBufferBase));
	}

	/// Bind this buffer to the specified uniform buffer binding point
	/**
	 *  @throws Error
	 */
	void BindBaseUniform(UniformBufferBindingPoint index) const
	{
		BindBase(IndexedTarget::Uniform, GLuint(index));
	}

	/// Bind this buffer to the specified TFB buffer binding point
	/**
	 *  @throws Error
	 */
	void BindBaseTransformFeedback(
		TransformFeedbackBufferBindingPoint index
	) const
	{
		BindBase(IndexedTarget::TransformFeedback, GLuint(index));
	}

	/// Unbind the current buffer from the specified indexed target
	/**
	 *  @throws Error
	 */
	static void UnbindBase(IndexedTarget target, GLuint index)
	{
		::glBindBufferBase(GLenum(target), index, 0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindBufferBase));
	}

	/// Bind a range in this buffer to the specified indexed target
	/**
	 *  @throws Error
	 */
	void BindRange(
		IndexedTarget target,
		GLuint index,
		GLintptr offset,
		GLsizeiptr size
	) const
	{
		assert(_name != 0);
		::glBindBufferRange(GLenum(target), index, _name, offset, size);
		AssertNoError(OGLPLUS_ERROR_INFO(BindBufferRange));
	}

	/// Uploads (sets) the buffer data
	/**
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void Data(
		Target target,
		GLsizei count,
		GLtype* data,
		Usage usage = Usage::StaticDraw
	)
	{
		::glBufferData(
			GLenum(target),
			count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BufferData));
	}

	/// Uploads (sets) the buffer data
	/**
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void Data(
		Target target,
		const std::vector<GLtype>& data,
		Usage usage = Usage::StaticDraw
	)
	{
		::glBufferData(
			GLenum(target),
			data.size() * sizeof(GLtype),
			data.data(),
			GLenum(usage)
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BufferData));
	}

	/// Uploads (sets) a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void SubData(
		Target target,
		GLintptr offset,
		GLsizei count,
		GLtype* data
	)
	{
		::glBufferData(
			GLenum(target),
			offset,
			count * sizeof(GLtype),
			data
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BufferSubData));
	}

	/// Uploads (sets) a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	static void SubData(
		Target target,
		GLintptr offset,
		const std::vector<GLtype>& data
	)
	{
		::glBufferData(
			GLenum(target),
			offset,
			data.size() * sizeof(GLtype),
			data.data()
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(BufferSubData));
	}

	/// Copy data between buffers
	/**
	 *  @see Data
	 *  @see SubData
	 *  @throws Error
	 */
	friend void CopySubData(
		const BufferOps& readtarget,
		const BufferOps& writetarget,
		GLintptr readoffset,
		GLintptr writeoffset,
		GLsizeiptr size
	)
	{
		::glCopyBufferSubData(
			readtarget._name,
			writetarget._name,
			readoffset,
			writeoffset,
			size
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(CopyBufferSubData));
	}
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates the OpenGL buffer-related functionality
class Buffer
 : public BufferOps
{ };
#else
typedef Object<BufferOps, true> Buffer;
#endif

} // namespace oglplus

#endif // include guard
