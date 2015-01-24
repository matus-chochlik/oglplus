/**
 *  @file oglplus/string/ref.hpp
 *  @brief String reference
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_REF_1107121519_HPP
#define OGLPLUS_STRING_REF_1107121519_HPP

#include <eagine/base/string.hpp>

namespace oglplus {

/// const String reference wrapper
typedef eagine::base::basic_string_ref<const char> CStrRef;

/// const GLString reference wrapper
typedef eagine::base::basic_string_ref<const GLchar> GLCStrRef;

using eagine::base::c_str;

} // namespace oglplus

#endif // include guard
