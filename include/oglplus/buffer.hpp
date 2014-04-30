/**
 *  @file oglplus/buffer.hpp
 *  @brief Buffer wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
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
#include <oglplus/buffer_binding.hpp>
#include <oglplus/buffer_usage.hpp>
#include <oglplus/buffer_storage_bit.hpp>
#include <oglplus/buffer_target.hpp>
#include <oglplus/buffer_map.hpp>
#include <oglplus/buffer_gpu_addr.hpp>
#include <oglplus/access_specifier.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/pixel_data.hpp>
#include <oglplus/binding_query.hpp>

#include <vector>
#include <cassert>

namespace oglplus {

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

	static GLuint _binding(Target);
	static GLenum _binding_query(Target target);
	static GLenum _binding_query(IndexedTarget target);
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Mapping of the buffer to the client address space
	typedef BufferTypedMap<GLubyte> Map;

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
#endif // GL_VERSION_3_0

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
			_binding(target)
		));
	}

	/// Bind this buffer to the specified indexed target
	/**
	 *  @throws Error
	 */
	void Bind(IndexedTarget target, GLuint index) const
	{
		BindBase(target, index);
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
	 *
	 *  @glvoereq{4,0,ARB,transform_feedback3}
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
	 *
	 *  @glvoereq{4,0,ARB,transform_feedback3}
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
	 *
	 *  @glvoereq{4,2,ARB,shader_atomic_counters}
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
	 *
	 *  @glvoereq{4,3,ARB,shader_storage_buffer_object}
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
		const GLtype* data,
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
			_binding(target)
		));
	}

	template <typename GLtype, std::size_t Count>
	static void Data(
		Target target,
		const GLtype (&data)[Count],
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
			_binding(target)
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
			_binding(target)
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
			_binding(target)
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
		const GLtype* data
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
			_binding(target)
		));
	}

	template <typename GLtype, std::size_t Count>
	static void SubData(
		Target target,
		GLintptr offset,
		const GLtype (&data)[Count]
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
			_binding(target)
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
			_binding(target)
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
			_binding(target)
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
			_binding(target)
		));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_invalidate_subdata
	/// Invalidate the buffer data
	/**
	 *  @see Data
	 *  @see ClearData
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,3,ARB,invalidate_subdata}
	 */
	void InvalidateData(void)
	{
		OGLPLUS_GLFUNC(InvalidateBufferData)(_name);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			InvalidateBufferData,
			Buffer,
			nullptr,
			_name
		));
	}

	/// Invalidate a subrange of the buffer data
	/**
	 *  @see Data
	 *  @see SubData
	 *  @see InvalidateData
	 *
	 *  @throws Error
	 *
	 *  @glvoereq{4,3,ARB,invalidate_subdata}
	 */
	void InvalidateSubData(GLintptr offset, GLsizeiptr size)
	{
		OGLPLUS_GLFUNC(InvalidateBufferSubData)(
			_name,
			offset,
			size
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			InvalidateBufferSubData,
			Buffer,
			nullptr,
			_name
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
	 *  @glvoereq{4,4,ARB,buffer_storage}
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
			_binding(target)
		));
	}

	/// Returns true if the buffer storage is immutable
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,buffer_storage}
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_IMMUTABLE_STORAGE}
	 */
	static bool ImmutableStorage(Target target)
	{
		return GetIntParam(
			target,
			GL_BUFFER_IMMUTABLE_STORAGE
		) == GL_TRUE;
	}

	/// Returns the buffer storage flags
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,4,ARB,buffer_storage}
	 *  @glsymbols
	 *  @glfunref{GetBufferParameter}
	 *  @gldefref{BUFFER_STORAGE_FLAGS}
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
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
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_NV_shader_buffer_load
	/// Makes buffer currently bound to target accessible to GLSL shaders
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{MakeBufferResidentNV}
	 *
	 *  @throws Error
	 */
	static void MakeResident(Target target, AccessSpecifier access)
	{
		OGLPLUS_GLFUNC(MakeBufferResidentNV)(
			GLenum(target),
			GLenum(access)
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			MakeBufferResidentNV,
			Buffer,
			EnumValueName(target),
			_binding(target)
		));
	}

	/// Makes buffer currently bound to target inaccessible to GLSL shaders
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{MakeBufferNonResidentNV}
	 *
	 *  @throws Error
	 */
	static void MakeNonResident(Target target)
	{
		OGLPLUS_GLFUNC(MakeBufferNonResidentNV)(GLenum(target));
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			MakeBufferNonResidentNV,
			Buffer,
			EnumValueName(target),
			_binding(target)
		));
	}

	/// Returns the GPU address of the buffer currently bound to target
	/**
	 *  @glextreq{NV,shader_buffer_load}
	 *  @glsymbols
	 *  @glfunref{GetBufferParameterui64vNV}
	 *  @gldefref{BUFFER_GPU_ADDRESS_NV}
	 *
	 *  @throws Error
	 */
	static BufferGPUAddress GPUAddress(Target target)
	{
		GLuint64EXT value = 0;
		OGLPLUS_GLFUNC(GetBufferParameterui64vNV)(
			GLenum(target),
			GL_BUFFER_GPU_ADDRESS_NV,
			&value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetBufferParameterui64vNV));
		return BufferGPUAddress(value);
	}
#endif
};

// Helper class for syntax sugar operators
struct BufferTargetAndUsage
{
	BufferTarget target;
	BufferUsage usage;

	BufferTargetAndUsage(BufferTarget t, BufferUsage u)
	 : target(t)
	 , usage(u)
	{ }
};

inline BufferTargetAndUsage operator << (
	BufferTarget target,
	BufferUsage usage
)
{
	return BufferTargetAndUsage(target, usage);
}

// Helper class for syntax sugar operators
struct BufferOpsAndIdxTgt
{
	const BufferOps& buf;
	BufferIndexedTarget target;

	BufferOpsAndIdxTgt(const BufferOps& b, BufferIndexedTarget t)
	 : buf(b)
	 , target(t)
	{ }
};

inline BufferOpsAndIdxTgt operator << (
	const BufferOps& buf,
	BufferIndexedTarget target
)
{
	return BufferOpsAndIdxTgt(buf, target);
}

// Helper class for syntax sugar operators
struct BufferTargetAndOffset
{
	BufferTarget target;
	GLintptr offset;

	BufferTargetAndOffset(BufferTarget t, GLintptr o)
	 : target(t)
	 , offset(o)
	{ }
};

inline BufferTargetAndOffset operator + (
	BufferTarget target,
	GLintptr offset
)
{
	return BufferTargetAndOffset(target, offset);
}

// Bind
inline BufferTarget operator << (
	const BufferOps& buf,
	BufferTarget target
)
{
	buf.Bind(target);
	return target;
}

// BindBase
inline const BufferOps& operator << (
	const BufferOpsAndIdxTgt& bat,
	GLuint index
)
{
	bat.buf.BindBase(bat.target, index);
	return bat.buf;
}

// Data
template <typename GLtype>
inline BufferTarget operator << (
	BufferTarget target,
	const std::vector<GLtype>& data
)
{
	BufferOps::Data(target, data);
	return target;
}

// Data
template <typename GLtype>
inline BufferTarget operator << (
	BufferTargetAndUsage&& tau,
	const std::vector<GLtype>& data
)
{
	BufferOps::Data(tau.target, data, tau.usage);
	return tau.target;
}

// Data
template <typename GLtype, std::size_t Count>
inline BufferTarget operator << (
	BufferTarget target,
	const GLtype (&data)[Count]
)
{
	BufferOps::Data(target, data);
	return target;
}

// Data
template <typename GLtype, std::size_t Count>
inline BufferTarget operator << (
	BufferTargetAndUsage&& tau,
	const GLtype (&data)[Count]
)
{
	BufferOps::Data(tau.target, data, tau.usage);
	return tau.target;
}

// SubData
template <typename GLtype>
inline BufferTarget operator << (
	BufferTargetAndOffset&& tao,
	const std::vector<GLtype>& data
)
{
	BufferOps::SubData(tao.target, tao.offset, data);
	return tao.target;
}

// SubData
template <typename GLtype, std::size_t Count>
inline BufferTarget operator << (
	BufferTargetAndOffset&& tao,
	const GLtype (&data)[Count]
)
{
	BufferOps::SubData(tao.target, tao.offset, data);
	return tao.target;
}

/// Class that can be used for unbinding of currently bound buffers
class NoBuffer
{
public:
	/// Buffer bind targets
	typedef BufferTarget Target;

	/// Buffer indexed bind targets
	typedef BufferIndexedTarget IndexedTarget;

	/// Unbinds the current buffer from the specified target
	/** This function binds the name 0 to the specified @p target.
	 *
	 *  @glsymbols
	 *  @glfunref{BindBuffer}
	 *
	 *  @throws Error
	 */
	static void Bind(Target target)
	{
		OGLPLUS_GLFUNC(BindBuffer)(GLenum(target), 0);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBuffer,
			Buffer,
			EnumValueName(target),
			0
		));
	}

	/// Unbinds the current buffer from the specified indexed target
	/**
	 *
	 *  @glsymbols
	 *  @glfunref{BindBufferBase}
	 *
	 *  @throws Error
	 */
	static void Bind(IndexedTarget target, GLuint index)
	{
		BindBase(target, index);
	}

	/// Unbinds the current buffer from the specified indexed target
	/**
	 *
	 *  @glsymbols
	 *  @glfunref{BindBufferBase}
	 *
	 *  @throws Error
	 */
	static void BindBase(IndexedTarget target, GLuint index)
	{
		OGLPLUS_GLFUNC(BindBufferBase)(GLenum(target), index, 0);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BindBufferBase,
			Buffer,
			EnumValueName(target),
			0
		));
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

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/buffer.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
