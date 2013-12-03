/**
 *  @file oglplus/compile_error.ipp
 *  @brief Implementation of GLSL compile error exception
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
CompileError::CompileError(const String& log, const ErrorInfo& info)
 : ProgramBuildError(
	"OpenGL shading language compilation error",
	log,
	info
)
{ }

} // namespace oglplus

