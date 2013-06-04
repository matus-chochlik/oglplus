/**
 *  @file eglplus/vg_colorspace.hpp
 *  @brief EGL OpenVG colorspace enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_VG_COLORSPACE_1303292057_HPP
#define EGLPLUS_VG_COLORSPACE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// OpenVG colorspace enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(VGColorspace, EGLenum)
#include <eglplus/enums/vg_colorspace.ipp>
EGLPLUS_ENUM_CLASS_END(VGColorspace)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/vg_colorspace_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/vg_colorspace_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
