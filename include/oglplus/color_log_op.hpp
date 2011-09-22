/**
 *  @file oglplus/color_log_op.hpp
 *  @brief OpenGL color logic operation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_COLOR_LOG_OP_1107121519_HPP
#define OGLPLUS_COLOR_LOG_OP_1107121519_HPP

namespace oglplus {

/// Color logic operation enumeration
/**
 *  @ingroup enumerations
 */
enum class ColorLogicOperation : GLenum
{
	/// CLEAR
	Clear = GL_CLEAR,
	/// AND
	And = GL_AND,
	/// AND_REVERSE
	AndReverse = GL_AND_REVERSE,
	/// COPY
	Copy = GL_COPY,
	/// AND_INVERTED
	AndInverted = GL_AND_INVERTED,
	/// NOOP
	NoOp = GL_NOOP,
	/// XOR
	Xor = GL_XOR,
	/// OR
	Or = GL_OR,
	/// NOR
	Nor = GL_NOR,
	/// EQUIV
	Equiv = GL_EQUIV,
	/// INVERT
	Invert = GL_INVERT,
	/// OR_REVERSE
	OrReverse = GL_OR_REVERSE,
	/// COPY_INVERTED
	CopyInverted = GL_COPY_INVERTED,
	/// OR_INVERTED
	OrInverted = GL_OR_INVERTED,
	/// NAND
	Nand = GL_NAND,
	/// SET
	Set = GL_SET
};

/// Alternate name for the ColorLogicOperation enumeration
typedef ColorLogicOperation ColorLogicOp;

} // namespace oglplus

#endif // include guard
