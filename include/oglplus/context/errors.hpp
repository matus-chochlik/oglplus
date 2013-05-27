/**
 *  @file oglplus/context/errors.hpp
 *  @brief Wrappers for error reporting operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONTEXT_ERRORS_1201040722_HPP
#define OGLPLUS_CONTEXT_ERRORS_1201040722_HPP

#include <oglplus/config_compiler.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/glfunc.hpp>

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

namespace context {

/// Wrapper for the error-reporting-related operations
/**
 *  @ingroup ogl_context
 */
class Errors
{
public:
	/// returns the error code
	/**
	 *  @glsymbols
	 *  @glfunref{GetError}
	 */
	static ErrorCode GetError(void)
	{
		return ErrorCode(OGLPLUS_GLFUNC(GetError)());
	}
};

} // namespace context
} // namespace oglplus

#endif // include guard
