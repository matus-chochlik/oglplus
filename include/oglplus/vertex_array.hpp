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

namespace oglplus {

class VertexArrayOps
{
protected:
	GLuint _name;

	VertexArrayOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenVertexArrays(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteVertexArrays(count, &_name);
	}
public:
	VertexArrayOps(GLuint _n)
	 : _name(_n)
	{ }

	void Bind(void) const
	{
		::glBindVertexArray(_name);
	}
};

typedef Object<VertexArrayOps> VertexArray;

} // namespace oglplus

#endif // include guard
