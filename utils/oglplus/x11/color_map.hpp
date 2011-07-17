/**
 *  @file oglplus/x11/color_map.hpp
 *  @brief Wrapper for X11 colormap class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_X11_COLOR_MAP_1107121519_HPP
#define UTILS_OGLPLUS_X11_COLOR_MAP_1107121519_HPP

#include <oglplus/friendly_to.hpp>
#include <oglplus/x11/display.hpp>
#include <oglplus/x11/visual_info.hpp>

#include <X11/Xlib.h>
#include <stdexcept>

namespace oglplus {
namespace x11 {

class ColorMap
 : public FriendlyTo<Display>
 , public FriendlyTo<VisualInfo>
{
private:
	const Display& _display;
	::Colormap _handle;

	friend class FriendlyTo<ColorMap>;
public:
	ColorMap(const Display& display, const VisualInfo& vi)
	 : _display(display)
	 , _handle(
		::XCreateColormap(
			FriendlyTo<Display>::GetHandle(_display),
			RootWindow(
				FriendlyTo<Display>::GetHandle(_display),
				FriendlyTo<VisualInfo>::GetHandle(vi)->screen
			),
			FriendlyTo<VisualInfo>::GetHandle(vi)->visual,
			AllocNone
		)
	)
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error creating X colormap"
			);
		}
	}

	ColorMap(const ColorMap&) = delete;

	ColorMap(ColorMap&& temp)
	 : _display(temp._display)
	 , _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~ColorMap(void)
	{
		if(_handle)
		{
			::XFreeColormap(
				FriendlyTo<Display>::GetHandle(_display),
				_handle
			);
		}
	}
};

} // namespace x11
} // namespace oglplus

#endif // include guard
