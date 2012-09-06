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

#ifndef OGLPLUS_USE_GLCOREARB_H
#define OGLPLUS_USE_GLCOREARB_H 1
#endif

#ifndef OGLPLUS_USE_GL3_H
#define OGLPLUS_USE_GL3_H 0
#endif

#ifndef OGLPLUS_USE_GLEW
#define OGLPLUS_USE_GLEW 0
#endif

#ifndef OGLPLUS_USE_GL3W
#define OGLPLUS_USE_GL3W 0
#endif


#ifndef OGLPLUS_NO_GL

# if OGLPLUS_USE_GLCOREARB_H
#  define GLCOREARB_PROTOTYPES
#  include <GL/glcorearb.h>

# elif OGLPLUS_USE_GL3_H
#  define GL3_PROTOTYPES
#  include <GL3/gl3.h>
#  define __gl_h__
#  define __glext_h__

# elif OGLPLUS_USE_GLEW
#  define GL3_PROTOTYPES
#  include <GL/glew.h>

# elif OGLPLUS_USE_GL3W
#  define GL3_PROTOTYPES
#  include <GL3/gl3w.h>

# else
#  error "Some library including OpenGL symbols is required!"
# endif // OGLPLUS_USE_*

#endif // OGLPLUS_NO_GL

#endif // include guard
