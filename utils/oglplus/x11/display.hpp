/**
 *  @file oglplus/x11/display.hpp
 *  @brief Wrapper for X11/Display class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_X11_DISPLAY_1107121519_HPP
#define UTILS_OGLPLUS_X11_DISPLAY_1107121519_HPP

#include <oglplus/friendly_to.hpp>

#include <X11/Xlib.h>
#include <stdexcept>

namespace oglplus {
namespace x11 {

class Display
{
private:
	::Display* _handle;

	friend class FriendlyTo<Display>;
public:
	Display(const char* name = 0)
	 : _handle(::XOpenDisplay(name))
	{
		if(!_handle)
			throw std::runtime_error("Failed to open X display");
	}

	Display(const Display&) = delete;
	Display(Display&& temp)
	 : _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~Display(void)
	{
		if(_handle) ::XCloseDisplay(_handle);
	}
};

} // namespace x11
} // namespace oglplus

#endif // include guard
