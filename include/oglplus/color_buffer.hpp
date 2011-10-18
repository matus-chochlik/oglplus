/**
 *  @file oglplus/color_buffer.hpp
 *  @brief OpenGL Color buffer enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_COLOR_BUFFER_1107121519_HPP
#define OGLPLUS_COLOR_BUFFER_1107121519_HPP

namespace oglplus {

/// Enumeration of color buffers for read/write operations
/**
 *  @ingroup enumerations
 */
enum class ColorBuffer : GLenum
{
#include <oglplus/enums/color_buffer.ipp>
};

} // namespace oglplus

#endif // include guard
