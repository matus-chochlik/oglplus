/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_BufferClearing_helpers
namespace oglplus {

typedef __BufferSelectBit ClearBit;

namespace context {

struct RGBAValue /*<
Helper structure storing the clear color components.
>*/
{
	GLfloat Red(void) const;
	GLfloat Green(void) const;
	GLfloat Blue(void) const;
	GLfloat Alpha(void) const;
};

class ClrBits /*<
Helper class used by [^__context_BufferClearing::Clear()].
Instances of this class cause the write buffers to be cleared
depending on which member functions were called during the life-time
of the instance.
The actual call to [glfunc Clear] is done in the destructor.
>*/
{
public:
	ClrBits ColorBuffer(void); /*<
	Calling this member function causes the color buffer to be marked
	for clearing.
	See [glconst COLOR_BUFFER_BIT].
	>*/
	ClrBits DepthBuffer(void); /*<
	Calling this member function causes the depth buffer to be marked
	for clearing.
	See [glconst DEPTH_BUFFER_BIT].
	>*/
	ClrBits StencilBuffer(void); /*<
	Calling this member function causes the stencil buffer to be marked
	for clearing.
	See [glconst STENCIL_BUFFER_BIT].
	>*/

	~ClrBits(void); /*<
	The destructor does the actual clearing of the buffers.
	See [glfunc Clear].
	>*/
};
//]

//[oglplus_context_BufferClearing
class BufferClearing
{
public:
	static void ClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a); /*<
	Sets the clear color components.
	See [glfunc ClearColor].
	>*/
	static void ClearDepth(GLclampd d); /*<
	Sets the clear depth value.
	See [glfunc ClearDepth].
	>*/
	static void ClearStencil(GLint s); /*<
	Sets the clear stencil buffer value.
	See [glfunc ClearStencil].
	>*/

	static RGBAValue ColorClearValue(void); /*<
	Returns the value used for clearing of the color buffer.
	See [glfunc Gen], [glconst COLOR_CLEAR_VALUE].
	>*/
	static GLfloat DepthClearValue(void); /*<
	Returns the value used for clearing of the depth buffer.
	See [glfunc Gen], [glconst DEPTH_CLEAR_VALUE].
	>*/
	static GLint ClearStencilValue(void);  /*<
	Returns the value used for clearing of the depth buffer.
	See [glfunc Gen], [glconst STENCIL_CLEAR_VALUE].
	>*/

	static void Clear(__Bitfield<__ClearBit> bits); /*<
	Clears buffers specified by the bits parameter.
	>*/
	static ClrBits Clear(void); /*<
	Clears buffers specified by calling functions of the returned object
	This function returns an object that allows to specify which buffers
	to clear by calling its [^ColorBuffer], [^DepthBuffer] and [^StencilBuffer]
	member functions.
	>*/

	static void ClearColorBuffer(GLint draw_buffer, const GLint* value); /*<
	Clears the color draw buffer of the currently bound framebuffer with
	the specified [^value].
	See [glfunc ClearBuffer], [glconst GL_COLOR].
	>*/
	static void ClearColorBuffer(GLint draw_buffer, const GLuint* value);
	static void ClearColorBuffer(GLint draw_buffer, const GLfloat* value);

	static void ClearColorBuffer(__ColorBuffer buffer, GLint draw_buffer, const GLint* value); /*<
	Clears the specified color draw buffer of the currently bound framebuffer
	with the specified [^value].
	>*/
	static void ClearColorBuffer(__ColorBuffer buffer, GLint draw_buffer, const GLuint* value);
	static void ClearColorBuffer(__ColorBuffer buffer, GLint draw_buffer, const GLfloat* value);

	static void ClearDepthBuffer(GLfloat value); /*<
	Clears the depth buffer of the currently bound framebuffer
	with the specified [^value].
	See [glfunc ClearBuffer], [glconst GL_DEPTH].
	>*/
	static void ClearStencilBuffer(GLint value); /*<
	Clears the stencil buffer of the currently bound framebuffer
	with the specified [^value].
	See [glfunc ClearBuffer], [glconst GL_STENCIL].
	>*/
	static void ClearStencilBuffer(GLfloat depth_value, GLint stencil_value); /*<
	Clears the depth and the stencil buffer of the currently bound framebuffer
	with the specified values.
	See [glfunc ClearBuffer], [glconst GL_DEPTH_STENCIL].
	>*/
};

} // namespace context
} // namespace oglplus
//]

