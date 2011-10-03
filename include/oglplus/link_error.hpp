/**
 *  @file oglplus/link_error.hpp
 *  @brief Program linking end validation rror exception
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_LINK_ERROR_1107121519_HPP
#define OGLPLUS_LINK_ERROR_1107121519_HPP

#include <oglplus/compile_error.hpp>
#include <oglplus/string.hpp>

#include <cassert>

namespace oglplus {

/// Exception class for OpenGL shading language program link error
/**
 *  @ingroup error_handling
 */
class LinkError
 : public ProgramBuildError
{
public:
	LinkError(const String& log, const ErrorInfo& info)
	 : ProgramBuildError(
		"OpenGL shading language program link error",
		log,
		info
	)
	{ }
};

/// Exception class for OpenGL shading language program validation error
/**
 *  @ingroup error_handling
 */
class ValidationError
 : public ProgramBuildError
{
public:
	ValidationError(const String& log, const ErrorInfo& info)
	 : ProgramBuildError(
		"OpenGL shading language program validation error",
		log,
		info
	)
	{ }
};

} // namespace oglplus

#endif // include guard
