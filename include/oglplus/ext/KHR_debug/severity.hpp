/**
 *  @file oglplus/ext/KHR_debug/severity.hpp
 *  @brief The DebugSeverity enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_KHR_DEBUG_SEVERITY_1308270710_HPP
#define OGLPLUS_EXT_KHR_DEBUG_SEVERITY_1308270710_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Debug output severity enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{KHR,debug}
 */
OGLPLUS_ENUM_CLASS_BEGIN(DebugSeverity, GLenum)
#include <oglplus/enums/ext/debug_severity.ipp>
OGLPLUS_ENUM_CLASS_END(DebugSeverity)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/debug_severity_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/debug_severity_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
