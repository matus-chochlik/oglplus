/**
 *  @file oglplus/ext/EXT_direct_state_acccess/vertex_attrib.hpp
 *  @brief VertexArrayAttrib wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_VERTEX_ATTRIB_DSA_1107121519_HPP
#define OGLPLUS_VERTEX_ATTRIB_DSA_1107121519_HPP

#include <oglplus/vertex_attrib.hpp>
#include <oglplus/ext/EXT_direct_state_access/vertex_array.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

class DSAVertexArrayAttribEXT
 : public VertexAttribOps
 , public FriendOf<DSAVertexArrayEXTOps>
 , public FriendOf<DSABufferEXTOps>
{
private:
	GLuint _vao;
public:
	/// References the vertex attribute array at @p location
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	DSAVertexArrayAttribEXT(
		const DSAVertexArrayEXTOps& vao,
		VertexAttribSlot location
	): VertexAttribOps(location)
	 , _vao(FriendOf<DSAVertexArrayEXTOps>::GetName(vao))
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	DSAVertexArrayAttribEXT(
		const DSAVertexArrayEXTOps& vao,
		const ProgramOps& program,
		const GLchar* identifier
	): VertexAttribOps(program, identifier)
	 , _vao(FriendOf<DSAVertexArrayEXTOps>::GetName(vao))
	{ }

	/// References the vertex attrib array @p identifier of the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetAttribLocation}
	 */
	DSAVertexArrayAttribEXT(
		const DSAVertexArrayEXTOps& vao,
		const ProgramOps& program,
		const String& identifier
	): VertexAttribOps(program, identifier.c_str())
	 , _vao(FriendOf<DSAVertexArrayEXTOps>::GetName(vao))
	{ }

	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexArrayVertexAttribOffsetEXT}
	 */
	const DSAVertexArrayAttribEXT& Offset(
		const DSABufferEXTOps& buffer,
		GLint values_per_vertex,
		DataType data_type,
		bool normalized,
		GLsizei stride,
		GLintptr offset
	) const
	{
		OGLPLUS_GLFUNC(VertexArrayVertexAttribOffsetEXT)(
			_vao,
			FriendOf<DSABufferEXTOps>::GetName(buffer),
			GLuint(_location),
			values_per_vertex,
			GLenum(data_type),
			normalized ? GL_TRUE : GL_FALSE,
			stride,
			offset
		);
		OGLPLUS_CHECK(
			OGLPLUS_ERROR_INFO(VertexArrayVertexAttribOffsetEXT)
		);
		return *this;
	}

	const DSAVertexArrayAttribEXT& Offset(
		const BufferOps& buffer,
		GLint values_per_vertex,
		DataType data_type,
		bool normalized,
		GLsizei stride,
		GLintptr offset
	) const
	{
		return Offset(
			Managed<DSABufferEXTOps>(buffer),
			values_per_vertex,
			data_type,
			normalized,
			stride,
			offset
		);
	}

	/// Setup the properties of this vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexArrayVertexAttribIOffsetEXT}
	 */
	const DSAVertexArrayAttribEXT& IOffset(
		const DSABufferEXTOps& buffer,
		GLint values_per_vertex,
		DataType data_type,
		GLsizei stride,
		GLintptr offset
	) const
	{
		OGLPLUS_GLFUNC(VertexArrayVertexAttribIOffsetEXT)(
			_vao,
			FriendOf<DSABufferEXTOps>::GetName(buffer),
			GLuint(_location),
			values_per_vertex,
			GLenum(data_type),
			stride,
			offset
		);
		OGLPLUS_CHECK(
			OGLPLUS_ERROR_INFO(VertexArrayVertexAttribIOffsetEXT)
		);
		return *this;
	}

	const DSAVertexArrayAttribEXT& IOffset(
		const BufferOps& buffer,
		GLint values_per_vertex,
		DataType data_type,
		GLsizei stride,
		GLintptr offset
	) const
	{
		return IOffset(
			Managed<DSABufferEXTOps>(buffer),
			values_per_vertex,
			data_type,
			stride,
			offset
		);
	}

	const DSAVertexArrayAttribEXT& Setup(
		const DSABufferEXTOps& buffer,
		GLint values_per_vertex,
		std::integral_constant<
			typename enums::EnumValueType<DataType>::Type,
			OGLPLUS_CONST_ENUM_VALUE(DataType::Float)
		>
	) const
	{
		return Offset(
			buffer,
			values_per_vertex,
			DataType::Float,
			false,
			0,
			0
		);
	}

	template <
		typename enums::EnumValueType<DataType>::Type DataTypeValue
	>
	const DSAVertexArrayAttribEXT& Setup(
		const DSABufferEXTOps& buffer,
		GLint values_per_vertex,
		std::integral_constant<
			typename enums::EnumValueType<DataType>::Type,
			DataTypeValue
		>
	) const
	{
		return IOffset(
			buffer,
			values_per_vertex,
			DataTypeValue,
			0,
			0
		);
	}

	/// Setup the properties of this vertex array attribute
	/**
	 *  @see Offset
	 *  @see IOffset
	 *
	 *  @glsymbols
	 *  @glfunref{VertexArrayVertexAttribOffsetEXT}
	 *  @glfunref{VertexArrayVertexAttribIOffsetEXT}
	 */
	template <typename T>
	const DSAVertexArrayAttribEXT& Setup(
		const DSABufferEXTOps& buffer,
		GLuint n = 1
	) const
	{
		typedef decltype(_get_element_type((T*)nullptr)) elem_type;

		return Setup(
			buffer,
			_get_values_per_vertex((T*)nullptr)*n,
			typename DataTypeCT<elem_type>::type()
		);
	}

	template <typename T>
	const DSAVertexArrayAttribEXT& Setup(
		const BufferOps& buffer,
		GLuint n = 1
	) const
	{
		return Setup<T>(
			Managed<DSABufferEXTOps>(buffer),
			n
		);
	}

	/// Enable this vertex array attribute
	/**
	 *  @glsymbols
	 *  @glfunref{EnableVertexArrayAttribEXT}
	 */
	const DSAVertexArrayAttribEXT& Enable(void) const
	{
		OGLPLUS_GLFUNC(EnableVertexArrayAttribEXT)(
			_vao,
			GLuint(_location)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(EnableVertexArrayAttribEXT));
		return *this;
	}

	/// Enable this specified vertex array attribute
	/**
	 *  @glsymbols
	 *  @glfunref{DisableVertexArrayAttribEXT}
	 */
	const DSAVertexArrayAttribEXT& Disable(void) const
	{
		OGLPLUS_GLFUNC(DisableVertexArrayAttribEXT)(
			_vao,
			GLuint(_location)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DisableVertexArrayAttribEXT));
		return *this;
	}
};

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#endif // include guard
