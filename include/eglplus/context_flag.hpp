/**
 *  @file eglplus/context_flag.hpp
 *  @brief EGL context flags type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_CONFIG_CONTEXT_FLAG_1303292057_HPP
#define EGLPLUS_CONFIG_CONTEXT_FLAG_1303292057_HPP

#include <eglplus/enumerations.hpp>
#include <eglplus/bitfield.hpp>

namespace eglplus {

/// EGL context flags enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(ContextFlag, EGLenum)
#include <eglplus/enums/context_flag.ipp>
EGLPLUS_ENUM_CLASS_END(ContextFlag)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/context_flag_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/context_flag_range.ipp>
#endif

EGLPLUS_MAKE_BITFIELD(ContextFlag)

} // namespace eglplus

#endif // include guard
