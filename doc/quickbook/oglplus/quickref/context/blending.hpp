/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_Blending
namespace oglplus {
namespace context {

class Blending
{
public:
#if GL_KHR_blend_equation_advanced
	static void BlendBarrier(void); /*<
	Specifies boundaries between blending passes.
	>*/
#endif

	static void BlendEquation(__OneOf<__BlendEquation, __BlendEquationAdvanced> eq); /*<
	Sets the blending equation.
	See [glfunc BlendEquation].
	>*/
	static void BlendEquationSeparate(
		__BlendEquation eq_rgb,
		__BlendEquation eq_alpha
	); /*<
	Sets the blend equation separately for RGB and alpha.
	See [glfunc BlendEquationSeparate].
	>*/

#if GL_VERSION_4_0
	static void BlendEquation(
		GLuint buffer,
		__OneOf<__BlendEquation, __BlendEquationAdvanced> eq
	); /*<
	Sets the blend equation for a particular draw [^buffer]
	See [glfunc BlendEquationi].
	>*/
	static void BlendEquationSeparate(
		GLuint buffer,
		__BlendEquation eq_rgb,
		__BlendEquation eq_alpha
	); /*<
	Sets the blend equation separate for RGB and alpha for the specified
	draw [^buffer].
	See [glfunc BlendEquationSeparatei].
	>*/
#endif

	static void BlendFunc(__BlendFunction src, __BlendFunction dst); /*<
	Sets the blend function. See [glfunc BlendFunc].
	>*/
	static void BlendFuncSeparate(
		__BlendFunction src_rgb,
		__BlendFunction dst_rgb,
		__BlendFunction src_alpha,
		__BlendFunction dst_alpha
	); /*<
	Sets the blend function separately for RGB and alpha.
	See [glfunc BlendFuncSeparate].
	>*/

#if GL_VERSION_4_0
	static void BlendFunc(
		GLuint buffer,
		__BlendFunction src,
		__BlendFunction dst
	); /*<
	Sets the blend function for a particular draw [^buffer].
	See [glfunc BlendFunci].
	>*/
	static void BlendFuncSeparate(
		GLuint buffer,
		__BlendFunction src_rgb,
		__BlendFunction dst_rgb,
		__BlendFunction src_alpha,
		__BlendFunction dst_alpha
	); /*<
	Sets the blend function separately for RGB and alpha for
	a particular draw [^buffer].
	See [glfunc BlendFuncSeparatei].
	>*/
#endif
};

} // namespace context
} // namespace oglplus
//]

