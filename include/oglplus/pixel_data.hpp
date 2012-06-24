/**
 *  @file oglplus/pixel_data.hpp
 *  @brief Pixel data-related declarations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PIXEL_DATA_1107121519_HPP
#define OGLPLUS_PIXEL_DATA_1107121519_HPP

#include <oglplus/config.hpp>

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
enum class PixelDataType : GLenum
{
#include <oglplus/enums/pixel_data_type.ipp>
};

inline const GLchar* EnumValueName(PixelDataType value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_data_type.ipp>
#endif
	return "";
}

/// OpenGL pixel data format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexImage1D}
 *  @glfunref{TexImage2D}
 *  @glfunref{TexImage3D}
 */
enum class PixelDataFormat : GLenum
{
#include <oglplus/enums/pixel_data_format.ipp>
};

inline const GLchar* EnumValueName(PixelDataFormat value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_data_format.ipp>
#endif
	return "";
}

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
enum class PixelDataInternalFormat : GLenum
{
#include <oglplus/enums/pixel_data_internal_format.ipp>
};

inline const GLchar* EnumValueName(PixelDataInternalFormat value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_data_internal_format.ipp>
#endif
	return "";
}

/// OpenGL image unit format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BindImageTexture}
 */
enum class ImageUnitFormat : GLenum
{
#include <oglplus/enums/image_unit_format.ipp>
};

inline const GLchar* EnumValueName(ImageUnitFormat value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/image_unit_format.ipp>
#endif
	return "";
}

} // namespace oglplus

#endif // include guard
