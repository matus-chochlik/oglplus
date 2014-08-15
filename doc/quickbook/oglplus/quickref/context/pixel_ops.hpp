/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_PixelOps
namespace oglplus {
namespace context {

class PixelOps
{
public:
	static void PixelStore(__PixelStorageMode parameter, GLfloat value); /*<
	Sets the [^value] of a pixel storage [^parameter].
	See [glfunc PixelStore].
	>*/
	static void PixelStore(__PixelStorageMode parameter, GLint value);

	static void ReadPixels(
		GLint x,
		GLint y,
		GLsizei width,
		GLsizei height,
		__PixelDataFormat format,
		__PixelDataType type,
		void* data
	); /*<
	Reads a block of pixels from the current framebuffer.
	See [glfunc ReadPixels].
	>*/

	static void BlitFramebuffer(
		GLint srcX0,
		GLint srcY0,
		GLint srcX1,
		GLint srcY1,
		GLint dstX0,
		GLint dstY0,
		GLint dstX1,
		GLint dstY1,
		__Bitfield<__BufferSelectBit> mask,
		__BlitFilter filter
	); /*<
	Transfers a rectangle of pixels from the read buffer the draw buffer.
	See [glfunc blitFramebuffer].
	>*/
};

} // namespace context
} // namespace oglplus
//]

