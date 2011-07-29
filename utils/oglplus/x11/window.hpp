/**
 *  @file oglplus/x11/window.hpp
 *  @brief Wrapper for X11 window class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef UTILS_OGLPLUS_X11_WINDOW_1107121519_HPP
#define UTILS_OGLPLUS_X11_WINDOW_1107121519_HPP

#include <oglplus/friendly_to.hpp>
#include <oglplus/x11/display.hpp>
#include <oglplus/x11/visual_info.hpp>
#include <oglplus/x11/color_map.hpp>

#include <X11/Xlib.h>
#include <stdexcept>

namespace oglplus {
namespace x11 {

class Window
 : public FriendlyTo<Display>
 , public FriendlyTo<VisualInfo>
 , public FriendlyTo<ColorMap>
{
private:
	const Display& _display;
	ColorMap _cmap;
	::Window _handle;

	static ::Window make_window(
		const Display& display,
		const VisualInfo& vi,
		const ColorMap& cmap,
		size_t width,
		size_t height
	)
	{
		::XSetWindowAttributes swa;
		swa.colormap = FriendlyTo<ColorMap>::GetHandle(cmap);
		swa.background_pixmap = None;
		swa.border_pixel = 0;
		swa.event_mask = StructureNotifyMask;
		//
		return ::XCreateWindow(
			FriendlyTo<Display>::GetHandle(display),
			RootWindow(
				FriendlyTo<Display>::GetHandle(display),
				FriendlyTo<VisualInfo>::GetHandle(vi)->screen
			),
			0, 0, width, height,
			0,
			FriendlyTo<VisualInfo>::GetHandle(vi)->depth,
			InputOutput,
			FriendlyTo<VisualInfo>::GetHandle(vi)->visual,
			CWBorderPixel | CWColormap | CWEventMask,
			&swa
		);
	}

	friend class FriendlyTo<Window>;
public:
	Window(
		const Display& display,
		const VisualInfo& vi,
		ColorMap&& cmap,
		const char* title,
		size_t width,
		size_t height
	): _display(display)
	 , _cmap(std::move(cmap))
	 , _handle(make_window(_display, vi, _cmap, width, height))
	{
		if(!_handle)
		{
			throw std::runtime_error(
				"Error creating X window"
			);
		}
		::XStoreName(
			FriendlyTo<Display>::GetHandle(_display),
			_handle,
			title
		);
		::XMapWindow(
			FriendlyTo<Display>::GetHandle(_display),
			_handle
		);
	}

	Window(const Window&) = delete;

	Window(Window&& temp)
	 : _display(temp._display)
	 , _cmap(std::move(temp._cmap))
	 , _handle(temp._handle)
	{
		temp._handle = 0;
	}

	~Window(void)
	{
		if(_handle)
		{
			::XDestroyWindow(
				FriendlyTo<Display>::GetHandle(_display),
				_handle
			);
		}
	}
};

} // namespace x11
} // namespace oglplus

#endif // include guard
