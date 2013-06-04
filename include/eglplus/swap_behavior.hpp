/**
 *  @file eglplus/swap_behavior.hpp
 *  @brief EGL buffer swap behavior enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_SWAP_BEHAVIOR_1303292057_HPP
#define EGLPLUS_SWAP_BEHAVIOR_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL buffer swap behavior enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(SwapBehavior, EGLenum)
#include <eglplus/enums/swap_behavior.ipp>
EGLPLUS_ENUM_CLASS_END(SwapBehavior)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/swap_behavior_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/swap_behavior_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
