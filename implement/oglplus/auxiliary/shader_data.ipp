/**
 *  .file oglplus/auxiliary/shader_data.ipp
 *  .brief Implementation of shader data helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {
namespace aux {

OGLPLUS_LIB_FUNC
void ShaderDataSetUtils::_handle_error(
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
		ObjectDescRegistry<ProgramOps>::
			_get_desc(program)
	);
	HandleShaderVariableError(
		result,
		location,
		"Error setting shading program variable value",
		error_info,
		std::move(props)
	);
}

} // namespace aux
} // namespace oglplus

