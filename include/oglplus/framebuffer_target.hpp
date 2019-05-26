/**
 *  @file oglplus/framebuffer_target.hpp
 *  @brief Framebuffer bind target enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_TARGET_1201201052_HPP
#define OGLPLUS_FRAMEBUFFER_TARGET_1201201052_HPP

#include <oglplus/enums/framebuffer_target.hpp>
#include <oglplus/fwd.hpp>

namespace oglplus {

#if !OGLPLUS_NO_ENUM_VALUE_CLASSES
#include <oglplus/enums/framebuffer_target_class.ipp>
#endif

template <>
struct ObjectTargetTag<FramebufferTarget> {
    using Type = tag::Framebuffer;
};

} // namespace oglplus

#endif // include guard
