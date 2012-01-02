/**
 *  @file oglplus/context.hpp
 *  @brief Declaration of OpenGL's state wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_1107121317_HPP
#define OGLPLUS_CONTEXT_1107121317_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/capability.hpp>
#include <oglplus/primitive_type.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/face_mode.hpp>
#include <oglplus/polygon_mode.hpp>
#include <oglplus/blend_func.hpp>
#include <oglplus/compare_func.hpp>
#include <oglplus/stencil_op.hpp>
#include <oglplus/color_log_op.hpp>
#include <oglplus/color_buffer.hpp>
#include <oglplus/memory_barrier.hpp>

#include <oglplus/auxiliary/clr_bits.hpp>
#include <oglplus/auxiliary/bitfield.hpp>

namespace oglplus {

/// Draw buffer clear bit enumeration
/**
 *  @ingroup enumerations
 */
enum class ClearBit : GLbitfield
{
#include <oglplus/enums/clear_bit.ipp>
};

/** @defgroup ogl_context Current OpenGL context operations
 *
 *  Here are listed classes and functions wrapping operations on the current
 *  OpenGL context, which are not related to any explicitly allocated
 *  object or resource, i.e. operations like enabling and disabling
 *  various OpenGL oglplus::Capability "capabilities" and changing the state
 *  values of the current context.
 */

/// Wrapper for the current OpenGL context operations
/**
 *  @ingroup ogl_context
 */
class Context
{
public:
	/// Enable a @p capability
	/**
	 *  @glsymbols
	 *  @glfunref{Enable}
	 */
	static void Enable(Capability capability)
	{
		OGLPLUS_GLFUNC(Enable)(GLenum(capability));
		AssertNoError(OGLPLUS_ERROR_INFO(Enable));
	}

	/// Enable a @p functionality
	/**
	 *  @glsymbols
	 *  @glfunref{Enable}
	 */
	static void Enable(Functionality functionality, GLuint offset)
	{
		OGLPLUS_GLFUNC(Enable)(GLenum(functionality)+offset);
		AssertNoError(OGLPLUS_ERROR_INFO(Enable));
	}

	/// Disable a @p capability
	/**
	 *  @glsymbols
	 *  @glfunref{Disable}
	 */
	static void Disable(Capability capability)
	{
		OGLPLUS_GLFUNC(Disable)(GLenum(capability));
		AssertNoError(OGLPLUS_ERROR_INFO(Disable));
	}

	/// Disable a @p functionality
	/**
	 *  @glsymbols
	 *  @glfunref{Disable}
	 */
	static void Disable(Functionality functionality, GLuint offset)
	{
		OGLPLUS_GLFUNC(Disable)(GLenum(functionality)+offset);
		AssertNoError(OGLPLUS_ERROR_INFO(Disable));
	}

	/// Checks if a @p capability is enabled
	/**
	 *  @glsymbols
	 *  @glfunref{IsEnabled}
	 */
	static bool IsEnabled(Capability capability)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsEnabled)(GLenum(capability));
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabled));
		return result == GL_TRUE;
	}

	/// Checks if a @p functionality is enabled
	/**
	 *  @glsymbols
	 *  @glfunref{IsEnabled}
	 */
	static bool IsEnabled(Functionality functionality, GLuint offset)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsEnabled)(
			GLenum(functionality)+
			offset
		);
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabled));
		return result == GL_TRUE;
	}

	/// Enable a @p capability for an indexed target
	/**
	 *  @glsymbols
	 *  @glfunref{Enablei}
	 */
	static void Enable(Capability capability, GLuint index)
	{
		OGLPLUS_GLFUNC(Enablei)(GLenum(capability), index);
		AssertNoError(OGLPLUS_ERROR_INFO(Enablei));
	}

	/// Disable a @p capability for an indexed target
	/**
	 *  @glsymbols
	 *  @glfunref{Disablei}
	 */
	static void Disable(Capability capability, GLuint index)
	{
		OGLPLUS_GLFUNC(Disablei)(GLenum(capability), index);
		AssertNoError(OGLPLUS_ERROR_INFO(Disablei));
	}

	/// Check if a @p capability is enabled for indexed target
	/**
	 *  @glsymbols
	 *  @glfunref{IsEnabledi}
	 */
	static bool IsEnabled(Capability capability, GLuint index)
	{
		GLboolean result = OGLPLUS_GLFUNC(IsEnabledi)(
			GLenum(capability),
			index
		);
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabledi));
		return result == GL_TRUE;
	}

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
		ThrowOnError(OGLPLUS_ERROR_INFO(ClearColor));
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
		ThrowOnError(OGLPLUS_ERROR_INFO(ClearDepth));
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
		ThrowOnError(OGLPLUS_ERROR_INFO(ClearStencil));
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
	 *
	 *  @glsymbols
	 *  @glfunref{Clear}
	 */
	static void Clear(std::initializer_list<ClearBit> bits)
	{
		OGLPLUS_GLFUNC(Clear)(aux::MakeBitfield(bits));
		AssertNoError(OGLPLUS_ERROR_INFO(Clear));
	}

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

	/// Sets the depth comparison @p function
	/**
	 *  @glsymbols
	 *  @glfunref{DepthFunc}
	 */
	static void DepthFunc(CompareFunction function)
	{
		OGLPLUS_GLFUNC(DepthFunc)(GLenum(function));
		AssertNoError(OGLPLUS_ERROR_INFO(DepthFunc));
	}

	/// Sets the blend equation
	/**
	 *  @glsymbols
	 *  @glfunref{BlendEquation}
	 */
	static void BlendEquation(oglplus::BlendEquation eq)
	{
		OGLPLUS_GLFUNC(BlendEquation)(GLenum(eq));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquation));
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquationSeparate));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend equation for a particular draw @p buffer
	/**
	 *  @glsymbols
	 *  @glfunref{BlendEquationi}
	 */
	static void BlendEquation(GLuint buffer, oglplus::BlendEquation eq)
	{
		OGLPLUS_GLFUNC(BlendEquationi)(buffer, GLenum(eq));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquationi));
	}

	/// Sets the blend equation separate for RGB and alpha for a @p buffer
	/**
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquationSeparatei));
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFunc));
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFuncSeparate));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend function for a particular @p buffer
	/**
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFunci));
	}

	/// Sets the blend function separate for RGB and alpha for a @p buffer
	/**
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFuncSeparatei));
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
		AssertNoError(OGLPLUS_ERROR_INFO(BlendColor));
	}

	/// Sets the color logical operation
	/**
	 *  @glsymbols
	 *  @glfunref{LogicOp}
	 */
	static void LogicOp(ColorLogicOperation op)
	{
		OGLPLUS_GLFUNC(LogicOp)(GLenum(op));
		AssertNoError(OGLPLUS_ERROR_INFO(LogicOp));
	}

	/// Sets the polygon facing mode
	/**
	 *  @glsymbols
	 *  @glfunref{FrontFace}
	 */
	static void FrontFace(FaceOrientation orientation)
	{
		OGLPLUS_GLFUNC(FrontFace)(GLenum(orientation));
		AssertNoError(OGLPLUS_ERROR_INFO(FrontFace));
	}

	/// Sets the face culling mode
	/**
	 *  @glsymbols
	 *  @glfunref{CullFace}
	 */
	static void CullFace(Face mode)
	{
		OGLPLUS_GLFUNC(CullFace)(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(CullFace));
	}

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

	/// Sets the polygon rasterization mode
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonMode}
	 */
	static void PolygonMode(Face face, oglplus::PolygonMode mode)
	{
		OGLPLUS_GLFUNC(PolygonMode)(GLenum(face), GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(PolygonMode));
	}

	/// Sets the polygon depth offset
	/**
	 *  @glsymbols
	 *  @glfunref{PolygonOffset}
	 */
	static void PolygonOffset(GLfloat factor, GLfloat units)
	{
		OGLPLUS_GLFUNC(PolygonOffset)(factor, units);
		AssertNoError(OGLPLUS_ERROR_INFO(PolygonOffset));
	}

	/// Sets the line width
	/**
	 *  @glsymbols
	 *  @glfunref{LineWidth}
	 */
	static void LineWidth(GLfloat width)
	{
		OGLPLUS_GLFUNC(LineWidth)(width);
		AssertNoError(OGLPLUS_ERROR_INFO(LineWidth));
	}

	/// Sets the point size
	/**
	 *  @glsymbols
	 *  @glfunref{PointSize}
	 */
	static void PointSize(GLfloat size)
	{
		OGLPLUS_GLFUNC(PointSize)(size);
		AssertNoError(OGLPLUS_ERROR_INFO(PointSize));
	}

	/// Sets the destination color buffer for draw operations
	/**
	 *  @glsymbols
	 *  @glfunref{DrawBuffer}
	 */
	static void DrawBuffer(ColorBuffer buffer)
	{
		OGLPLUS_GLFUNC(DrawBuffer)(GLenum(buffer));
		AssertNoError(OGLPLUS_ERROR_INFO(DrawBuffer));
	}

	/// Sets the source color buffer for read operations
	/**
	 *  @glsymbols
	 *  @glfunref{ReadBuffer}
	 */
	static void ReadBuffer(ColorBuffer buffer)
	{
		OGLPLUS_GLFUNC(ReadBuffer)(GLenum(buffer));
		AssertNoError(OGLPLUS_ERROR_INFO(ReadBuffer));
	}

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
		ThrowOnError(OGLPLUS_ERROR_INFO(Viewport));
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
		ThrowOnError(OGLPLUS_ERROR_INFO(Viewport));
	}


	/// Draws @a count of primitives from the bound array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawArrays}
	 */
	static void DrawArrays(
		PrimitiveType primitive,
		GLint first,
		GLsizei count
	)
	{
		OGLPLUS_GLFUNC(DrawArrays)(GLenum(primitive), first, count);
		AssertNoError(OGLPLUS_ERROR_INFO(DrawArrays));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Draws @a count of primitives from the bound array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawArraysInstanced}
	 */
	static void DrawArraysInstanced(
		PrimitiveType primitive,
		GLint first,
		GLsizei count,
		GLsizei inst_count
	)
	{
		OGLPLUS_GLFUNC(DrawArraysInstanced)(
			GLenum(primitive),
			first,
			count,
			inst_count
		);
		AssertNoError(OGLPLUS_ERROR_INFO(DrawArraysInstanced));
	}
#endif

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawElements}
	 */
	static void DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type
	)
	{
		OGLPLUS_GLFUNC(DrawElements)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			0
		);
		AssertNoError(OGLPLUS_ERROR_INFO(DrawElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawElements}
	 */
	template <typename T>
	static void DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* p
	)
	{
		OGLPLUS_GLFUNC(DrawElements)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			p
		);
		AssertNoError(OGLPLUS_ERROR_INFO(DrawElements));
	}


#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2 || GL_ARB_shader_image_load_store
	/// Defines a barrier for memory transactions
	/**
	 *  example:
	 *  @code
	 *  Context gl;
	 *  gl.MemoryBarrier({MemoryBarrierBit::VertexAttribArray});
	 *  gl.MemoryBarrier({
	 *      MemoryBarrierBit::ElementArray,
	 *      MemoryBarrierBit::Uniform
	 *  });
	 *  gl.MemoryBarrier({
	 *      MemoryBarrierBit::TextureFetch,
	 *      MemoryBarrierBit::TextureUpdate
	 *  });
	 *  @endcode
	 *
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{MemoryBarrier}
	 */
	static void MemoryBarrier(std::initializer_list<MemoryBarrierBit> bits)
	{
		OGLPLUS_GLFUNC(MemoryBarrier)(aux::MakeBitfield(bits));
		AssertNoError(OGLPLUS_ERROR_INFO(MemoryBarrier));
	}
#endif

	/// Defines the scissor rectangle for the first viewport
	static void Scissor(
		GLint left,
		GLint bottom,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(Scissor)(left, bottom, width, height);
		AssertNoError(OGLPLUS_ERROR_INFO(Scissor));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_viewport_array
	/// Defines the scissor rectangle for the specified viewport
	static void ScissorIndexed(
		GLuint index,
		GLint left,
		GLint bottom,
		GLsizei width,
		GLsizei height
	)
	{
		OGLPLUS_GLFUNC(ScissorIndexed)(
			index,
			left,
			bottom,
			width,
			height
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ScissorIndexed));
	}

	/// Defines the scissor rectangle for the specified viewport
	static void ScissorIndexedv(GLuint index, GLint* v)
	{
		OGLPLUS_GLFUNC(ScissorIndexedv)(index, v);
		ThrowOnError(OGLPLUS_ERROR_INFO(ScissorIndexedv));
	}

	/// Defines the scissor rectangle for multiple viewports
	static void ScissorArrayv(GLuint first, GLsizei count, GLint* v)
	{
		OGLPLUS_GLFUNC(ScissorArrayv)(first, count, v);
		ThrowOnError(OGLPLUS_ERROR_INFO(ScissorArrayv));
	}
#endif
};

} // namespace oglplus

#endif // include guard
