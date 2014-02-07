/**
 *  @file oglplus/context_flag_bit.hpp
 *  @brief GL context flag bit enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_FLAG_BIT_1201201052_HPP
#define OGLPLUS_CONTEXT_FLAG_BIT_1201201052_HPP

#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// GL context flag bit enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ContextFlagBit, GLbitfield)
#include <oglplus/enums/context_flag_bit.ipp>
OGLPLUS_ENUM_CLASS_END(ContextFlagBit)

OGLPLUS_MAKE_BITFIELD(ContextFlagBit)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/context_flag_bit_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/context_flag_bit_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
