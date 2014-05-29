/**
 *  @file oglplus/framebuffer_target.hpp
 *  @brief Framebuffer bind target enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_TARGET_1201201052_HPP
#define OGLPLUS_FRAMEBUFFER_TARGET_1201201052_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Framebuffer bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferTarget, GLenum)
#include <oglplus/enums/framebuffer_target.ipp>
OGLPLUS_ENUM_CLASS_END(FramebufferTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/framebuffer_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/framebuffer_target_range.ipp>
#endif

template <>
struct ObjectTargetTag<FramebufferTarget>
{
	typedef tag::Framebuffer Type;
};

} // namespace oglplus

#endif // include guard
