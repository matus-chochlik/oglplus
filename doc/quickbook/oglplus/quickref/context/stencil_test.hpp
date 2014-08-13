/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_StencilTest
namespace oglplus {
namespace context {

class StencilTest
{
public:
	static void StencilFunc(
		__CompareFunction function,
		GLint ref = GLint(0),
		GLuint mask = ~GLuint(0)
	); /*<
	Sets the stencil [^function], [^ref]erence value and a [^mask].
	See [glfunc StencilFunc].
	>*/
	static void StencilFuncSeparate(
		__Face face,
		__CompareFunction function,
		GLint ref = GLint(0),
		GLuint mask = ~GLuint(0)
	); /*<
	Sets the stencil [^function] separately for front and back [^face].
	See [glfunc StencilFuncSeparate].
	>*/

	static void StencilOp(
		__StencilOperation sfail,
		__StencilOperation dfail,
		__StencilOperation dpass
	); /*<
	Sets the stencil operations.
	See [glfunc StencilOp].
	>*/

	static void StencilOpSeparate(
		__Face face,
		__StencilOperation sfail,
		__StencilOperation dfail,
		__StencilOperation dpass
	); /*<
	Sets the stencil operations separately for front and back [^face].
	See [glfunc StencilOpSeparate].
	>*/

	static __CompareFunction StencilFunc(bool backface = false); /*<
	Returns the currently set stencil function.
	See [glfunc Get], [glconst STENCIL_FUNC], [glconst STENCIL_BACK_FUNC].
	>*/
	static CompareFunction StencilFunc(__Face face);

	static GLuint StencilValueMask(bool backface = false); /*<
	Returns the currently set value of stencil mask.
	See [glfunc Get], [glconst STENCIL_VALUE_MASK], [glconst STENCIL_BACK_VALUE_MASK].
	>*/
	static GLuint StencilValueMask(__Face face);

	static GLuint StencilRef(bool backface = false); /*<
	Returns the currently set stencil reference value.
	See [glfunc Get], [glconst STENCIL_REF], [glconst STENCIL_BACK_REF].
	>*/
	static GLuint StencilRef(__Face face);

	static __StencilOperation StencilFail(bool backface = false); /*<
	Returns the stencil-fail action.
	See [glfunc Get], [glconst STENCIL_FAIL], [glconst STENCIL_BACK_FAIL].
	>*/
	static StencilOperation StencilFail(__Face face);

	static __StencilOperation StencilPassDepthFail(bool backface = false); /*<
	Returns the stencil-pass depth-fail action.
	See [glfunc Get], [glconst STENCIL_PASS_DEPTH_FAIL], [glconst STENCIL_BACK_PASS_DEPTH_FAIL].
	>*/
	static StencilOperation StencilPassDepthFail(__Face face);

	static __StencilOperation StencilPassDepthPass(bool backface = false); /*<
	Returns the stencil-pass depth-fail action.
	See [glfunc Get], [glconst STENCIL_PASS_DEPTH_PASS], [glconst STENCIL_BACK_PASS_DEPTH_PASS].
	>*/
	static StencilOperation StencilPassDepthPass(__Face face)
};

} // namespace context
} // namespace oglplus
//]

