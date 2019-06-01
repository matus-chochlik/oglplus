/**
 *  @file oglplus/limit_query.hpp
 *  @brief OpenGL min/max implementation-dependent limit queries
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_LIMIT_QUERY_1202091518_HPP
#define OGLPLUS_LIMIT_QUERY_1202091518_HPP

#include <oglplus/enums/limit_query.hpp>
#include <cstdint>

namespace oglplus {
namespace enums {
template <LimitQuery Query>
struct EnumAssocType<LimitQuery, Query> {
    using Type = int;
};
} // namespace enums

#if !OGLPLUS_NO_ENUM_VALUE_CLASSES
#include <oglplus/enums/limit_query_class.ipp>
#endif

} // namespace oglplus

#endif // include guard
