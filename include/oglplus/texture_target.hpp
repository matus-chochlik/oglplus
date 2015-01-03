/**
 *  @file oglplus/texture_target.hpp
 *  @brief Texture target enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_TARGET_1107121519_HPP
#define OGLPLUS_TEXTURE_TARGET_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/enums/texture_target.hpp>

namespace oglplus {

template <>
struct ObjectTargetTag<TextureTarget>
{
	typedef tag::Texture Type;
};

} // namespace oglplus

#endif // include guard
