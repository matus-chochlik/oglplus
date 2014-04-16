/**
 *  @file oglplus/buffer_target.hpp
 *  @brief Buffer bind target enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_TARGET_1201201052_HPP
#define OGLPLUS_BUFFER_TARGET_1201201052_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Buffer bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferTarget, GLenum)
#include <oglplus/enums/buffer_target.ipp>
OGLPLUS_ENUM_CLASS_END(BufferTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_target_range.ipp>
#endif

template <>
struct ObjectTargetOps<BufferTarget>
{
	typedef BufferOps Type;
};

/// Buffer indexed bind target
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferIndexedTarget, GLenum)
#include <oglplus/enums/buffer_indexed_target.ipp>
OGLPLUS_ENUM_CLASS_END(BufferIndexedTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_indexed_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_indexed_target_range.ipp>
#endif

template <>
struct ObjectTargetOps<BufferIndexedTarget>
{
	typedef BufferOps Type;
};

} // namespace oglplus

#endif // include guard
