/**
 *  @file oglplus/texture.hpp
 *  @brief Query object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_QUERY_1107121519_HPP
#define OGLPLUS_QUERY_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

class QueryOps
{
protected:
	GLuint _name;

	QueryOps(void)
	{ }

	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenQueries(count, &_name);
		ThrowOnError();
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		::glDeleteQueries(count, &_name);
	}
public:
	QueryOps(GLuint _n)
	 : _name(_n)
	{ }

	enum class Target {
		SamplesPassed = GL_SAMPLES_PASSED,
		AnySamplesPassed = GL_ANY_SAMPLES_PASSED
	};

	void Begin(Target target) const
	{
		::glBeginQuery(GLenum(target), _name);
	}

	void End(Target target) const
	{
		::glEndQuery(GLenum(target));
	}
};

typedef Object<QueryOps> Query;

} // namespace oglplus

#endif // include guard
