/**
 *  @file oglplus/buffer_usage.hpp
 *  @brief Buffer usage enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_USAGE_1201201052_HPP
#define OGLPLUS_BUFFER_USAGE_1201201052_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Buffer usage enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferUsage, GLenum)
#include <oglplus/enums/buffer_usage.ipp>
OGLPLUS_ENUM_CLASS_END(BufferUsage)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_usage_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_usage_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
