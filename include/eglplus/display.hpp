/**
 *  @file eglplus/display.hpp
 *  @brief Declares and implements wrapper for EGLDisplay
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_DISPLAY_1305291005_HPP
#define EGLPLUS_DISPLAY_1305291005_HPP

#include <eglplus/eglfunc.hpp>
#include <eglplus/error/basic.hpp>

namespace eglplus {

class EGLInitializer;

class Display;
::EGLDisplay GetEGLHandle(const Display&);

/// Wrapper around EGLDisplay
class Display
{
private:
	::EGLDisplay _handle;

	friend ::EGLDisplay GetEGLHandle(const Display&);
public:
	/// Opens the default display
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetDisplay}
	 *  @egldefref{DEFAULT_DISPLAY}
	 */
	Display(void)
	 : _handle(EGLPLUS_EGLFUNC(GetDisplay)(EGL_DEFAULT_DISPLAY))
	{
		EGLPLUS_CHECK_SIMPLE(GetDisplay);
	}

	/// Opens the display specified by @p display_id
	/**
	 *  @eglsymbols
	 *  @eglfunref{GetDisplay}
	 */
	Display(::EGLNativeDisplayType display_id)
	 : _handle(EGLPLUS_EGLFUNC(GetDisplay)(display_id))
	{
		EGLPLUS_CHECK_SIMPLE(GetDisplay);
	}

	/// Sets the SwapInterval for the current display
	/**
	 *  @eglsymbols
	 *  @eglfunref{SwapInterval}
	 */
	bool SwapInterval(EGLint interval)
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(SwapInterval)(
			_handle,
			interval
		);
		EGLPLUS_CHECK_SIMPLE(SwapInterval);
		return result == EGL_TRUE;
	}

	/// Releases the current context without assigning a new one
	/**
	 *  @eglsymbols
	 *  @eglfunref{MakeCurrent}
	 */
	bool ReleaseContext(void)
	{
		EGLBoolean result = EGLPLUS_EGLFUNC(MakeCurrent)(
			_handle,
			EGL_NO_SURFACE,
			EGL_NO_SURFACE,
			EGL_NO_CONTEXT
		);
		EGLPLUS_CHECK_SIMPLE(MakeCurrent);
		return result == EGL_TRUE;
	}
};

inline ::EGLDisplay GetEGLHandle(const Display& display)
{
	return display._handle;
}

} // namespace eglplus

#endif // include guard
