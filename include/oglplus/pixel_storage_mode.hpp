/**
 *  @file oglplus/pixel_storage_mode.hpp
 *  @brief OpenGL pixel storage mode parameter names
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PIXEL_STORAGE_MODE_1201200843_HPP
#define OGLPLUS_PIXEL_STORAGE_MODE_1201200843_HPP

namespace oglplus {

/// Pixel storage mode parameter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PixelStore}
 *  @glfunref{ReadPixels}
 */
enum class PixelStorageMode : GLenum
{
#include <oglplus/enums/pixel_storage_mode.ipp>
};

inline const GLchar* EnumValueName(PixelStorageMode value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/pixel_storage_mode.ipp>
#endif
	return "";
}

} // namespace oglplus

#endif // include guard
