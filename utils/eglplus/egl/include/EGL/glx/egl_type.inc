/**
 *  .file EGL/glx/egl_type.h
 *  .brief EGL/GLX header
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
struct eglplus_egl_glx_ConfigImpl {
    void* _glx_fb_config;
};

struct eglplus_egl_glx_ContextImpl;
struct eglplus_egl_glx_DisplayImpl;
struct eglplus_egl_glx_SurfaceImpl;
struct eglplus_egl_glx_ClientBufferImpl;

using EGLNativeDisplayType = void*;
using EGLNativePixmapType = khronos_uint32_t;
using EGLNativeWindowType = khronos_uint32_t;

using EGLAttrib = intptr_t;
using EGLSync = void*;
using EGLTime = khronos_utime_nanoseconds_t;

using EGLint = khronos_int32_t;
using EGLBoolean = unsigned int;
using EGLenum = unsigned int;

using EGLConfig = struct eglplus_egl_glx_ConfigImpl;
using EGLContext = struct eglplus_egl_glx_ContextImpl*;
using EGLDisplay = struct eglplus_egl_glx_DisplayImpl*;
using EGLSurface = struct eglplus_egl_glx_SurfaceImpl*;
using EGLClientBuffer = struct eglplus_egl_glx_ClientBufferImpl*;
