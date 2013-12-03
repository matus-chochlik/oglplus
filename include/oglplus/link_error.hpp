/**
 *  @file oglplus/link_error.hpp
 *  @brief Program linking and validation error exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_LINK_ERROR_1107121519_HPP
#define OGLPLUS_LINK_ERROR_1107121519_HPP

#include <oglplus/compile_error.hpp>
#include <oglplus/string.hpp>

namespace oglplus {

/// Exception class for OpenGL shading language program link error
/**
 *  @ingroup error_handling
 */
class LinkError
 : public ProgramBuildError
{
public:
	LinkError(const String& log, const ErrorInfo& info);
};

/// Exception class for OpenGL shading language program validation error
/**
 *  @ingroup error_handling
 */
class ValidationError
 : public ProgramBuildError
{
public:
	ValidationError(const String& log, const ErrorInfo& info);
};

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/link_error.ipp>
#endif

#endif // include guard
