/**
 *  @file oglplus/limit_query.hpp
 *  @brief OpenGL min/max implementation-dependent limit queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_LIMIT_QUERY_1202091518_HPP
#define OGLPLUS_LIMIT_QUERY_1202091518_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of implementation-dependent limit queries
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{LogicOp}
 */
OGLPLUS_ENUM_CLASS_BEGIN(LimitQuery, GLenum)
#include <oglplus/enums/limit_query.ipp>
OGLPLUS_ENUM_CLASS_END(LimitQuery)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/limit_query_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/limit_query_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
