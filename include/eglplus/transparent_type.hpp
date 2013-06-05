/**
 *  @file eglplus/transparent_type.hpp
 *  @brief EGL transparent type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_TRANSPARENT_TYPE_1303292057_HPP
#define EGLPLUS_TRANSPARENT_TYPE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL transparent type enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(TransparentType, EGLenum)
#include <eglplus/enums/transparent_type.ipp>
EGLPLUS_ENUM_CLASS_END(TransparentType)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/transparent_type_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/transparent_type_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
