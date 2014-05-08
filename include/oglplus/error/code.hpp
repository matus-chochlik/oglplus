/**
 *  @file oglplus/error/code.hpp
 *  @brief Enumeration of error-codes
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_CODE_1405082311_HPP
#define OGLPLUS_ERROR_CODE_1405082311_HPP

#include <oglplus/enumerations.hpp>

namespace oglplus {

/// Error code enumeration
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glfunref{GetError}
 */
OGLPLUS_ENUM_CLASS_BEGIN(ErrorCode, GLenum)
#include <oglplus/enums/error_code.ipp>
OGLPLUS_ENUM_CLASS_END(ErrorCode)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/error_code_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/error_code_range.ipp>
#endif

} // namespace oglplus

#endif // include guard
