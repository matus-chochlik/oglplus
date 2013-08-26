/**
 *  @file oglplus/uniform_subroutines.ipp
 *  @brief Implementation of Subroutine uniform functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine

namespace aux {

OGLPLUS_LIB_FUNC
void SubroutineUniformInitOps::_handle_error(
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
		"stage",
		EnumValueName(_stage)
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
		OGLPLUS_ERROR_INFO(GetSubroutineUniformLocation),
		std::move(props)
	);
}

OGLPLUS_LIB_FUNC
void SubroutineInitOps::_handle_error(
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
		"Getting the location of inactive subroutine",
		OGLPLUS_ERROR_INFO(GetSubroutineIndex),
		std::move(props)
	);
}

} // namespace aux

#endif

} // namespace oglplus

