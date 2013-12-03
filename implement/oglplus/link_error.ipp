/**
 *  @file oglplus/link_error.ipp
 *  @brief Implementation of 
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
LinkError::LinkError(const String& log, const ErrorInfo& info)
 : ProgramBuildError(
	"OpenGL shading language program link error",
	log,
	info
)
{ }

OGLPLUS_LIB_FUNC
ValidationError::ValidationError(const String& log, const ErrorInfo& info)
 : ProgramBuildError(
	"OpenGL shading language program validation error",
	log,
	info
)
{ }

} // namespace oglplus

