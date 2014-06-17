/**
 *  @file oglplus/dsa/buffer.hpp
 *  @brief Buffer wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DSA_BUFFER_1309301821_HPP
#define OGLPLUS_DSA_BUFFER_1309301821_HPP

#include <oglplus/buffer.hpp>
#include <oglplus/dsa/buffer_map.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Class wrapping renderbuffer-related functionality with direct state access
/** @note Do not use this class directly, use DSABuffer instead.
 *
 */
template <>
class ObjectOps<tag::DirectState, tag::Buffer>
 : public ObjZeroOps<tag::DirectState, tag::Buffer>
{
protected:
	ObjectOps(void){ }
public:
	GLint GetIntParam(GLenum query) const;

	/// Types related to Buffer
	struct Property
	{
		/// The Buffer usage mode
		typedef BufferUsage Usage;

		/// The buffer map access mode
		typedef BufferMapAccess MapAccess;
	};

	/// Mapping of the buffer to the client address space
	typedef DSABufferTypedMap<GLubyte> Map;

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
		OGLPLUS_CHECK(
			NamedBufferDataEXT,
			ObjectError,
			Object(*this).
			EnumParam(usage)
		);
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
		OGLPLUS_CHECK(
			NamedBufferDataEXT,
			ObjectError,
			Object(*this).
			EnumParam(usage)
		);
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
		OGLPLUS_CHECK(
			NamedBufferDataEXT,
			ObjectError,
			Object(*this).
			EnumParam(usage)
		);
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
		OGLPLUS_CHECK(
			NamedBufferDataEXT,
			ObjectError,
			Object(*this).
			EnumParam(usage)
		);
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
		OGLPLUS_CHECK(
			NamedBufferSubDataEXT,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			NamedBufferSubDataEXT,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			NamedBufferSubDataEXT,
			ObjectError,
			Object(*this)
		);
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
		BufferName readbuffer,
		BufferName writebuffer,
		GLintptr readoffset,
		GLintptr writeoffset,
		GLsizeiptr size
	)
	{
		OGLPLUS_GLFUNC(NamedCopyBufferSubDataEXT)(
			GetGLName(readbuffer),
			GetGLName(writebuffer),
			readoffset,
			writeoffset,
			size
		);
		OGLPLUS_CHECK(
			NamedCopyBufferSubDataEXT,
			ObjectPairError,
			Subject(readbuffer).
			Object(writebuffer)
		);
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
		OGLPLUS_CHECK(
			ClearNamedBufferDataEXT,
			ObjectError,
			Object(*this).
			EnumParam(internal_format)
		);
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
		OGLPLUS_CHECK(
			ClearNamedBufferSubDataEXT,
			ObjectError,
			Object(*this).
			EnumParam(internal_format)
		);
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
		OGLPLUS_CHECK(
			MakeNamedBufferResidentNV,
			ObjectError,
			Object(*this).
			EnumParam(access)
		);
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
		OGLPLUS_CHECK(
			MakeNamedBufferNonResidentNV,
			ObjectError,
			Object(*this)
		);
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
		OGLPLUS_CHECK(
			GetNamedBufferParameterui64vNV,
			ObjectError,
			Object(*this)
		);
		return BufferGPUAddress(value);
	}
#endif
};

/// Buffer operations with direct state access
typedef ObjectOps<tag::DirectState, tag::Buffer>
	DSABufferOps;

// Helper class for syntax sugar operators
struct DSABufferOpsAndUsage
{
	DSABufferOps& buf;
	BufferUsage usage;

	DSABufferOpsAndUsage(DSABufferOps& b, BufferUsage u)
	 : buf(b)
	 , usage(u)
	{ }
};

inline DSABufferOpsAndUsage operator << (
	DSABufferOps& buf,
	BufferUsage usage
)
{
	return DSABufferOpsAndUsage(buf, usage);
}

// Helper class for syntax sugar operators
struct DSABufferOpsAndIdxTgt
{
	DSABufferOps& buf;
	BufferIndexedTarget target;

	DSABufferOpsAndIdxTgt(DSABufferOps& b, BufferIndexedTarget t)
	 : buf(b)
	 , target(t)
	{ }
};

inline DSABufferOpsAndIdxTgt operator << (
	DSABufferOps& buf,
	BufferIndexedTarget target
)
{
	return DSABufferOpsAndIdxTgt(buf, target);
}

// Helper class for syntax sugar operators
struct DSABufferOpsAndOffset
{
	DSABufferOps& buf;
	GLintptr offset;

	DSABufferOpsAndOffset(DSABufferOps& b, GLintptr o)
	 : buf(b)
	 , offset(o)
	{ }
};

inline DSABufferOpsAndOffset operator + (
	DSABufferOps& buf,
	GLintptr offset
)
{
	return DSABufferOpsAndOffset(buf, offset);
}

// syntax-sugar operators

// Bind
inline DSABufferOps& operator << (
	DSABufferOps& buf,
	BufferTarget target
)
{
	buf.Bind(target);
	return buf;
}

// BindBase
inline DSABufferOps& operator << (
	const DSABufferOpsAndIdxTgt& bat,
	GLuint index
)
{
	bat.buf.BindBase(bat.target, index);
	return bat.buf;
}

// Data
template <typename GLtype>
inline DSABufferOps& operator << (
	DSABufferOps& buf,
	const std::vector<GLtype>& data
)
{
	buf.Data(data);
	return buf;
}

// Data
template <typename GLtype>
inline DSABufferOps& operator << (
	DSABufferOpsAndUsage&& bau,
	const std::vector<GLtype>& data
)
{
	bau.buf.Data(data, bau.usage);
	return bau.buf;
}

// Data
template <typename GLtype, std::size_t Count>
inline DSABufferOps& operator << (
	DSABufferOps& buf,
	const GLtype (&data)[Count]
)
{
	buf.Data(data);
	return buf;
}

// Data
template <typename GLtype, std::size_t Count>
inline DSABufferOps& operator << (
	DSABufferOpsAndUsage&& bau,
	const GLtype (&data)[Count]
)
{
	bau.buf.Data(data, bau.usage);
	return bau.buf;
}

// SubData
template <typename GLtype>
inline DSABufferOps& operator << (
	DSABufferOpsAndOffset&& bao,
	const std::vector<GLtype>& data
)
{
	bao.buf.SubData(bao.offset, data);
	return bao.buf;
}

// SubData
template <typename GLtype, std::size_t Count>
inline DSABufferOps& operator << (
	DSABufferOpsAndOffset&& bao,
	const GLtype (&data)[Count]
)
{
	bao.buf.SubData(bao.offset, data);
	return bao.buf;
}

/// An @ref oglplus_object encapsulating the OpenGL buffer functionality
/**
 *  @ingroup oglplus_objects
 */
typedef Object<DSABufferOps> DSABuffer;

#else
#error Direct State Access Buffers not available
#endif // GL_EXT_direct_state_access

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/dsa/buffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
