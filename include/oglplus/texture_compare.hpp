/**
 *  @file oglplus/texture.hpp
 *  @brief Texture compare mode enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_COMPARE_1107121519_HPP
#define OGLPLUS_TEXTURE_COMPARE_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Texture compare mode enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_COMPARE_MODE}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureCompareMode, GLenum)
#include <oglplus/enums/texture_compare_mode.ipp>
OGLPLUS_ENUM_CLASS_END(TextureCompareMode)


#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_compare_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_compare_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
