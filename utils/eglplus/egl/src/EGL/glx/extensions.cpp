/**
 *  .file EGL/glx/extension.cpp
 *  .brief EGL Extensions functionality implementation.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <EGL/egl.h>

#include "../error.hpp"

//------------------------------------------------------------------------------
// EGL API
//------------------------------------------------------------------------------
extern "C" {
//------------------------------------------------------------------------------
// eglGetProcAddress
//------------------------------------------------------------------------------
EGLAPI void EGLAPIENTRY (*eglGetProcAddress(const char* /*procname*/))(void)
{
	return nullptr;
}
//------------------------------------------------------------------------------
} // extern "C"
