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
	 *  @glfunref{GetInteger}
	 */
	static GLint GetLimit(oglplus::LimitQuery query)
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetIntegerv)(GLenum(query), &result);
		HandleIfError(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
