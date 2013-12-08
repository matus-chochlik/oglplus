/**
 *  @file oglplus/context/buffer_masking.hpp
 *  @brief Wrappers for operations for fine control of buffer updates
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_BUFFER_MASKING_1201040722_HPP
#define OGLPLUS_CONTEXT_BUFFER_MASKING_1201040722_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/face_mode.hpp>

namespace oglplus {
namespace context {

/// Helper structure storing the clear color component mask
struct RGBAMask
{
	// private implementation detail, do not use
	GLint _v[4];

	/// The red component mask
	bool Red(void) const
	{
		return _v[0] == GL_TRUE;
	}

	/// The green component mask
	bool Green(void) const
	{
		return _v[1] == GL_TRUE;
	}

	/// The blue component mask
	bool Blue(void) const
	{
		return _v[2] == GL_TRUE;
	}

	/// The alpha component mask
	bool Alpha(void) const
	{
		return _v[3] == GL_TRUE;
	}
};

/// Wrappers for operations for fine control of buffer updates
/**
 *  @ingroup ogl_context
 */
class BufferMasking
{
public:
	/// Sets the color mask
	/**
	 *  @glsymbols
	 *  @glfunref{ColorMask}
	 */
	static void ColorMask(bool r, bool g, bool b, bool a)
	{
		OGLPLUS_GLFUNC(ColorMask)(
			r ? GL_TRUE : GL_FALSE,
			g ? GL_TRUE : GL_FALSE,
			b ? GL_TRUE : GL_FALSE,
			a ? GL_TRUE : GL_FALSE
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ColorMask));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Sets the color mask for a particular @p buffer
	/**
	 *  @glsymbols
	 *  @glfunref{ColorMaski}
	 */
	static void ColorMask(GLuint buffer, bool r, bool g, bool b, bool a)
	{
		OGLPLUS_GLFUNC(ColorMaski)(
			buffer,
			r ? GL_TRUE : GL_FALSE,
			g ? GL_TRUE : GL_FALSE,
			b ? GL_TRUE : GL_FALSE,
			a ? GL_TRUE : GL_FALSE
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ColorMaski));
	}
#endif

	/// Sets the depth @p mask
	/**
	 *  @glsymbols
	 *  @glfunref{DepthMask}
	 */
	static void DepthMask(bool mask)
	{
		OGLPLUS_GLFUNC(DepthMask)(mask ? GL_TRUE : GL_FALSE);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DepthMask));
	}

	/// Sets the stencil @p mask
	/**
	 *  @glsymbols
	 *  @glfunref{StencilMask}
	 */
	static void StencilMask(GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilMask)(mask);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(StencilMask));
	}

	/// Sets the stencil mask separately for front and back faces
	/**
	 *  @glsymbols
	 *  @glfunref{StencilMaskSeparate}
	 */
	static void StencilMaskSeparate(Face face, GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilMaskSeparate)(GLenum(face), mask);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(StencilMaskSeparate));
	}

	/// Returns the value of color buffer write mask
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{COLOR_WRITEMASK}
	 */
	static oglplus::context::RGBAMask ColorWriteMask(GLuint buffer = 0)
	{
		oglplus::context::RGBAMask result;
		OGLPLUS_GLFUNC(GetIntegeri_v)(
			GL_COLOR_WRITEMASK,
			buffer,
			result._v
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetIntegeri_v));
		return result;
	}

	/// Returns the value of depth buffer write mask
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{DEPTH_WRITEMASK}
	 */
	static bool DepthWriteMask(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_DEPTH_WRITEMASK, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result == GL_TRUE;
	}

	/// Returns the value of stencil write mask
	/**
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{STENCIL_WRITEMASK}
	 *  @gldefref{STENCIL_BACK_WRITEMASK}
	 */
	static GLuint StencilWriteMask(bool backface = false)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(
			backface?
			GL_STENCIL_BACK_WRITEMASK:
			GL_STENCIL_WRITEMASK,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return GLuint(result);
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
