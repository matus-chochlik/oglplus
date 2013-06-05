/**
 *  @file eglplus/opengl_rns.hpp
 *  @brief EGL OpenGL reset notification strategy enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_OPENGL_RESET_NOTIFICATION_STRATEGY_1303292057_HPP
#define EGLPLUS_OPENGL_RESET_NOTIFICATION_STRATEGY_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL OpenGL reset notification strategy enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(OpenGLResetNotificationStrategy, EGLenum)
#include <eglplus/enums/opengl_rns.ipp>
EGLPLUS_ENUM_CLASS_END(OpenGLResetNotificationStrategy)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/opengl_rns_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/opengl_rns_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
