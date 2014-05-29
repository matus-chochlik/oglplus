/**
 *  @file oglplus/ext/KHR_debug/source.hpp
 *  @brief The DebugSource enumeration
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_KHR_DEBUG_SOURCE_1308270710_HPP
#define OGLPLUS_EXT_KHR_DEBUG_SOURCE_1308270710_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Debug output source enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{KHR,debug}
 */
OGLPLUS_ENUM_CLASS_BEGIN(DebugSource, GLenum)
#include <oglplus/enums/ext/debug_source.ipp>
OGLPLUS_ENUM_CLASS_END(DebugSource)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/debug_source_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/debug_source_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
