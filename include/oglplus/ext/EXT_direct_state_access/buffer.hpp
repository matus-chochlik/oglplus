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
#include <oglplus/ext/EXT_direct_state_access/buffer_map.hpp>

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

	/// Mapping of the buffer to the client address space
	typedef DSABufferTypedMapEXT<GLubyte> Map;

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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_NV_shader_buffer_load
	/// Makes this buffer accessible to GLSL shaders
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{MakeNamedBufferResidentNV}
	 *
	 *  @throws Error
	 */
	void MakeResident(AccessSpecifier access) const
	{
		OGLPLUS_GLFUNC(MakeNamedBufferResidentNV)(
			_name,
			GLenum(access)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			MakeNamedBufferResidentNV,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	/// Makes this buffer inaccessible to GLSL shaders
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{MakeNamedBufferNonResidentNV}
	 *
	 *  @throws Error
	 */
	void MakeNonResident(void) const
	{
		OGLPLUS_GLFUNC(MakeNamedBufferNonResidentNV)(_name);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			MakeNamedBufferNonResidentNV,
			Buffer,
			EnumValueName(target),
			_name
		));
	}

	/// Returns the GPU address of this buffer
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{GetNamedBufferParameterui64vNV}
	 *  @gldefref{BUFFER_GPU_ADDRESS_NV}
	 *
	 *  @throws Error
	 */
	BufferGPUAddress GPUAddress(void) const
	{
		GLuint64EXT value = 0;
		OGLPLUS_GLFUNC(GetNamedBufferParameterui64vNV)(
			_name,
			GL_BUFFER_GPU_ADDRESS_NV,
			&value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetNamedBufferParameterui64vNV));
		return BufferGPUAddress(value);
	}
#endif
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

// Helper class for syntax sugar operators
struct DSABufferEXTOpsAndOffset
{
	DSABufferEXTOps& buf;
	GLintptr offset;

	DSABufferEXTOpsAndOffset(DSABufferEXTOps& b, GLintptr o)
	 : buf(b)
	 , offset(o)
	{ }
};

inline DSABufferEXTOpsAndOffset operator + (
	DSABufferEXTOps& buf,
	GLintptr offset
)
{
	return DSABufferEXTOpsAndOffset(buf, offset);
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

// SubData
template <typename GLtype>
inline DSABufferEXTOps& operator << (
	DSABufferEXTOpsAndOffset&& bao,
	const std::vector<GLtype>& data
)
{
	bao.buf.SubData(bao.offset, data);
	return bao.buf;
}

// SubData
template <typename GLtype, std::size_t Count>
inline DSABufferEXTOps& operator << (
	DSABufferEXTOpsAndOffset&& bao,
	const GLtype (&data)[Count]
)
{
	bao.buf.SubData(bao.offset, data);
	return bao.buf;
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
