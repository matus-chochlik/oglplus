/**
 *  @file oglplus/buffer_map_access.hpp
 *  @brief Buffer map access enumeration/bitfield
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_MAP_ACCESS_1201201052_HPP
#define OGLPLUS_BUFFER_MAP_ACCESS_1201201052_HPP

#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Buffer map access enumeration
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferMapAccess, GLbitfield)
#include <oglplus/enums/buffer_map_access.ipp>
OGLPLUS_ENUM_CLASS_END(BufferMapAccess)
OGLPLUS_MAKE_BITFIELD(BufferMapAccess)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_map_access_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_map_access_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
