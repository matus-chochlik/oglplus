/**
 *  @file oglplus/gl.hpp
 *  @brief Includes GL3/gl3.h and disables gl.h/glext.h
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_GL_1107121519_HPP
#define OGLPLUS_GL_1107121519_HPP

#define GL3_PROTOTYPES
#define GL_VERSION_4_1
#include <GL3/gl3.h>
#define __gl_h__
#define __glext_h__

#endif // include guard
