/**
 *  @file eglplus/gl_colorspace.hpp
 *  @brief EGL OpenGL colorspace enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_GL_COLORSPACE_1303292057_HPP
#define EGLPLUS_GL_COLORSPACE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// OpenGL colorspace enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(GLColorspace, EGLenum)
#include <eglplus/enums/gl_colorspace.ipp>
EGLPLUS_ENUM_CLASS_END(GLColorspace)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/gl_colorspace_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/gl_colorspace_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
