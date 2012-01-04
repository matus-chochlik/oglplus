/**
 *  @file oglplus/context/stencil_test.hpp
 *  @brief Wrappers for stencil tests and operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_STENCIL_TEST_1201040722_HPP
#define OGLPLUS_CONTEXT_STENCIL_TEST_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/compare_func.hpp>
#include <oglplus/stencil_op.hpp>
#include <oglplus/face_mode.hpp>

namespace oglplus {
namespace context {

/// Wrapper for the stencil-buffer-related operations
/**
 *  @ingroup ogl_context
 */
class StencilTest
{
public:
	/// Sets the stencil function
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFunc}
	 */
	static void StencilFunc(
		CompareFunction func,
		GLint ref = GLint(0),
		GLuint mask = ~GLuint(0)
	)
	{
		OGLPLUS_GLFUNC(StencilFunc)(GLenum(func), ref, mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilFunc));
	}

	/// Sets the stencil function separately for front and back faces
	/**
	 *  @glsymbols
	 *  @glfunref{StencilFuncSeparate}
	 */
	static void StencilFuncSeparate(
		Face face,
		CompareFunction func,
		GLint ref = GLint(0),
		GLuint mask = ~GLuint(0)
	)
	{
		OGLPLUS_GLFUNC(StencilFuncSeparate)(
			GLenum(face),
			GLenum(func),
			ref,
			mask
		);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilFuncSeparate));
	}

	/// Sets the stencil operation
	/**
	 *  @glsymbols
	 *  @glfunref{StencilOp}
	 */
	static void StencilOp(
		StencilOperation sfail,
		StencilOperation dfail,
		StencilOperation dpass
	)
	{
		OGLPLUS_GLFUNC(StencilOp)(
			GLenum(sfail),
			GLenum(dfail),
			GLenum(dpass)
		);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilOp));
	}

	/// Sets the stencil operation separately for front and back faces
	/**
	 *  @glsymbols
	 *  @glfunref{StencilOpSeparate}
	 */
	static void StencilOpSeparate(
		Face face,
		StencilOperation sfail,
		StencilOperation dfail,
		StencilOperation dpass
	)
	{
		OGLPLUS_GLFUNC(StencilOpSeparate)(
			GLenum(face),
			GLenum(sfail),
			GLenum(dfail),
			GLenum(dpass)
		);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilOpSeparate));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
