/**
 *  @file oalplus/context_attrib.hpp
 *  @brief OpenAL context attribute type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_CONFIG_CONTEXT_1303292057_HPP
#define OALPLUS_CONFIG_CONTEXT_1303292057_HPP

#include <oalplus/enumerations.hpp>

namespace oalplus {

/// OpenAL context attribute enumeration
/**
 *  @ingroup oalplus_enumerations
 */
OALPLUS_ENUM_CLASS_BEGIN(ContextAttrib, ALenum)
#include <oalplus/enums/context_attrib.ipp>
OALPLUS_ENUM_CLASS_END(ContextAttrib)

#if !OALPLUS_NO_ENUM_VALUE_NAMES
#include <oalplus/enums/context_attrib_names.ipp>
#endif

#if !OALPLUS_ENUM_VALUE_RANGES
#include <oalplus/enums/context_attrib_range.ipp>
#endif

} // namespace oalplus

#endif // include guard
