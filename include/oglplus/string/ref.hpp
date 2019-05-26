/**
 *  @file oglplus/string/ref.hpp
 *  @brief String reference
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_REF_1107121519_HPP
#define OGLPLUS_STRING_REF_1107121519_HPP

#include <oglplus/string/ref_tpl.hpp>

namespace oglplus {

/// String const reference wrapper
using StrCRef = StrCRefTpl<GLchar>;

} // namespace oglplus

#endif // include guard
