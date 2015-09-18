/**
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define OGLPLUS_CONFIG_QUERY_GL_VER_MAJOR 3
#define OGLPLUS_CONFIG_QUERY_GL_VER_MINOR 2

#include "init_GL.ipp"
#include "has_GL_ARB_separate_shader_objects.ipp"

bool do_query_gl(void)
{
	if(!does_have_ARB_separate_shader_objects())
	{
		return false;
	}

	unsigned missing_gl_symbols = 0;
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1i);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2i);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3i);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4i);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1f);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2f);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3f);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4f);

	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glUseProgramStages);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glActiveShaderProgram);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glCreateShaderProgramv);

	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glGenProgramPipelines);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glDeleteProgramPipelines);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glIsProgramPipeline);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glBindProgramPipeline);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glGetProgramPipelineInfoLog);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glValidateProgramPipeline);
	return missing_gl_symbols == 0;
}
