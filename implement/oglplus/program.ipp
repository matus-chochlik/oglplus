/**
 *  @file oglplus/program.ipp
 *  @brief Implementation of Program
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_3

OGLPLUS_LIB_FUNC
GLenum ProgramResource::ReferencedByProperty(ShaderType shader_type) const
{
	if(shader_type == ShaderType::Vertex)
	{
		return GL_REFERENCED_BY_VERTEX_SHADER;
	}
	if(shader_type == ShaderType::TessControl)
	{
		return GL_REFERENCED_BY_TESS_CONTROL_SHADER;
	}
	if(shader_type == ShaderType::TessEvaluation)
	{
		return GL_REFERENCED_BY_TESS_EVALUATION_SHADER;
	}
	if(shader_type == ShaderType::Geometry)
	{
		return GL_REFERENCED_BY_GEOMETRY_SHADER;
	}
	if(shader_type == ShaderType::Fragment)
	{
		return GL_REFERENCED_BY_FRAGMENT_SHADER;
	}
	if(shader_type == ShaderType::Compute)
	{
		return GL_REFERENCED_BY_COMPUTE_SHADER;
	}
	return GL_NONE;
}

#endif // GL_VERSION_4_3

OGLPLUS_LIB_FUNC
void ProgramOps::HandleLinkError(void) const
{
	HandleBuildError<LinkError>(
		GetInfoLog(),
		OGLPLUS_OBJECT_ERROR_INFO(
			LinkProgram,
			Program,
			nullptr,
			_name
		)
	);
}

} // namespace oglplus

