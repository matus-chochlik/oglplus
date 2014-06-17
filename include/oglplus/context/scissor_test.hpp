/**
 *  @file oglplus/context/scissor_test.hpp
 *  @brief Wrappers for scissor tests and operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_SCISSOR_TEST_1201040722_HPP
#define OGLPLUS_CONTEXT_SCISSOR_TEST_1201040722_HPP

#include <oglplus/glfunc.hpp>

namespace oglplus {
namespace context {

/// Helper structure storing the extents of a 2D scissor rectangle
struct ScissorRectangle
{
	// private implementation detail, do not use
	GLint _v[4];

	/// The x-coordinate
	GLint X(void) const
	{
		return _v[0];
	}

	/// The y-coordinate
	GLint Y(void) const
	{
		return _v[1];
	}

	/// The x-coordinate
	GLint Left(void) const
	{
		return _v[0];
	}

	/// The y-coordinate
	GLint Bottom(void) const
	{
		return _v[1];
	}

	/// The width of the viewport
	GLint Width(void) const
	{
		return _v[2];
	}

	/// The height of the viewport
	GLint Height(void) const
	{
		return _v[3];
	}
};

/// Wrapper for the scissor-buffer-related operations
/**
 *  @ingroup ogl_context
 */
class ScissorTest
{
public:
	/// Defines the scissor rectangle for the first viewport
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Scissor}
	 */
	static void Scissor(
		GLint left,
		GLint bottom,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(Scissor)(left, bottom, width, height);
		OGLPLUS_VERIFY_SIMPLE(Scissor);
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_viewport_array
	/// Defines the scissor rectangle for the specified @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,1,ARB,viewport_array}
	 *  @glsymbols
	 *  @glfunref{ScissorIndexed}
	 */
	static void Scissor(
		GLuint viewport,
		GLint left,
		GLint bottom,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(ScissorIndexed)(
			viewport,
			left,
			bottom,
			width,
			height
		);
		OGLPLUS_CHECK(
			ScissorIndexed,
			Error,
			Index(viewport)
		);
	}

	/// Defines the scissor rectangle for the specified @p viewport
	/**
	 *  @glvoereq{4,1,ARB,viewport_array}
	 *  @glsymbols
	 *  @glfunref{ScissorIndexedv}
	 */
	static void Scissor(GLuint viewport, GLint* v)
	{
		OGLPLUS_GLFUNC(ScissorIndexedv)(viewport, v);
		OGLPLUS_CHECK(
			ScissorIndexedv,
			Error,
			Index(viewport)
		);
	}

	/// Defines scissor boxes for viewports specified by @p first @p count
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,1,ARB,viewport_array}
	 *  @glsymbols
	 *  @glfunref{ScissorArrayv}
	 */
	static void ScissorArray(GLuint first, GLsizei count, GLint* v)
	{
		OGLPLUS_GLFUNC(ScissorArrayv)(first, count, v);
		OGLPLUS_CHECK_SIMPLE(ScissorArrayv);
	}

	/// Returns the extents of scissor box of the specified @p viewport
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,1,ARB,viewport_array}
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{SCISSOR_BOX}
	 */
	static ScissorRectangle ScissorBox(GLuint viewport)
	{
		ScissorRectangle result;
		OGLPLUS_GLFUNC(GetIntegeri_v)(
			GL_SCISSOR_BOX,
			viewport,
			result._v
		);
		OGLPLUS_CHECK(
			GetIntegeri_v,
			Error,
			Index(viewport)
		);
		return result;
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
