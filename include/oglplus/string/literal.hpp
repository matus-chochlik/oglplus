/**
 *  @file oglplus/string/literal.hpp
 *  @brief String-literal wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_LITERAL_1107121519_HPP
#define OGLPLUS_STRING_LITERAL_1107121519_HPP

#include <oglplus/string/lit_tpl.hpp>

namespace oglplus {

/// String literal wrapper
/** The literal optionally checks the source c-string literal
 *  for UTF-8 validity (which is required by the OpenGL specification
 *  for input string parameters of GL functions).
 *
 *  @see #OGLPLUS_NO_UTF8_CHECKS
 *
 *  @ingroup oglplus_strings
 */
typedef StrLitTpl<GLchar> StrLit;

} // namespace oglplus

#endif // include guard
