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

#include <oglplus/config.hpp>
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
	/// Enable capability
	static void Enable(Capability cap)
	{
		::glEnable(GLenum(cap));
		AssertNoError(OGLPLUS_ERROR_INFO(Enable));
	}

	/// Disable capability
	static void Disable(Capability cap)
	{
		::glDisable(GLenum(cap));
		AssertNoError(OGLPLUS_ERROR_INFO(Disable));
	}

	/// Check if capability is enabled
	static bool IsEnabled(Capability cap)
	{
		GLboolean result = ::glIsEnabled(GLenum(cap));
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabled));
		return result == GL_TRUE;
	}

	/// Enable capability for indexed target
	static void Enable(Capability cap, GLuint index)
	{
		::glEnablei(GLenum(cap), index);
		AssertNoError(OGLPLUS_ERROR_INFO(Enablei));
	}

	/// Disable capability for indexed target
	static void Disable(Capability cap, GLuint index)
	{
		::glDisablei(GLenum(cap), index);
		AssertNoError(OGLPLUS_ERROR_INFO(Disablei));
	}

	/// Check if capability is enabled for indexed target
	static bool IsEnabled(Capability cap, GLuint index)
	{
		GLboolean result = ::glIsEnabledi(GLenum(cap), index);
		AssertNoError(OGLPLUS_ERROR_INFO(IsEnabledi));
		return result == GL_TRUE;
	}

	/// Sets the clear color
	/**
	 *  @throws Error
	 */
	static void ClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		::glClearColor(r, g, b, a);
		ThrowOnError(OGLPLUS_ERROR_INFO(ClearColor));
	}

	/// Sets the clear depth
	/**
	 *  @throws Error
	 */
	static void ClearDepth(GLclampd d)
	{
		::glClearDepth(d);
		ThrowOnError(OGLPLUS_ERROR_INFO(ClearDepth));
	}

	/// Sets the clear stencil buffer value
	/**
	 *  @throws Error
	 */
	static void ClearStencil(GLint s)
	{
		::glClearStencil(s);
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
		AssertNoError(OGLPLUS_ERROR_INFO(Clear));
	}

	/// Sets the stencil function
	static void StencilFunc(
		CompareFunction func,
		GLint ref = GLint(0),
		GLuint mask = ~GLuint(0)
	)
	{
		::glStencilFunc(GLenum(func), ref, mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilFunc));
	}

	/// Sets the stencil function separately for front and back faces
	static void StencilFuncSeparate(
		Face face,
		CompareFunction func,
		GLint ref = GLint(0),
		GLuint mask = ~GLuint(0)
	)
	{
		::glStencilFuncSeparate(GLenum(face), GLenum(func), ref, mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilFuncSeparate));
	}

	/// Sets the stencil operation
	static void StencilOp(
		StencilOperation sfail,
		StencilOperation dfail,
		StencilOperation dpass
	)
	{
		::glStencilOp(GLenum(sfail), GLenum(dfail), GLenum(dpass));
		AssertNoError(OGLPLUS_ERROR_INFO(StencilOp));
	}

	/// Sets the stencil operation separately for front and back faces
	static void StencilOpSeparate(
		Face face,
		StencilOperation sfail,
		StencilOperation dfail,
		StencilOperation dpass
	)
	{
		::glStencilOpSeparate(
			GLenum(face),
			GLenum(sfail),
			GLenum(dfail),
			GLenum(dpass)
		);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilOpSeparate));
	}

	/// Sets the depth comparison function
	static void DepthFunc(CompareFunction func)
	{
		::glDepthFunc(GLenum(func));
		AssertNoError(OGLPLUS_ERROR_INFO(DepthFunc));
	}

	/// Sets the blend equation
	static void BlendEquation(oglplus::BlendEquation eq)
	{
		::glBlendEquation(GLenum(eq));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquation));
	}

	/// Sets the blend equation separate for RGB and alpha
	static void BlendEquationSeparate(
		oglplus::BlendEquation eq_rgb,
		oglplus::BlendEquation eq_alpha
	)
	{
		::glBlendEquationSeparate(GLenum(eq_rgb), GLenum(eq_alpha));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquationSeparate));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend equation for a particular draw @p buffer
	static void BlendEquation(GLuint buffer, oglplus::BlendEquation eq)
	{
		::glBlendEquationi(buffer, GLenum(eq));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquationi));
	}

	/// Sets the blend equation separate for RGB and alpha for a @p buffer
	static void BlendEquationSeparate(
		GLuint buffer,
		oglplus::BlendEquation eq_rgb,
		oglplus::BlendEquation eq_alpha
	)
	{
		::glBlendEquationSeparatei(
			buffer,
			GLenum(eq_rgb),
			GLenum(eq_alpha)
		);
		AssertNoError(OGLPLUS_ERROR_INFO(BlendEquationSeparatei));
	}
#endif

	/// Sets the blend function
	static void BlendFunc(BlendFunction src, BlendFunction dst)
	{
		::glBlendFunc(GLenum(src), GLenum(dst));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFunc));
	}

	/// Sets the blend function separate for RGB and alpha
	static void BlendFuncSeparate(
		BlendFunction src_rgb,
		BlendFunction dst_rgb,
		BlendFunction src_alpha,
		BlendFunction dst_alpha
	)
	{
		::glBlendFuncSeparate(
			GLenum(src_rgb),
			GLenum(dst_rgb),
			GLenum(src_alpha),
			GLenum(dst_alpha)
		);
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFuncSeparate));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0
	/// Sets the blend function for a particular @p buffer
	static void BlendFunci(
		GLuint buffer,
		BlendFunction src,
		BlendFunction dst
	)
	{
		::glBlendFunci(buffer, GLenum(src), GLenum(dst));
		AssertNoError(OGLPLUS_ERROR_INFO(BlendFunci));
	}

	/// Sets the blend function separate for RGB and alpha for a @p buffer
	static void BlendFuncSeparatei(
		GLuint buffer,
		BlendFunction src_rgb,
		BlendFunction dst_rgb,
		BlendFunction src_alpha,
		BlendFunction dst_alpha
	)
	{
		::glBlendFuncSeparatei(
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
	static void BlendColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		::glBlendColor(r, g, b, a);
		AssertNoError(OGLPLUS_ERROR_INFO(BlendColor));
	}

	/// Sets the color logical operation
	static void LogicOp(ColorLogicOperation op)
	{
		::glLogicOp(GLenum(op));
		AssertNoError(OGLPLUS_ERROR_INFO(LogicOp));
	}

	/// Sets the polygon facing mode
	static void FrontFace(FaceOrientation orientation)
	{
		::glFrontFace(GLenum(orientation));
		AssertNoError(OGLPLUS_ERROR_INFO(FrontFace));
	}

	/// Sets the face culling mode
	static void CullFace(Face mode)
	{
		::glCullFace(GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(CullFace));
	}

	/// Sets the color mask
	static void ColorMask(bool r, bool g, bool b, bool a)
	{
		::glColorMask(
			r ? GL_TRUE : GL_FALSE,
			g ? GL_TRUE : GL_FALSE,
			b ? GL_TRUE : GL_FALSE,
			a ? GL_TRUE : GL_FALSE
		);
		AssertNoError(OGLPLUS_ERROR_INFO(ColorMask));
	}

	/// Sets the color mask for a particular @p buffer
	static void ColorMask(GLuint buffer, bool r, bool g, bool b, bool a)
	{
		::glColorMaski(
			buffer,
			r ? GL_TRUE : GL_FALSE,
			g ? GL_TRUE : GL_FALSE,
			b ? GL_TRUE : GL_FALSE,
			a ? GL_TRUE : GL_FALSE
		);
		AssertNoError(OGLPLUS_ERROR_INFO(ColorMaski));
	}

	/// Sets the depth @p mask
	static void DepthMask(bool mask)
	{
		::glDepthMask(mask ? GL_TRUE : GL_FALSE);
		AssertNoError(OGLPLUS_ERROR_INFO(DepthMask));
	}

	/// Sets the stencil @p mask
	static void StencilMask(GLuint mask)
	{
		::glStencilMask(mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilMask));
	}

	/// Sets the stencil mask separately for front and back faces
	static void StencilMaskSeparate(Face face, GLuint mask)
	{
		::glStencilMaskSeparate(GLenum(face), mask);
		AssertNoError(OGLPLUS_ERROR_INFO(StencilMaskSeparate));
	}

	/// Sets the polygon rasterization mode
	static void PolygonMode(Face face, oglplus::PolygonMode mode)
	{
		::glPolygonMode(GLenum(face), GLenum(mode));
		AssertNoError(OGLPLUS_ERROR_INFO(PolygonMode));
	}

	/// Sets the polygon depth offset
	static void PolygonOffset(GLfloat factor, GLfloat units)
	{
		::glPolygonOffset(factor, units);
		AssertNoError(OGLPLUS_ERROR_INFO(PolygonOffset));
	}

	/// Sets the line width
	static void LineWidth(GLfloat width)
	{
		::glLineWidth(width);
		AssertNoError(OGLPLUS_ERROR_INFO(LineWidth));
	}

	/// Sets the point size
	static void PointSize(GLfloat size)
	{
		::glPointSize(size);
		AssertNoError(OGLPLUS_ERROR_INFO(PointSize));
	}

	/// Sets the destination color buffer for draw operations
	static void DrawBuffer(ColorBuffer buffer)
	{
		::glDrawBuffer(GLenum(buffer));
		AssertNoError(OGLPLUS_ERROR_INFO(DrawBuffer));
	}

	/// Sets the source color buffer for read operations
	static void ReadBuffer(ColorBuffer buffer)
	{
		::glReadBuffer(GLenum(buffer));
		AssertNoError(OGLPLUS_ERROR_INFO(ReadBuffer));
	}

	/// Sets the current viewport
	/**
	 *  @throws Error
	 */
	static void Viewport(GLint x, GLint y, GLsizei w, GLsizei h)
	{
		::glViewport(x, y, w, h);
		ThrowOnError(OGLPLUS_ERROR_INFO(Viewport));
	}

	/// Sets the current viewport starting at (0,0)
	/**
	 *  @throws Error
	 */
	static void Viewport(GLsizei w, GLsizei h)
	{
		::glViewport(0, 0, w, h);
		ThrowOnError(OGLPLUS_ERROR_INFO(Viewport));
	}


	/// Draws @a count of primitives from the bound array buffers
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
		AssertNoError(OGLPLUS_ERROR_INFO(DrawArrays));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Draws @a count of primitives from the bound array buffers
	/**
	 *  @throws Error
	 */
	static void DrawArraysInstanced(
		PrimitiveType primitive,
		GLint first,
		GLsizei count,
		GLsizei inst_count
	)
	{
		::glDrawArraysInstanced(
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
	 */
	static void DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type
	)
	{
		::glDrawElements(GLenum(primitive), count, GLenum(data_type),0);
		AssertNoError(OGLPLUS_ERROR_INFO(DrawElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 */
	template <typename T>
	static void DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* p
	)
	{
		::glDrawElements(GLenum(primitive), count, GLenum(data_type),p);
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
	 *      MemoryBarrierBit::UniformArray
	 *  });
	 *  gl.MemoryBarrier({
	 *      MemoryBarrierBit::TextureFetch,
	 *      MemoryBarrierBit::TextureUpdate
	 *  });
	 *  @endcode
	 *
	 *  @throws Error
	 */
	static void MemoryBarrier(
		const std::initializer_list<MemoryBarrierBit>& bits
	)
	{
		::glMemoryBarrier(aux::MakeBitfield(bits));
		AssertNoError(OGLPLUS_ERROR_INFO(MemoryBarrier));
	}
#endif
};

} // namespace oglplus

#endif // include guard
