/**
 *  @file oglplus/query.hpp
 *  @brief Query object wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
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
OGLPLUS_ENUM_CLASS_END(QueryTarget)

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
	static void _init(GLsizei count, GLuint* _name)
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_timer_query
	/// Do a counter query on the specified @p target
	/**
	 *  @glsymbols
	 *  @glfunref{QueryCounter}
	 */
	void Counter(Target target) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(QueryCounter)(_name, GLenum(target));
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			QueryCounter,
			Query,
			EnumValueName(target),
			_name
		));
	}

	/// Do a timestamp query
	/**
	 *  @glsymbols
	 *  @glfunref{QueryCounter}
	 *  @gldefref{TIMESTAMP}
	 */
	void Timestamp(void) const
	{
		Counter(Target::Timestamp);
	}
#endif

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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
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
#endif // GL_VERSION_3_0

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

	class Activator
	 : public FriendOf<QueryOps>
	{
	protected:
		GLuint _name;
		QueryOps::Target _target;
	private:
		bool _alive;
		Activator(const Activator&);

		void _begin(void);
		void _end(void);
	public:
		Activator(
			const QueryOps& query,
			QueryOps::Target target
		): _name(FriendOf<QueryOps>::GetName(query))
		 , _target(target)
		 , _alive(false)
		{
			_begin();
			_alive = true;
		}

		Activator(Activator&& temp)
		 : _name(temp._name)
		 , _target(temp._target)
		 , _alive(temp._alive)
		{
			temp._alive = false;
		}

		~Activator(void)
		{
			try { Finish(); }
			catch(...) { }
		}

		bool Finish(void)
		{
			if(_alive)
			{
				_end();
				_alive = false;
				return true;
			}
			else return false;
		}
	};

	/// A helper class automatically executing a query
	/** Instances of this class begin the query in the constructor
	 *  and end the query in the destructor. It is more convenient
	 *  not to use this class directly, use the Execute() function
	 *  instead.
	 *
	 *  @see Execute
	 */
	template <typename ResultType>
	class Execution : public Activator
	{
	private:
		ResultType& _result;
	public:
		Execution(
			const QueryOps& query,
			typename QueryOps::Target target,
			ResultType& result
		): Activator(query, target)
		 , _result(result)
		{ }

		Execution(Execution&& temp)
		 : Activator(static_cast<Activator&&>(temp))
		 , _result(temp._result)
		{ }

		~Execution(void)
		{
			try { WaitForResult(); }
			catch(...) { }
		}

		void WaitForResult(void);
	};

	/// Executes the query on the specified @p target and gets the @p result
	/** This function creates an instance of the Execution class which
	 *  begins a query on the specified @p target when it is constructed
	 *  and ends this query and gets its @p result when it is destroyed.
	 */
	template <typename ResultType>
	Execution<ResultType> Execute(Target target, ResultType& result) const
	{
		return Execution<ResultType>(*this, target, result);
	}
};


inline void QueryOps::Activator::_begin(void)
{
	Managed<QueryOps>(_name).Begin(_target);
}

inline void QueryOps::Activator::_end(void)
{
	Managed<QueryOps>(_name).End(_target);
}

template <typename ResultType>
inline void QueryOps::Execution<ResultType>::WaitForResult(void)
{
	if(this->Finish())
	{
		Managed<QueryOps>(_name).WaitForResult(_result);
	}
}

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the OpenGL asynchronous query functionality
/**
 *  @ingroup oglplus_objects
 */
class Query
 : public QueryOps
{ };
#else
typedef Object<QueryOps> Query;
#endif

} // namespace oglplus

#endif // include guard
