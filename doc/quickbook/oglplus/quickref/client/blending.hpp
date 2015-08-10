/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_client_BlendingOps
namespace client {

using oglplus::__context_BlendingOps;

} // namespace client
//]
//[oglplus_client_BlendingState
namespace client {

class BlendingState
{
	// TODO
	__SettingStack<__context_RGBAValue, ...> BlendColor; /*<
	Stack managing the setting of blend color.
	>*/
};

} // namespace client
//]

