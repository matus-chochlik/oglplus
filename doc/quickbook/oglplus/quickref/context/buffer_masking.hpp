/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_BufferMasking_helpers
namespace oglplus {
namespace context {


struct RGBAMask /*<
Helper structure storing the color component mask.
>*/
{
	bool Red(void) const;
	bool Green(void) const;
	bool Blue(void) const;
	bool Alpha(void) const;
};
//]

//[oglplus_context_BufferMasking
class BufferMasking
{
public:
	static void ColorMask(bool r, bool g, bool b, bool a); /*<
	Sets the color mask for the default color buffer.
	See [glfunc ColorMask].
	>*/
	static void ColorMask(GLuint buffer, bool r, bool g, bool b, bool a); /*<
	Sets the color mask for the specified color [^buffer].
	See [glfunc ColorMaski].
	>*/

	static void DepthMask(bool mask); /*<
	Sets the depth buffer [^mask].
	See [glfunc DepthMask].
	>*/

	static void StencilMask(GLuint mask); /*<
	Sets the stencil buffer [^mask];
	See [glfunc StencilMask].
	>*/
	static void StencilMaskSeparate(__Face face, GLuint mask); /*<
	Sets the stencil mask separately for front and back faces.
	See [glfunc StencilMaskSeparate].
	>*/

	static RGBAMask ColorWriteMask(GLuint buffer = 0); /*<
	Returns the value of color buffer write mask.
	See [glfunc Get], [glconst COLOR_WRITEMASK].
	>*/
	static bool DepthWriteMask(void); /*<
	Returns the value of depth buffer write mask.
	See [glfunc Get], [glconst DEPTH_WRITEMASK].
	>*/
	static GLuint StencilWriteMask(bool backface = false); /*<
	Returns the value of stencil buffer write mask.
	See [glfunc Get], [glconst STENCIL_WRITEMASK] and
	[glconst STENCIL_BACK_WRITEMASK].
	>*/
	static GLuint StencilWriteMask(__Face face);
};

} // namespace context
} // namespace oglplus
//]

