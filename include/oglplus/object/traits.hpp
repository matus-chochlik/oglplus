/**
 *  @file oglplus/object/traits.hpp
 *  @brief GL Object trait templates.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_TRAITS_1405011014_HPP
#define OGLPLUS_OBJECT_TRAITS_1405011014_HPP

#include <type_traits>

namespace oglplus {

// indicates if
template <typename ObjTag>
struct IsMultiObject
 : std::true_type
{ };

} // namespace oglplus

#endif // include guard
