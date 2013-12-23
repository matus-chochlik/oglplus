/**
 *  @file oglplus/buffer_select_bit.hpp
 *  @brief Color, depth or stencil buffer selection bit enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_SELECT_BIT_1201201052_HPP
#define OGLPLUS_BUFFER_SELECT_BIT_1201201052_HPP

#include <oglplus/bitfield.hpp>
#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Buffer selection bit enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Clear}
 *  @glfunref{BlitFramebuffer}
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferSelectBit, GLbitfield)
#include <oglplus/enums/buffer_select_bit.ipp>
OGLPLUS_ENUM_CLASS_END(BufferSelectBit)

OGLPLUS_MAKE_BITFIELD(BufferSelectBit)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/buffer_select_bit_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/buffer_select_bit_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
