/**
 *  @file oglplus/primitive_type.hpp
 *  @brief OpenGL primitive type-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PRIMITIVE_TYPE_1107121519_HPP
#define OGLPLUS_PRIMITIVE_TYPE_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Primitive type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{DrawArrays}
 *  @glfunref{DrawArraysInstanced}
 *  @glfunref{DrawElements}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PrimitiveType, GLenum)
#include <oglplus/enums/primitive_type.ipp>
OGLPLUS_ENUM_CLASS_END(PrimitiveType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/primitive_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/primitive_type_range.ipp>
#endif

/// Tesselation generation stage primitive type
/**
 * @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TessGenPrimitiveType, GLenum)
#include <oglplus/enums/tess_gen_primitive_type.ipp>
OGLPLUS_ENUM_CLASS_END(TessGenPrimitiveType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/tess_gen_primitive_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/tess_gen_primitive_type_range.ipp>
#endif

/// Tesselation primitive spacing
/**
 * @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(TessGenPrimitiveSpacing, GLenum)
#include <oglplus/enums/tess_gen_primitive_spacing.ipp>
OGLPLUS_ENUM_CLASS_END(TessGenPrimitiveSpacing)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/tess_gen_primitive_spacing_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/tess_gen_primitive_spacing_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
