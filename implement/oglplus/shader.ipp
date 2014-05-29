/**
 *  @file oglplus/shader.ipp
 *  @brief Implementation of Shader
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/detail/info_log.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

OGLPLUS_LIB_FUNC
String ObjectOps<tag::DirectState, tag::Shader>::
GetInfoLog(void) const
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
ObjectOps<tag::DirectState, tag::Shader>&
ObjectOps<tag::DirectState, tag::Shader>::
Compile(void)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(CompileShader)(_name);
	OGLPLUS_CHECK(
		CompileShader,
		ObjectError,
		Object(*this).
		EnumParam(Type())
	);
	OGLPLUS_HANDLE_ERROR_IF(
		!IsCompiled(),
		GL_INVALID_OPERATION,
		CompileError::Message(),
		CompileError,
		Log(GetInfoLog()).
		Object(*this).
		EnumParam(Type())
	);
	return *this;
}

} // namespace oglplus

