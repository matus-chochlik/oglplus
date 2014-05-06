/**
 *  .file oglplus/prog_var/set_ops.ipp
 *  .brief Implementation of GPU program variable helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/desc.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

OGLPLUS_LIB_FUNC
void ProgVarSetUtils::_handle_error(
	const oglplus::ErrorInfo& error_info,
	GLuint program,
	GLuint location,
	GLenum result
)
{
	Error::PropertyMapInit props;
	Error::AddPropertyValue(
		props,
		"program",
		DescriptionOf(ProgramName(program))
	);
	HandleShaderVariableError(
		result,
		location,
		"Error setting shading program variable value",
		error_info,
		std::move(props)
	);
}

} // namespace oglplus

