/**
 *  @file oglplus/uniform_block.ipp
 *  @brief Implementation of UniformBlock
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_uniform_buffer_object

namespace aux {

OGLPLUS_LIB_FUNC
void UniformBlockInitOps::_handle_error(
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
		"Getting the location of inactive uniform block",
		OGLPLUS_ERROR_INFO(GetUniformBlockIndex),
		std::move(props)
	);
}

OGLPLUS_LIB_FUNC
GLenum _translate_ref(ShaderType shader_type)
{
	switch(shader_type)
	{
#ifdef GL_VERTEX_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex):
		return GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER;
#endif
#ifdef GL_TESS_CONTROL_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl):
		return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER;
#endif
#ifdef GL_TESS_EVALUATION_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation):
		return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER;
#endif
#ifdef GL_GEOMETRY_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry):
		return GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER;
#endif
#ifdef GL_FRAGMENT_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment):
		return GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER;
#endif
#ifdef GL_COMPUTE_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Compute):
		return GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER;
#endif
	}
	return 0;
}

OGLPLUS_LIB_FUNC
GLenum _translate_max(ShaderType shader_type)
{
	switch(shader_type)
	{
#ifdef GL_VERTEX_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex):
		return GL_MAX_VERTEX_UNIFORM_BLOCKS;
#endif
#ifdef GL_TESS_CONTROL_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl):
		return GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS;
#endif
#ifdef GL_TESS_EVALUATION_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation):
		return GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS;
#endif
#ifdef GL_GEOMETRY_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry):
		return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
#endif
#ifdef GL_FRAGMENT_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment):
		return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
#endif
#ifdef GL_COMPUTE_SHADER
		case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Compute):
		return GL_MAX_COMPUTE_UNIFORM_BLOCKS;
#endif
	}
	return 0;
}

} // namespace aux

#endif // uniform buffer object

} // namespace oglplus

