/**
 *  @file eglplus/string.hpp
 *  @brief String-related type-defs
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_STRING_1303291951_HPP
#define EGLPLUS_STRING_1303291951_HPP

#include <oglplus/string/ref_tpl.hpp>
#include <string>

namespace eglplus {

/// String class
/**
 *  @ingroup eglplus_strings
 */
using String = ::std::basic_string<char>;

/// String const reference wrapper
/**
 *  @ingroup eglplus_strings
 */
using StrCRef = ::oglplus::StrCRefTpl<char>;

} // namespace eglplus

#endif // include guard
