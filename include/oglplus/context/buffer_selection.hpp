/** *  @file oglplus/context/buffer_selection.hpp
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
#include <oglplus/framebuffer.hpp>
#include <oglplus/one_of.hpp>

namespace oglplus {
namespace context {

/// Wrappers for functions selecting the buffers for read/write operations
/**
 *  @ingroup ogl_context
 */
class BufferSelection
{
public:
	/// Color buffer specification type
	typedef OneOf<
		GLenum,
		oglplus::ColorBuffer,
		oglplus::FramebufferColorAttachment
	> ColorBuffer;

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

	/// Sets the destination color buffers for draw operations
	/**
	 *  @glsymbols
	 *  @glfunref{DrawBuffers}
	 */
	template <size_t N>
	static void DrawBuffers(ColorBuffer (&buffers)[N])
	{
		// TODO: if the alignment, etc. is right we could
		// do without the temporary copy
		GLenum _tmp[N];
		for(size_t i=0; i!=N; ++i)
			_tmp[i] = GLenum(buffers[i]);
		OGLPLUS_GLFUNC(DrawBuffers)(N, _tmp);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(DrawBuffers));
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
