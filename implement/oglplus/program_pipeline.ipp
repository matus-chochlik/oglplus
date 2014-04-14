/**
 *  @file oglplus/program_pipeline.ipp
 *  @brief Implementation of ProgramPipeline functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_separate_shader_objects

OGLPLUS_LIB_FUNC
GLenum ProgramPipelineOps::_binding_query(Target)
{
	return GL_PROGRAM_PIPELINE_BINDING;
}

OGLPLUS_LIB_FUNC
String ProgramPipelineOps::GetInfoLog(void) const
{
	assert(_name != 0);
	return aux::GetInfoLog(
		_name, OGLPLUS_GLFUNC(GetProgramPipelineiv),
		OGLPLUS_GLFUNC(GetProgramPipelineInfoLog),
		"GetProgramPipelineiv",
		"GetProgramPipelineInfoLog"
	);
}

OGLPLUS_LIB_FUNC
void ProgramPipelineOps::HandleValidationError(void) const
{
	HandleBuildError<ValidationError>(
		GetInfoLog(),
		OGLPLUS_OBJECT_ERROR_INFO(
			ValidateProgramPipeline,
			ProgramPipeline,
			nullptr,
			_name
		)
	);
}

#endif // program pipeline

} // namespace oglplus

