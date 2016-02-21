/**
 *  .file EGL/egl.h
 *  .brief EGL header
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_EGL_1306251503_H
#define EGLPLUS_EGL_1306251503_H

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif

#include <KHR/khrplatform.h>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include "egl_ppdef.inc"

#ifdef __cplusplus
extern "C" {
#endif

#include "glx/egl_type.inc"
#include "egl_func.inc"

#ifdef __cplusplus
} // extern "C"
#endif

#endif // include guard
