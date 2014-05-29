/**
 *  @file oglplus/framebuffer_status.hpp
 *  @brief Framebuffer status enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_FRAMEBUFFER_STATUS_1405022240_HPP
#define OGLPLUS_FRAMEBUFFER_STATUS_1405022240_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Framebuffer status enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(FramebufferStatus, GLenum)
#include <oglplus/enums/framebuffer_status.ipp>
OGLPLUS_ENUM_CLASS_END(FramebufferStatus)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/framebuffer_status_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/framebuffer_status_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
