/**
 *  @file oglplus/ext/ARB_debug_output/severity.hpp
 *  @brief The DebugOutputARBSeverity enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_ARB_DEBUG_OUTPUT_SEVERITY_1203031902_HPP
#define OGLPLUS_EXT_ARB_DEBUG_OUTPUT_SEVERITY_1203031902_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Debug output severity enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{ARB,debug_output}
 */
OGLPLUS_ENUM_CLASS_BEGIN(DebugOutputARBSeverity, GLenum)
#include <oglplus/enums/ext/debug_output_severity.ipp>
OGLPLUS_ENUM_CLASS_END(DebugOutputARBSeverity)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/debug_output_severity_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/debug_output_severity_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
