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
enum class BlendFunction : GLenum
{
	Zero = GL_ZERO,
	One = GL_ONE,
	SrcColor = GL_SRC_COLOR,
	OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
	DstColor = GL_DST_COLOR,
	OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
	SrcAlpha = GL_SRC_ALPHA,
	OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
	DstAlpha = GL_DST_ALPHA,
	OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
	ConstantColor = GL_CONSTANT_COLOR,
	OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
	ConstantAlpha = GL_CONSTANT_ALPHA,
	OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
	SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
	Src1Color = GL_SRC1_COLOR,
	OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
	//Src1Alpha = GL_SRC1_ALPHA,
	OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA
};

typedef BlendFunction BlendFn;

/// Blend equation enumeration
enum class BlendEquation : GLenum
{
	Add = GL_FUNC_ADD,
	Subtract = GL_FUNC_SUBTRACT,
	ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
	Min = GL_MIN,
	Max = GL_MAX
};

typedef BlendEquation BlendEq;

} // namespace oglplus

#endif // include guard
