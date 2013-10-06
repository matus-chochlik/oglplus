/**
 *  @file oglplus/buffer.hpp
 *  @brief Buffer wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_1107121519_HPP
#define OGLPLUS_BUFFER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/array.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/bitfield.hpp>
#include <oglplus/limited_value.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/pixel_data.hpp>
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

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the atomic counter buffer binding point index
class AtomicCounterBufferBindingPoint
 : public LimitedCount
{
public:
	/// Construction from a @c GLuint
	AtomicCounterBufferBindingPoint(GLuint count);
};
#elif GL_VERSION_4_2 || GL_ARB_shader_atomic_counters
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	AtomicCounterBufferBindingPoint,
	MAX_ATOMIC_COUNTER_BUFFER_BINDINGS
)
#else
typedef GLuint AtomicCounterBufferBindingPoint;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Type for the shader storage buffer binding point index
class ShaderStorageBufferBindingPoint
 : public LimitedCount
{
public:
	/// Construction from a @c GLuint
	ShaderStorageBufferBindingPoint(GLuint count);
};
#elif GL_VERSION_4_3 || GL_ARB_shader_storage_buffer_object
OGLPLUS_DECLARE_LIMITED_COUNT_TYPE(
	ShaderStorageBufferBindingPoint,
	MAX_SHADER_STORAGE_BUFFER_BINDINGS
)
#else
typedef GLuint ShaderStorageBufferBindingPoint;
#endif

/// Buffer usage enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferUsage, GLenum)
#include <oglplus/enums/buffer_usage.ipp>
OGLPLUS_ENUM_CLASS_END(BufferUsage)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_usage_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_usage_range.ipp>
#endif

/// Buffer map access enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferMapAccess, GLbitfield)
#include <oglplus/enums/buffer_map_access.ipp>
OGLPLUS_ENUM_CLASS_END(BufferMapAccess)
OGLPLUS_MAKE_BITFIELD(BufferMapAccess)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_map_access_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_map_access_range.ipp>
#endif

/// Buffer storage flags/bits
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferStorageBit, GLbitfield)
#include <oglplus/enums/buffer_storage_bit.ipp>
OGLPLUS_ENUM_CLASS_END(BufferStorageBit)

OGLPLUS_MAKE_BITFIELD(BufferStorageBit)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_storage_bit_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_storage_bit_range.ipp>
#endif

/// Buffer bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferTarget, GLenum)
#include <oglplus/enums/buffer_target.ipp>
OGLPLUS_ENUM_CLASS_END(BufferTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_target_range.ipp>
#endif


/// Buffer indexed bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferIndexedTarget, GLenum)
#include <oglplus/enums/buffer_indexed_target.ipp>
OGLPLUS_ENUM_CLASS_END(BufferIndexedTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_indexed_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_indexed_target_range.ipp>
#endif


/// Wrapper for OpenGL buffer operations
/**
 *  @note Do not use this class directly, use Buffer instead
 *
 *  @see Buffer
 *
 *  @glsymbols
 *  @glfunref{GenBuffers}
 *  @glfunref{DeleteBuffers}
 *  @glfunref{IsBuffer}
 */
class BufferOps
 : public Named
 , public BaseObject<true>
{
public:
	/// Buffer bind targets
	typedef BufferTarget Target;

	/// Buffer indexed bind targets
	typedef BufferIndexedTarget IndexedTarget;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenBuffers)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenBuffers));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteBuffers)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsBuffer)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_BUFFER
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Buffer;
	}
#endif

	static void _bind(GLuint _name, Target target)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindBuffer)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffer,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	friend class FriendOf<BufferOps>;

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

	static GLint GetIntParam(Target target, GLenum query)
	{
		GLint value = 0;
		OGLPLUS_GLFUNC(GetBufferParameteriv)(
			GLenum(target),
			query,
			&value
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetBufferParameteriv));
		return value;
	}

public:
	/// Types related to Buffer
	struct Property
	{
		/// The Buffer usage mode
		typedef BufferUsage Usage;

		/// The buffer map access mode
		typedef BufferMapAccess MapAccess;
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
			Bitfield<BufferMapAccess> access
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
		TypedMap(Target target, Bitfield<BufferMapAccess> access)
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
		TypedMap(const TypedMap&) = delete;
#else
	private:
		TypedMap(const TypedMap&);
	public:
#endif

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
			assert(((index+1)*sizeof(Type)) <= std::size_t(_size));
			return ((Type*)_ptr)[index];
		}
	};

	/// Mapping of the buffer to the client address space
	typedef TypedMap<GLubyte> Map;

	/// Returns true if the buffer is mapped
	/**
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_MAPPED}
	 *
	 *  @throws Error
	 */
	static bool Mapped(Target target)
	{
		return GetIntParam(target, GL_BUFFER_MAPPED) == GL_TRUE;
	}

	/// Bind this buffer to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target target) const
	{
		_bind(_name, target);
	}

	/// Unbind the current buffer from the specified target
	/** This function binds the name 0 to the specified @p target.
	 *
	 *  @throws Error
	 */
	static void Unbind(Target target)
	{
		OGLPLUS_GLFUNC(BindBuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffer,
			Buffer,
			EnumValueName(target),
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
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBufferBase,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback3
	/// Bind this buffer to the specified uniform buffer binding point
	/**
	 *  @throws Error
	 */
	void BindBaseUniform(UniformBufferBindingPoint index) const
	{
		BindBase(IndexedTarget::Uniform, GLuint(index));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback3
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
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2 || GL_ARB_shader_atomic_counters
	/// Bind this buffer to the specified atomic counter buffer binding point
	/**
	 *  @throws Error
	 */
	void BindBaseAtomicCounter(
		AtomicCounterBufferBindingPoint index
	) const
	{
		BindBase(IndexedTarget::AtomicCounter, GLuint(index));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_shader_storage_buffer_object
	/// Bind this buffer to the specified shader storage buffer binding point
	/**
	 *  @throws Error
	 */
	void BindBaseShaderStorage(
		ShaderStorageBufferBindingPoint index
	) const
	{
		BindBase(IndexedTarget::ShaderStorage, GLuint(index));
	}
#endif

	/// Unbind the current buffer from the specified indexed target
	/**
	 *  @throws Error
	 */
	static void UnbindBase(IndexedTarget target, GLuint index)
	{
		OGLPLUS_GLFUNC(BindBufferBase)(GLenum(target), index, 0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindBufferBase));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	static void BindBase(
		BufferIndexedTarget target,
		GLuint first,
		GLsizei count,
		const GLuint* names
	)
	{
		OGLPLUS_GLFUNC(BindBuffersBase)(
			GLenum(target),
			first,
			count,
			names
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffersBase,
			Buffer,
			EnumValueName(target),
			0
		));
	}
#endif

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
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBufferRange,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	static void BindRange(
		BufferIndexedTarget target,
		GLuint first,
		GLsizei count,
		const GLuint* names,
		const GLintptr* offsets,
		const GLsizeiptr* sizes
	)
	{
		OGLPLUS_GLFUNC(BindBuffersRange)(
			GLenum(target),
			first,
			count,
			names,
			offsets,
			sizes
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffersRange,
			Buffer,
			EnumValueName(target),
			0
		));
	}
#endif

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
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	template <typename GLtype, std::size_t Count>
	static void Data(
		Target target,
		GLtype (&data)[Count],
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			Count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueName(target),
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
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			data.size() * sizeof(GLtype),
			data.data(),
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	/// Uploads (sets) the buffer data
	/**
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype, std::size_t N>
	static void Data(
		Target target,
		const std::vector<Vector<GLtype, N> >& data,
		BufferUsage usage = BufferUsage::StaticDraw
	)
	{
		//TODO: is this a good idea ?
		OGLPLUS_GLFUNC(BufferData)(
			GLenum(target),
			data.size() * sizeof(GLtype) * N,
			reinterpret_cast<const GLtype*>(data.data()),
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferData,
			Buffer,
			EnumValueName(target),
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
		OGLPLUS_GLFUNC(BufferSubData)(
			GLenum(target),
			offset * sizeof(GLtype),
			count * sizeof(GLtype),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferSubData,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	template <typename GLtype, std::size_t Count>
	static void SubData(
		Target target,
		GLintptr offset,
		GLtype (&data)[Count]
	)
	{
		OGLPLUS_GLFUNC(BufferSubData)(
			GLenum(target),
			offset * sizeof(GLtype),
			Count * sizeof(GLtype),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferSubData,
			Buffer,
			EnumValueName(target),
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
		OGLPLUS_GLFUNC(BufferSubData)(
			GLenum(target),
			offset * sizeof(GLtype),
			data.size() * sizeof(GLtype),
			data.data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferSubData,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_copy_buffer
	/// Copy data between buffers
	/**
	 *  @see Data
	 *  @see SubData
	 *  @throws Error
	 *
	 *  @glvoereq{3,1,ARB,copy_buffer}
	 */
	static inline void CopySubData(
		BufferOps::Target readtarget,
		BufferOps::Target writetarget,
		GLintptr readoffset,
		GLintptr writeoffset,
		GLsizeiptr size
	)
	{
		OGLPLUS_GLFUNC(CopyBufferSubData)(
			GLenum(readtarget),
			GLenum(writetarget),
			readoffset,
			writeoffset,
			size
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(CopyBufferSubData));
	}
#endif // copy buffer

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Clear the buffer data
	/**
	 *  @see Data
	 *  @see ClearSubData
	 *  @see SubData
	 *  @see CopySubData
	 *
	 *  @throws Error
	 *
	 *  @glverreq{4,3}
	 */
	template <typename GLtype>
	static void ClearData(
		Target target,
		PixelDataInternalFormat internal_format,
		PixelDataFormat format,
		const GLtype* data
	)
	{
		OGLPLUS_GLFUNC(ClearBufferData)(
			GLenum(target),
			GLenum(internal_format),
			GLenum(format),
			GLenum(GetDataType<GLtype>()),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ClearBufferData,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	/// Clear a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see ClearData
	 *  @see SubData
	 *  @see CopySubData
	 *
	 *  @throws Error
	 *
	 *  @glverreq{4,3}
	 */
	template <typename GLtype>
	static void ClearSubData(
		Target target,
		PixelDataInternalFormat internal_format,
		GLintptr offset,
		GLsizeiptr size,
		PixelDataFormat format,
		const GLtype* data
	)
	{
		OGLPLUS_GLFUNC(ClearBufferSubData)(
			GLenum(target),
			GLenum(internal_format),
			offset,
			size,
			GLenum(format),
			GLenum(GetDataType<GLtype>()),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ClearBufferSubData,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_buffer_storage
	/// Creates a data store for a buffer object
	/**
	 *  @see Data
	 *  @see SubData
	 *  @see CopySubData
	 *
	 *  @throws Error
	 *
	 *  @glverreq{4,4}
	 *  @glsymbols
	 *  @glfunref{BufferStorage}
	 */
	template <typename GLtype>
	static void Storage(
		Target target,
		GLsizeiptr size,
		const void* data,
		Bitfield<BufferStorageBit> flags
	)
	{
		OGLPLUS_GLFUNC(BufferStorage)(
			GLenum(target),
			size,
			data,
			GLbitfield(flags)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			BufferStorage,
			Buffer,
			EnumValueName(target),
			BindingQuery<BufferOps>::QueryBinding(target)
		));
	}

	/// Returns true if the buffer storage is immutable
	/**
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_IMMUTABLE_STORAGE}
	 *
	 *  @throws Error
	 */
	static bool ImmutableStorage(Target target)
	{
		return GLsizei(GetIntParam(target, GL_BUFFER_IMMUTABLE_STORAGE));
	}

	/// Returns the buffer storage flags
	/**
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_STORAGE_FLAGS}
	 *
	 *  @throws Error
	 */
	static Bitfield<BufferStorageBit> StorageFlags(Target target)
	{
		return Bitfield<BufferStorageBit>(GLbitfield(
			GetIntParam(target, GL_BUFFER_STORAGE_FLAGS)
		));
	}
#endif

	/// Returns the buffer size
	/**
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_SIZE}
	 *
	 *  @throws Error
	 */
	static GLsizei Size(Target target)
	{
		return GLsizei(GetIntParam(target, GL_BUFFER_SIZE));
	}

	/// Returns the buffer usage
	/**
	 *  @see Access
	 *
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_USAGE}
	 *
	 *  @throws Error
	 */
	static BufferUsage Usage(Target target)
	{
		return BufferUsage(GetIntParam(target, GL_BUFFER_USAGE));
	}

	/// Returns the buffer usage
	/**
	 *  @see Usage
	 *
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_ACCESS}
	 *
	 *  @throws Error
	 */
	static Bitfield<BufferMapAccess> Access(Target target)
	{
		return Bitfield<BufferMapAccess>(
			GLbitfield(GetIntParam(target, GL_BUFFER_ACCESS))
		);
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL buffer functionality
/**
 *  @ingroup oglplus_objects
 */
class Buffer
 : public BufferOps
{ };
#else
typedef Object<BufferOps> Buffer;
#endif

template <>
class Group<Buffer>
 : public BaseGroup<Buffer>
{
public:
	/// Constructs an empty group of Buffers
	Group(void)
	{ }

	/// Constructs an empty group and reserves space for @c n Buffers
	Group(std::size_t n)
	 : BaseGroup<Buffer>(n)
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	/// Bind the buffers in this group to the specified indexed targets
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	void BindBase(BufferIndexedTarget target, GLuint first) const
	{
		if(!this->empty())
		{
			BufferOps::BindBase(
				target,
				first,
				GLsizei(this->size()),
				this->_names.data()
			);
		}
	}

	/// Bind ranges of the buffers in this group to the specified targets
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	void BindRange(
		BufferIndexedTarget target,
		GLuint first,
		const GLintptr* offsets,
		const GLsizeiptr* sizes
	) const
	{
		if(!this->empty())
		{
			BufferOps::BindRange(
				target,
				first,
				GLsizei(this->size()),
				this->_names.data(),
				offsets,
				sizes
			);
		}
	}
#endif
};

template <>
class Array<Buffer>
 : public aux::BaseArray<
	Buffer,
	Buffer::IsMultiObject::value
>
{
private:
	typedef aux::BaseArray<
		Buffer,
		Buffer::IsMultiObject::value
	> BaseArray;
public:
	/// Constructs an Array of @c c Buffers
	Array(GLsizei c)
	 : BaseArray(c)
	{ }

	Array(Array&& tmp)
	 : BaseArray(std::move(tmp))
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_4 || GL_ARB_multi_bind
	/// Bind the buffers in this array to the specified indexed targets
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	void BindBase(BufferIndexedTarget target, GLuint first) const
	{
		if(!this->empty())
		{
			BufferOps::BindBase(
				target,
				first,
				GLsizei(this->size()),
				this->_names.data()
			);
		}
	}

	/// Bind ranges of the buffers in this group to the specified targets
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,multi_bind}
	 */
	void BindRange(
		BufferIndexedTarget target,
		GLuint first,
		const GLintptr* offsets,
		const GLsizeiptr* sizes
	) const
	{
		if(!this->empty())
		{
			BufferOps::BindRange(
				target,
				first,
				GLsizei(this->size()),
				this->_names.data(),
				offsets,
				sizes
			);
		}
	}
#endif
};

} // namespace oglplus

#endif // include guard
