/**
 *  @file oglplus/context/numeric_queries.hpp
 *  @brief Wrappers for GL numeric queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_NUMERIC_QUERIES_1202210920_HPP
#define OGLPLUS_CONTEXT_NUMERIC_QUERIES_1202210920_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>

#include <cassert>

namespace oglplus {
namespace context {

/// Wrapper for the GL numeric-query-related operations
/**
 *  @ingroup ogl_context
 */
class NumericQueries
{
public:
	/**
	 *  @throws Error
	 *
	 *  @see MinorVersion
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MAJOR_VERSION}
	 */
	static GLint MajorVersion(void)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_MAJOR_VERSION, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
	}

	/// Queries the minor version number
	/**
	 *  @throws Error
	 *
	 *  @see MajorVersion
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{MINOR_VERSION}
	 */
	static GLint MinorVersion(void)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_MINOR_VERSION, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_3 || GL_ARB_timer_query
	/// Query the current GL timestamp
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{TIMESTAMP}
	 */
	static GLint64 Timestamp(void)
	{
		GLint64 result = 0;
		OGLPLUS_GLFUNC(GetInteger64v)(GL_TIMESTAMP, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetInteger64v));
		return result;
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
