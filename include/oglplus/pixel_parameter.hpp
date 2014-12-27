/**
 *  @file oglplus/pixel_parameter.hpp
 *  @brief OpenGL pixel storage mode parameter names
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PIXEL_PARAMETER_1201200843_HPP
#define OGLPLUS_PIXEL_PARAMETER_1201200843_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Pixel storage mode parameter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PixelStore}
 *  @glfunref{ReadPixels}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PixelParameter, GLenum)
#include <oglplus/enums/pixel_parameter.ipp>
OGLPLUS_ENUM_CLASS_END(PixelParameter)

#include <oglplus/enums/pixel_parameter_type.ipp>

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/pixel_parameter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/pixel_parameter_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
