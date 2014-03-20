/**
 *  @file oglplus/ext/ARB_compatibility/attrib_group.hpp
 *  @brief The CompatibilityAttributeGroup enumerations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_ARB_COMPATIBILITY_ATTRIB_GROUP_1203031902_HPP
#define OGLPLUS_EXT_ARB_COMPATIBILITY_ATTRIB_GROUP_1203031902_HPP

#include <oglplus/enumerations.hpp>
#include <oglplus/bitfield.hpp>

namespace oglplus {

/// Compatibility server context attribute bits enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PushAttrib}
 *  @glfunref{PopAttrib}
 *  @glextref{ARB,compatibility}
 */
OGLPLUS_ENUM_CLASS_BEGIN(CompatibilityAttributeGroup, GLbitfield)
#include <oglplus/enums/ext/compat_attrib_group.ipp>
OGLPLUS_ENUM_CLASS_END(CompatibilityAttributeGroup)

OGLPLUS_MAKE_BITFIELD(CompatibilityAttributeGroup)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/compat_attrib_group_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/compat_attrib_group_range.ipp>
#endif

/// Compatibility client context attribute bits enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{PushClientAttrib}
 *  @glfunref{PopClientAttrib}
 *  @glextref{ARB,compatibility}
 */
OGLPLUS_ENUM_CLASS_BEGIN(CompatibilityClientAttributeGroup, GLbitfield)
#include <oglplus/enums/ext/compat_client_attrib_group.ipp>
OGLPLUS_ENUM_CLASS_END(CompatibilityClientAttributeGroup)

OGLPLUS_MAKE_BITFIELD(CompatibilityClientAttributeGroup)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/compat_client_attrib_group_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/compat_client_attrib_group_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
