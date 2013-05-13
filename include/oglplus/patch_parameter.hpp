/**
 *  @file oglplus/patch_parameter.hpp
 *  @brief OpenGL patch parameters enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PATCH_PARAMETER_1301211323_HPP
#define OGLPLUS_PATCH_PARAMETER_1301211323_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of patch parameters
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PatchParameteri}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PatchParameter, GLenum)
#include <oglplus/enums/patch_parameter.ipp>
OGLPLUS_ENUM_CLASS_END(PatchParameter)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/patch_parameter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/patch_parameter_range.ipp>
#endif

/// Alternate name for the PatchParameter enumeration
typedef PatchParameter PatchParam;

} // namespace oglplus

#endif // include guard
