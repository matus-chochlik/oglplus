/**
 *  @file oglplus/shader.ipp
 *  @brief Implementation of Shader
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
String ShaderOps::GetInfoLog(void) const
{
	assert(_name != 0);
	return aux::GetInfoLog(
		_name, OGLPLUS_GLFUNC(GetShaderiv),
		OGLPLUS_GLFUNC(GetShaderInfoLog),
		"GetShaderiv",
		"GetShaderInfoLog"
	);
}

OGLPLUS_LIB_FUNC
void ShaderOps::HandleCompileError(void) const
{
	HandleBuildError<CompileError>(
		GetInfoLog(),
		OGLPLUS_OBJECT_ERROR_INFO(
			CompileShader,
			Shader,
			EnumValueName(Type()),
			_name
		)
	);
}

} // namespace oglplus

