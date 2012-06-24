/**
 *  @file oglplus/string_query.hpp
 *  @brief OpenGL string query enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_STRING_QUERY_1202210916_HPP
#define OGLPLUS_STRING_QUERY_1202210916_HPP

namespace oglplus {

/// OpenGL string query enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{GetString}
 */
enum class StringQuery : GLenum
{
#include <oglplus/enums/string_query.ipp>
};

inline const GLchar* EnumValueName(StringQuery value)
OGLPLUS_NOEXCEPT(true)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/string_query.ipp>
#endif
	return "";
}

} // namespace oglplus

#endif // include guard
