/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_DepthTest
namespace oglplus {
namespace context {

class DepthTest
{
public:
	static void DepthFunc(__CompareFunction function); /*<
	Sets the depth comparison [^function].
	See [glfunc DepthFunc].
	>*/
	static __CompareFunction DepthFunc(void); /*<
	Returns the currently set depth comparison function.
	See [glfunc Get], [glconst DEPTH_FUNC].
	>*/
};

} // namespace context
} // namespace oglplus
//]

