/**
 *  @file oglplus/context_profile_bit.hpp
 *  @brief GL context profile bit enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_PROFILE_BIT_1201201052_HPP
#define OGLPLUS_CONTEXT_PROFILE_BIT_1201201052_HPP

#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// GL context profile bit enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ContextProfileBit, GLbitfield)
#include <oglplus/enums/context_profile_bit.ipp>
OGLPLUS_ENUM_CLASS_END(ContextProfileBit)

OGLPLUS_MAKE_BITFIELD(ContextProfileBit)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/context_profile_bit_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/context_profile_bit_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
