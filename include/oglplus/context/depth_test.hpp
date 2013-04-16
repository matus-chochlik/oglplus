/**
 *  @file oglplus/context/depth_test.hpp
 *  @brief Wrappers for depth tests and operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_DEPTH_TEST_1201040722_HPP
#define OGLPLUS_CONTEXT_DEPTH_TEST_1201040722_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/compare_func.hpp>

namespace oglplus {
namespace context {

/// Wrapper for the depth-buffer-related operations
/**
 *  @ingroup ogl_context
 */
class DepthTest
{
public:
	/// Sets the depth comparison @p function
	/**
	 *  @glsymbols
	 *  @glfunref{DepthFunc}
	 */
	static void DepthFunc(CompareFunction function)
	{
		OGLPLUS_GLFUNC(DepthFunc)(GLenum(function));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DepthFunc));
	}

	/// Returns the depth comparison function
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{DEPTH_FUNC}
	 */
	static CompareFunction DepthFunc(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_DEPTH_FUNC, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return CompareFunction(result);
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
