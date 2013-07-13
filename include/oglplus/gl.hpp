/**
 *  @file oglplus/gl.hpp
 *  @brief Includes GL3/gl3.h and disables gl.h/glext.h
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
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

namespace oglplus {
struct GLAPIInitializer
{
	GLAPIInitializer(
		int /*gl_ver_major*/ = 3,
		int /*gl_ver_minor*/ = 3
	){ }
};
} // namespace oglplus

# elif OGLPLUS_USE_GL3_H
#  define GL3_PROTOTYPES
#  ifdef __APPLE__
#   include <OpenGL/gl3.h>
#  else
#   include <GL3/gl3.h>
#  endif
#  define __gl_h__
#  define __glext_h__

namespace oglplus {
struct GLAPIInitializer
{
	GLAPIInitializer(
		int /*gl_ver_major*/ = 3,
		int /*gl_ver_minor*/ = 3
	){ }
};
} // namespace oglplus

# elif OGLPLUS_USE_GLEW
#  define GL3_PROTOTYPES
#  include <GL/glew.h>
#  include <stdexcept>

namespace oglplus {
class GLAPIInitializer
{
public:
	GLAPIInitializer(
		int /*gl_ver_major*/ = 3,
		int /*gl_ver_minor*/ = 3
	)
	{
		auto init_result = glewInit();
		glGetError();
		if(init_result != GLEW_OK)
		{
			throw std::runtime_error(
				"OpenGL/GLEW initialization error."
			);
		}
	}
};
} // namespace oglplus

# elif OGLPLUS_USE_GL3W
#  define GL3_PROTOTYPES
#  include <GL3/gl3w.h>
#  include <stdexcept>

namespace oglplus {
class GLAPIInitializer
{
public:
	GLAPIInitializer(
		int gl_ver_major = 3,
		int gl_ver_minor = 3
	)
	{
		auto init_failed = gl3wInit();
		glGetError();
		if(init_failed)
		{
			throw std::runtime_error(
				"OpenGL/GL3W initialization error."
			);
		}
		if(!gl3wIsSupported(gl_ver_major, gl_ver_minor))
		{
			throw std::runtime_error(
				"Requested OpenGL version not supported"
			);
		}
	}
};
} // namespace oglplus

# else
#  error "Some library including OpenGL symbols is required!"
# endif // OGLPLUS_USE_*

#define GL_VERTEX_ARRAY 0x8074

#endif // OGLPLUS_NO_GL

#endif // include guard
