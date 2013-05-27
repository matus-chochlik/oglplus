/**
 *  @file oglplus/precision_type.hpp
 *  @brief OpenGL precision type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PRECISION_TYPE_1107121519_HPP
#define OGLPLUS_PRECISION_TYPE_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Precision type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{GetShaderPrecisionFormat}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PrecisionType, GLenum)
#include <oglplus/enums/precision_type.ipp>
OGLPLUS_ENUM_CLASS_END(PrecisionType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/precision_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/precision_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
