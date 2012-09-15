/**
 *  @file oglplus/query.hpp
 *  @brief Query object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_QUERY_1107121519_HPP
#define OGLPLUS_QUERY_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/friend_of.hpp>
#include <cassert>

namespace oglplus {

/// Query bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(QueryTarget, GLenum)
#include <oglplus/enums/query_target.ipp>
OGLPLUS_ENUM_CLASS_END

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/query_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/query_target_range.ipp>
#endif

/// Wrapper for asynchronous query functions
/** @note Do not use this class directly, use Query instead.
 *
 *  @glsymbols
 *  @glfunref{GenQueries}
 *  @glfunref{DeleteQueries}
 *  @glfunref{IsQuery}
 */
class QueryOps
 : public Named
 , public BaseObject<true>
{
protected:
	static void _init(GLsizei count, GLuint* _name, std::true_type)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		try{OGLPLUS_GLFUNC(GenQueries)(count, _name);}
		catch(...){ }
	}

	static void _init(GLsizei count, GLuint* _name, std::false_type)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenQueries)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenQueries));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteQueries)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsQuery)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_QUERY
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Query;
	}
#endif
public:
	/// Query bind target
	typedef QueryTarget Target;

	/// Begin the query on the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{BeginQuery}
	 */
	void Begin(Target target) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(BeginQuery)(GLenum(target), _name);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			BeginQuery,
			Query,
			EnumValueName(target),
			_name
		));
	}

	/// End the query on the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{EndQuery}
	 */
	void End(Target target) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(EndQuery)(GLenum(target));
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			EndQuery,
			Query,
			EnumValueName(target),
			_name
		));
	}

	/// Returns true if the query result is available
	/**
	 *  @glsymbols
	 *  @glfunref{GetQueryObject}
	 *  @gldefref{QUERY_RESULT_AVAILABLE}
	 */
	bool ResultAvailable(void) const
	{
		assert(_name != 0);
		GLuint result = GL_FALSE;
		OGLPLUS_GLFUNC(GetQueryObjectuiv)(
			_name,
			GL_QUERY_RESULT_AVAILABLE,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetQueryObjectuiv,
			Query,
			nullptr,
			_name
		));
		return result == GL_TRUE;
	}

	/// Get the query result
	/**
	 *  @glsymbols
	 *  @glfunref{GetQueryObject}
	 *  @gldefref{QUERY_RESULT}
	 */
	void Result(GLint& result) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(GetQueryObjectiv)(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetQueryObjectiv,
			Query,
			nullptr,
			_name
		));
	}

	/// Get the query result
	/**
	 *  @glsymbols
	 *  @glfunref{GetQueryObject}
	 *  @gldefref{QUERY_RESULT}
	 */
	void Result(GLuint& result) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(GetQueryObjectuiv)(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetQueryObjectuiv,
			Query,
			nullptr,
			_name
		));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_timer_query
	/// Get the query result
	/**
	 *  @glvoereq{3,3,ARB,timer_query}
	 *  @glsymbols
	 *  @glfunref{GetQueryObject}
	 *  @gldefref{QUERY_RESULT}
	 */
	void Result(GLint64& result) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(GetQueryObjecti64v)(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetQueryObjecti64v,
			Query,
			nullptr,
			_name
		));
	}

	/// Get the query result
	/**
	 *  @glvoereq{3,3,ARB,timer_query}
	 *  @glsymbols
	 *  @glfunref{GetQueryObject}
	 *  @gldefref{QUERY_RESULT}
	 */
	void Result(GLuint64& result) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(GetQueryObjectui64v)(
			_name,
			GL_QUERY_RESULT,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetQueryObjectui64v,
			Query,
			nullptr,
			_name
		));
	}
#endif // timer query

	/// Waits for and queries the result
	template <typename ResultType>
	void WaitForResult(ResultType& result) const
	{
		while(!ResultAvailable())
			OGLPLUS_GLFUNC(Finish)();
		Result(result);
	}

	/// A helper class automatically executing a query
	/** Instances of this class begin the query in the constructor
	 *  and end the query in the destructor. It is more convenient
	 *  not to use this class directly, use the Execute() function
	 *  instead.
	 *
	 *  @see Execute
	 */
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

#if !OGLPLUS_NO_DELETED_FUNCTIONS
		Execution(const Execution&) = delete;
#else
	private:
		Execution(const Execution&);
	public:
#endif

		Execution(Execution&& temp)
		 : _target(temp._target)
		 , _query(temp._query)
		 , _result(temp._result)
		 , _alive(temp._alive)
		{
			temp._alive = false;
		}

		void Finish(void)
		{
			if(_alive)
			{
				_query.End(_target);
				_query.WaitForResult(_result);
				_alive = false;
			}
		}

		~Execution(void)
		{
			try{ Finish(); }
			catch(...){ }
		}
	};

	/// Executes the query on the specified @p target and gets the @p result
	/** This function creates an instance of the Execution class which
	 *  begins a query on the specified @p target when it is constructed
	 *  and ends this query and gets its @p result when it is destroyed.
	 */
	template <typename ResultType>
	Execution<ResultType> Execute(Target target, ResultType& result) const
	{
		return Execution<ResultType>(target, *this, result);
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL asynchronous query functionality
/**
 *  @ingroup objects
 */
class Query
 : public QueryOps
{ };
#else
typedef Object<QueryOps> Query;
OGLPLUS_OBJECT_TYPE_ID(Query, 5)
#endif

} // namespace oglplus

#endif // include guard
