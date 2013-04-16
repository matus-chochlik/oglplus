/**
 *  @file oglplus/context/blending.hpp
 *  @brief Wrappers for blending operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_BLENDING_1201040722_HPP
#define OGLPLUS_CONTEXT_BLENDING_1201040722_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/blend_func.hpp>

namespace oglplus {
namespace context {

/// Wrapper for blending operations
/**
 *  @ingroup ogl_context
 */
class Blending
{
public:
	/// Sets the blend equation
	/**
	 *  @glsymbols
	 *  @glfunref{BlendEquation}
	 */
	static void BlendEquation(oglplus::BlendEquation eq)
	{
		OGLPLUS_GLFUNC(BlendEquation)(GLenum(eq));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendEquation));
	}

	/// Sets the blend equation separate for RGB and alpha
	/**
	 *  @glsymbols
	 *  @glfunref{BlendEquationSeparate}
	 */
	static void BlendEquationSeparate(
		oglplus::BlendEquation eq_rgb,
		oglplus::BlendEquation eq_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendEquationSeparate)(
			GLenum(eq_rgb),
			GLenum(eq_alpha)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendEquationSeparate));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend equation for a particular draw @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendEquationi}
	 */
	static void BlendEquation(GLuint buffer, oglplus::BlendEquation eq)
	{
		OGLPLUS_GLFUNC(BlendEquationi)(buffer, GLenum(eq));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendEquationi));
	}

	/// Sets the blend equation separate for RGB and alpha for a @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendEquationSeparatei}
	 */
	static void BlendEquationSeparate(
		GLuint buffer,
		oglplus::BlendEquation eq_rgb,
		oglplus::BlendEquation eq_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendEquationSeparatei)(
			buffer,
			GLenum(eq_rgb),
			GLenum(eq_alpha)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendEquationSeparatei));
	}
#endif

	/// Sets the blend function
	/**
	 *  @glsymbols
	 *  @glfunref{BlendFunc}
	 */
	static void BlendFunc(BlendFunction src, BlendFunction dst)
	{
		OGLPLUS_GLFUNC(BlendFunc)(GLenum(src), GLenum(dst));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendFunc));
	}

	/// Sets the blend function separate for RGB and alpha
	/**
	 *  @glsymbols
	 *  @glfunref{BlendFuncSeparate}
	 */
	static void BlendFuncSeparate(
		BlendFunction src_rgb,
		BlendFunction dst_rgb,
		BlendFunction src_alpha,
		BlendFunction dst_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendFuncSeparate)(
			GLenum(src_rgb),
			GLenum(dst_rgb),
			GLenum(src_alpha),
			GLenum(dst_alpha)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendFuncSeparate));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend function for a particular @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendFunci}
	 */
	static void BlendFunc(
		GLuint buffer,
		BlendFunction src,
		BlendFunction dst
	)
	{
		OGLPLUS_GLFUNC(BlendFunci)(buffer, GLenum(src), GLenum(dst));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendFunci));
	}

	/// Sets the blend function separate for RGB and alpha for a @p buffer
	/**
	 *  @glverreq{4,0}
	 *  @glsymbols
	 *  @glfunref{BlendFuncSeparatei}
	 */
	static void BlendFuncSeparate(
		GLuint buffer,
		BlendFunction src_rgb,
		BlendFunction dst_rgb,
		BlendFunction src_alpha,
		BlendFunction dst_alpha
	)
	{
		OGLPLUS_GLFUNC(BlendFuncSeparatei)(
			buffer,
			GLenum(src_rgb),
			GLenum(dst_rgb),
			GLenum(src_alpha),
			GLenum(dst_alpha)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendFuncSeparatei));
	}
#endif

	/// Sets the blend color
	/**
	 *  @glsymbols
	 *  @glfunref{BlendColor}
	 */
	static void BlendColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		OGLPLUS_GLFUNC(BlendColor)(r, g, b, a);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(BlendColor));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
