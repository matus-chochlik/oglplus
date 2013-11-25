/**
 *  @file oglplus/compile_error.hpp
 *  @brief Shader compilation error exception
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_COMPILE_ERROR_1107121519_HPP
#define OGLPLUS_COMPILE_ERROR_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/string.hpp>

#include <cassert>

namespace oglplus {

/// Base class for SL compilation or linking errors
/**
 *  @ingroup error_handling
 */
class ProgramBuildError
 : public Error
{
private:
	String _log;
public:
	ProgramBuildError(
		const char* message,
		const String& log,
		const ErrorInfo& info
	): Error(0, message, info)
	 , _log(log)
	{ }

	~ProgramBuildError(void) throw()
	{ }

	/// Returns the compiler error output
	const String& Log(void) const
	{
		return _log;
	}
};

/// Exception class for OpenGL shading language compilation error
/**
 *  @ingroup error_handling
 */
class CompileError
 : public ProgramBuildError
{
public:
	CompileError(const String& log, const ErrorInfo& info);
};

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/compile_error.ipp>
#endif

#endif // include guard
