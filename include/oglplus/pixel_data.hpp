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
OGLPLUS_ENUM_CLASS_BEGIN(PixelDataType, GLenum)
#include <oglplus/enums/pixel_data_type.ipp>
OGLPLUS_ENUM_CLASS_END

inline StrLit EnumValueName(PixelDataType value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_data_type.ipp>
#endif
	return StrLit();
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
OGLPLUS_ENUM_CLASS_BEGIN(PixelDataFormat, GLenum)
#include <oglplus/enums/pixel_data_format.ipp>
OGLPLUS_ENUM_CLASS_END

inline StrLit EnumValueName(PixelDataFormat value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_data_format.ipp>
#endif
	return StrLit();
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
OGLPLUS_ENUM_CLASS_BEGIN(PixelDataInternalFormat, GLenum)
#include <oglplus/enums/pixel_data_internal_format.ipp>
OGLPLUS_ENUM_CLASS_END

inline StrLit EnumValueName(PixelDataInternalFormat value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_data_internal_format.ipp>
#endif
	return StrLit();
}

/// OpenGL image unit format enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BindImageTexture}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ImageUnitFormat, GLenum)
#include <oglplus/enums/image_unit_format.ipp>
OGLPLUS_ENUM_CLASS_END

inline StrLit EnumValueName(ImageUnitFormat value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/image_unit_format.ipp>
#endif
	return StrLit();
}

} // namespace oglplus

#endif // include guard
