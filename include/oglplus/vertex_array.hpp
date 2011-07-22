/**
 *  @file oglplus/vertex_array.hpp
 *  @brief VertexArray wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_VERTEX_ARRAY_1107121519_HPP
#define OGLPLUS_VERTEX_ARRAY_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

class VertexArrayOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenVertexArrays(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteVertexArrays(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsVertexArray(_name);
	}

	friend class FriendOf<VertexArrayOps>;
public:
	void Bind(void) const
	{
		assert(_name != 0);
		::glBindVertexArray(_name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	static void Unbind(void)
	{
		::glBindVertexArray(0);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

typedef Object<VertexArrayOps, true> VertexArray;

} // namespace oglplus

#endif // include guard
