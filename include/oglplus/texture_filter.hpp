/**
 *  @file oglplus/texture_filter.hpp
 *  @brief Texture magnification/minification filter enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_FILTER_1107121519_HPP
#define OGLPLUS_TEXTURE_FILTER_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Texture filter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @gldefref{TEXTURE_MAG_FILTER}
 *  @gldefref{TEXTURE_MIN_FILTER}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureFilter, GLenum)
#include <oglplus/enums/texture_filter.ipp>
OGLPLUS_ENUM_CLASS_END(TextureFilter)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_filter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_filter_range.ipp>
#endif

/// Texture magnification filter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_MAG_FILTER}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureMagFilter, GLenum)
#include <oglplus/enums/texture_mag_filter.ipp>
OGLPLUS_ENUM_CLASS_END(TextureMagFilter)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_mag_filter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_mag_filter_range.ipp>
#endif

/// Texture minification filter enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_MIN_FILTER}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureMinFilter, GLenum)
#include <oglplus/enums/texture_min_filter.ipp>
OGLPLUS_ENUM_CLASS_END(TextureMinFilter)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_min_filter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_min_filter_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
