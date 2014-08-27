/**
 *  @file oglplus/context_release_behavior.hpp
 *  @brief Flush control enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CTX_RELEASE_BEHAVIOR_1107121519_HPP
#define OGLPLUS_CTX_RELEASE_BEHAVIOR_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// GL Context release behavior enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ContextReleaseBehavior, GLenum)
#include <oglplus/enums/context_release_behavior.ipp>
OGLPLUS_ENUM_CLASS_END(ContextReleaseBehavior)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/context_release_behavior_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/context_release_behavior_range.ipp>
#endif

/// Alternate name for the ContextReleaseBehavior enumeration
typedef ContextReleaseBehavior ReleaseBehavior;

} // namespace oglplus

#endif // include guard
