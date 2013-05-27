/**
 *  @file oglplus/pixel_storage_mode.hpp
 *  @brief OpenGL pixel storage mode parameter names
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PIXEL_STORAGE_MODE_1201200843_HPP
#define OGLPLUS_PIXEL_STORAGE_MODE_1201200843_HPP

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
OGLPLUS_ENUM_CLASS_BEGIN(PixelStorageMode, GLenum)
#include <oglplus/enums/pixel_storage_mode.ipp>
OGLPLUS_ENUM_CLASS_END(PixelStorageMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/pixel_storage_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/pixel_storage_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
