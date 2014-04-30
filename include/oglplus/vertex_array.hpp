/**
 *  @file oglplus/vertex_array.hpp
 *  @brief VertexArray wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_VERTEX_ARRAY_1107121519_HPP
#define OGLPLUS_VERTEX_ARRAY_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

/// Encapsulates vertex array-related functions
/** @note Do not use this class directly, use VertexArray instead.
 *  @see VertexArray
 *
 *  @glsymbols
 *  @glfunref{GenVertexArrays}
 *  @glfunref{DeleteVertexArrays}
 *  @glfunref{IsVertexArray}
 */
class VertexArrayOps
 : public Named
 , public BaseObject<true>
{
public:
	typedef Nothing Target;
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

	static void _bind(GLuint _name, Nothing)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindVertexArray)(_name);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindVertexArray));
	}

	friend class FriendOf<VertexArrayOps>;
public:
	/// Bind this vertex array
	/**
	 *  @glsymbols
	 *  @glfunref{BindVertexArray}
	 */
	void Bind(void) const
	{
		_bind(_name, Nothing());
	}

	/// Bind the name 0
	/**
	 *  @glsymbols
	 *  @glfunref{BindVertexArray}
	 */
	static void Unbind(void)
	{
		OGLPLUS_GLFUNC(BindVertexArray)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindVertexArray));
	}
};

/// Class that can be used to unbind the current vertex array object
class NoVertexArray
{
public:
	/// Breaks the current VAO binding (unbinds the current VAO)
	static void Bind(void)
	{
		OGLPLUS_GLFUNC(BindVertexArray)(0);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BindVertexArray));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL vertex array functionality
/**
 *  @ingroup oglplus_objects
 */
class VertexArray
 : public VertexArrayOps
{ };
#else
typedef Object<VertexArrayOps> VertexArray;
#endif

} // namespace oglplus

#endif // include guard
