/**
 *  @file oglplus/pixel_data.hpp
 *  @brief Pixel data-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PIXEL_DATA_1107121519_HPP
#define OGLPLUS_PIXEL_DATA_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// OpenGL pixel data type enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexImage1D}
 *  @glfunref{TexImage2D}
 *  @glfunref{TexImage3D}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PixelDataType, GLenum)
#include <oglplus/enums/pixel_data_type.ipp>
OGLPLUS_ENUM_CLASS_END(PixelDataType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/pixel_data_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/pixel_data_type_range.ipp>
#endif

/// OpenGL pixel data format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexImage1D}
 *  @glfunref{TexImage2D}
 *  @glfunref{TexImage3D}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PixelDataFormat, GLenum)
#include <oglplus/enums/pixel_data_format.ipp>
OGLPLUS_ENUM_CLASS_END(PixelDataFormat)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/pixel_data_format_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/pixel_data_format_range.ipp>
#endif

/// Alias for PixelDataFormat
/**
 *  @ingroup enumerations
 */
typedef PixelDataFormat Format;

/// OpenGL pixel data internal format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexImage1D}
 *  @glfunref{TexImage2D}
 *  @glfunref{TexImage3D}
 *  @glfunref{RenderbufferStorage}
 *  @glfunref{RenderbufferStorageMultisample}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PixelDataInternalFormat, GLenum)
#include <oglplus/enums/pixel_data_internal_format.ipp>
OGLPLUS_ENUM_CLASS_END(PixelDataInternalFormat)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/pixel_data_internal_format_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/pixel_data_internal_format_range.ipp>
#endif

/// Alias for PixelDataInternalFormat
/**
 *  @ingroup enumerations
 */
typedef PixelDataInternalFormat InternalFormat;

/// OpenGL image unit format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BindImageTexture}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ImageUnitFormat, GLenum)
#include <oglplus/enums/image_unit_format.ipp>
OGLPLUS_ENUM_CLASS_END(ImageUnitFormat)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/image_unit_format_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/image_unit_format_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
