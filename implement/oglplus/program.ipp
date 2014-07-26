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

#include <oglplus/lib/incl_begin.ipp>
#include <oglplus/detail/info_log.hpp>
#include <oglplus/object/reference.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/lib/incl_end.ipp>

namespace oglplus {

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
AttachShader(ShaderName shader)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(AttachShader)(
		_name,
		GetGLName(shader)
	);
	OGLPLUS_CHECK(
		AttachShader,
		ObjectPairError,
		Subject(shader).
		Object(*this)
	);
	return *this;
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
AttachShaders(const Sequence<ShaderName>& shaders)
{
	for(std::size_t i=0, n=shaders.size(); i!=n; ++i)
	{
		this->AttachShader(shaders[i]);
	}
	return *this;
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
DetachShader(ShaderName shader)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(DetachShader)(
		_name,
		GetGLName(shader)
	);
	OGLPLUS_CHECK(
		DetachShader,
		ObjectPairError,
		Subject(shader).
		Object(*this)
	);
	return *this;
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
Link(void)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(LinkProgram)(_name);
	OGLPLUS_CHECK(
		LinkProgram,
		ObjectError,
		Object(*this)
	);
	OGLPLUS_HANDLE_ERROR_IF(
		!IsLinked(),
		GL_INVALID_OPERATION,
		LinkError::Message(),
		LinkError,
		Log(GetInfoLog()).
		Object(*this)
	);
	return *this;
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
Build(void)
{
	ShaderRange shaders = AttachedShaders();
	while(!shaders.Empty())
	{
		Reference<ShaderOps> shader = shaders.Front();
		if(!shader.IsCompiled())
		{
			shader.Compile();
		}
		shaders.Next();
	}
	return Link();
}

#if GL_ARB_shading_language_include
OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
BuildInclude(
	GLsizei count,
	const GLchar* const* paths,
	const GLint* lengths
)
{
	ShaderRange shaders = AttachedShaders();
	while(!shaders.Empty())
	{
		Reference<ShaderOps> shader = shaders.Front();
		if(!shader.IsCompiled())
		{
			shader.CompileInclude(
				count,
				paths,
				lengths
			);
		}
		shaders.Next();
	}
	return Link();
}
#endif

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
Validate(void)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ValidateProgram)(_name);
	OGLPLUS_VERIFY(
		ValidateProgram,
		ObjectError,
		Object(*this)
	);
	OGLPLUS_HANDLE_ERROR_IF(
		!IsValid(),
		GL_INVALID_OPERATION,
		ValidationError::Message(),
		ValidationError,
		Log(GetInfoLog()).
		Object(*this)
	);
	return *this;
}

OGLPLUS_LIB_FUNC
String ObjectOps<tag::DirectState, tag::Program>::
GetInfoLog(void) const
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
void ObjectOps<tag::DirectState, tag::Program>::
TransformFeedbackVaryings(
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
	OGLPLUS_CHECK(
		TransformFeedbackVaryings,
		ObjectError,
		Object(*this)
	);
}

OGLPLUS_LIB_FUNC
void ObjectOps<tag::DirectState, tag::Program>::
TransformFeedbackVaryings(
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
	OGLPLUS_CHECK(
		TransformFeedbackVaryings,
		ObjectError,
		Object(*this)
	);
}

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
MakeSeparable(bool para)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ProgramParameteri)(
		_name,
		GL_PROGRAM_SEPARABLE,
		para ? GL_TRUE : GL_FALSE
	);
	OGLPLUS_CHECK(
		ProgramParameteri,
		ObjectError,
		Object(*this)
	);
	return *this;
}
#endif

#if GL_VERSION_4_1 || GL_ARB_get_program_binary

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>&
ObjectOps<tag::DirectState, tag::Program>::
MakeRetrievable(bool para)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ProgramParameteri)(
		_name,
		GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
		para ? GL_TRUE : GL_FALSE
	);
	OGLPLUS_CHECK(
		ProgramParameteri,
		ObjectError,
		Object(*this)
	);
	return *this;
}

OGLPLUS_LIB_FUNC
void ObjectOps<tag::DirectState, tag::Program>::
GetBinary(std::vector<GLubyte>& binary, GLenum& format) const
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
		OGLPLUS_CHECK(
			GetProgramBinary,
			ObjectError,
			Object(*this)
		);
	}
}

OGLPLUS_LIB_FUNC
void ObjectOps<tag::DirectState, tag::Program>::
Binary(const std::vector<GLubyte>& binary, GLenum format)
{
	assert(_name != 0);
	OGLPLUS_GLFUNC(ProgramBinary)(
		_name,
		format,
		binary.data(),
		binary.size()
	);
	OGLPLUS_CHECK(
		ProgramBinary,
		ObjectError,
		Object(*this)
	);
}
#endif

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::
ShaderIterationContext::ShaderIterationContext(
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
	OGLPLUS_CHECK(
		GetAttachedShaders,
		ObjectError,
		Object(ProgramName(name))
	);
}

#if GL_VERSION_4_3
OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::InterfaceContext
ObjectOps<tag::DirectState, tag::Program>::
ActiveResourceContext(ProgramInterface intf) const
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
ObjectOps<tag::DirectState, tag::Program>::ActiveResourceRange
ObjectOps<tag::DirectState, tag::Program>::
ActiveResources(ProgramInterface intf) const
{
	// get the count of active attributes
	GLint count = 0;
	OGLPLUS_GLFUNC(GetProgramInterfaceiv)(
		_name,
		GLenum(intf),
		GL_ACTIVE_RESOURCES,
		&count
	);
	OGLPLUS_VERIFY(
		GetProgramInterfaceiv,
		ObjectError,
		Object(*this).
		EnumParam(intf)
	);
	return ActiveResourceRange(ActiveResourceContext(intf), count);
}
#endif

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::InterfaceContext
ObjectOps<tag::DirectState, tag::Program>::
ActiveAttribContext(void) const
{
	return InterfaceContext(
		_name,
		GetIntParam(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH)
	);
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::ActiveAttribRange
ObjectOps<tag::DirectState, tag::Program>::
ActiveAttribs(void) const
{
	return ActiveAttribRange(
		ActiveAttribContext(),
		GetIntParam(GL_ACTIVE_ATTRIBUTES)
	);
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::InterfaceContext
ObjectOps<tag::DirectState, tag::Program>::
ActiveUniformContext(void) const
{
	return InterfaceContext(
		_name,
		GetIntParam(GL_ACTIVE_UNIFORM_MAX_LENGTH)
	);
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::ActiveUniformRange
ObjectOps<tag::DirectState, tag::Program>::
ActiveUniforms(void) const
{
	return ActiveUniformRange(
		ActiveUniformContext(),
		GetIntParam(GL_ACTIVE_UNIFORMS)
	);
}

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine
OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::InterfaceContext
ObjectOps<tag::DirectState, tag::Program>::
ActiveSubroutineContext(ShaderType stage) const
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
ObjectOps<tag::DirectState, tag::Program>::ActiveSubroutineRange
ObjectOps<tag::DirectState, tag::Program>::
ActiveSubroutines(ShaderType stage) const
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
ObjectOps<tag::DirectState, tag::Program>::InterfaceContext
ObjectOps<tag::DirectState, tag::Program>::
ActiveSubroutineUniformContext(ShaderType stage) const
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
ObjectOps<tag::DirectState, tag::Program>::ActiveSubroutineUniformRange
ObjectOps<tag::DirectState, tag::Program>::
ActiveSubroutineUniforms(ShaderType stage) const
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
ObjectOps<tag::DirectState, tag::Program>::InterfaceContext
ObjectOps<tag::DirectState, tag::Program>::
TransformFeedbackVaryingContext(void) const
{
	return InterfaceContext(
		_name,
		GetIntParam(GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH)
	);
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::TransformFeedbackVaryingRange
ObjectOps<tag::DirectState, tag::Program>::
TransformFeedbackVaryings(void) const
{
	return TransformFeedbackVaryingRange(
		TransformFeedbackVaryingContext(),
		GetIntParam(GL_TRANSFORM_FEEDBACK_VARYINGS)
	);
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::ShaderRange
ObjectOps<tag::DirectState, tag::Program>::
AttachedShaders(void) const
{
	GLint count = GetIntParam(GL_ATTACHED_SHADERS);
	return ShaderRange(
		ShaderIterationContext(_name, count),
		0, count
	);
}

OGLPLUS_LIB_FUNC
ObjectOps<tag::DirectState, tag::Program>::ActiveUniformBlockRange
ObjectOps<tag::DirectState, tag::Program>::
ActiveUniformBlocks(void) const
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
	const GLchar* const* strings
)
{
	GLuint program = OGLPLUS_GLFUNC(CreateShaderProgramv)(
		GLenum(shader_type),
		count,
		const_cast<const GLchar**>(strings)
	);
	OGLPLUS_CHECK(
		CreateShaderProgramv,
		Error,
		EnumParam(shader_type)
	);
	return program;
}

OGLPLUS_LIB_FUNC
void ShaderProgram::_check(void)
{
	OGLPLUS_HANDLE_ERROR_IF(
		!IsValid(),
		GL_INVALID_OPERATION,
		ValidationError::Message(),
		ValidationError,
		Log(GetInfoLog()).
		Object(*this)
	);
}
#endif

} // namespace oglplus

