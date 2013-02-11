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

#include <oglplus/x11/display.hpp>
#include <oglplus/glx/fb_config.hpp>

#include <X11/Xlib.h>
#include <stdexcept>

namespace oglplus {
namespace x11 {

class VisualInfo
 : public Object< ::XVisualInfo, int(void*)>
{
public:
	VisualInfo(const Display& display, const glx::FBConfig& fbc)
	 : Object< ::XVisualInfo, int(void*)>(
		::glXGetVisualFromFBConfig(display, fbc),
		::XFree,
		"Error Getting X VisualInfo from GLX FB config"
	){ }
};

} // namespace x11
} // namespace oglplus

#endif // include guard
