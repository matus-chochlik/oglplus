/**
 *  @file oglplus/access_specifier.hpp
 *  @brief Access type specifier enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ACCESS_SPECIFIER_1202231207_HPP
#define OGLPLUS_ACCESS_SPECIFIER_1202231207_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of access type specifiers
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BindImageTexture}
 */
OGLPLUS_ENUM_CLASS_BEGIN(AccessSpecifier, GLenum)
#include <oglplus/enums/access_specifier.ipp>
OGLPLUS_ENUM_CLASS_END(AccessSpecifier)

/// Alternate name for AccessSpecifier
/**
 *  @ingroup enumerations
 */
typedef AccessSpecifier Access;

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/access_specifier_names.ipp>
#endif

#if !OGLPLUS_NO_ENUM_VALUE_RANGES
#include <oglplus/enums/access_specifier_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
