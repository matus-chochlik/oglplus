/**
 *  @file oglplus/auxiliary/uniform_init.ipp
 *  @brief Implementation of uniform variable initialization helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/error.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {
namespace aux {

OGLPLUS_LIB_FUNC
void UniformInitOps::_handle_error(
	GLuint program,
	const GLchar* identifier,
	GLint location
) const
{
	Error::PropertyMapInit props;
	Error::AddPropertyValue(
		props,
		"identifier",
		identifier
	);
	Error::AddPropertyValue(
		props,
		"program",
		aux::ObjectDescRegistry<ProgramOps>::
				_get_desc(program)
	);
	HandleShaderVariableError(
		GL_INVALID_OPERATION,
		location,
		"Getting the location of inactive uniform",
		OGLPLUS_ERROR_INFO(GetUniformLocation),
		std::move(props)
	);
}

} // namespace aux
} // namespace oglplus

