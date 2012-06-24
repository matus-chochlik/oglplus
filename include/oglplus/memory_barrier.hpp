/**
 *  @file oglplus/memory_barrier.hpp
 *  @brief OpenGL memory barrier bits enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_MEMORY_BARRIER_1107121519_HPP
#define OGLPLUS_MEMORY_BARRIER_1107121519_HPP

#include <oglplus/bitfield.hpp>

namespace oglplus {

/// Enumeration of memory barrier bits
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{MemoryBarrier}
 */
enum class MemoryBarrierBit : GLbitfield
{
#include <oglplus/enums/memory_barrier_bit.ipp>
};

OGLPLUS_MAKE_BITFIELD(MemoryBarrierBit)

inline const GLchar* EnumValueName(MemoryBarrierBit value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/memory_barrier_bit.ipp>
#endif
	return "";
}

} // namespace oglplus

#endif // include guard
