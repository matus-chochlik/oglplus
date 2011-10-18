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
 */
enum class PixelDataType : GLenum
{
#include <oglplus/enums/pixel_data_type.ipp>
};

/// OpenGL pixel data format enumeration
/**
 *  @ingroup enumerations
 */
enum class PixelDataFormat : GLenum
{
#include <oglplus/enums/pixel_data_format.ipp>
};

/// OpenGL pixel data internal format enumeration
/**
 *  @ingroup enumerations
 */
enum class PixelDataInternalFormat : GLenum
{
#include <oglplus/enums/pixel_data_internal_format.ipp>
};

} // namespace oglplus

#endif // include guard
