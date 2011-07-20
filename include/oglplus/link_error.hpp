/**
 *  @file oglplus/link_error.hpp
 *  @brief Program linking error exception
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

#include <string>
#include <cassert>

namespace oglplus {

/// Exception class for OpenGL shading language program link error
class LinkError
 : public CompileOrLinkError
{
public:
	LinkError(const std::string& log, const ErrorInfo& info)
	 : CompileOrLinkError(
		"OpenGL shading language link error",
		log,
		info
	)
	{ }
};

} // namespace oglplus

#endif // include guard
