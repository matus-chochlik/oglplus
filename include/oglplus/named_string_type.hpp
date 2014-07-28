/**
 *  @file oglplus/named_string_type.hpp
 *  @brief NamedString type specifier enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_NAMED_STRING_TYPE_1202231207_HPP
#define OGLPLUS_NAMED_STRING_TYPE_1202231207_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of named string type specifiers
/**
 *  @ingroup enumerations
 *
 */
OGLPLUS_ENUM_CLASS_BEGIN(NamedStringType, GLenum)
#include <oglplus/enums/named_string_type.ipp>
OGLPLUS_ENUM_CLASS_END(NamedStringType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/named_string_type_names.ipp>
#endif

#if !OGLPLUS_NO_ENUM_VALUE_RANGES
#include <oglplus/enums/named_string_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
