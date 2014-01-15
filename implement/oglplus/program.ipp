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

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_get_program_binary
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
#endif

} // namespace oglplus

