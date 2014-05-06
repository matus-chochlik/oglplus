/**
 *  @file oglplus/uniform.ipp
 *  @brief Implementation of Uniform functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/error.hpp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/desc.hpp>
#include <oglplus/lib/incl_end.ipp>
#include <cstring>

namespace oglplus {

OGLPLUS_LIB_FUNC
GLenum ProgVarTypeOps<tag::Uniform>::
GetType(GLuint program, GLint /*location*/, const GLchar* identifier)
{

	GLenum type, result = GL_NONE;
	GLint size;
	GLsizei length = 0;
	const GLsizei id_len = std::strlen(identifier);
	// The +2 is intentional
	// to distinguish between the searched identifier
	// and the identifiers having the searched identifier
	// as prefix
	std::vector<GLchar> buffer(id_len+2);

	GLint active_uniforms = 0;
	OGLPLUS_GLFUNC(GetProgramiv)(
		program,
		GL_ACTIVE_UNIFORMS,
		&active_uniforms
	);
	OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetProgramiv));

	for(GLint index=0; index!=active_uniforms; ++index)
	{
		OGLPLUS_GLFUNC(GetActiveUniform)(
			program,
			index,
			buffer.size(),
			&length,
			&size,
			&type,
			buffer.data()
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetActiveUniform));
		if(id_len == length)
		{
			if(std::strncmp(
				identifier,
				buffer.data(),
				length
			) == 0)
			{
				result = type;
				break;
			}
		}
	}
	return result;
}

} // namespace oglplus

