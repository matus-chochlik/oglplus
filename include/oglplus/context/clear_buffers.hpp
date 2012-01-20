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

#include <oglplus/auxiliary/clr_bits.hpp>
#include <oglplus/auxiliary/bitfield.hpp>

namespace oglplus {

/// Draw buffer clear bit enumeration
/**
 *  @ingroup enumerations
 */
typedef BufferSelectBit ClearBit;

namespace context {

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
		HandleIfError(OGLPLUS_ERROR_INFO(ClearColor));
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
		HandleIfError(OGLPLUS_ERROR_INFO(ClearDepth));
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
		HandleIfError(OGLPLUS_ERROR_INFO(ClearStencil));
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
	static void Clear(std::initializer_list<oglplus::ClearBit> bits)
	{
		OGLPLUS_GLFUNC(Clear)(aux::MakeBitfield(bits));
		AssertNoError(OGLPLUS_ERROR_INFO(Clear));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
