/**
 *  @file oglplus/capability.hpp
 *  @brief Enumeration of OpenGL capabilities that can be Enabled/Disabled
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CAPABILITY_1107121519_HPP
#define OGLPLUS_CAPABILITY_1107121519_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Capability enumeration
/** This enumaration lists capabilities i.e. features that can
 *  be enabled, disabled or queried by the
 *  @ref oglplus::context::Capabilities::Enable() "Enable",
 *  @ref oglplus::context::Capabilities::Disable() "Disable" and
 *  @ref oglplus::context::Capabilities::IsEnabled() "IsEnabled"
 *  member functions of the Context class.
 *
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Enable}
 *  @glfunref{Disable}
 *  @glfunref{IsEnabled}
 */
OGLPLUS_ENUM_CLASS_BEGIN(Capability, GLenum)
#include <oglplus/enums/capability.ipp>
OGLPLUS_ENUM_CLASS_END(Capability)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/capability_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/capability_range.ipp>
#endif

/// Functionality enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Enable}
 *  @glfunref{Disable}
 *  @glfunref{IsEnabled}
 */
OGLPLUS_ENUM_CLASS_BEGIN(Functionality, GLenum)
#include <oglplus/enums/functionality.ipp>
OGLPLUS_ENUM_CLASS_END(Functionality)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/functionality_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/functionality_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
