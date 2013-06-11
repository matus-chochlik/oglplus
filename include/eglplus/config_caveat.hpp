/**
 *  @file eglplus/config_caveat.hpp
 *  @brief EGL config caveat type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_CONFIG_CAVEAT_TYPE_1303292057_HPP
#define EGLPLUS_CONFIG_CAVEAT_TYPE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL config caveat enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(ConfigCaveat, EGLenum)
#include <eglplus/enums/config_caveat.ipp>
EGLPLUS_ENUM_CLASS_END(ConfigCaveat)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/config_caveat_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/config_caveat_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
