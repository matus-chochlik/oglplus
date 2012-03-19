/**
 *  @file oglplus/context/buffer_selection.hpp
 *  @brief Wrappers for functions selecting the buffers for read/write operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_BUFFER_SELECTION_1201040722_HPP
#define OGLPLUS_CONTEXT_BUFFER_SELECTION_1201040722_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/color_buffer.hpp>

namespace oglplus {
namespace context {

/// Wrappers for functions selecting the buffers for read/write operations
/**
 *  @ingroup ogl_context
 */
class BufferSelection
{
public:
	/// Sets the destination color buffer for draw operations
	/**
	 *  @glsymbols
	 *  @glfunref{DrawBuffer}
	 */
	static void DrawBuffer(ColorBuffer buffer)
	{
		OGLPLUS_GLFUNC(DrawBuffer)(GLenum(buffer));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawBuffer));
	}

	/// Sets the source color buffer for read operations
	/**
	 *  @glsymbols
	 *  @glfunref{ReadBuffer}
	 */
	static void ReadBuffer(ColorBuffer buffer)
	{
		OGLPLUS_GLFUNC(ReadBuffer)(GLenum(buffer));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ReadBuffer));
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
