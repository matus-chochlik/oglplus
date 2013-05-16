/**
 *  @file oalplus/data_format.hpp
 *  @brief Data format enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_DATA_FORMAT_1303201808_HPP
#define OALPLUS_DATA_FORMAT_1303201808_HPP

#include <oalplus/enumerations.hpp>

namespace oalplus {

/// Enumeration of data format specifiers
/**
 *  @ingroup enumerations
 *
 */
OALPLUS_ENUM_CLASS_BEGIN(DataFormat, ALenum)
#include <oalplus/enums/data_format.ipp>
OALPLUS_ENUM_CLASS_END(DataFormat)


#if !OALPLUS_NO_ENUM_VALUE_NAMES
#include <oalplus/enums/data_format_names.ipp>
#endif

#if !OALPLUS_NO_ENUM_VALUE_RANGES
#include <oalplus/enums/data_format_range.ipp>
#endif

} // namespace oalplus

#endif // include guard
