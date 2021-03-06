/**
 *  @file oalplus/object/name.hpp
 *  @brief Base class for OpenAL "named" objects
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_OBJECT_NAME_1107121519_HPP
#define OALPLUS_OBJECT_NAME_1107121519_HPP

#include <oglplus/object/name_tpl.hpp>
#include <oalplus/object/tags.hpp>

namespace oalplus {

using oglplus::ObjectName;

using SourceName = ObjectName<tag::Source>;
using BufferName = ObjectName<tag::Buffer>;

/// Returns the ALuint OpenAL name assigned to @p named object
template <typename ObjTag>
inline ALuint GetALName(ObjectName<ObjTag> named) noexcept {
    return GetName(named);
}

} // namespace oalplus

#endif // include guard
