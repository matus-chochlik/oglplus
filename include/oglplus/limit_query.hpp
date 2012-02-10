/**
 *  @file oglplus/limit_query.hpp
 *  @brief OpenGL min/max implementation-dependent limit queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_LIMIT_QUERY_1202091518_HPP
#define OGLPLUS_LIMIT_QUERY_1202091518_HPP

#include <oglplus/config.hpp>

namespace oglplus {

/// Enumeration of implementation-dependent limit queries
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{LogicOp}
 */
enum class LimitQuery : GLenum
{
#include <oglplus/enums/limit_query.ipp>
};

inline const GLchar* EnumValueName(LimitQuery value)
{
#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/names/limit_query.ipp>
#endif
	return "";
}

/// Alternate name for the ColorLogicOperation enumeration
typedef ColorLogicOperation ColorLogicOp;

} // namespace oglplus

#endif // include guard
