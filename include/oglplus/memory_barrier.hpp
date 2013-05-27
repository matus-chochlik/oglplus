/**
 *  @file oglplus/memory_barrier.hpp
 *  @brief OpenGL memory barrier bits enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_MEMORY_BARRIER_1107121519_HPP
#define OGLPLUS_MEMORY_BARRIER_1107121519_HPP

#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of memory barrier bits
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{MemoryBarrier}
 */
OGLPLUS_ENUM_CLASS_BEGIN(MemoryBarrierBit, GLbitfield)
#include <oglplus/enums/memory_barrier_bit.ipp>
OGLPLUS_ENUM_CLASS_END(MemoryBarrierBit)

OGLPLUS_MAKE_BITFIELD(MemoryBarrierBit)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/memory_barrier_bit_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/memory_barrier_bit_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
