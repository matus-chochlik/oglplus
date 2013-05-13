/**
 *  @file oglplus/color_log_op.hpp
 *  @brief OpenGL color logic operation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_COLOR_LOG_OP_1107121519_HPP
#define OGLPLUS_COLOR_LOG_OP_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Color logic operation enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{LogicOp}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ColorLogicOperation, GLenum)
#include <oglplus/enums/color_logic_operation.ipp>
OGLPLUS_ENUM_CLASS_END(ColorLogicOperation)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/color_logic_operation_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/color_logic_operation_range.ipp>
#endif

/// Alternate name for the ColorLogicOperation enumeration
typedef ColorLogicOperation ColorLogicOp;

} // namespace oglplus

#endif // include guard
