/**
 *  @file eglplus/color_buffer_type.hpp
 *  @brief EGL color buffer type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_COLOR_BUFFER_TYPE_1303292057_HPP
#define EGLPLUS_COLOR_BUFFER_TYPE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL color_buffer_type enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(ColorBufferType, EGLenum)
#include <eglplus/enums/color_buffer_type.ipp>
EGLPLUS_ENUM_CLASS_END(ColorBufferType)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/color_buffer_type_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/color_buffer_type_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
