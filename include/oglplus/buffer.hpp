/**
 *  @file oglplus/buffer.hpp
 *  @brief Buffer wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BUFFER_1107121519_HPP
#define OGLPLUS_BUFFER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/limited_value.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/auxiliary/binding_query.hpp>

#include <vector>
#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the uniform buffer binding point index
class UniformBufferBindingPoint
 : public LimitedCount
{
public:
	/// Construction from a @c GLuint
	UniformBufferBindingPoint(GLuint count);
};
#elif GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	UniformBufferBindingPoint,
	MAX_UNIFORM_BUFFER_BINDINGS
)
#else
typedef GLuint UniformBufferBindingPoint;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the transform feedback buffer binding point index
class TransformFeedbackBufferBindingPoint
 : public LimitedCount
{
public:
	/// Construction from a @c GLuint
	TransformFeedbackBufferBindingPoint(GLuint count);
};
#elif GL_VERSION_4_0 || GL_ARB_transform_feedback3
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	TransformFeedbackBufferBindingPoint,
	MAX_TRANSFORM_FEEDBACK_BUFFERS
)
#else
typedef GLuint TransformFeedbackBufferBindingPoint;
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
		OGLPLUS_GLFUNC(GenBuffers)(count, &_name);
		HandleIfError(OGLPLUS_ERROR_INFO(GenBuffers));
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(DeleteBuffers)(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsBuffer)(_name);
	}

	friend class FriendOf<BufferOps>;
public:
	/// Buffer bind targets
	enum class Target : GLenum {
#include <oglplus/enums/buffer_target.ipp>
	};

protected:
	static GLenum _binding_query(Target target)
	{
		switch(GLenum(target))
		{
#include <oglplus/enums/buffer_target_bq.ipp>
			default:;
		}
		return 0;
	}
	friend class BindingQuery<BufferOps>;
public:

	/// Buffer indexed bind targets
	enum class IndexedTarget : GLenum {
#include <oglplus/enums/buffer_indexed_target.ipp>
	};

	/// Buffer usage
	enum class Usage : GLenum {
#include <oglplus/enums/buffer_usage.ipp>
	};

	// TODO
	/// Mapped data access types
	enum class MapAccess : GLbitfield {
		/// MAP_READ_BIT
		Read = GL_MAP_READ_BIT,
		/// MAP_WRITE_BIT
		Write = GL_MAP_WRITE_BIT,
		/// MAP_READ_BIT | MAP_WRITE_BIT
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
			OGLPLUS_GLFUNC(GetBufferParameteriv)(
				GLenum(target),
				GL_BUFFER_SIZE,
				&value
			);
			HandleIfError(OGLPLUS_ERROR_INFO(GetBufferParameteriv));
			return GLsizeiptr(value);
		}

		static GLenum _translate(MapAccess access)
		{
			switch(access)
			{
				// TODO
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
			OGLPLUS_GLFUNC(MapBufferRange)(
				GLenum(target),
				offset,
				size,
				GLbitfield(access)
			)
		), _target(target)
		{
			HandleIfError(OGLPLUS_ERROR_INFO(MapBufferRange));
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
		 , _ptr(
			OGLPLUS_GLFUNC(MapBuffer)(
				GLenum(target),
				_translate(access)
			)
		), _target(target)
		{
			HandleIfError(OGLPLUS_ERROR_INFO(MapBuffer));
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
			if(_ptr != nullptr)
				OGLPLUS_GLFUNC(UnmapBuffer)(GLenum(_target));
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
		OGLPLUS_GLFUNC(BindBuffer)(GLenum(target), _name);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffer,
			Buffer,
			EnumValueNameTpl(target),
			_name
		));
	}

	/// Unbind the current buffer from the specified target
	/** This function binds the name 0 to the specified @p target.
	 *
	 *  @throws Error
	 */
	static void Unbind(Target target)
	{
		OGLPLUS_GLFUNC(BindBuffer)(GLenum(target), 0);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffer,
			Buffer,
			EnumValueNameTpl(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	/// Bind this buffer to the specified indexed target
	/**
	 *  @throws Error
	 */
	void BindBase(IndexedTarget target, GLuint index) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindBufferBase)(GLenum(target), index, _name);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			BindBufferBase,
			Buffer,
			EnumValueNameTpl(target),
			_name
		));
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
		OGLPLUS_GLFUNC(BindBufferBase)(GLenum(target), index, 0);
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
		OGLPLUS_GLFUNC(BindBufferRange)(
			GLenum(target),
			index,
			_name,
			offset,
			size
		);
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			BindBufferRange,
			Buffer,
			EnumValueNameTpl(target),
			_name
		));
	}

	/// Uploads (sets) the buffer data
	/** This member function uploads @p count units of @c sizeof(GLtype)
	 *  from the location pointed to by @p data to the buffer bound
	 *  to the specified @p target using the @p usage as hint.
	 *
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
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueNameTpl(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	/// Uploads (sets) the buffer data
	/** This member function uploads @p data.size() units of @c sizeof(GLtype)
	 *  from the location pointed to by @p data.data() to the buffer bound
	 *  to the specified @p target using the @p usage as hint.
	 *
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
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			data.size() * sizeof(GLtype),
			data.data(),
			GLenum(usage)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueNameTpl(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	/// Uploads (sets) the buffer data
	/**
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype, size_t N>
	static void Data(
		Target target,
		const std::vector<Vector<GLtype, N> >& data,
		Usage usage = Usage::StaticDraw
	)
	{
		//TODO: is this a good idea ?
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			data.size() * sizeof(GLtype) * N,
			reinterpret_cast<const GLtype*>(data.data()),
			GLenum(usage)
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueNameTpl(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
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
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			offset,
			count * sizeof(GLtype),
			data
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			BufferSubData,
			Buffer,
			EnumValueNameTpl(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
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
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			offset,
			data.size() * sizeof(GLtype),
			data.data()
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			BufferSubData,
			Buffer,
			EnumValueNameTpl(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_copy_buffer
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
		OGLPLUS_GLFUNC(CopyBufferSubData)(
			readtarget._name,
			writetarget._name,
			readoffset,
			writeoffset,
			size
		);
		HandleIfError(OGLPLUS_ERROR_INFO(CopyBufferSubData));
	}
#endif // copy buffer
};

inline const GLchar* EnumValueName(BufferOps::Target value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/buffer_target.ipp>
#endif
	return "";
}

inline const GLchar* EnumValueName(BufferOps::IndexedTarget value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/buffer_indexed_target.ipp>
#endif
	return "";
}

inline const GLchar* EnumValueName(BufferOps::Usage value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/buffer_usage.ipp>
#endif
	return "";
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL buffer functionality
/**
 *  @ingroup objects
 */
class Buffer
 : public BufferOps
{ };
#else
typedef Object<BufferOps, true> Buffer;
#endif

} // namespace oglplus

#endif // include guard
