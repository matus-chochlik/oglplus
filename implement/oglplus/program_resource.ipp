/**
 *  @file oglplus/program_resource.ipp
 *  @brief Implementation of ProgramResource functions
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

OGLPLUS_LIB_FUNC
ProgramResource::ProgramResource(
	aux::ProgramInterfaceContext& context,
	GLuint index
): _program(context.Program())
 , _interface(context.Interface())
 , _index(index)
{
	GLsizei bufsize = context.Buffer().size();
	if(bufsize != 0)
	{
		GLsizei length = 0;
		OGLPLUS_GLFUNC(GetProgramResourceName)(
			_program,
			_interface,
			_index,
			bufsize,
			&length,
			context.Buffer().data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetProgramResourceName));
		_name.assign(context.Buffer().data(), length);
	}
}

#endif // GL_VERSION_4_3

} // namespace oglplus

