/**
 *  @file oglplus/vertex_array_object.hpp
 *  @brief Vertex array object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_VERTEX_ARRAY_OBJECT_1107121519_HPP
#define OGLPLUS_VERTEX_ARRAY_OBJECT_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class VertexArrayObjectOps
{
protected:
	GLuint _name;

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
	VertexArrayObjectOps(void) = default;

	VertexArrayObjectOps(GLuint _b)
	 : _name(_b)
	{ }

	void Bind(void) const
	{
		::glBindVertexArray(_name);
		ThrowOnError();
	}
};

typedef Object<VertexArrayObjectOps> VertexArrayObject;

} // namespace oglplus

#endif // include guard
