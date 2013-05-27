/**
 *  @file oglplus/polygon_mode.hpp
 *  @brief OpenGL polygon rasterization mode-related enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_POLYGON_MODE_1107121519_HPP
#define OGLPLUS_POLYGON_MODE_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Polygon rasterization mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PolygonMode}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PolygonMode, GLenum)
#include <oglplus/enums/polygon_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PolygonMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/polygon_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/polygon_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
