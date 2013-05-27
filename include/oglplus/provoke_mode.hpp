/**
 *  @file oglplus/provoke_mode.hpp
 *  @brief OpenGL provoking vertex mode enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROVOKE_MODE_1201041118_HPP
#define OGLPLUS_PROVOKE_MODE_1201041118_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Provoking vertex selection mode (for flatshading) enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{ProvokingVertex}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ProvokeMode, GLenum)
#include <oglplus/enums/provoke_mode.ipp>
OGLPLUS_ENUM_CLASS_END(ProvokeMode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/provoke_mode_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/provoke_mode_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
