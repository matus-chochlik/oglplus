/**
 *  @file oglplus/context/scissor_test.hpp
 *  @brief Wrappers for scissor tests and operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_SCISSOR_TEST_1201040722_HPP
#define OGLPLUS_CONTEXT_SCISSOR_TEST_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>

namespace oglplus {
namespace context {

/// Wrapper for the scissor-buffer-related operations
/**
 *  @ingroup ogl_context
 */
class ScissorTest
{
public:
	/// Defines the scissor rectangle for the first viewport
	static void Scissor(
		GLint left,
		GLint bottom,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(Scissor)(left, bottom, width, height);
		AssertNoError(OGLPLUS_ERROR_INFO(Scissor));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_viewport_array
	/// Defines the scissor rectangle for the specified viewport
	static void ScissorIndexed(
		GLuint index,
		GLint left,
		GLint bottom,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(ScissorIndexed)(
			index,
			left,
			bottom,
			width,
			height
		);
		HandleIfError(OGLPLUS_ERROR_INFO(ScissorIndexed));
	}

	/// Defines the scissor rectangle for the specified viewport
	static void ScissorIndexedv(GLuint index, GLint* v)
	{
		OGLPLUS_GLFUNC(ScissorIndexedv)(index, v);
		HandleIfError(OGLPLUS_ERROR_INFO(ScissorIndexedv));
	}

	/// Defines the scissor rectangle for multiple viewports
	static void ScissorArrayv(GLuint first, GLsizei count, GLint* v)
	{
		OGLPLUS_GLFUNC(ScissorArrayv)(first, count, v);
		HandleIfError(OGLPLUS_ERROR_INFO(ScissorArrayv));
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
