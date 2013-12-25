/**
 *  .file EGL/glx/surface.cpp
 *  .brief EGL Surface implementation
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <EGL/egl.h>

#include "surface.hpp"
#include "display.hpp"
#include "../error.hpp"

#include <cassert>


//------------------------------------------------------------------------------
// eglplus_egl_glx_SurfaceImpl
//------------------------------------------------------------------------------
eglplus_egl_glx_SurfaceImpl::eglplus_egl_glx_SurfaceImpl( ::Window window)
 : _glx_drawable( ::GLXDrawable(window))
 , _do_cleanup(nullptr)
{
}

/*
eglplus_egl_glx_SurfaceImpl::eglplus_egl_glx_SurfaceImpl(
	::Display* display,
	::Pixmap pixmap
): _glx_drawable( ::GLXDrawable( ::XCreatePixmap()))
 , _deleter( ::XFreePixmap)
{
}
*/

eglplus_egl_glx_SurfaceImpl::~eglplus_egl_glx_SurfaceImpl(void)
{
	assert(!_glx_drawable);
}

void eglplus_egl_glx_SurfaceImpl::_cleanup( ::Display* display)
{
	if(_do_cleanup) _do_cleanup(display, _glx_drawable);
	_glx_drawable = 0;
}
//------------------------------------------------------------------------------
// EGL API
//------------------------------------------------------------------------------
extern "C" {
//------------------------------------------------------------------------------
// eglDestroySurface
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglDestroySurface(
	EGLDisplay display,
	EGLSurface surface
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}
	if(!surface)
	{
		eglplus_egl_ErrorCode = EGL_BAD_SURFACE;
		return EGL_FALSE;
	}
	surface->_cleanup(display->_x_open_display);
	delete surface;
}
//------------------------------------------------------------------------------
// eglCreateWindowSurface
//------------------------------------------------------------------------------
EGLAPI EGLSurface EGLAPIENTRY
eglCreateWindowSurface(
	EGLDisplay display,
	EGLConfig config,
	EGLNativeWindowType native_win,
	const EGLint *egl_attrib_list
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}

	EGLint empty_list = EGL_NONE;
	if(!egl_attrib_list)
	{
		egl_attrib_list = &empty_list;
	}

	::Window win = static_cast< ::Window>(native_win);

	// TODO
	return nullptr;
}
//------------------------------------------------------------------------------
// eglCreatePixmapSurface
//------------------------------------------------------------------------------
EGLAPI EGLSurface EGLAPIENTRY
eglCreatePixmapSurface(
	EGLDisplay dpy,
	EGLConfig config,
	EGLNativePixmapType pixmap,
	const EGLint *attrib_list
)
{
	// TODO
	return nullptr;
}
//------------------------------------------------------------------------------
} // extern "C"
