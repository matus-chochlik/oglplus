/**
 *  @file oglplus/gl.hpp
 *  @brief Includes GL3/gl3.h and disables gl.h/glext.h
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_GL_1107121519_HPP
#define OGLPLUS_GL_1107121519_HPP

#ifndef OGLPLUS_NO_SITE_CONFIG
#include <oglplus/site_config.hpp>
#endif

#ifndef OGLPLUS_USE_GLEW
#define OGLPLUS_USE_GLEW 0
#endif

#if OGLPLUS_USE_GLEW

#include <GL/glew.h>

#else // using GL3/gl3.h is the fallback

#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#define __gl_h__
#define __glext_h__

#endif // OGLPLUS_USE_*

#endif // include guard
