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

#include <vector>
#include <cassert>


//------------------------------------------------------------------------------
// eglplus_egl_glx_SurfaceImpl
//------------------------------------------------------------------------------
eglplus_egl_glx_SurfaceImpl::eglplus_egl_glx_SurfaceImpl( ::GLXDrawable drawable)
 : _glx_drawable(drawable)
 , _do_cleanup(nullptr)
{
}

eglplus_egl_glx_SurfaceImpl::eglplus_egl_glx_SurfaceImpl(
	::GLXDrawable drawable,
	void (*do_cleanup)( ::Display*, ::GLXDrawable)
): _glx_drawable(drawable)
 , _do_cleanup(do_cleanup)
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

	int glx_attrib_count = 0;

	if(*egl_attrib_list != EGL_NONE)
	{
		const EGLint* tmp_attrib_list = egl_attrib_list;
		while(*tmp_attrib_list != EGL_NONE)
		{
			bool bad_attrib = false;

			switch(*tmp_attrib_list++)
			{
				case EGL_WIDTH:
				case EGL_HEIGHT:
				{
					if(*tmp_attrib_list < 0)
						bad_attrib = true;
					break;
				}
				case EGL_LARGEST_PBUFFER:
				{
					switch(*tmp_attrib_list)
					{
						case EGL_TRUE:
						case EGL_FALSE:
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
				// TODO: this is not supported right now
				case EGL_TEXTURE_FORMAT:
				case EGL_TEXTURE_TARGET:
				case EGL_MIPMAP_TEXTURE:
				default: bad_attrib = true;
			}

			if(bad_attrib)
			{
				eglplus_egl_ErrorCode = EGL_BAD_ATTRIBUTE;
				return EGL_NO_SURFACE;
			}
			++tmp_attrib_list;
			glx_attrib_count += 2;
		}
	}

	std::vector<int> glx_attrib_list(glx_attrib_count+1);
	glx_attrib_count = 0;

	if(*egl_attrib_list != EGL_NONE)
	{
		const EGLint* tmp_attrib_list = egl_attrib_list;
		while(*tmp_attrib_list != EGL_NONE)
		{
			switch(*tmp_attrib_list++)
			{
				case EGL_WIDTH:
				{
					glx_attrib_list[glx_attrib_count++] =
						GLX_PBUFFER_WIDTH;
					glx_attrib_list[glx_attrib_count++] =
						int(*tmp_attrib_list++);
					break;
				}
				case EGL_HEIGHT:
				{
					glx_attrib_list[glx_attrib_count++] =
						GLX_PBUFFER_HEIGHT;
					glx_attrib_list[glx_attrib_count++] =
						int(*tmp_attrib_list++);
					break;
				}
				case EGL_LARGEST_PBUFFER:
				{
					glx_attrib_list[glx_attrib_count++] =
						GLX_LARGEST_PBUFFER;
					glx_attrib_list[glx_attrib_count++] =
						(*tmp_attrib_list++ == EGL_TRUE)?
						True:
						False;
					break;
				}
				default:;
			}
		}
	}
	glx_attrib_list[glx_attrib_count] = None;

	int glx_attrib_value = 0;

	int glx_result = ::glXGetFBConfigAttrib(
		display->_x_open_display,
		static_cast< ::GLXFBConfig>(config._glx_fb_config),
		GLX_DRAWABLE_TYPE,
		&glx_attrib_value
	);

	if((glx_attrib_value & GLX_PBUFFER_BIT) != GLX_PBUFFER_BIT)
	{
		eglplus_egl_ErrorCode = EGL_BAD_MATCH;
		return EGL_NO_SURFACE;
	}

	::GLXPbuffer pbuffer = ::glXCreatePbuffer(
		display->_x_open_display,
		static_cast< ::GLXFBConfig>(config._glx_fb_config),
		glx_attrib_list.data()
	);

	try
	{
		return new eglplus_egl_glx_SurfaceImpl(
			pbuffer,
			& ::glXDestroyPbuffer
		);
	}
	catch(...)
	{
		eglplus_egl_ErrorCode = EGL_BAD_ALLOC;
		return EGL_NO_SURFACE;
	}
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
// eglSurfaceAttrib
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglSurfaceAttrib(
	EGLDisplay display,
	EGLSurface surface,
	EGLint egl_attribute,
	EGLint egl_attrib_value
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}

	if(surface == EGL_NO_SURFACE)
	{
		eglplus_egl_ErrorCode = EGL_BAD_SURFACE;
		return EGL_FALSE;
	}

	//TODO
	return EGL_FALSE;
}
//------------------------------------------------------------------------------
// eglQuerySurface
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglQuerySurface(
	EGLDisplay display,
	EGLSurface surface,
	EGLint egl_attribute,
	EGLint *egl_attrib_value
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}

	if(surface == EGL_NO_SURFACE)
	{
		eglplus_egl_ErrorCode = EGL_BAD_SURFACE;
		return EGL_FALSE;
	}

	if(!egl_attrib_value)
	{
		return EGL_TRUE;
	}

	int glx_attribute;

	bool bad_attrib = false;

	switch(egl_attribute)
	{
		case EGL_RENDER_BUFFER:
		{
			// TODO
			*egl_attrib_value = EGL_BACK_BUFFER;
			return EGL_TRUE;
		}
		case EGL_SWAP_BEHAVIOR:
		{
			// TODO
			*egl_attrib_value = EGL_BUFFER_DESTROYED;
			return EGL_TRUE;
		}
		case EGL_MULTISAMPLE_RESOLVE:
		{
			*egl_attrib_value = EGL_MULTISAMPLE_RESOLVE_DEFAULT;
			return EGL_TRUE;
		}
		case EGL_TEXTURE_TARGET:
		case EGL_TEXTURE_FORMAT:
		{
			// TODO
			*egl_attrib_value = EGL_NO_TEXTURE;
			return EGL_TRUE;
		}
		case EGL_MIPMAP_TEXTURE:
		{
			// TODO
			*egl_attrib_value = EGL_FALSE;
			return EGL_TRUE;
		}
		case EGL_VG_COLORSPACE:
		{
			*egl_attrib_value = EGL_VG_COLORSPACE_sRGB;
			return EGL_TRUE;

		}
		case EGL_VG_ALPHA_FORMAT:
		{
			*egl_attrib_value = EGL_VG_ALPHA_FORMAT_NONPRE;
			return EGL_TRUE;
		}
		case EGL_MIPMAP_LEVEL:
		case EGL_HORIZONTAL_RESOLUTION:
		case EGL_VERTICAL_RESOLUTION:
		case EGL_PIXEL_ASPECT_RATIO:
		{
			// TODO
			*egl_attrib_value = EGL_UNKNOWN;
			return EGL_TRUE;
		}
		case EGL_CONFIG_ID:
			glx_attribute = GLX_FBCONFIG_ID;
			break;
		case EGL_WIDTH:
			glx_attribute = GLX_WIDTH;
			break;
		case EGL_HEIGHT:
			glx_attribute = GLX_HEIGHT;
			break;
		case EGL_LARGEST_PBUFFER:
			glx_attribute = GLX_LARGEST_PBUFFER;
			break;
		// TODO
		default: bad_attrib = true;
	}

	if(bad_attrib)
	{
		eglplus_egl_ErrorCode = EGL_BAD_ATTRIBUTE;
		return EGL_FALSE;
	}

	unsigned glx_attrib_value = 0;

	::glXQueryDrawable(
		display->_x_open_display,
		surface->_glx_drawable,
		glx_attribute,
		&glx_attrib_value
	);

	switch(egl_attribute)
	{
		case EGL_LARGEST_PBUFFER:
		{
			if(glx_attrib_value == True)
				*egl_attrib_value = EGL_TRUE;
			else	*egl_attrib_value = EGL_FALSE;
			break;
		}
		default: *egl_attrib_value = EGLint(glx_attrib_value);
	}
	return EGL_TRUE;
}
//------------------------------------------------------------------------------
// eglBindTexImage
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglBindTexImage(
	EGLDisplay display,
	EGLSurface surface,
	EGLint buffer
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_FALSE;
	}

	if(surface == EGL_NO_SURFACE)
	{
		eglplus_egl_ErrorCode = EGL_BAD_SURFACE;
		return EGL_FALSE;
	}

	if(buffer != EGL_BACK_BUFFER)
	{
		eglplus_egl_ErrorCode = EGL_BAD_PARAMETER;
		return EGL_FALSE;
	}

	// Not supported
	eglplus_egl_ErrorCode = EGL_BAD_SURFACE;
	return EGL_FALSE;
}
//------------------------------------------------------------------------------
// eglReleaseTexImage
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglReleaseTexImage(
	EGLDisplay display,
	EGLSurface surface,
	EGLint buffer
)
{
	// Not supported
	return eglBindTexImage(display, surface, buffer);
}
//------------------------------------------------------------------------------
} // extern "C"
