/**
 *  @file oglplus/object/type.hpp
 *  @brief ObjectType enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_TYPE_1405022040_HPP
#define OGLPLUS_OBJECT_TYPE_1405022040_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of object types
/**
 *  @ingroup enumerations
 */
OGLPLUS_ENUM_CLASS_BEGIN(ObjectType, GLenum)
#include <oglplus/enums/object_type.ipp>
OGLPLUS_ENUM_CLASS_END(ObjectType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/object_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/object_type_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
