/**
 *  @file oglplus/ext/ARB_compatibility/primitive_type.hpp
 *  @brief The CompatibilityPrimitiveType enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_ARB_COMPATIBILITY_PRIMITIVE_TYPE_1203031902_HPP
#define OGLPLUS_EXT_ARB_COMPATIBILITY_PRIMITIVE_TYPE_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Compatibility primitive type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Begin}
 *  @glextref{ARB,compatibility}
 */
OGLPLUS_ENUM_CLASS_BEGIN(CompatibilityPrimitiveType, GLenum)
#include <oglplus/enums/ext/compat_prim_type.ipp>
OGLPLUS_ENUM_CLASS_END(CompatibilityPrimitiveType)

/// Shorter name for CompatibilityPrimitiveType
typedef CompatibilityPrimitiveType CompatPrimType;

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/compat_prim_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/compat_prim_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
