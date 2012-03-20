/**
 *  @file oglplus/context/limit_queries.hpp
 *  @brief Wrappers for implementation-dependent-limit queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_LIMIT_QUERIES_1201040722_HPP
#define OGLPLUS_CONTEXT_LIMIT_QUERIES_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/limit_query.hpp>

namespace oglplus {
namespace context {

/// Wrapper for implementation-dependent limit queries
/**
 *  @ingroup ogl_context
 */
class LimitQueries
{
public:
	/// Gets the implementation-dependent limit value
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 */
	static GLint IntLimit(LimitQuery query)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GLenum(query), &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
	}

	/// Gets the implementation-dependent limit value
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 */
	static GLfloat FloatLimit(LimitQuery query)
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetFloatv)(GLenum(query), &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetFloatv));
		return result;
	}

	/// Raises a LimitError if @p value is greater than the specified @p limit
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *
	 *  @throws LimitError
	 */
	static void RequireAtLeast(LimitQuery limit, GLint value)
	{
		GLint max_limit = IntLimit(limit);
		if(value > max_limit)
		{
			HandleLimitError<LimitError>(
				value,
				max_limit,
				OGLPLUS_ERROR_INFO_STR(EnumValueName(limit))
			);
		}
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
