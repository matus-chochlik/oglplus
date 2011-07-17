/**
 *  @file oglplus/x11/visual_info.hpp
 *  @brief Wrapper for X11 visual info class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_X11_VISUAL_INFO_1107121519_HPP
#define UTILS_OGLPLUS_X11_VISUAL_INFO_1107121519_HPP

#include <oglplus/friendly_to.hpp>
#include <oglplus/x11/display.hpp>
#include <oglplus/glx/fb_config.hpp>

#include <X11/Xlib.h>
#include <stdexcept>

namespace oglplus {
namespace x11 {

class VisualInfo
 : public FriendlyTo<x11::Display>
 , public FriendlyTo<glx::FBConfig>
{
private:
	::XVisualInfo* _handle;

	friend class FriendlyTo<VisualInfo>;
public:
	VisualInfo(const Display& display, const glx::FBConfig& fbc)
	 : _handle(
		::glXGetVisualFromFBConfig(
			FriendlyTo<Display>::GetHandle(display),
			FriendlyTo<glx::FBConfig>::GetHandle(fbc)
		)
	)
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error Getting X VisualInfo from GLX FB config"
			);
		}
	}

	VisualInfo(const VisualInfo&) = delete;
	VisualInfo(VisualInfo&& temp)
	 : _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~VisualInfo(void)
	{
		if(_handle) ::XFree(_handle);
	}
};

} // namespace x11
} // namespace oglplus

#endif // include guard
