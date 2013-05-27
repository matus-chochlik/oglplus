/**
 *  @file oalplus/source_type.hpp
 *  @brief OpenAL Source type enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_SOURCE_TYPE_1303292057_HPP
#define OALPLUS_SOURCE_TYPE_1303292057_HPP

#include <oalplus/enumerations.hpp>

namespace oalplus {

/// OpenAL source type enumeration
/**
 *  @ingroup enumerations
 */
OALPLUS_ENUM_CLASS_BEGIN(SourceType, ALenum)
#include <oalplus/enums/source_type.ipp>
OALPLUS_ENUM_CLASS_END(SourceType)

#if !OALPLUS_NO_ENUM_VALUE_NAMES
#include <oalplus/enums/source_type_names.ipp>
#endif

#if !OALPLUS_ENUM_VALUE_RANGES
#include <oalplus/enums/source_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
