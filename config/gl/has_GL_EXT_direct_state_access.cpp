/**
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define OGLPLUS_CONFIG_QUERY_GL_VER_MAJOR 3
#define OGLPLUS_CONFIG_QUERY_GL_VER_MINOR 2

#include "init_GL.ipp"
#include "has_GL_EXT_direct_state_access.ipp"

bool do_query_gl(void)
{
	if(!does_have_EXT_direct_state_access())
	{
		return false;
	}

	unsigned missing_gl_symbols = 0;

	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1iEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2iEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3iEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4iEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1uiEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2uiEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3uiEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4uiEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1fEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2fEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3fEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4fEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1dEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2dEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3dEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4dEXT);

	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1ivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2ivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3ivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4ivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1uivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2uivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3uivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4uivEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform1dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform2dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform3dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniform4dvEXT);

	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix2fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix2x3fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix2x4fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix3x2fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix3fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix3x4fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix4x2fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix4x3fvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix4fvEXT);

	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix2dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix2x3dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix2x4dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix3x2dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix3dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix3x4dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix4x2dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix4x3dvEXT);
	OGLPLUS_CONFIG_ASSERT_GL_FUNC(glProgramUniformMatrix4dvEXT);

	return missing_gl_symbols == 0;
}
