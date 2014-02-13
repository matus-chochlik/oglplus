/**
 *  @file oglplus/ext/EXT_direct_state_access/buffer.hpp
 *  @brief Buffer wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_DSA_1309301821_HPP
#define OGLPLUS_BUFFER_DSA_1309301821_HPP

#include <oglplus/buffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Wrapper for direct state access buffer operations
/**
 *  @note Do not use this class directly, use DSABufferEXT instead
 *
 *  @see DSABufferEXT
 *
 *  @glsymbols
 *  @glfunref{GenBuffers}
 *  @glfunref{DeleteBuffers}
 *  @glfunref{IsBuffer}
 */
class DSABufferEXTOps
 : public Named
 , public BaseObject<true>
{
public:
	/// Buffer bind targets
	typedef BufferTarget Target;
	Target target;

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

	friend class FriendOf<DSABufferEXTOps>;

	GLint GetIntParam(GLenum query) const
	{
		GLint value = 0;
		OGLPLUS_GLFUNC(GetNamedBufferParameterivEXT)(
			_name,
			query,
			&value
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetNamedBufferParameterivEXT));
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
		TypedMap(
			const DSABufferEXTOps& buffer,
			GLintptr offset,
			GLsizeiptr size,
			Bitfield<BufferMapAccess> access
		): _offset(offset * sizeof(Type))
		 , _size(size * sizeof(Type))
		 , _ptr(
			OGLPLUS_GLFUNC(MapNamedBufferRangeEXT)(
				FriendOf<DSABufferEXTOps>::GetName(buffer),
				offset,
				size,
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
		TypedMap(
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
		 , _name(temp._name)
		{
			temp._ptr = nullptr;
		}

		~TypedMap(void)
		{
			if(_ptr != nullptr)
			{
				OGLPLUS_GLFUNC(UnmapNamedBufferEXT)(_name);
				OGLPLUS_IGNORE(
					OGLPLUS_ERROR_INFO(UnmapNamedBufferEXT)
				);
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
	bool Mapped(void) const
	{
		return GetIntParam(GL_BUFFER_MAPPED) == GL_TRUE;
	}

	/// Bind this buffer to the current target
	/**
	 *  @throws Error
	 */
	void Bind(void)
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


	/// Bind this buffer to the specified target
	/**
	 *  @throws Error
	 */
	void Bind(Target new_target)
	{
		target = new_target;
		Bind();
	}

	/// Unbind the current buffer from this Buffer's target
	/** This function binds the name 0 to the @p target.
	 *
	 *  @throws Error
	 */
	void Unbind(void) const
	{
		OGLPLUS_GLFUNC(BindBuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffer,
			Buffer,
			EnumValueName(target),
			0
		));
	}

	/// Bind this buffer to the specified indexed target
	/**
	 *  @throws Error
	 */
	void BindBase(IndexedTarget idx_target, GLuint index) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindBufferBase)(GLenum(idx_target), index, _name);
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

	/// Bind a range in this buffer to the specified indexed target
	/**
	 *  @throws Error
	 */
	void BindRange(
		IndexedTarget idx_target,
		GLuint index,
		GLintptr offset,
		GLsizeiptr size
	) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindBufferRange)(
			GLenum(idx_target),
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

	/// Uploads (sets) the buffer data
	/** This member function uploads @p count units of @c sizeof(GLtype)
	 *  from the location pointed to by @p data to this buffer
	 *  using the @p usage as hint.
	 *
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	void Data(
		GLsizei count,
		GLtype* data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		OGLPLUS_GLFUNC(NamedBufferDataEXT)(
			_name,
			count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferDataEXT,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	template <typename GLtype, std::size_t Count>
	void Data(
		GLtype (&data)[Count],
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		OGLPLUS_GLFUNC(NamedBufferDataEXT)(
			_name,
			Count * sizeof(GLtype),
			data,
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferDataEXT,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	/// Uploads (sets) the buffer data
	/** This member function uploads @p data.size() units of @c sizeof(GLtype)
	 *  from the location pointed to by @p data.data() to this buffer
	 *  using the @p usage as hint.
	 *
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	void Data(
		const std::vector<GLtype>& data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		OGLPLUS_GLFUNC(NamedBufferDataEXT)(
			_name,
			data.size() * sizeof(GLtype),
			data.data(),
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferDataEXT,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	/// Uploads (sets) the buffer data
	/**
	 *  @see SubData
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype, std::size_t N>
	void Data(
		const std::vector<Vector<GLtype, N> >& data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const
	{
		//TODO: is this a good idea ?
		OGLPLUS_GLFUNC(NamedBufferDataEXT)(
			_name,
			data.size() * sizeof(GLtype) * N,
			reinterpret_cast<const GLtype*>(data.data()),
			GLenum(usage)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferDataEXT,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	/// Uploads (sets) a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	void SubData(
		GLintptr offset,
		GLsizei count,
		GLtype* data
	) const
	{
		OGLPLUS_GLFUNC(NamedBufferSubDataEXT)(
			_name,
			offset * sizeof(GLtype),
			count * sizeof(GLtype),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferSubDataEXT,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	template <typename GLtype, std::size_t Count>
	void SubData(
		GLintptr offset,
		GLtype (&data)[Count]
	) const
	{
		OGLPLUS_GLFUNC(NamedBufferSubDataEXT)(
			_name,
			offset * sizeof(GLtype),
			Count * sizeof(GLtype),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferSubDataEXT,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	/// Uploads (sets) a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see CopySubData
	 *  @throws Error
	 */
	template <typename GLtype>
	void SubData(
		GLintptr offset,
		const std::vector<GLtype>& data
	) const
	{
		OGLPLUS_GLFUNC(NamedBufferSubDataEXT)(
			_name,
			offset * sizeof(GLtype),
			data.size() * sizeof(GLtype),
			data.data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			NamedBufferSubDataEXT,
			Buffer,
			EnumValueName(target),
			_name
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
	static void CopySubData(
		const DSABufferEXTOps& readbuffer,
		const DSABufferEXTOps& writebuffer,
		GLintptr readoffset,
		GLintptr writeoffset,
		GLsizeiptr size
	)
	{
		OGLPLUS_GLFUNC(NamedCopyBufferSubDataEXT)(
			readbuffer._name,
			writebuffer._name,
			readoffset,
			writeoffset,
			size
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(NamedCopyBufferSubDataEXT));
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
	void ClearData(
		PixelDataInternalFormat internal_format,
		PixelDataFormat format,
		const GLtype* data
	) const
	{
		OGLPLUS_GLFUNC(ClearNamedBufferDataEXT)(
			_name,
			GLenum(internal_format),
			GLenum(format),
			GLenum(GetDataType<GLtype>()),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ClearNamedBufferDataEXT,
			Buffer,
			EnumValueName(target),
			_name
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
	void ClearSubData(
		PixelDataInternalFormat internal_format,
		GLintptr offset,
		GLsizeiptr size,
		PixelDataFormat format,
		const GLtype* data
	) const
	{
		OGLPLUS_GLFUNC(ClearNamedBufferSubDataEXT)(
			_name,
			GLenum(internal_format),
			offset,
			size,
			GLenum(format),
			GLenum(GetDataType<GLtype>()),
			data
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			ClearNamedBufferSubDataEXT,
			Buffer,
			EnumValueName(target),
			_name
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
	GLsizei Size(void) const
	{
		return GLsizei(GetIntParam(GL_BUFFER_SIZE));
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
	BufferUsage Usage(void) const
	{
		return BufferUsage(GetIntParam(GL_BUFFER_USAGE));
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
	Bitfield<BufferMapAccess> Access(void) const
	{
		return Bitfield<BufferMapAccess>(
			GLbitfield(GetIntParam(GL_BUFFER_ACCESS))
		);
	}
};

// Helper class for syntax sugar operators
struct DSABufferEXTOpsAndUsage
{
	DSABufferEXTOps& buf;
	BufferUsage usage;

	DSABufferEXTOpsAndUsage(DSABufferEXTOps& b, BufferUsage u)
	 : buf(b)
	 , usage(u)
	{ }
};

inline DSABufferEXTOpsAndUsage operator << (
	DSABufferEXTOps& buf,
	BufferUsage usage
)
{
	return DSABufferEXTOpsAndUsage(buf, usage);
}

// Helper class for syntax sugar operators
struct DSABufferEXTOpsAndIdxTgt
{
	DSABufferEXTOps& buf;
	BufferIndexedTarget target;

	DSABufferEXTOpsAndIdxTgt(DSABufferEXTOps& b, BufferIndexedTarget t)
	 : buf(b)
	 , target(t)
	{ }
};

inline DSABufferEXTOpsAndIdxTgt operator << (
	DSABufferEXTOps& buf,
	BufferIndexedTarget target
)
{
	return DSABufferEXTOpsAndIdxTgt(buf, target);
}

// syntax-sugar operators

// Bind
inline DSABufferEXTOps& operator << (
	DSABufferEXTOps& buf,
	BufferTarget target
)
{
	buf.Bind(target);
	return buf;
}

// BindBase
inline DSABufferEXTOps& operator << (
	const DSABufferEXTOpsAndIdxTgt& bat,
	GLuint index
)
{
	bat.buf.BindBase(bat.target, index);
	return bat.buf;
}

// Data
template <typename GLtype>
inline DSABufferEXTOps& operator << (
	DSABufferEXTOps& buf,
	const std::vector<GLtype>& data
)
{
	buf.Data(data);
	return buf;
}

// Data
template <typename GLtype>
inline DSABufferEXTOps& operator << (
	DSABufferEXTOpsAndUsage&& bau,
	const std::vector<GLtype>& data
)
{
	bau.buf.Data(data, bau.usage);
	return bau.buf;
}

// Data
template <typename GLtype, std::size_t Count>
inline DSABufferEXTOps& operator << (
	DSABufferEXTOps& buf,
	const GLtype (&data)[Count]
)
{
	buf.Data(data);
	return buf;
}

// Data
template <typename GLtype, std::size_t Count>
inline DSABufferEXTOps& operator << (
	DSABufferEXTOpsAndUsage&& bau,
	const GLtype (&data)[Count]
)
{
	bau.buf.Data(data, bau.usage);
	return bau.buf;
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL buffer functionality
/**
 *  @ingroup oglplus_objects
 */
class DSABufferEXT
 : public DSABufferEXTOps
{ };
#else
typedef Object<DSABufferEXTOps> DSABufferEXT;
#endif

template <>
struct NonDSAtoDSA<BufferOps>
{
	typedef DSABufferEXTOps Type;
};

template <>
struct DSAtoNonDSA<DSABufferEXTOps>
{
	typedef BufferOps Type;
};

template <>
class ConvertibleObjectBaseOps<BufferOps, DSABufferEXTOps>
 : public std::true_type
{ };

template <>
class ConvertibleObjectBaseOps<DSABufferEXTOps, BufferOps>
 : public std::true_type
{ };

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#endif // include guard
