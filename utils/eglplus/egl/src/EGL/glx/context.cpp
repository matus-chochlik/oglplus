/**
 *  .file EGL/glx/context.cpp
 *  .brief EGL rendering context implementation
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <EGL/egl.h>

#include "context.hpp"
#include "surface.hpp"
#include "display.hpp"
#include "../error.hpp"
#include "../api.hpp"

#include <vector>
#include <cassert>

//------------------------------------------------------------------------------
// eglplus_egl_glx_ContextImpl
//------------------------------------------------------------------------------
eglplus_egl_glx_ContextImpl::eglplus_egl_glx_ContextImpl( ::GLXContext context)
 : _glx_context(context)
{
}

eglplus_egl_glx_ContextImpl::~eglplus_egl_glx_ContextImpl(void)
{
	assert(!_glx_context);
}

void eglplus_egl_glx_ContextImpl::_cleanup( ::Display* display)
{
	::glXDestroyContext(display, _glx_context);
	_glx_context = 0;
}
//------------------------------------------------------------------------------
// glXCreateContextAttribsARB
//------------------------------------------------------------------------------
typedef ::GLXContext (*glXCreateContextAttribsARBProc)(
	::Display*,
	::GLXFBConfig,
	::GLXContext,
	Bool,
	const int*
);
glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
//------------------------------------------------------------------------------
// EGL API
//------------------------------------------------------------------------------
extern "C" {
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
EGLAPI EGLContext EGLAPIENTRY
eglCreateContext(
	EGLDisplay display,
	EGLConfig config,
	EGLContext egl_share_context,
	const EGLint *egl_attrib_list
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_NOT_INITIALIZED;
		return EGL_NO_CONTEXT;
	}

	if(!config._glx_fb_config)
	{
		eglplus_egl_ErrorCode = EGL_BAD_CONFIG;
		return EGL_NO_CONTEXT;
	}

	if(eglplus_egl_CurrentAPI != EGL_OPENGL_API)
	{
		eglplus_egl_ErrorCode = EGL_BAD_MATCH;
		return EGL_NO_CONTEXT;
	}

	if(!glXCreateContextAttribsARB)
	{
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
		glXGetProcAddressARB((const unsigned char*)"glXCreateContextAttribsARB");
	}

	if(!glXCreateContextAttribsARB)
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_NO_CONTEXT;
	}

	::GLXContext glx_share_context = ::GLXContext(0);
	if(egl_share_context)
	{
		glx_share_context = egl_share_context->_glx_context;
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
				case 0x3098: //EGL_CONTEXT_MAJOR_VERSION_KHR
				case 0x30FB: //EGL_CONTEXT_MINOR_VERSION_KHR
					break;
				case 0x30FC: //EGL_CONTEXT_FLAGS_KHR
				{
					if((*tmp_attrib_list & ~0x07) != 0)
					{
						bad_attrib = true;
					}
					break;
				}
				case 0x30FD: //EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR
				{
					if((*tmp_attrib_list & ~0x03) != 0)
					{
						bad_attrib = true;
					}
					break;
				}
				default: bad_attrib = true;
			}

			if(bad_attrib)
			{
				eglplus_egl_ErrorCode = EGL_BAD_ATTRIBUTE;
				return EGL_NO_CONTEXT;
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
				case 0x3098: //EGL_CONTEXT_MAJOR_VERSION_KHR
				{
					glx_attrib_list[glx_attrib_count++] =
						//GLX_CONTEXT_MAJOR_VERSION_ARB
						0x2091;
					glx_attrib_list[glx_attrib_count++] =
						int(*tmp_attrib_list++);
					break;
				}
				case 0x30FB: //EGL_CONTEXT_MINOR_VERSION_KHR
				{
					glx_attrib_list[glx_attrib_count++] =
						//GLX_CONTEXT_MINOR_VERSION_ARB
						0x2092;
					glx_attrib_list[glx_attrib_count++] =
						int(*tmp_attrib_list++);
					break;
				}
				case 0x30FC: //EGL_CONTEXT_FLAGS_KHR
				{
					glx_attrib_list[glx_attrib_count++] =
						//GLX_CONTEXT_FLAGS_ARB
						0x2094;
					EGLint egl_flags = *tmp_attrib_list++;
					int glx_flags = 0;

					// EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR
					if((egl_flags & 0x00000001) == 0x00000001)
						glx_flags |= 0x0001;
					// EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR
					if((egl_flags & 0x00000002) == 0x00000002)
						glx_flags |= 0x0002;
					// EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR
					// TODO: currently ignored

					glx_attrib_list[glx_attrib_count++] =
						glx_flags;
					break;
				}
				case 0x30FD: //EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR
				{
					glx_attrib_list[glx_attrib_count++] =
						//GLX_CONTEXT_PROFILE_MASK_ARB
						0x9126;
					EGLint egl_flags = *tmp_attrib_list++;
					int glx_flags = 0;

					// EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR
					if((egl_flags & 0x00000001) == 0x00000001)
						glx_flags |= 0x0001;
					// EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR
					if((egl_flags & 0x00000002) == 0x00000002)
						glx_flags |= 0x0002;

					glx_attrib_list[glx_attrib_count++] =
						glx_flags;
					break;
				}
				//TODO
				default:;
			}
		}
	}
	glx_attrib_list[glx_attrib_count] = None;

	::GLXContext context = glXCreateContextAttribsARB(
		display->_x_open_display,
		static_cast< ::GLXFBConfig>(config._glx_fb_config),
		glx_share_context,
		True, // direct rendering
		glx_attrib_list.data()
	);

	if(context == ::GLXContext(0))
	{
		eglplus_egl_ErrorCode = EGL_BAD_ALLOC;
		return EGL_NO_CONTEXT;
	}

	::XSync(display->_x_open_display, False);

	try { return new eglplus_egl_glx_ContextImpl(context); }
	catch(...)
	{
		eglplus_egl_ErrorCode = EGL_BAD_ALLOC;
		return EGL_NO_CONTEXT;
	}
}
//------------------------------------------------------------------------------
// eglDestroyContext
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglDestroyContext(
	EGLDisplay display,
	EGLContext context
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}

	if(context == EGL_NO_CONTEXT)
	{
		eglplus_egl_ErrorCode = EGL_BAD_CONTEXT;
		return EGL_FALSE;
	}

	context->_cleanup(display->_x_open_display);
	delete context;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
EGLAPI EGLBoolean EGLAPIENTRY
eglMakeCurrent(
	EGLDisplay display,
	EGLSurface egl_draw,
	EGLSurface egl_read,
	EGLContext context
)
{
	if((!display) || (!display->_x_open_display))
	{
		eglplus_egl_ErrorCode = EGL_BAD_DISPLAY;
		return EGL_FALSE;
	}

	if(context == EGL_NO_CONTEXT)
	{
		eglplus_egl_ErrorCode = EGL_BAD_CONTEXT;
		return EGL_FALSE;
	}

	::GLXDrawable glx_draw = ::GLXDrawable(0);
	::GLXDrawable glx_read = ::GLXDrawable(0);

	if(egl_draw != EGL_NO_SURFACE)
	{
		glx_draw = egl_draw->_glx_drawable;
	}

	if(egl_read != EGL_NO_SURFACE)
	{
		glx_read = egl_read->_glx_drawable;
	}

	if(::glXMakeContextCurrent(
		display->_x_open_display,
		glx_draw,
		glx_read,
		context->_glx_context
	) != True)
	{
		// TODO proper glx error handling
		eglplus_egl_ErrorCode = EGL_BAD_MATCH;
		return EGL_FALSE;
	}

	return EGL_TRUE;
}
//------------------------------------------------------------------------------
} // extern "C"
