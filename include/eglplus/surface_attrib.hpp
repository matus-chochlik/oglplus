/**
 *  @file eglplus/surface_attrib.hpp
 *  @brief EGL surface attribute enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_SURFACE_ATTRIBUTE_1303292057_HPP
#define EGLPLUS_SURFACE_ATTRIBUTE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL surface attribute enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(SurfaceAttrib, EGLenum)
#include <eglplus/enums/surface_attrib.ipp>
EGLPLUS_ENUM_CLASS_END(SurfaceAttrib)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/surface_attrib_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/surface_attrib_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
