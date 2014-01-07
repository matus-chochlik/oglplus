/**
 *  .file EGL/error.cpp
 *  .brief EGL Error handling implementation
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <EGL/egl.h>

#include "error.hpp"

EGLint eglplus_egl_ErrorCode = EGL_SUCCESS;

extern "C" {

EGLAPI EGLint EGLAPIENTRY eglGetError(void)
{
	EGLint old_ec = eglplus_egl_ErrorCode;
	eglplus_egl_ErrorCode = EGL_SUCCESS;
	return old_ec;
}

} // extern "C"
