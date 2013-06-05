/**
 *  @file eglplus/context_attrib.hpp
 *  @brief EGL context attribute type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_CONFIG_CONTEXT_1303292057_HPP
#define EGLPLUS_CONFIG_CONTEXT_1303292057_HPP

#include <eglplus/enumerations.hpp>

namespace eglplus {

/// EGL context attribute enumeration
/**
 *  @ingroup eglplus_enumerations
 */
EGLPLUS_ENUM_CLASS_BEGIN(ContextAttrib, EGLenum)
#include <eglplus/enums/context_attrib.ipp>
EGLPLUS_ENUM_CLASS_END(ContextAttrib)

#if !EGLPLUS_NO_ENUM_VALUE_NAMES
#include <eglplus/enums/context_attrib_names.ipp>
#endif

#if !EGLPLUS_ENUM_VALUE_RANGES
#include <eglplus/enums/context_attrib_range.ipp>
#endif

} // namespace eglplus

#endif // include guard
