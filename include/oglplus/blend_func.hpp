/**
 *  @file oglplus/blend_func.hpp
 *  @brief OpenGL blending function and equation enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BLEND_FUNC_1107121519_HPP
#define OGLPLUS_BLEND_FUNC_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Blend function type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlendFunc}
 */
OGLPLUS_ENUM_CLASS_BEGIN(BlendFunction, GLenum)
#include <oglplus/enums/blend_function.ipp>
OGLPLUS_ENUM_CLASS_END(BlendFunction)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/blend_function_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/blend_function_range.ipp>
#endif

/// Alternative name for the BlendFunction enumeration
typedef BlendFunction BlendFn;

/// Blend equation enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlendEquation}
 */
OGLPLUS_ENUM_CLASS_BEGIN(BlendEquation, GLenum)
#include <oglplus/enums/blend_equation.ipp>
OGLPLUS_ENUM_CLASS_END(BlendEquation)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/blend_equation_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/blend_equation_range.ipp>
#endif

/// Alternative name for the BlendEquation enumeration
typedef BlendEquation BlendEq;

} // namespace oglplus

#endif // include guard
