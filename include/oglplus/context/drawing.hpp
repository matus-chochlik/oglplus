/**
 *  @file oglplus/context/drawing.hpp
 *  @brief Wrappers for drawing operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_DRAWING_1201040722_HPP
#define OGLPLUS_CONTEXT_DRAWING_1201040722_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/primitive_type.hpp>
#include <oglplus/patch_parameter.hpp>
#include <oglplus/data_type.hpp>
#include <oglplus/transform_feedback.hpp>

namespace oglplus {
namespace context {

/// Wrapper for primitive drawing operations
/**
 *  @ingroup ogl_context
 */
class Drawing
 : public FriendOf<TransformFeedbackOps>
{
public:
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawArrays));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2
	/// Draws @a count of primitives from the bound array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{4,2}
	 *  @glsymbols
	 *  @glfunref{DrawArraysInstancedBaseInstance}
	 */
	static void DrawArraysInstancedBaseInstance(
		PrimitiveType primitive,
		GLint first,
		GLsizei count,
		GLsizei inst_count,
		GLsizei base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawArraysInstancedBaseInstance)(
			GLenum(primitive),
			first,
			count,
			inst_count,
			base_instance
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(DrawArraysInstancedBaseInstance)
		);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Draws @a count of primitives from the bound array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{3,1}
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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawArraysInstanced));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_draw_indirect
	/// Draws primitives from an indirect buffer
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,draw_indirect}
	 *  @glsymbols
	 *  @glfunref{DrawArraysIndirect}
	 */
	static void DrawArraysIndirect(
		PrimitiveType primitive,
		const void* indirect = nullptr
	)
	{
		OGLPLUS_GLFUNC(DrawArraysIndirect)(
			GLenum(primitive),
			indirect
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawArraysIndirect));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Draws @a primcount ranges of primitives from the bound array buffers
	/**
	 *  @throws Error
	 *
	 *  @see DrawArrays
	 *
	 *  @glsymbols
	 *  @glfunref{MultiDrawArrays}
	 */
	static void MultiDrawArrays(
		PrimitiveType primitive,
		const GLint* first,
		const GLsizei* count,
		GLsizei primcount
	)
	{
		OGLPLUS_GLFUNC(MultiDrawArrays)(
			GLenum(primitive),
			const_cast<GLint*>(first), //TODO: cast because of GLEW
			const_cast<GLsizei*>(count), // remove when GLEW fixed
			primcount
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawArrays));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3 || GL_ARB_multi_draw_indirect
	/// Draws multiple sets of primitives from an indirect buffer
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,3,ARB,multi_draw_indirect}
	 *  @glsymbols
	 *  @glfunref{MultiDrawArraysIndirect}
	 */
	static void MultiDrawArraysIndirect(
		PrimitiveType primitive,
		GLsizei draw_count,
		GLsizei stride = 0,
		const void* indirect = nullptr
	)
	{
		OGLPLUS_GLFUNC(MultiDrawArraysIndirect)(
			GLenum(primitive),
			indirect,
			draw_count,
			stride
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawArraysIndirect));
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
			nullptr
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawElements}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		const T* indices
	)
	{
		OGLPLUS_GLFUNC(DrawElements)(
			GLenum(primitive),
			count,
			GLenum(GetDataType<T>()),
			indices
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstanced}
	 */
	static void DrawElementsInstanced(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		GLsizei instance_count
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstanced)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			nullptr,
			instance_count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElementsInstanced));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstanced}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawElementsInstanced(
		PrimitiveType primitive,
		GLsizei count,
		const T* indices,
		GLsizei instance_count
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstanced)(
			GLenum(primitive),
			count,
			GLenum(GetDataType<T>()),
			indices,
			instance_count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElementsInstanced));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2
	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{4,2}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseInstance}
	 */
	static void DrawElementsInstancedBaseInstance(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		GLsizei inst_count,
		GLuint base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseInstance)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			nullptr,
			inst_count,
			base_instance
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(DrawElementsInstancedBaseInstance)
		);
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{4,2}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseInstance}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawElementsInstancedBaseInstance(
		PrimitiveType primitive,
		GLsizei count,
		const T* indices,
		GLsizei inst_count,
		GLuint base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseInstance)(
			GLenum(primitive),
			count,
			GLenum(GetDataType<T>()),
			indices,
			inst_count,
			base_instance
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(DrawElementsInstancedBaseInstance)
		);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{MultiDrawElements}
	 */
	static void MultiDrawElements(
		PrimitiveType primitive,
		const GLsizei* count,
		DataType data_type,
		GLsizei draw_count
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElements)(
			GLenum(primitive),
			const_cast<GLsizei*>(count), //TODO: cast because of GLEW
			GLenum(data_type),
			nullptr,
			draw_count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{MultiDrawElements}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	MultiDrawElements(
		PrimitiveType primitive,
		const GLsizei* count,
		T* const * indices,
		GLsizei draw_count
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElements)(
			GLenum(primitive),
			const_cast<GLsizei*>(count), //TODO: cast because of GLEW
			GLenum(GetDataType<T>()),
			indices,
			draw_count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawElements));
	}
#endif

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawRangeElements}
	 */
	static void DrawRangeElements(
		PrimitiveType primitive,
		GLuint start,
		GLuint end,
		GLsizei count,
		DataType data_type
	)
	{
		OGLPLUS_GLFUNC(DrawRangeElements)(
			GLenum(primitive),
			start,
			end,
			count,
			GLenum(data_type),
			nullptr
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawRangeElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawRangeElements}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawRangeElements(
		PrimitiveType primitive,
		GLuint start,
		GLuint end,
		GLsizei count,
		const T* indices
	)
	{
		OGLPLUS_GLFUNC(DrawRangeElements)(
			GLenum(primitive),
			start,
			end,
			count,
			GLenum(GetDataType<T>()),
			indices
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawRangeElements));
	}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_draw_indirect
	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{4,0,ARB,GL_ARB_draw_indirect}
	 *  @glsymbols
	 *  @glfunref{DrawElementsIndirect}
	 */
	static void DrawElementsIndirect(
		PrimitiveType primitive,
		DataType data_type,
		const void* indirect = nullptr
	)
	{
		OGLPLUS_GLFUNC(DrawElementsIndirect)(
			GLenum(primitive),
			GLenum(data_type),
			indirect
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElementsIndirect));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3
	/// Draws sequences of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{4,3}
	 *  @glsymbols
	 *  @glfunref{MultiDrawElementsIndirect}
	 */
	static void MultiDrawElementsIndirect(
		PrimitiveType primitive,
		DataType data_type,
		GLsizei draw_count,
		GLsizei stride = 0,
		const void* indirect = nullptr
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElementsIndirect)(
			GLenum(primitive),
			GLenum(data_type),
			indirect,
			draw_count,
			stride
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawElementsIndirect));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_draw_elements_base_vertex
	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawElementsBaseVertex}
	 */
	static void DrawElementsBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawElementsBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			nullptr,
			base_vertex
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElementsBaseVertex));
	}
	/// Draws a sequence of primitives from the bound element array buffers

	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawElementsBaseVertex}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawElementsBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		const T* indices,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawElementsBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(GetDataType<T>()),
			indices,
			base_vertex
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElementsBaseVertex));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawRangeElementsBaseVertex}
	 */
	static void DrawRangeElementsBaseVertex(
		PrimitiveType primitive,
		GLuint start,
		GLuint end,
		GLsizei count,
		DataType data_type,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawRangeElementsBaseVertex)(
			GLenum(primitive),
			start,
			end,
			count,
			GLenum(data_type),
			nullptr,
			base_vertex
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawRangeElementsBaseVertex));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawRangeElementsBaseVertex}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawRangeElementsBaseVertex(
		PrimitiveType primitive,
		GLuint start,
		GLuint end,
		GLsizei count,
		const T* indices,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawRangeElementsBaseVertex)(
			GLenum(primitive),
			start,
			end,
			count,
			GLenum(GetDataType<T>()),
			indices,
			base_vertex
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawRangeElementsBaseVertex));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseVertex}
	 */
	static void DrawElementsInstancedBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		GLsizei inst_count,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			nullptr,
			inst_count,
			base_vertex
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(DrawElementsInstancedBaseVertex)
		);
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseVertex}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawElementsInstancedBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		const T* indices,
		GLsizei inst_count,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(GetDataType<T>()),
			indices,
			inst_count,
			base_vertex
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(DrawElementsInstancedBaseVertex)
		);
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{MultiDrawElementsBaseVertex}
	 */
	static void MultiDrawElementsBaseVertex(
		PrimitiveType primitive,
		const GLsizei* count,
		DataType data_type,
		GLsizei draw_count,
		const GLint* base_vertex
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElementsBaseVertex)(
			GLenum(primitive),
			const_cast<GLsizei*>(count), //TODO remove const_cast
			GLenum(data_type),
			nullptr,
			draw_count,
			const_cast<GLint*>(base_vertex) //TODO remove const_cast
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawElementsBaseVertex));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB,draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{MultiDrawElementsBaseVertex}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	MultiDrawElementsBaseVertex(
		PrimitiveType primitive,
		const GLsizei* count,
		T* const * indices,
		GLsizei draw_count,
		const GLint* base_vertex
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElementsBaseVertex)(
			GLenum(primitive),
			const_cast<GLsizei*>(count), //TODO remove const_cast
			GLenum(GetDataType<T>()),
			indices,
			draw_count,
			const_cast<GLint*>(base_vertex) //TODO remove const_cast
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawElementsBaseVertex));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_2
	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{4,2}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseVertexBaseInstance}
	 */
	static void DrawElementsInstancedBaseVertexBaseInstance(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		GLsizei inst_count,
		GLint base_vertex,
		GLuint base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseVertexBaseInstance)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			nullptr,
			inst_count,
			base_vertex,
			base_instance
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(
				DrawElementsInstancedBaseVertexBaseInstance
			)
		);
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glverreq{4,2}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseVertexBaseInstance}
	 */
	template <typename T>
	static typename std::enable_if<IsGLDataType<T>::value, void>::type
	DrawElementsInstancedBaseVertexBaseInstance(
		PrimitiveType primitive,
		GLsizei count,
		const T* indices,
		GLsizei inst_count,
		GLint base_vertex,
		GLuint base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseVertexBaseInstance)(
			GLenum(primitive),
			count,
			GLenum(GetDataType<T>()),
			indices,
			inst_count,
			base_vertex,
			base_instance
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(
				DrawElementsInstancedBaseVertexBaseInstance
			)
		);
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback2
	static void DrawTransformFeedback(
		PrimitiveType primitive,
		const TransformFeedbackOps& xfb
	)
	{
		OGLPLUS_GLFUNC(DrawTransformFeedback)(
			GLenum(primitive),
			FriendOf<TransformFeedbackOps>::GetName(xfb)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawTransformFeedback));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Sets the primitive restart index
	/**
	 *  @throws Error
	 *
	 *  @glverreq{3,1}
	 *  @glsymbols
	 *  @glfunref{PrimitiveRestartIndex}
	 */
	static void PrimitiveRestartIndex(GLuint index)
	{
		OGLPLUS_GLFUNC(PrimitiveRestartIndex)(index);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PrimitiveRestartIndex));
	}
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_tessellation_shader || GL_VERSION_4_0
	static void PatchParameter(
		oglplus::PatchParameter parameter,
		GLint value
	)
	{
		OGLPLUS_GLFUNC(PatchParameteri)(GLenum(parameter), value);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(PatchParameteri));
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
