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
		return EGL_NO_SURFACE;
	}

	if(!config._glx_fb_config)
	{
		eglplus_egl_ErrorCode = EGL_BAD_CONFIG;
		return EGL_NO_SURFACE;
	}

	EGLint empty_list = EGL_NONE;
	if(!egl_attrib_list)
	{
		egl_attrib_list = &empty_list;
	}

	if(*egl_attrib_list != EGL_NONE)
	{
		const EGLint* tmp_attrib_list = egl_attrib_list;
		while(*tmp_attrib_list != EGL_NONE)
		{
			bool bad_attrib = false;

			switch(*tmp_attrib_list++)
			{
				case EGL_RENDER_BUFFER:
				{
					switch(*tmp_attrib_list)
					{
						case EGL_SINGLE_BUFFER:
						case EGL_BACK_BUFFER:
							break;
						default: bad_attrib = true;
					}
					break;
				}
				case EGL_VG_COLORSPACE:
				{
					switch(*tmp_attrib_list)
					{
						case EGL_VG_COLORSPACE_sRGB:
						case EGL_VG_COLORSPACE_LINEAR:
							break;
						default: bad_attrib = true;
					}
					break;
				}
				case EGL_VG_ALPHA_FORMAT:
				{
					switch(*tmp_attrib_list)
					{
						case EGL_VG_ALPHA_FORMAT_PRE:
						case EGL_VG_ALPHA_FORMAT_NONPRE:
							break;
						default: bad_attrib = true;
					}
					break;
				}

				default: bad_attrib = true;
			}

			if(bad_attrib)
			{
				eglplus_egl_ErrorCode = EGL_BAD_ATTRIBUTE;
				return EGL_NO_SURFACE;
			}
			++tmp_attrib_list;
		}
	}

	int glx_attrib_value = 0;

	int glx_result = ::glXGetFBConfigAttrib(
		display->_x_open_display,
		static_cast< ::GLXFBConfig>(config._glx_fb_config),
		GLX_DRAWABLE_TYPE,
		&glx_attrib_value
	);

	if((glx_attrib_value & GLX_WINDOW_BIT) != GLX_WINDOW_BIT)
	{
		eglplus_egl_ErrorCode = EGL_BAD_MATCH;
		return EGL_NO_SURFACE;
	}

	::Window window = static_cast< ::Window>(native_window);

	::XWindowAttributes win_attr;

	switch(::XGetWindowAttributes(
		display->_x_open_display,
		window,
		&win_attr
	))
	{
		case BadDrawable:
		case BadWindow:
		{
			eglplus_egl_ErrorCode = EGL_BAD_NATIVE_WINDOW;
			return EGL_NO_SURFACE;
		}
		default:;
	}

	// TODO: config matches window

	try { return new eglplus_egl_glx_SurfaceImpl(window); }
	catch(...)
	{
		eglplus_egl_ErrorCode = EGL_BAD_ALLOC;
		return EGL_NO_SURFACE;
	}
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
		return EGL_NO_SURFACE;
	}

	EGLint empty_list = EGL_NONE;
	if(!egl_attrib_list)
	{
		egl_attrib_list = &empty_list;
	}

	// TODO
	return EGL_NO_SURFACE;
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
		return EGL_NO_SURFACE;
	}

	EGLint empty_list = EGL_NONE;
	if(!egl_attrib_list)
	{
		egl_attrib_list = &empty_list;
	}

	// TODO
	eglplus_egl_ErrorCode = EGL_BAD_MATCH;
	return EGL_NO_SURFACE;
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
		return EGL_NO_SURFACE;
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
