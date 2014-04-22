/**
 *  @file oglplus/ext/ARB_robustness/reset_notif_strategy.hpp
 *  @brief Wrapper for the ARB_robustness graphics reset notification strategy
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_ARB_ROBUSTNESS_RESET_NOTIF_STRATEGY_1404220911_HPP
#define OGLPLUS_EXT_ARB_ROBUSTNESS_RESET_NOTIF_STRATEGY_1404220911_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Graphics reset notification strategy enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,robustness}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ResetNotificationStrategy, GLenum)
#include <oglplus/enums/ext/reset_notif_strategy.ipp>
OGLPLUS_ENUM_CLASS_END(ResetNotificationStrategy)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/reset_notif_strategy_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/reset_notif_strategy_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
