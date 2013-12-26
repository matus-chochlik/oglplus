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
eglplus_egl_glx_SurfaceImpl::eglplus_egl_glx_SurfaceImpl( ::GLXDrawable drawable)
 : _glx_drawable(drawable)
 , _do_cleanup(nullptr)
{
}

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
	EGLNativeWindowType native_window,
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

	::Window window = static_cast< ::Window>(native_window);

	// TODO: config?
	// TODO: attributes (at least EGL_RENDER_BUFFER)?

	return new eglplus_egl_glx_SurfaceImpl(window);
}
//------------------------------------------------------------------------------
// eglCreatePbufferSurface
//------------------------------------------------------------------------------
EGLAPI EGLSurface EGLAPIENTRY
eglCreatePbufferSurface(
	EGLDisplay display,
	EGLConfig config,
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

	// TODO
	return nullptr;
}
//------------------------------------------------------------------------------
// eglCreatePbufferFromClientBuffer
//------------------------------------------------------------------------------
EGLAPI EGLSurface EGLAPIENTRY
eglCreatePbufferFromClientBuffer(
	EGLDisplay display,
	EGLenum buftype,
	EGLClientBuffer buffer,
	EGLConfig config,
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

	// TODO
	return nullptr;
}
//------------------------------------------------------------------------------
// eglCreatePixmapSurface
//------------------------------------------------------------------------------
EGLAPI EGLSurface EGLAPIENTRY
eglCreatePixmapSurface(
	EGLDisplay display,
	EGLConfig config,
	EGLNativePixmapType native_pixmap,
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

	::Pixmap pixmap = static_cast< ::Pixmap>(native_pixmap);

	// TODO: config?
	// TODO: attributes (at least EGL_RENDER_BUFFER)?

	return new eglplus_egl_glx_SurfaceImpl(pixmap);
}
//------------------------------------------------------------------------------
} // extern "C"
