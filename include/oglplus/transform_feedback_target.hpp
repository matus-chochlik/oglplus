/**
 *  @file oglplus/transform_feedback_target.hpp
 *  @brief TransformFeedbackTarget enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TRANSFORM_FEEDBACK_TARGET_1107121519_HPP
#define OGLPLUS_TRANSFORM_FEEDBACK_TARGET_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_transform_feedback2

/// Transform feedback bind targets
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TransformFeedbackTarget, GLenum)
#include <oglplus/enums/transform_feedback_target.ipp>
OGLPLUS_ENUM_CLASS_END(TransformFeedbackTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/transform_feedback_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/transform_feedback_target_range.ipp>
#endif

#endif

} // namespace oglplus

#endif // include guard
