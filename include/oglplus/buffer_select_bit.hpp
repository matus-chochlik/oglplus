/**
 *  @file oglplus/buffer_select_bit.hpp
 *  @brief OpenGL buffer selection bit enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BUFFER_SELECT_BIT_1201201052_HPP
#define OGLPLUS_BUFFER_SELECT_BIT_1201201052_HPP

#include <oglplus/bitfield.hpp>

namespace oglplus {

/// Polygon facing enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Clear}
 *  @glfunref{BlitFramebuffer}
 */
OGLPLUS_ENUM_CLASS_BEGIN(BufferSelectBit, GLenum)
#include <oglplus/enums/buffer_select_bit.ipp>
OGLPLUS_ENUM_CLASS_END

OGLPLUS_MAKE_BITFIELD(BufferSelectBit)

inline StrLit EnumValueName(BufferSelectBit value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/buffer_select_bit.ipp>
#endif
	OGLPLUS_FAKE_USE(value);
	return StrLit();
}

} // namespace oglplus

#endif // include guard
