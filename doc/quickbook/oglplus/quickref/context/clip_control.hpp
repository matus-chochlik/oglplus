/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_ClipControlState
namespace oglplus {
namespace context {

class ClipControlState
{
public:
#if GL_VERSION_4_5 || GL_ARB_clip_control
	static void ClipControl(__ClipOrigin origin, __ClipDepthMode depth); /*<
	Sets the clipping mode.
	See [glfunc ClipControl].
	>*/

	static __ClipOrigin ClipOrigin(void); /*<
	Queries the current clip origin setting.
	See [glfunc Get], [glconst CLIP_ORIGIN].
	>*/

	static __ClipDepthMode ClipDepthMode(void); /*<
	Queries the current clip depth mode setting.
	See [glfunc Get], [glconst CLIP_DEPTH_MODE].
	>*/
#endif

};

} // namespace context
} // namespace oglplus
//]

