/**
 *  @file oglplus/vertex_array.hpp
 *  @brief VertexArray wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

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
{
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenVertexArrays)(count, _name);
		HandleIfError(OGLPLUS_ERROR_INFO(GenVertexArrays));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		OGLPLUS_GLFUNC(DeleteVertexArrays)(count, _name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsVertexArray)(_name);
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
		assert(_name != 0);
		OGLPLUS_GLFUNC(BindVertexArray)(_name);
		AssertNoError(OGLPLUS_ERROR_INFO(BindVertexArray));
	}

	/// Bind the name 0
	/**
	 *  @glsymbols
	 *  @glfunref{BindVertexArray}
	 */
	static void Unbind(void)
	{
		OGLPLUS_GLFUNC(BindVertexArray)(0);
		AssertNoError(OGLPLUS_ERROR_INFO(BindVertexArray));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL vertex array functionality
/**
 *  @ingroup objects
 */
class VertexArray
 : public VertexArrayOps
{ };
#else
typedef Object<VertexArrayOps, true> VertexArray;
#endif

} // namespace oglplus

#endif // include guard
