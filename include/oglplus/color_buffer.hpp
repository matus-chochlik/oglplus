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
	/// NONE
	None = GL_NONE,
	/// FRONT_LEFT
	FrontLeft = GL_FRONT_LEFT,
	/// FRONT_RIGHT
	FrontRight = GL_FRONT_RIGHT,
	/// BACK_LEFT
	BackLeft = GL_BACK_LEFT,
	/// BACK_RIGHT
	BackRight = GL_BACK_RIGHT,
	/// FRONT
	Front = GL_FRONT,
	/// BACK
	Back = GL_BACK,
	/// LEFT
	Left = GL_LEFT,
	/// RIGHT
	Right = GL_RIGHT,
	/// FRONT_AND_BACK
	FrontAndBack = GL_FRONT_AND_BACK
};

} // namespace oglplus

#endif // include guard
