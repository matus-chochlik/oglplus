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

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/object/desc.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

OGLPLUS_LIB_FUNC
void VertexAttribOps::
_handle_inactive(
	ProgramName program,
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
void VertexAttribOps::
_handle_inconsistent_location(
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

GLint _get_location(ProgramName, const GLchar*)
{
	return 0; //TODO
}

OGLPLUS_LIB_FUNC
GLint VertexAttribOps::
_find_location(
	ProgramName program,
	const GLchar* identifier
)
{
	GLint result = _get_location(program, identifier);
	OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetAttribLocation));
	if(OGLPLUS_IS_ERROR(result == GLint(-1)))
	{
		_handle_inactive(program, identifier, result);
	}
	return result;
}

OGLPLUS_LIB_FUNC
bool VertexAttribOps::
_query_location(
	ProgramName program,
	const String& identifier,
	VertexAttribSlot& location
)
{
	GLint result = _get_location(program, identifier.c_str());
	if(OGLPLUS_GLFUNC(GetError)() != GL_NO_ERROR)
		return false;
	if(result < 0) return false;
	location = result;
	return true;
}

OGLPLUS_LIB_FUNC
bool VertexAttribOps::
_query_common_location(
	const Sequence<ProgramName>& programs,
	const GLchar* identifier,
	VertexAttribSlot& location
)
{
	if(std::size_t n=programs.size())
	{
		if(!_query_location(
			programs[0],
			identifier,
			location
		)) return false;

		const VertexAttribSlot prev_loc(location);

		for(std::size_t i=1; i!=n; ++i)
		{
			if(!_query_location(
				programs[i],
				identifier,
				location
			)) return false;

			if(prev_loc != location)
				return false;
		}
		return true;
	}
	return false;
}

OGLPLUS_LIB_FUNC
VertexAttribSlot VertexAttribOps::
_get_common_location(
	const Sequence<ProgramName>& programs,
	const GLchar* identifier
)
{
	VertexAttribSlot location;

	bool queried = _query_common_location(programs, identifier, location);

	if(OGLPLUS_IS_ERROR(!queried))
	{
		_handle_inconsistent_location(identifier, location);
	}
	return location;
}

} // namespace oglplus

