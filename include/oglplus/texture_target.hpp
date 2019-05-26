/**
 *  @file oglplus/texture_target.hpp
 *  @brief Texture target enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_TARGET_1107121519_HPP
#define OGLPLUS_TEXTURE_TARGET_1107121519_HPP

#include <oglplus/config/enums.hpp>
#include <oglplus/enums/texture_target.hpp>
#include <oglplus/fwd.hpp>

namespace oglplus {

#if !OGLPLUS_NO_ENUM_VALUE_CLASSES
#include <oglplus/enums/texture_target_class.ipp>
#endif

template <>
struct ObjectTargetTag<TextureTarget> {
    using Type = tag::Texture;
};

} // namespace oglplus

#endif // include guard
