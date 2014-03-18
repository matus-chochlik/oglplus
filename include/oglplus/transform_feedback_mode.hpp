/**
 *  @file oglplus/transform_feedback_mode.hpp
 *  @brief TransformFeedbackMode enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TRANSFORM_FEEDBACK_MODE_1107121519_HPP
#define OGLPLUS_TRANSFORM_FEEDBACK_MODE_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// The mode used to capture the varying variables in TF
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TransformFeedbackMode, GLenum)
#include <oglplus/enums/transform_feedback_mode.ipp>
OGLPLUS_ENUM_CLASS_END(TransformFeedbackMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/transform_feedback_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/transform_feedback_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
