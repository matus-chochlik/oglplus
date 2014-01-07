/**
 *  .file EGL/glx/display.cpp
 *  .brief EGL Display implementation
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <EGL/egl.h>

#include "display.hpp"
#include "../error.hpp"

#include <map>
#include <memory>
#include <cassert>
#include <iostream>


//------------------------------------------------------------------------------
// X error handler
//------------------------------------------------------------------------------
static int (*eglplus_egl_X_old_error_handler)(::Display*, ::XErrorEvent*) = 0;

int eglplus_egl_X_error_handler(::Display* display, ::XErrorEvent* error_event)
{
	switch(error_event->error_code)
	{
		case BadAccess:
		{
			eglplus_egl_ErrorCode = EGL_BAD_ACCESS;
			break;
		}
		case BadAlloc:
		{
			eglplus_egl_ErrorCode = EGL_BAD_ALLOC;
			break;
		}
		case BadDrawable:
		{
			eglplus_egl_ErrorCode = EGL_BAD_SURFACE;
			break;
		}
		case BadMatch:
		{
			eglplus_egl_ErrorCode = EGL_BAD_MATCH;
			break;
		}
		case BadPixmap:
		{
			eglplus_egl_ErrorCode = EGL_BAD_NATIVE_PIXMAP;
			break;
		}
		case BadWindow:
		{
			eglplus_egl_ErrorCode = EGL_BAD_NATIVE_WINDOW;
			break;
		}
		default:
		{
			if(eglplus_egl_X_old_error_handler)
			{
				return eglplus_egl_X_old_error_handler(
					display,
					error_event
				);
			}
		}
	}

	char message[128] = {'\0'};

	::XGetErrorText(
		display,
		error_event->error_code,
		message,
		sizeof(message)
	);

	std::cerr
		<< "Error "
		<< error_event->error_code
		<< " ("
		<< message
		<< "): request "
		<< error_event->request_code
		<< "."
		<< error_event->minor_code
		<< std::endl;

	return 0;
}
//------------------------------------------------------------------------------
// eglplus_egl_glx_DisplayImpl
//------------------------------------------------------------------------------
// the number of initialized displays
static int eglplus_egl_init_display_count = 0;

eglplus_egl_glx_DisplayImpl::eglplus_egl_glx_DisplayImpl(EGLNativeDisplayType id)
 : _x_display_id(static_cast< ::Display*>(id))
 , _x_open_display(static_cast < ::Display*>(nullptr))
{ }

bool eglplus_egl_glx_DisplayImpl::_init(void)
{
	// if already open
	if(_x_open_display != nullptr) return false;

	// try open
	if(_x_display_id != EGL_DEFAULT_DISPLAY)
	{
		_x_open_display = _x_display_id;
	}
	else
	{
		_x_open_display = ::XOpenDisplay(nullptr);
	}

	// check if open
	if(_x_open_display == nullptr) return false;

	// install error handler
	if(eglplus_egl_init_display_count++ == 0)
	{
		eglplus_egl_X_old_error_handler =
			::XSetErrorHandler(eglplus_egl_X_error_handler);
	}
	// TODO: support for multithreading

	// everything should be ok
	return true;
}

bool eglplus_egl_glx_DisplayImpl::_cleanup(void)
{
	// if not open
	if(_x_open_display == nullptr) return false;

	// if the number of initialized displays is zero
	if(eglplus_egl_init_display_count == 0) return false;
	assert(eglplus_egl_init_display_count > 0);

	// restore error handler
	if(--eglplus_egl_init_display_count == 0)
	{
		::XSetErrorHandler(eglplus_egl_X_old_error_handler);
	}

	// try close
	if(_x_display_id != EGL_DEFAULT_DISPLAY)
	{
		_x_open_display = nullptr;
	}
	else
	{
		::XCloseDisplay(_x_open_display);
		_x_open_display = nullptr;
	}

	// check if open
	if(_x_open_display != nullptr) return false;

	// everything should be ok
	return true;
}
//------------------------------------------------------------------------------
// Displays
//------------------------------------------------------------------------------
// display id to display namespace map type
typedef std::map<
	EGLNativeDisplayType,
	std::unique_ptr<eglplus_egl_glx_DisplayImpl>
> eglplus_egl_display_map;

// the map of accessed displays
static eglplus_egl_display_map eglplus_egl_displays;

// checks if the passed handle is a valid display
bool eglplus_egl_valid_display(EGLDisplay display)
{
	auto i = eglplus_egl_displays.begin();
	auto e = eglplus_egl_displays.end();
	while(i != e)
	{
		if(i->second.get() == display)
			return true;
		++i;
	}
	return false;
}

// checks if the passed handle is an open display
bool eglplus_egl_is_open_display(EGLDisplay display)
{
	if(!eglplus_egl_valid_display(display))
		return false;
	return display->_x_open_display != nullptr;
}

//------------------------------------------------------------------------------
// EGL API
//------------------------------------------------------------------------------
extern "C" {
//------------------------------------------------------------------------------
// eglGetDisplay
//------------------------------------------------------------------------------
EGLAPI EGLDisplay EGLAPIENTRY
eglGetDisplay(EGLNativeDisplayType display_id)
{
	auto p = eglplus_egl_displays.find(display_id);
	if(p == eglplus_egl_displays.end())
	{
		p = eglplus_egl_displays.insert(
			eglplus_egl_display_map::value_type(
				display_id,
				std::unique_ptr<eglplus_egl_glx_DisplayImpl>(
					new eglplus_egl_glx_DisplayImpl(
						display_id
					)
				)
			)
		).first;
	}
	assert(p != eglplus_egl_displays.end());

	return p->second.get();
}

//------------------------------------------------------------------------------
// eglInitialize
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglInitialize(EGLDisplay display, EGLint *major, EGLint *minor)
{
	if(display == nullptr)
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}
	if(!eglplus_egl_valid_display(display))
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}

	if(!display->_init())
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}

	if(major) *major = 1;
	if(minor) *minor = 4;
	return EGL_TRUE;
}
//------------------------------------------------------------------------------
// eglTerminate
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglTerminate(EGLDisplay display)
{
	if(display == nullptr)
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}
	if(!eglplus_egl_valid_display(display))
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}
	if(!eglplus_egl_is_open_display(display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}
	if(!display->_cleanup())
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}
	return EGL_TRUE;
}
//------------------------------------------------------------------------------
EGLAPI const char * EGLAPIENTRY
eglQueryString(EGLDisplay display, EGLint name)
{
	// Query of client extensions
	if((display == EGL_NO_DISPLAY) && (name == EGL_EXTENSIONS))
	{
		return	"EGL_KHR_client_get_all_proc_addresses "
			"EGL_EXT_client_extensions";
	}

	if(!eglplus_egl_is_open_display(display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return nullptr;
	}
	else if(name == EGL_VENDOR)
	{
		return "OGLplus/EGLplus";
	}
	else if(name == EGL_VERSION)
	{
		return "1.4 X11/glX";
	}
	else if(name == EGL_CLIENT_APIS)
	{
		return "OpenGL";
	}
	else if(name == EGL_EXTENSIONS)
	{
		return	"EGL_KHR_get_all_proc_addresses "
			"EGL_KHR_create_context";
	}
	eglplus_egl_ErrorCode = EGL_BAD_PARAMETER;
	return nullptr;
}
//------------------------------------------------------------------------------
} // extern "C"
