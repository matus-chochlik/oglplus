/**
 *  @file oglplus/context/clear_buffers.hpp
 *  @brief Wrappers for operations clearing the buffers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_CLEAR_BUFFERS_1201040722_HPP
#define OGLPLUS_CONTEXT_CLEAR_BUFFERS_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/buffer_select_bit.hpp>
#include <oglplus/bitfield.hpp>

#include <oglplus/auxiliary/clr_bits.hpp>

namespace oglplus {

/// Draw buffer clear bit enumeration
/**
 *  @ingroup enumerations
 */
typedef BufferSelectBit ClearBit;

namespace context {

/// Helper structure storing the clear color components
struct RGBAValue
{
	// private implementation detail, do not use
	GLfloat _v[4];

	/// The red component
	GLfloat Red(void) const
	{
		return _v[0];
	}

	/// The green component
	GLfloat Green(void) const
	{
		return _v[1];
	}

	/// The blue component
	GLfloat Blue(void) const
	{
		return _v[2];
	}

	/// The alpha component
	GLfloat Alpha(void) const
	{
		return _v[3];
	}
};

/// Wrapper for the operations that are used to clear the draw buffers
/**
 *  @ingroup ogl_context
 */
class ClearBuffers
{
public:
	/// Sets the clear color
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearColor}
	 */
	static void ClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		OGLPLUS_GLFUNC(ClearColor)(r, g, b, a);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClearColor));
	}

	/// Sets the clear depth
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearDepth}
	 */
	static void ClearDepth(GLclampd d)
	{
		OGLPLUS_GLFUNC(ClearDepth)(d);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClearDepth));
	}

	/// Sets the clear stencil buffer value
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearStencil}
	 */
	static void ClearStencil(GLint s)
	{
		OGLPLUS_GLFUNC(ClearStencil)(s);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClearStencil));
	}

	/// Clears buffers specified by calling functions of the returned object
	/** This function returns an object that allows to specify which buffers
	 *  to clear by calling its ColorBuffer, DepthBuffer and StencilBuffer
	 *  member functions.
	 *
	 *  example:
	 *  @code
	 *  Context gl;
	 *  gl.Clear().ColorBuffer();
	 *  gl.Clear().ColorBuffer().DepthBuffer();
	 *  gl.Clear().StencilBuffer().DepthBuffer();
	 *  gl.Clear().ColorBuffer().DepthBuffer().StencilBuffer();
	 *  @endcode
	 *
	 *  @throws Error
	 *
	 *  @see ClearColor
	 *  @see ClearDepth
	 *  @see ClearStencil
	 *
	 *  @glsymbols
	 *  @glfunref{Clear}
	 */
#if OGLPLUS_DOCUMENTATION_ONLY
	static UnspecifiedType Clear(void);
#else
	static oglplus::aux::ClrBits Clear(void)
	{
		return aux::ClrBits(0);
	}
#endif

	/// Clears buffers specified by the bits parameter
	/** This function clears the specified buffers.
	 *
	 *  example:
	 *  @code
	 *  Context gl;
	 *  gl.Clear({ClearBit::ColorBuffer});
	 *  gl.Clear({ClearBit::ColorBuffer, ClearBit::DepthBuffer});
	 *  gl.Clear({ClearBit::ColorBuffer, ClearBit::StencilBuffer});
	 *  @endcode
	 *
	 *  @throws Error
	 *
	 *  @see ClearColor
	 *  @see ClearDepth
	 *  @see ClearStencil
	 *
	 *  @glsymbols
	 *  @glfunref{Clear}
	 */
	static void Clear(Bitfield<oglplus::ClearBit> bits)
	{
		OGLPLUS_GLFUNC(Clear)(GLbitfield(bits));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Clear));
	}

	/// Returns the color value used for clearing of the color buffer
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{COLOR_CLEAR_VALUE}
	 */
	static oglplus::context::RGBAValue ColorClearValue(void)
	{
		oglplus::context::RGBAValue result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_COLOR_CLEAR_VALUE, result._v);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetFloatv));
		return result;
	}

	/// Returns the depth value used for clearing of the depth buffer
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{DEPTH_CLEAR_VALUE}
	 */
	static GLfloat DepthClearValue(void)
	{
		GLfloat result;
		OGLPLUS_GLFUNC(GetFloatv)(GL_DEPTH_CLEAR_VALUE, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetFloatv));
		return result;
	}

	/// Returns the value used for clearing of the stencil buffer
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{Get}
	 *  @gldefref{STENCIL_CLEAR_VALUE}
	 */
	static GLint ClearStencilValue(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(GL_STENCIL_CLEAR_VALUE, &result);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		return result;
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
