/**
 *  @file oglplus/texture_target.hpp
 *  @brief Texture target enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_TARGET_1107121519_HPP
#define OGLPLUS_TEXTURE_TARGET_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Texture bind and image specification targets
/** @note Not all of the values enumerated here are valid
 *  bind targets. Some of them are just image specification
 *  targets.
 *
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureTarget, GLenum)
#include <oglplus/enums/texture_target.ipp>
OGLPLUS_ENUM_CLASS_END(TextureTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_target_range.ipp>
#endif

template <>
struct ObjectTargetTag<TextureTarget>
{
	typedef tag::Texture Type;
};

} // namespace oglplus

#endif // include guard
