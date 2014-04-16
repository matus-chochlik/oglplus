/**
 *  @file oglplus/program.ipp
 *  @brief Implementation of Program
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

namespace oglplus {

OGLPLUS_LIB_FUNC
GLenum ProgramOps::_binding_query(Target)
{
	return GL_CURRENT_PROGRAM;
}

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::AttachShader(const ShaderOps& shader)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(AttachShader)(
		_name,
		FriendOf<ShaderOps>::GetName(shader)
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		AttachShader,
		Program,
		nullptr,
		_name
	));
	return *this;
}

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::AttachShaders(const Group<Shader>& shaders)
{
	for(std::size_t i=0, n=shaders.size(); i!=n; ++i)
	{
		this->AttachShader(shaders[i]);
	}
	return *this;
}

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::DetachShader(const ShaderOps& shader)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(DetachShader)(
		_name,
		FriendOf<ShaderOps>::GetName(shader)
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		DetachShader,
		Program,
		nullptr,
		_name
	));
	return *this;
}

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::Link(void)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(LinkProgram)(_name);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		LinkProgram,
		Program,
		nullptr,
		_name
	));
	if(OGLPLUS_IS_ERROR(!IsLinked()))
	{
		HandleLinkError();
	}
	return *this;
}

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::Validate(void)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ValidateProgram)(_name);
	OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
		ValidateProgram,
		Program,
		nullptr,
		_name
	));
	if(OGLPLUS_IS_ERROR(!IsValid()))
	{
		HandleBuildError<ValidationError>(
			GetInfoLog(),
			OGLPLUS_OBJECT_ERROR_INFO(
				ValidateProgram,
				Program,
				nullptr,
				_name
			)
		);
	}
	return *this;
}

OGLPLUS_LIB_FUNC
String ProgramOps::GetInfoLog(void) const
{
	assert(_name != 0);
	return aux::GetInfoLog(
		_name,
		OGLPLUS_GLFUNC(GetProgramiv),
		OGLPLUS_GLFUNC(GetProgramInfoLog),
		"GetProgramiv",
		"GetProgramInfoLog"
	);
}

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

OGLPLUS_LIB_FUNC
void ProgramOps::TransformFeedbackVaryings(
	GLsizei count,
	const GLchar** varyings,
	TransformFeedbackMode mode
)
{
	OGLPLUS_GLFUNC(TransformFeedbackVaryings)(
		_name,
		count,
		varyings,
		GLenum(mode)
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TransformFeedbackVaryings,
		Program,
		nullptr,
		_name
	));
}

OGLPLUS_LIB_FUNC
void ProgramOps::TransformFeedbackVaryings(
	const std::vector<String>& varyings,
	TransformFeedbackMode mode
) const
{
	std::vector<const GLchar*> tmp(varyings.size());
	auto i = varyings.begin(), e = varyings.end();
	auto t = tmp.begin();
	while(i != e)
	{
		assert(t != tmp.end());
		*t = i->c_str();
		++i;
		++t;
	}
	OGLPLUS_GLFUNC(TransformFeedbackVaryings)(
		_name,
		GLsizei(tmp.size()),
		tmp.data(),
		GLenum(mode)
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		TransformFeedbackVaryings,
		Program,
		nullptr,
		_name
	));
}

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::MakeSeparable(bool para)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ProgramParameteri)(
		_name,
		GL_PROGRAM_SEPARABLE,
		para ? GL_TRUE : GL_FALSE
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		ProgramParameteri,
		Program,
		nullptr,
		_name
	));
	return *this;
}
#endif

#if GL_VERSION_4_1 || GL_ARB_get_program_binary

OGLPLUS_LIB_FUNC
ProgramOps& ProgramOps::MakeRetrievable(bool para)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ProgramParameteri)(
		_name,
		GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
		para ? GL_TRUE : GL_FALSE
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		ProgramParameteri,
		Program,
		nullptr,
		_name
	));
	return *this;
}

OGLPLUS_LIB_FUNC
void ProgramOps::GetBinary(std::vector<GLubyte>& binary, GLenum& format) const
{
	assert(_name != 0);
	GLint size = GetIntParam(GL_PROGRAM_BINARY_LENGTH);
	if(size > 0)
	{
		GLsizei len = 0;
		binary.resize(size);
		OGLPLUS_GLFUNC(GetProgramBinary)(
			_name,
			size,
			&len,
			&format,
			binary.data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramBinary,
			Program,
			nullptr,
			_name
		));
	}
}

OGLPLUS_LIB_FUNC
void ProgramOps::Binary(const std::vector<GLubyte>& binary, GLenum format)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ProgramBinary)(
		_name,
		format,
		binary.data(),
		binary.size()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		ProgramBinary,
		Program,
		nullptr,
		_name
	));
}
#endif

OGLPLUS_LIB_FUNC
ProgramOps::ShaderIterationContext::ShaderIterationContext(
	GLuint name,
	GLuint count
): _shader_names(count)
{
	OGLPLUS_GLFUNC(GetAttachedShaders)(
		name,
		_shader_names.size(),
		nullptr,
		_shader_names.data()
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		GetAttachedShaders,
		Program,
		nullptr,
		name
	));
}

#if GL_VERSION_4_3
OGLPLUS_LIB_FUNC
ProgramOps::InterfaceContext
ProgramOps::ActiveResourceContext(ProgramInterface intf) const
{
	// get the maximum string length of the longest identifier
	GLint length = 0;
	OGLPLUS_GLFUNC(GetProgramInterfaceiv)(
		_name,
		GLenum(intf),
		GL_MAX_NAME_LENGTH,
		&length
	);
	// for some interfaces the call above is not applicable
	// so GetError may return INVALID_OPERATION and we
	// silently ignore it here
	OGLPLUS_GLFUNC(GetError)();

	return InterfaceContext(_name, length, GLenum(intf));
}

OGLPLUS_LIB_FUNC
ProgramOps::ActiveResourceRange
ProgramOps::ActiveResources(ProgramInterface intf) const
{
	// get the count of active attributes
	GLint count = 0;
	OGLPLUS_GLFUNC(GetProgramInterfaceiv)(
		_name,
		GLenum(intf),
		GL_ACTIVE_RESOURCES,
		&count
	);
	OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetProgramInterfaceiv));

	return ActiveResourceRange(ActiveResourceContext(intf), count);
}
#endif

OGLPLUS_LIB_FUNC
ProgramOps::InterfaceContext
ProgramOps::ActiveAttribContext(void) const
{
	return InterfaceContext(
		_name,
		GetIntParam(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::ActiveAttribRange
ProgramOps::ActiveAttribs(void) const
{
	return ActiveAttribRange(
		ActiveAttribContext(),
		GetIntParam(GL_ACTIVE_ATTRIBUTES)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::InterfaceContext
ProgramOps::ActiveUniformContext(void) const
{
	return InterfaceContext(
		_name,
		GetIntParam(GL_ACTIVE_UNIFORM_MAX_LENGTH)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::ActiveUniformRange
ProgramOps::ActiveUniforms(void) const
{
	return ActiveUniformRange(
		ActiveUniformContext(),
		GetIntParam(GL_ACTIVE_UNIFORMS)
	);
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine
OGLPLUS_LIB_FUNC
ProgramOps::InterfaceContext
ProgramOps::ActiveSubroutineContext(ShaderType stage) const
{
	return InterfaceContext(
		_name,
		GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINE_MAX_LENGTH
		),
		GLenum(stage)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::ActiveSubroutineRange
ProgramOps::ActiveSubroutines(ShaderType stage) const
{
	return ActiveSubroutineRange(
		ActiveSubroutineContext(stage),
		GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINES
		)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::InterfaceContext
ProgramOps::ActiveSubroutineUniformContext(ShaderType stage) const
{
	return InterfaceContext(
		_name,
		GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH
		),
		GLenum(stage)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::ActiveSubroutineUniformRange
ProgramOps::ActiveSubroutineUniforms(ShaderType stage) const
{
	return ActiveSubroutineUniformRange(
		ActiveSubroutineUniformContext(stage),
		GetStageIntParam(
			GLenum(stage),
			GL_ACTIVE_SUBROUTINE_UNIFORMS
		)
	);
}
#endif

OGLPLUS_LIB_FUNC
ProgramOps::InterfaceContext
ProgramOps::TransformFeedbackVaryingContext(void) const
{
	return InterfaceContext(
		_name,
		GetIntParam(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::TransformFeedbackVaryingRange
ProgramOps::TransformFeedbackVaryings(void) const
{
	return TransformFeedbackVaryingRange(
		TransformFeedbackVaryingContext(),
		GetIntParam(GL_TRANSFORM_FEEDBACK_VARYINGS)
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::ShaderRange
ProgramOps::AttachedShaders(void) const
{
	GLint count = GetIntParam(GL_ATTACHED_SHADERS);
	return ShaderRange(
		ShaderIterationContext(_name, count),
		0, count
	);
}

OGLPLUS_LIB_FUNC
ProgramOps::ActiveUniformBlockRange
ProgramOps::ActiveUniformBlocks(void) const
{
	// get the count of active uniform blocks
	GLint count = GetIntParam(GL_ACTIVE_UNIFORM_BLOCKS);
	GLint length = 0;
	if(count != 0)
	{
		// get the string length of the first identifier
		length = GetIntParam(GL_UNIFORM_BLOCK_NAME_LENGTH);
	}
	return ActiveUniformBlockRange(
		aux::ProgramInterfaceContext(_name, length),
		0, count
	);
}

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects

OGLPLUS_LIB_FUNC
GLuint ShaderProgram::_make(
	ShaderType shader_type,
	GLsizei count,
	const GLchar** strings
)
{
	GLuint program = OGLPLUS_GLFUNC(CreateShaderProgramv)(
		GLenum(shader_type),
		count,
		strings
	);
	OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
		CreateShaderProgramv,
		Program,
		nullptr,
		program
	));
	return program;
}

OGLPLUS_LIB_FUNC
void ShaderProgram::_check(void)
{
	if(OGLPLUS_IS_ERROR(!IsValid()))
	{
		HandleBuildError<ValidationError>(
			GetInfoLog(),
			OGLPLUS_OBJECT_ERROR_INFO(
				ValidateProgram,
				Program,
				nullptr,
				this->_name
			)
		);
	}
}
#endif

} // namespace oglplus

