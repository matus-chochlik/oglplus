/**
 *  @file oglplus/access_specifier.hpp
 *  @brief Access type specifier enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ACCESS_SPECIFIER_1202231207_HPP
#define OGLPLUS_ACCESS_SPECIFIER_1202231207_HPP

namespace oglplus {

/// Enumeration of access type specifiers
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BindImageTexture}
 */
enum class AccessSpecifier : GLenum
{
#include <oglplus/enums/access_specifier.ipp>
};

/// Alternate name for AccessSpecifier
/**
 *  @ingroup enumerations
 */
typedef AccessSpecifier Access;

inline const GLchar* EnumValueName(AccessSpecifier value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/access_specifier.ipp>
#endif
	return "";
}

} // namespace oglplus

#endif // include guard
