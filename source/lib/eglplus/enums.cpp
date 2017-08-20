/**
 *  .file lib/eglplus/enums.cpp
 *  .brief String-related functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2017 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "prologue.ipp"
#include <eglplus/string.hpp>
#include "implement.ipp"

#include <eglplus/detail/base_range.hpp>
#include <eglplus/detail/enum_class.hpp>

namespace eglplus {
#include <eglplus/lib/enum_value_name.ipp>
#include <eglplus/lib/enum_value_range.ipp>
} // namespace eglplus

#include "epilogue.ipp"
