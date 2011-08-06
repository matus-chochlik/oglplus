/**
 *  @file oglplus/compile_error.hpp
 *  @brief Shader compilation error exception
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_COMPILE_ERROR_1107121519_HPP
#define OGLPLUS_COMPILE_ERROR_1107121519_HPP

#include <oglplus/error.hpp>

#include <string>
#include <cassert>

namespace oglplus {

/// Base class for SL compilation or linking errors
class ProgramBuildError
 : public Error
{
private:
	std::string _log;
public:
	ProgramBuildError(
		const char* what,
		const std::string& log,
		const ErrorInfo& info
	): Error(0, what, info)
	 , _log(log)
	{ }

	~ProgramBuildError(void) throw()
	{ }

	/// Returns the compiler error output
	const std::string& Log(void) const
	{
		return _log;
	}
};

/// Exception class for OpenGL shading language compilation error
class CompileError
 : public ProgramBuildError
{
public:
	CompileError(const std::string& log, const ErrorInfo& info)
	 : ProgramBuildError(
		"OpenGL shading language compilation error",
		log,
		info
	)
	{ }
};

} // namespace oglplus

#endif // include guard
