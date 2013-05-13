/**
 *  @file oglplus/hint.hpp
 *  @brief Enumeration of hint targets and options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_HINT_1201201108_HPP
#define OGLPLUS_HINT_1201201108_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of hint targets
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Hint}
 */
OGLPLUS_ENUM_CLASS_BEGIN(HintTarget, GLenum)
#include <oglplus/enums/hint_target.ipp>
OGLPLUS_ENUM_CLASS_END(HintTarget)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/hint_target_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/hint_target_range.ipp>
#endif

/// Enumeration of hint options
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{Hint}
 */
OGLPLUS_ENUM_CLASS_BEGIN(HintOption, GLenum)
#include <oglplus/enums/hint_option.ipp>
OGLPLUS_ENUM_CLASS_END(HintOption)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/hint_option_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/hint_option_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
