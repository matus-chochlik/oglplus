/**
 *  @file oglplus/context/buffer_masking.hpp
 *  @brief Wrappers for operations for fine control of buffer updates
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_BUFFER_MASKING_1201040722_HPP
#define OGLPLUS_CONTEXT_BUFFER_MASKING_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/face_mode.hpp>

namespace oglplus {
namespace context {

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
		AssertNoError(OGLPLUS_ERROR_INFO(ColorMask));
	}

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
		AssertNoError(OGLPLUS_ERROR_INFO(ColorMaski));
	}

	/// Sets the depth @p mask
	/**
	 *  @glsymbols
	 *  @glfunref{DepthMask}
	 */
	static void DepthMask(bool mask)
	{
		OGLPLUS_GLFUNC(DepthMask)(mask ? GL_TRUE : GL_FALSE);
		AssertNoError(OGLPLUS_ERROR_INFO(DepthMask));
	}

	/// Sets the stencil @p mask
	/**
	 *  @glsymbols
	 *  @glfunref{StencilMask}
	 */
	static void StencilMask(GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilMask)(mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilMask));
	}

	/// Sets the stencil mask separately for front and back faces
	/**
	 *  @glsymbols
	 *  @glfunref{StencilMaskSeparate}
	 */
	static void StencilMaskSeparate(Face face, GLuint mask)
	{
		OGLPLUS_GLFUNC(StencilMaskSeparate)(GLenum(face), mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilMaskSeparate));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
