/**
 *  @file oglplus/texture_wrap.hpp
 *  @brief Texture wrap enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_WRAP_1107121519_HPP
#define OGLPLUS_TEXTURE_WRAP_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Texture wrap parameter coordinate enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureWrapCoord, GLenum)
#include <oglplus/enums/texture_wrap_coord.ipp>
OGLPLUS_ENUM_CLASS_END(TextureWrapCoord)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_wrap_coord_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_wrap_coord_range.ipp>
#endif

/// Texture wrap enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{TexParameter}
 *  @glfunref{GetTexParameter}
 *  @gldefref{TEXTURE_WRAP_S}
 *  @gldefref{TEXTURE_WRAP_T}
 *  @gldefref{TEXTURE_WRAP_R}
 */
OGLPLUS_ENUM_CLASS_BEGIN(TextureWrap, GLenum)
#include <oglplus/enums/texture_wrap.ipp>
OGLPLUS_ENUM_CLASS_END(TextureWrap)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/texture_wrap_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/texture_wrap_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
