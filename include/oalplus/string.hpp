/**
 *  @file oalplus/string.hpp
 *  @brief String-related typedefs
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_STRING_1303291951_HPP
#define OALPLUS_STRING_1303291951_HPP

#include <eagine/base/string.hpp>

namespace oalplus {

/// String class
/**
 *  @ingroup oalplus_strings
 */
typedef ::eagine::base::basic_string<ALchar> ALString;

/// char string const reference wrapper
/**
 *  @ingroup oalplus_strings
 */
typedef ::eagine::base::basic_string_ref<const char> CStrRef;

/// ALchar string const reference wrapper
/**
 *  @ingroup oalplus_strings
 */
typedef ::eagine::base::basic_string_ref<const ALchar> ALCStrRef;

} // namespace oalplus

#endif // include guard
