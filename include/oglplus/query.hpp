/**
 *  @file oglplus/query.hpp
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
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

class QueryOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint& _name)
	{
		::glGenQueries(count, &_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei count, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteQueries(count, &_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsQuery(_name);
	}
public:
	enum class Target {
		SamplesPassed = GL_SAMPLES_PASSED,
		AnySamplesPassed = GL_ANY_SAMPLES_PASSED
	};

	void Begin(Target target) const
	{
		assert(_name != 0);
		::glBeginQuery(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	void End(Target target) const
	{
		assert(_name != 0);
		::glEndQuery(GLenum(target));
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

typedef Object<QueryOps, true> Query;

} // namespace oglplus

#endif // include guard
