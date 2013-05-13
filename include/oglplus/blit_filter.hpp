/**
 *  @file oglplus/blit_filter.hpp
 *  @brief Enumeration of Blit operation filtering modes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BLIT_FILTER_1201201108_HPP
#define OGLPLUS_BLIT_FILTER_1201201108_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Enumeration of blit operation filtering modes
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{BlitFramebuffer}
 */
OGLPLUS_ENUM_CLASS_BEGIN(BlitFilter, GLenum)
#include <oglplus/enums/blit_filter.ipp>
OGLPLUS_ENUM_CLASS_END(BlitFilter)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/blit_filter_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/blit_filter_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
