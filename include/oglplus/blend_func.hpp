/**
 *  @file oglplus/blend_func.hpp
 *  @brief OpenGL blending function and equation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_BLEND_FUNC_1107121519_HPP
#define OGLPLUS_BLEND_FUNC_1107121519_HPP

namespace oglplus {

/// Blend function type enumeration
/**
 *  @ingroup enumerations
 */
enum class BlendFunction : GLenum
{
	/// ZERO
	Zero = GL_ZERO,
	/// ONE
	One = GL_ONE,
	/// SRC_COLOR
	SrcColor = GL_SRC_COLOR,
	/// ONE_MINUS_SRC_COLOR
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
	/// DST_COLOR
	DstColor = GL_DST_COLOR,
	/// ONE_MINUS_DST_COLOR
	OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
	/// SRC_ALPHA
	SrcAlpha = GL_SRC_ALPHA,
	/// ONE_MINUS_SRC_ALPHA
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
	/// DST_ALPHA
	DstAlpha = GL_DST_ALPHA,
	/// ONE_MINUS_DST_ALPHA
	OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
	/// CONSTANT_COLOR
	ConstantColor = GL_CONSTANT_COLOR,
	/// ONE_MINUS_CONSTANT_COLOR
	OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
	/// CONSTANT_ALPHA
	ConstantAlpha = GL_CONSTANT_ALPHA,
	/// ONE_MINUS_CONSTANT_ALPHA
	OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
	/// SRC_ALPHA_SATURATE
	SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
	/// SRC1_COLOR
	Src1Color = GL_SRC1_COLOR,
	/// ONE_MINUS_SRC1_COLOR
	OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
	// SRC1_ALPHA
	//Src1Alpha = GL_SRC1_ALPHA,
	/// ONE_MINUS_SRC1_ALPHA
	OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA
};

/// Alternative name for the BlendFunction enumeration
typedef BlendFunction BlendFn;

/// Blend equation enumeration
/**
 *  @ingroup enumerations
 */
enum class BlendEquation : GLenum
{
	/// FUNC_ADD
	Add = GL_FUNC_ADD,
	/// FUNC_SUBTRACT
	Subtract = GL_FUNC_SUBTRACT,
	/// FUNC_REVERSE_SUBTRACT
	ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
	/// MIN
	Min = GL_MIN,
	/// MAX
	Max = GL_MAX
};

/// Alternative name for the BlendEquation enumeration
typedef BlendEquation BlendEq;

} // namespace oglplus

#endif // include guard
