/**
 *  @file oglplus/ext/ARB_compatibility/matrix_mode.hpp
 *  @brief The CompatibilityMatrixMode enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_ARB_COMPATIBILITY_MATRIX_MODE_1203031902_HPP
#define OGLPLUS_EXT_ARB_COMPATIBILITY_MATRIX_MODE_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Compatibility matrix mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{MatrixMode}
 *  @glextref{ARB,compatibility}
 */
OGLPLUS_ENUM_CLASS_BEGIN(CompatibilityMatrixMode, GLenum)
#include <oglplus/enums/ext/compat_matrix_mode.ipp>
OGLPLUS_ENUM_CLASS_END(CompatibilityMatrixMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/compat_matrix_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/compat_matrix_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
