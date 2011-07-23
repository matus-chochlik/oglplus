/**
 *  @file oglplus/context.hpp
 *  @brief Declaration of OpenGL's state wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_1107121317_HPP
#define OGLPLUS_CONTEXT_1107121317_HPP

#include <oglplus/error.hpp>
#include <oglplus/primitive_type.hpp>
#include <oglplus/data_type.hpp>

#include <oglplus/auxiliary/clr_bits.hpp>
#include <oglplus/auxiliary/bitfield.hpp>

namespace oglplus {

enum class ClearBit : GLbitfield
{
	ColorBuffer = GL_COLOR_BUFFER_BIT,
	DepthBuffer = GL_DEPTH_BUFFER_BIT,
	StencilBuffer = GL_STENCIL_BUFFER_BIT
};

/// Wrapper for the current OpenGL context operations
class Context
{
public:
	/// Sets the clear color
	/**
	 *  @throws Error
	 */
	static void ClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		::glClearColor(r, g, b, a);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	/// Sets the clear depth
	/**
	 *  @throws Error
	 */
	static void ClearDepth(GLclampd d)
	{
		::glClearDepth(d);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	/// Sets the clear stencil buffer value
	/**
	 *  @throws Error
	 */
	static void ClearStencil(GLint s)
	{
		::glClearStencil(s);
		ThrowOnError(OGLPLUS_ERROR_INFO());
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
	 */
	static aux::ClrBits Clear(void)
	{
		return aux::ClrBits(0);
	}

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
	 */
	static void Clear(const std::initializer_list<ClearBit>& bits)
	{
		::glClear(aux::MakeBitfield(bits));
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	/// Sets the current viewport
	/**
	 *  @throws Error
	 */
	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		::glViewport(x, y, w, h);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	/// Sets the current viewport starting at (0,0)
	/**
	 *  @throws Error
	 */
	static void Viewport(GLsizei w, GLsizei h)
	{
		::glViewport(0, 0, w, h);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	/// Draws the @a count of primitives from the bound array buffers
	/**
	 *  @throws Error
	 */
	static void DrawArrays(
		PrimitiveType primitive,
		GLint first,
		GLsizei count
	)
	{
		::glDrawArrays(GLenum(primitive), first, count);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}


	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 */
	static void DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type
	)
	{
		::glDrawElements(GLenum(primitive), count, GLenum(data_type),0);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
};

} // namespace oglplus

#endif // include guard
