/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_client_BufferMaskingState
namespace client {

class BufferMaskingState
{
	__SettingStack<__context_RGBAMask, ...> ColorMask; /*<
	Stack managing the setting of color channel mask.
	>*/

	__SettingStack<__Boolean, ...> DepthMask; /*<
	Stack managing the setting of depth mask.
	>*/

	__EnumToClass<
		__Nothing,
		__SingleFace,
		__SettingStack<__Boolean, ...> // TODO
	> StencilMask; /*<
	Stacks managing the setting of stencil mask separatelly for the front
	and the back face.
	>*/
};

} // namespace client
//]

