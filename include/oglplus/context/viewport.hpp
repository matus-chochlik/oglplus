/**
 *  @file oglplus/context/viewport.hpp
 *  @brief Wrappers for viewport-related operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_VIEWPORT_1201040722_HPP
#define OGLPLUS_CONTEXT_VIEWPORT_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>

namespace oglplus {
namespace context {

/// Wrapper for the viewport-related operations
/**
 *  @ingroup ogl_context
 */
class ViewportOps
{
public:
	/// Sets the current viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Viewport}
	 */
	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		OGLPLUS_GLFUNC(Viewport)(x, y, w, h);
		HandleIfError(OGLPLUS_ERROR_INFO(Viewport));
	}

	/// Sets the current viewport starting at (0,0)
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Viewport}
	 */
	static void Viewport(GLsizei w, GLsizei h)
	{
		OGLPLUS_GLFUNC(Viewport)(0, 0, w, h);
		HandleIfError(OGLPLUS_ERROR_INFO(Viewport));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
