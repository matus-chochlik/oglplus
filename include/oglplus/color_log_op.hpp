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
 *
 *  @glsymbols
 *  @glfunref{LogicOp}
 */
enum class ColorLogicOperation : GLenum
{
#include <oglplus/enums/color_logic_operation.ipp>
};

inline const GLchar* EnumValueName(ColorLogicOperation value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/color_logic_operation.ipp>
#endif
	return "";
}

/// Alternate name for the ColorLogicOperation enumeration
typedef ColorLogicOperation ColorLogicOp;

} // namespace oglplus

#endif // include guard
