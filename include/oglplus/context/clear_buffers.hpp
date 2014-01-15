/**
 *  @file oglplus/context/clear_buffers.hpp
 *  @brief Wrappers for operations clearing the buffers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_CLEAR_BUFFERS_1201040722_HPP
#define OGLPLUS_CONTEXT_CLEAR_BUFFERS_1201040722_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/buffer_select_bit.hpp>
#include <oglplus/color_buffer.hpp>
#include <oglplus/bitfield.hpp>

namespace oglplus {

/// Draw buffer clear bit enumeration
/**
 *  @ingroup enumerations
 */
typedef BufferSelectBit ClearBit;

namespace context {

class ClearBuffers;

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

/// Helper class used by ClearBuffers::Clear()
/** Instances of this class cause the write buffers to be cleared
 *  depending on which member functions were called during the life-time
 *  of the instance.
 *
 *  @note The actual clearing of the buffers is done when the instance
 *  is destroyed.
 *
 *  @see ClearBuffers
 *  @see ClearBuffers::Clear()
 *
 *  @ingroup ogl_context
 */
class ClrBits
{
private:
	GLbitfield _bits;

	GLbitfield _forward(void)
	{
		GLbitfield res = _bits;
		_bits = 0;
		return res;
	}

	friend class ClearBuffers;

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	ClrBits(void) = delete;
	ClrBits(const ClrBits&) = delete;
#else
	ClrBits(void);
	ClrBits(const ClrBits&);
#endif

	ClrBits(GLbitfield bit)
	 : _bits(bit)
	{ }

	inline ClrBits _make(GLbitfield bit)
	{
		return ClrBits(_forward() | bit);
	}
public:
	/// Calling this member function causes the color buffer to be cleared
	/**
	 *  @glsymbols
	 *  @gldefref{COLOR_BUFFER_BIT}
	 */
	inline ClrBits ColorBuffer(void)
	{
		return _make(GL_COLOR_BUFFER_BIT);
	}

	/// Calling this member function causes the depth buffer to be cleared
	/**
	 *  @glsymbols
	 *  @gldefref{DEPTH_BUFFER_BIT}
	 */
	inline ClrBits DepthBuffer(void)
	{
		return _make(GL_DEPTH_BUFFER_BIT);
	}

	/// Calling this member function causes the stencil buffer to be cleared
	/**
	 *  @glsymbols
	 *  @gldefref{STENCIL_BUFFER_BIT}
	 */
	inline ClrBits StencilBuffer(void)
	{
		return _make(GL_STENCIL_BUFFER_BIT);
	}

	inline ClrBits(ClrBits&& temp)
	 : _bits(temp._forward())
	{ }

	void DoIt(void) const
	{
		if(_bits)
		{
			OGLPLUS_GLFUNC(Clear)(_bits);
			OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Clear));
		}
	}

	void Dismiss(void)
	{
		_bits = 0;
	}

	void operator()(void) const
	{
		DoIt();
	}

	void operator()(bool dismiss)
	{
		DoIt();
		if(dismiss) Dismiss();
	}

	/// The destructor does the actual clearing of the buffers
	/**
	 *  @glsymbols
	 *  @glfunref{Clear}
	 */
	inline ~ClrBits(void)
	{
		try{ DoIt(); }
		catch(...){ }
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
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
#else
	static void ClearDepth(GLfloat d)
	{
		OGLPLUS_GLFUNC(ClearDepthf)(d);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ClearDepthf));
	}
#endif

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
	static ClrBits Clear(void)
	{
		return ClrBits(0);
	}

	/// Clears buffers specified by the bits parameter
	/** This function clears the specified buffers.
	 *
	 *  example:
	 *  @code
	 *  Context gl;
	 *  gl.Clear(ClearBit::ColorBuffer);
	 *  gl.Clear(ClearBit::ColorBuffer|ClearBit::DepthBuffer);
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


	/// Clears the specified color draw buffer
	/** This function clears the specified color draw buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 *  @gldefref{GL_COLOR}
	 */
	static void ClearColorBuffer(
		GLint draw_buffer,
		const GLint* value
	)
	{
		OGLPLUS_GLFUNC(ClearBufferiv)(
			GL_COLOR,
			draw_buffer,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferiv));
	}

	/// Clears the specified color draw buffer
	/** This function clears the specified color draw buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 */
	static void ClearColorBuffer(
		ColorBuffer buffer,
		GLint draw_buffer,
		const GLint* value
	)
	{
		OGLPLUS_GLFUNC(ClearBufferiv)(
			GLenum(buffer),
			draw_buffer,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferiv));
	}

	/// Clears the specified color draw buffer
	/** This function clears the specified color draw buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 *  @gldefref{GL_COLOR}
	 */
	static void ClearColorBuffer(
		GLint draw_buffer,
		const GLuint* value
	)
	{
		OGLPLUS_GLFUNC(ClearBufferuiv)(
			GL_COLOR,
			draw_buffer,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferuiv));
	}

	/// Clears the specified color draw buffer
	/** This function clears the specified color draw buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 */
	static void ClearColorBuffer(
		ColorBuffer buffer,
		GLint draw_buffer,
		const GLuint* value
	)
	{
		OGLPLUS_GLFUNC(ClearBufferuiv)(
			GLenum(buffer),
			draw_buffer,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferuiv));
	}

	/// Clears the specified color draw buffer
	/** This function clears the specified color draw buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 *  @gldefref{GL_COLOR}
	 */
	static void ClearColorBuffer(
		GLint draw_buffer,
		const GLfloat* value
	)
	{
		OGLPLUS_GLFUNC(ClearBufferfv)(
			GL_COLOR,
			draw_buffer,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferfv));
	}

	/// Clears the specified color draw buffer
	/** This function clears the specified color draw buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 */
	static void ClearColorBuffer(
		ColorBuffer buffer,
		GLint draw_buffer,
		const GLfloat* value
	)
	{
		OGLPLUS_GLFUNC(ClearBufferfv)(
			GLenum(buffer),
			draw_buffer,
			value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferfv));
	}

	/// Clears the depth buffer
	/** This function clears the depth buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 *  @gldefref{GL_DEPTH}
	 */
	static void ClearDepthBuffer(GLfloat value)
	{
		OGLPLUS_GLFUNC(ClearBufferfv)(GL_DEPTH, 0, &value);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferfv));
	}

	/// Clears the stencil buffer
	/** This function clears the stencil buffer of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 *  @gldefref{GL_STENCIL}
	 */
	static void ClearStencilBuffer(GLint value)
	{
		OGLPLUS_GLFUNC(ClearBufferiv)(GL_STENCIL, 0, &value);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferiv));
	}

	/// Clears the depth and the stencil buffer
	/** This function clears the depth and stencil buffers of the currently
	 *  bound framebuffer.
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{ClearBuffer}
	 *  @gldefref{GL_DEPTH_STENCIL}
	 */
	static void ClearStencilBuffer(GLfloat depth_value, GLint stencil_value)
	{
		OGLPLUS_GLFUNC(ClearBufferfi)(
			GL_DEPTH_STENCIL,
			0,
			depth_value,
			stencil_value
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(ClearBufferfi));
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
