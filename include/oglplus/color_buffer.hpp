/**
 *  @file oglplus/color_buffer.hpp
 *  @brief OpenGL Color buffer enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_COLOR_BUFFER_1107121519_HPP
#define OGLPLUS_COLOR_BUFFER_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of color buffers for read/write operations
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{ReadBuffer}
 *  @glfunref{DrawBuffer}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ColorBuffer, GLenum)
#include <oglplus/enums/color_buffer.ipp>
OGLPLUS_ENUM_CLASS_END(ColorBuffer)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/color_buffer_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/color_buffer_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
