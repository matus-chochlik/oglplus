/**
 *  @file oglplus/ext/EXT_direct_state_access/vertex_array.hpp
 *  @brief VertexArray wrappers with direct state access
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_VERTEX_ARRAY_DSA_1107121519_HPP
#define OGLPLUS_VERTEX_ARRAY_DSA_1107121519_HPP

#include <oglplus/vertex_array.hpp>
#include <oglplus/ext/EXT_direct_state_access/buffer.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_EXT_direct_state_access

/// Encapsulates vertex array-related functions with direct state access
/** @note Do not use this class directly, use DSAVertexArrayEXT instead.
 *  @see DSAVertexArrayEXT
 *
 *  @glsymbols
 *  @glfunref{GenVertexArrays}
 *  @glfunref{DeleteVertexArrays}
 *  @glfunref{IsVertexArray}
 */
class DSAVertexArrayEXTOps
 : public Named
 , public BaseObject<true>
 , public FriendOf<DSABufferEXTOps>
{
public:
	typedef Nothing Target;
	Target target;
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenVertexArrays)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenVertexArrays));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteVertexArrays)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsVertexArray)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_VERTEX_ARRAY
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::VertexArray;
	}
#endif

	friend class FriendOf<DSAVertexArrayEXTOps>;
public:
	/// Bind this vertex array
	/**
	 *  @glsymbols
	 *  @glfunref{BindVertexArray}
	 */
	void Bind(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindVertexArray)(_name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindVertexArray));
	}

	/// Unbinds this vertex array (binds the name 0)
	/**
	 *  @glsymbols
	 *  @glfunref{BindVertexArray}
	 */
	static void Unbind(void)
	{
		OGLPLUS_GLFUNC(BindVertexArray)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindVertexArray));
	}

	/// Setup the properties of the specified vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexArrayVertexAttribOffsetEXT}
	 */
	const DSAVertexArrayEXTOps& VertexAttribOffset(
		const DSABufferEXTOps& buffer,
		VertexAttribSlot location,
		GLint values_per_vertex,
		DataType data_type,
		bool normalized,
		GLsizei stride,
		GLintptr offset
	) const
	{
		OGLPLUS_GLFUNC(VertexArrayVertexAttribOffsetEXT)(
			_name,
			FriendOf<DSABufferEXTOps>::GetName(buffer),
			GLuint(location),
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

	/// Setup the properties of the specified vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{VertexArrayVertexAttribIOffsetEXT}
	 */
	const DSAVertexArrayEXTOps& VertexAttribIOffset(
		const DSABufferEXTOps& buffer,
		VertexAttribSlot location,
		GLint values_per_vertex,
		DataType data_type,
		GLsizei stride,
		GLintptr offset
	) const
	{
		OGLPLUS_GLFUNC(VertexArrayVertexAttribIOffsetEXT)(
			_name,
			FriendOf<DSABufferEXTOps>::GetName(buffer),
			GLuint(location),
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

	/// Enable the specified vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{EnableVertexArrayAttribEXT}
	 */
	const DSAVertexArrayEXTOps& EnableVertexAttrib(VertexAttribSlot location)
	{
		OGLPLUS_GLFUNC(EnableVertexArrayAttribEXT)(
			_name,
			GLuint(location)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(EnableVertexArrayAttribEXT));
		return *this;
	}

	/// Enable the specified vertex attribute array
	/**
	 *  @glsymbols
	 *  @glfunref{DisableVertexArrayAttribEXT}
	 */
	const DSAVertexArrayEXTOps& DisableVertexAttrib(VertexAttribSlot location)
	{
		OGLPLUS_GLFUNC(DisableVertexArrayAttribEXT)(
			_name,
			GLuint(location)
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(DisableVertexArrayAttribEXT));
		return *this;
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL vertex array functionality
/**
 *  @ingroup oglplus_objects
 */
class DSAVertexArrayEXT
 : public DSAVertexArrayEXTOps
{ };
#else
typedef Object<DSAVertexArrayEXTOps> DSAVertexArrayEXT;
#endif

template <>
struct NonDSAtoDSA<VertexArrayOps>
{
	typedef DSAVertexArrayEXTOps Type;
};

template <>
struct DSAtoNonDSA<DSAVertexArrayEXTOps>
{
	typedef VertexArrayOps Type;
};

template <>
class ConvertibleObjectBaseOps<VertexArrayOps, DSAVertexArrayEXTOps>
 : public std::true_type
{ };

template <>
class ConvertibleObjectBaseOps<DSAVertexArrayEXTOps, VertexArrayOps>
 : public std::true_type
{ };

#endif // GL_EXT_direct_state_access

} // namespace oglplus

#endif // include guard
