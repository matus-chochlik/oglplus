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
		ThrowOnError(OGLPLUS_ERROR_INFO(GenQueries));
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

	enum class Target : GLenum {
		TimeElapsed = GL_TIME_ELAPSED,
		Timestamp = GL_TIMESTAMP,
		SamplesPassed = GL_SAMPLES_PASSED,
		AnySamplesPassed = GL_ANY_SAMPLES_PASSED,
		PrimitivesGenerated = GL_PRIMITIVES_GENERATED,
		TransformFeedbackPrimitivesWritten =
			GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
	};

	void Begin(Target target) const
	{
		assert(_name != 0);
		::glBeginQuery(GLenum(target), _name);
		AssertNoError(OGLPLUS_ERROR_INFO(BeginQuery));
	}

	void End(Target target) const
	{
		assert(_name != 0);
		::glEndQuery(GLenum(target));
		AssertNoError(OGLPLUS_ERROR_INFO(EndQuery));
	}

	bool ResultAvailable(void) const
	{
		assert(_name != 0);
		GLuint result = GL_FALSE;
		::glGetQueryObjectuiv(
			_name,
			GL_QUERY_RESULT_AVAILABLE,
			&result
		);
		AssertNoError(OGLPLUS_ERROR_INFO(GetQueryObjectuiv));
		return result == GL_TRUE;
	}

	void Result(GLint& result) const
	{
		assert(_name != 0);
		::glGetQueryObjectiv(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetQueryObjectiv));
	}

	void Result(GLuint& result) const
	{
		assert(_name != 0);
		::glGetQueryObjectuiv(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetQueryObjectuiv));
	}

	void Result(GLint64& result) const
	{
		assert(_name != 0);
		::glGetQueryObjecti64v(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetQueryObjecti64v));
	}

	void Result(GLuint64& result) const
	{
		assert(_name != 0);
		::glGetQueryObjectui64v(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetQueryObjectui64v));
	}

	template <typename ResultType>
	void WaitForResult(ResultType& result) const
	{
		while(!ResultAvailable())
			glFinish();
		Result(result);
	}

	template <typename ResultType>
	class Execution
	{
	private:
		typename QueryOps::Target _target;
		const QueryOps& _query;
		ResultType& _result;
		bool _alive;
	public:
		Execution(
			typename QueryOps::Target target,
			const QueryOps& query,
			ResultType& result
		): _target(target)
		 , _query(query)
		 , _result(result)
		 , _alive(false)
		{
			_query.Begin(_target);
			_alive = true;
		}

		Execution(const Execution&) = delete;

		Execution(Execution&& temp)
		 : _target(temp._target)
		 , _query(temp._query)
		 , _result(temp._result)
		 , _alive(temp._alive)
		{
			temp._alive = false;
		}

		~Execution(void)
		{
			if(_alive)
			{
				_query.End(_target);
				_query.WaitForResult(_result);
			}
		}
	};

	template <typename ResultType>
	Execution<ResultType> Execute(Target target, ResultType& result) const
	{
		return Execution<ResultType>(target, *this, result);
	}
};

typedef Object<QueryOps, true> Query;

} // namespace oglplus

#endif // include guard
