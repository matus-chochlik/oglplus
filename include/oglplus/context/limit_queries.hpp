/**
 *  @file oglplus/context/limit_queries.hpp
 *  @brief Wrappers for implementation-dependent-limit queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_LIMIT_QUERIES_1201040722_HPP
#define OGLPLUS_CONTEXT_LIMIT_QUERIES_1201040722_HPP

#include <oglplus/glfunc.hpp>
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
		OGLPLUS_VERIFY_SIMPLE(GetIntegerv);
		return result;
	}

	/// Gets the implementation-dependent indexed limit value
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 */
	static GLint IntLimit(LimitQuery query, GLuint index)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegeri_v)(GLenum(query), index, &result);
		OGLPLUS_VERIFY_SIMPLE(GetIntegeri_v);
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
		OGLPLUS_VERIFY_SIMPLE(GetFloatv);
		return result;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_viewport_array
	/// Gets the implementation-dependent indexed limit value
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 */
	static GLfloat FloatLimit(LimitQuery query, GLuint index)
	{
		GLfloat result = 0;
		OGLPLUS_GLFUNC(GetFloati_v)(GLenum(query), index, &result);
		OGLPLUS_VERIFY_SIMPLE(GetFloati_v);
		return result;
	}
#endif

	static void ThrowIfOverLimit(
		LimitQuery limit,
		GLint value,
		GLint max_limit
	)
	{
		OGLPLUS_HANDLE_ERROR_IF(
			value > max_limit,
			GL_INVALID_VALUE,
			LimitError::Message(),
			LimitError,
			GLFuncName(EnumValueName(limit).c_str())
		);
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
		ThrowIfOverLimit(limit, value, IntLimit(limit));
	}

	/// Raises a LimitError if @p value is greater than the specified @p limit
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *
	 *  @throws LimitError
	 */
	static void RequireAtLeast(LimitQuery limit, GLuint index, GLint value)
	{
		ThrowIfOverLimit(limit, value, IntLimit(limit, index));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
