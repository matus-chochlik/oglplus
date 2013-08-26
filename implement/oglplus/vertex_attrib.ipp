/**
 *  @file oglplus/vertex_attrib.ipp
 *  @brief Implementation of VertexAttrib functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
void VertexAttribOps::_handle_inactive(
	const ProgramOps& program,
	const GLchar* identifier,
	GLint result
)
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
		DescriptionOf(program)
	);
	HandleShaderVariableError(
		GL_INVALID_OPERATION,
		result,
		"Getting the location of inactive vertex attrib",
		OGLPLUS_ERROR_INFO(GetAttribLocation),
		std::move(props)
	);
}

OGLPLUS_LIB_FUNC
void VertexAttribOps::_handle_inconsistent_location(
	const GLchar* identifier,
	VertexAttribSlot location
)
{
	Error::PropertyMapInit props;
	Error::AddPropertyValue(
		props,
		"identifier",
		identifier
	);
	HandleShaderVariableError(
		GL_INVALID_OPERATION,
		GLint(location),
		"Inconsistent location of a vertex "
		"attribute in multiple programs",
		OGLPLUS_ERROR_INFO(GetAttribLocation),
		std::move(props)
	);
}

} // namespace oglplus

