/**
 *  @file oglplus/context/drawing.hpp
 *  @brief Wrappers for drawing operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_DRAWING_1201040722_HPP
#define OGLPLUS_CONTEXT_DRAWING_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/primitive_type.hpp>
#include <oglplus/data_type.hpp>

namespace oglplus {
namespace context {

/// Wrapper for primitive drawing operations
/**
 *  @ingroup ogl_context
 */
class Drawing
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
		GLsizei prim_count,
		GLsizei base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawArraysInstancedBaseInstance)(
			GLenum(primitive),
			first,
			count,
			prim_count,
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
	static void DrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* indices
	)
	{
		OGLPLUS_GLFUNC(DrawElements)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElements));
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
	template <typename T>
	static void DrawElementsInstancedBaseInstance(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* indices,
		GLsizei prim_count,
		GLuint base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseInstance)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices,
			prim_count,
			base_instance
		);
		OGLPLUS_VERIFY(
			OGLPLUS_ERROR_INFO(DrawElementsInstancedBaseInstance)
		);
	}
#endif

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{MultiDrawElements}
	 */
	template <typename T>
	static void MultiDrawElements(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T** indices,
		GLsizei prim_count
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElements)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices,
			prim_count
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(MultiDrawElements));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glsymbols
	 *  @glfunref{DrawRangeElements}
	 */
	template <typename T>
	static void DrawRangeElements(
		PrimitiveType primitive,
		GLuint start,
		GLuint end,
		GLsizei count,
		DataType data_type,
		T* indices
	)
	{
		OGLPLUS_GLFUNC(DrawRangeElements)(
			GLenum(primitive),
			start,
			end,
			count,
			GLenum(data_type),
			indices
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawRangeElements));
	}


#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_2 || GL_ARB_draw_elements_base_vertex
	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB_draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawElementsBaseVertex}
	 */
	template <typename T>
	static void DrawElementsBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* indices,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawElementsBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices,
			base_vertex
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawElementsBaseVertex));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB_draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawRangeElementsBaseVertex}
	 */
	template <typename T>
	static void DrawRangeElementsBaseVertex(
		PrimitiveType primitive,
		GLuint start,
		GLuint end,
		GLsizei count,
		DataType data_type,
		T* indices,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawRangeElementsBaseVertex)(
			GLenum(primitive),
			start,
			end,
			count,
			GLenum(data_type),
			indices,
			base_vertex
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawRangeElementsBaseVertex));
	}

	/// Draws a sequence of primitives from the bound element array buffers
	/**
	 *  @throws Error
	 *
	 *  @glvoereq{3,2,ARB_draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{DrawElementsInstancedBaseVertex}
	 */
	template <typename T>
	static void DrawElementsInstancedBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* indices,
		GLsizei prim_count,
		GLint base_vertex
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices,
			prim_count,
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
	 *  @glvoereq{3,2,ARB_draw_elements_base_vertex}
	 *  @glsymbols
	 *  @glfunref{MultiDrawElementsBaseVertex}
	 */
	template <typename T>
	static void MultiDrawElementsBaseVertex(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T** indices,
		GLsizei prim_count,
		const int* base_vertex
	)
	{
		OGLPLUS_GLFUNC(MultiDrawElementsBaseVertex)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices,
			prim_count,
			base_vertex
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
	template <typename T>
	static void DrawElementsInstancedBaseVertexBaseInstance(
		PrimitiveType primitive,
		GLsizei count,
		DataType data_type,
		T* indices,
		GLsizei prim_count,
		GLint base_vertex,
		GLuint base_instance
	)
	{
		OGLPLUS_GLFUNC(DrawElementsInstancedBaseVertexBaseInstance)(
			GLenum(primitive),
			count,
			GLenum(data_type),
			indices,
			prim_count,
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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1
	/// Sets the primitive restart index
	/**
	 *  @throws Error
	 *
	 *  @glverreq{3,1}
	 *  @glsymbols
	 *  @glfunref{PrimitiveRestartIndex}
	 */
	void PrimitiveRestartIndex(GLuint index)
	{
		OGLPLUS_GLFUNC(PrimitiveRestartIndex)(index);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(PrimitiveRestartIndex));
	}
#endif
};

} // namespace context
} // namespace oglplus

#endif // include guard
