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
 *  There are also some syntax-sugar operators defined for Capability
 *  so it can be used in the following ways:
 *  @code
 *  oglplus::Context gl;
 *  // to enable the depth test capability:
 *  gl.Enable(Capability::DepthTest);
 *  // or
 *  Capability::DepthTest << true;
 *  // or
 *  +Capability::DepthTest;
 *
 *  // to disable this capability:
 *  gl.Disable(Capability::DepthTest);
 *  // or
 *  Capability::DepthTest << false;
 *  // or
 *  -Capability::DepthTest;
 *  @endcode
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

inline void operator << (Capability capability, bool enable)
{
	if(enable)
	{
		OGLPLUS_GLFUNC(Enable)(GLenum(capability));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Enable));
	}
	else
	{
		OGLPLUS_GLFUNC(Disable)(GLenum(capability));
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
	}
}

inline void operator + (Capability capability)
{
	OGLPLUS_GLFUNC(Enable)(GLenum(capability));
	OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Enable));
}

inline void operator - (Capability capability)
{
	OGLPLUS_GLFUNC(Disable)(GLenum(capability));
	OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
}

/// Functionality enumeration
/** Functionalities are similar to capabilities in that they can be
 *  enabled or disabled by the
 *  @ref oglplus::context::Capabilities::Enable() "Enable",
 *  @ref oglplus::context::Capabilities::Disable() "Disable" and
 *  @ref oglplus::context::Capabilities::IsEnabled() "IsEnabled"
 *  member functions of the Context class.
 *
 *  The difference between them is that functionalities
 *  have multiple 0-based-indexed 'slots' that can be enabled or disabled.
 *  One example of Functionality is ClipDistance where the i-th 'slot' enabled
 *  the i-th clipping plane.
 *
 *  There are also some syntax-sugar operators defined for Functionality
 *  so it can be used in the following ways:
 *  @code
 *  oglplus::Context gl;
 *  // to enable the second clipping plane
 *  gl.Enable(Functionality::ClipDistance, 2);
 *  // or
 *  (Functionality::ClipDistance|2) << true;
 *  // or
 *  +(Functionality::ClipDistance|2);
 *
 *  // to disable the i-th clip plane:
 *  int i = 3;
 *  gl.Disable(Functionality::ClipDistance, i);
 *  // or
 *  (Functionality::ClipDistance|i) << false;
 *  // or
 *  -(Functionality::ClipDistance|i);
 *  @endcode
 *
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

struct FunctionalityAndNumber
{
	GLenum _code;
};

inline FunctionalityAndNumber operator | (Functionality func, GLuint number)
{
	FunctionalityAndNumber result = { GLenum(func)+number };
	return result;
}

inline void operator << (FunctionalityAndNumber func_and_num, bool enable)
{
	if(enable)
	{
		OGLPLUS_GLFUNC(Enable)(func_and_num._code);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Enable));
	}
	else
	{
		OGLPLUS_GLFUNC(Disable)(func_and_num._code);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
	}
}

inline void operator + (FunctionalityAndNumber func_and_num)
{
	OGLPLUS_GLFUNC(Enable)(func_and_num._code);
	OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Enable));
}

inline void operator - (FunctionalityAndNumber func_and_num)
{
	OGLPLUS_GLFUNC(Disable)(func_and_num._code);
	OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(Disable));
}

} // namespace oglplus

#endif // include guard
