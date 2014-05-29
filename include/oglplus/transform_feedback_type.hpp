/**
 *  @file oglplus/transform_feedback_type.hpp
 *  @brief TransformFeedbackType enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TRANSFORM_FEEDBACK_TYPE_1107121519_HPP
#define OGLPLUS_TRANSFORM_FEEDBACK_TYPE_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Transform feedback primitive modes
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TransformFeedbackPrimitiveType, GLenum)
#include <oglplus/enums/transform_feedback_primitive_type.ipp>
OGLPLUS_ENUM_CLASS_END(TransformFeedbackPrimitiveType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/transform_feedback_primitive_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/transform_feedback_primitive_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
