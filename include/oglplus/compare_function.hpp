/**
 *  @file oglplus/compare_function.hpp
 *  @brief OpenGL test/comparison function enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CMP_FUNC_1107121519_HPP
#define OGLPLUS_CMP_FUNC_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Comparison function type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{DepthFunc}
 *  @glfunref{StencilFunc}
 *  @glfunref{TexParameter}
 *  @glfunref{SamplerParameter}
 */
OGLPLUS_ENUM_CLASS_BEGIN(CompareFunction, GLenum)
#include <oglplus/enums/compare_function.ipp>
OGLPLUS_ENUM_CLASS_END(CompareFunction)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/compare_function_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/compare_function_range.ipp>
#endif

/// Alternate name for the CompareFunction enumeration
typedef CompareFunction CompareFn;

} // namespace oglplus

#endif // include guard
