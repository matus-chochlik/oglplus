/**
 *  @file oglplus/stencil_op.hpp
 *  @brief OpenGL stencil operation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STENCIL_FUNC_1107121519_HPP
#define OGLPLUS_STENCIL_FUNC_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Stencil operation type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{StencilOp}
 */
OGLPLUS_ENUM_CLASS_BEGIN(StencilOperation, GLenum)
#include <oglplus/enums/stencil_operation.ipp>
OGLPLUS_ENUM_CLASS_END(StencilOperation)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/stencil_operation_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/stencil_operation_range.ipp>
#endif

/// Alternate name for the StencilOperation enumeration
typedef StencilOperation StencilOp;

} // namespace oglplus

#endif // include guard
