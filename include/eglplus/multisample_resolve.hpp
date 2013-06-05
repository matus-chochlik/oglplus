/**
 *  @file eglplus/multisample_resolve.hpp
 *  @brief EGL Multisample resolve enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_MULTISAMPLE_RESOLVE_1303292057_HPP
#define EGLPLUS_MULTISAMPLE_RESOLVE_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// Multisample resolve enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(MultisampleResolve, EGLenum)
#include <eglplus/enums/multisample_resolve.ipp>
EGLPLUS_ENUM_CLASS_END(MultisampleResolve)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/multisample_resolve_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/multisample_resolve_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
