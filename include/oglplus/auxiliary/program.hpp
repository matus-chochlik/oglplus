/**
 *  @file oglplus/auxiliary/program.hpp
 *  @brief Helper classes used in Program
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_PROGRAM_1107121519_HPP
#define OGLPLUS_AUX_PROGRAM_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <vector>
#include <cassert>

namespace oglplus {

class ProgramOps;

namespace aux {

class ProgramInterfaceContext
{
private:
	GLuint _program;
	GLuint _size;
	GLenum _stage_or_intf;
	std::vector<GLchar> _buffer;
public:
	ProgramInterfaceContext(
		GLuint name,
		GLuint size,
		GLenum stage_or_intf = GL_NONE
	): _program(name)
	 , _size(size)
	 , _stage_or_intf(stage_or_intf)
	{ }

	ProgramInterfaceContext(ProgramInterfaceContext&& tmp)
	 : _program(tmp._program)
	 , _size(tmp._size)
	 , _stage_or_intf(tmp._stage_or_intf)
	 , _buffer(std::move(tmp._buffer))
	{ }

	GLuint Program(void) const
	{
		return _program;
	}

	GLenum Stage(void) const
	{
		return _stage_or_intf;
	}

	GLenum Interface(void) const
	{
		return _stage_or_intf;
	}

	std::vector<GLchar>& Buffer(void)
	{
		if(_size && _buffer.empty())
			_buffer.resize(_size);
		return _buffer;
	}
};

// Information about a single active vertex attribute, uniform, etc.
class ActiveVariableInfo
{
private:
	GLuint _index;
	GLint _size;
	GLenum _type;
	String _name;

	ActiveVariableInfo(
		GLuint index,
		GLint size,
		GLenum type,
		const String& name
	): _index(index)
	 , _size(size)
	 , _type(type)
	 , _name(name)
	{ }

	friend class ActiveSubroutineInfo;
	friend class ActiveSubroutineUniformInfo;
	friend class ActiveUniformBlockInfo;
protected:

	ActiveVariableInfo(
		ProgramInterfaceContext& context,
		GLuint index,
		void (GLAPIENTRY *GetActiveVariable)(
			GLuint /*program*/,
			GLuint /*index*/,
			GLsizei /*bufsize*/,
			GLsizei* /*length*/,
			GLint* /*size*/,
			GLenum* /*type*/,
			GLchar* /*name*/
		)
	): _index(index)
	 , _size(0)
	{
		GLsizei strlen = 0;
		GetActiveVariable(
			context.Program(),
			index,
			context.Buffer().size(),
			&strlen,
			&_size,
			&_type,
			context.Buffer().data()
		);
		_name = String(context.Buffer().data(), strlen);
	}

	// TODO: this is here only because GLEW defines
	// glGetTransformFeedbackVaryings this way
	ActiveVariableInfo(
		ProgramInterfaceContext& context,
		GLuint index,
		void (GLAPIENTRY *GetActiveVariable)(GLuint, GLuint, GLint*)
	): _index(index)
	 , _size(0)
	 , _type(0)
	 , _name(0)
	{
		OGLPLUS_FAKE_USE(context);
		OGLPLUS_FAKE_USE(GetActiveVariable);
	}
public:
	GLuint Index(void) const
	{
		return _index;
	}

	const String& Name(void) const
	{
		return _name;
	}

	GLint Size(void) const
	{
		return _size;
	}

	SLDataType Type(void) const
	{
		return SLDataType(_type);
	}
};

class ActiveAttribInfo : public ActiveVariableInfo
{
public:
	ActiveAttribInfo(
		ProgramInterfaceContext& context,
		GLuint index
	): ActiveVariableInfo(
		context,
		index,
		OGLPLUS_GLFUNC(GetActiveAttrib)
	)
	{
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetActiveAttrib,
			Program,
			nullptr,
			context.Program()
		));
	}
};

class ActiveUniformInfo : public ActiveVariableInfo
{
public:
	ActiveUniformInfo(
		ProgramInterfaceContext& context,
		GLuint index
	): ActiveVariableInfo(
		context,
		index,
		OGLPLUS_GLFUNC(GetActiveUniform)
	)
	{
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetActiveUniform,
			Program,
			nullptr,
			context.Program()
		));
	}
};

#if GL_VERSION_4_0 || GL_ARB_shader_subroutine
class ActiveSubroutineInfo
{
private:
	GLuint _index;
	String _name;
public:
	ActiveSubroutineInfo(
		ProgramInterfaceContext& context,
		GLuint index
	): _index(index)
	{
		GLsizei strlen = 0;
		OGLPLUS_GLFUNC(GetActiveSubroutineName)(
			context.Program(),
			context.Stage(),
			index,
			context.Buffer().size(),
			&strlen,
			context.Buffer().data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetActiveSubroutineName,
			Program,
			nullptr,
			context.Program()
		));
		_name = String(context.Buffer().data(), strlen);
	}

	GLuint Index(void) const
	{
		return _index;
	}

	const String& Name(void) const
	{
		return _name;
	}

	GLint Size(void) const
	{
		return 0;
	}

	SLDataType Type(void) const
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
	{
#ifdef None
#pragma push_macro("None")
#undef None
		return SLDataType::None;
#pragma pop_macro("None")
#else
		return SLDataType::None;
#endif // None
	}
#else
;
#endif

	operator ActiveVariableInfo(void) const
	{
		return ActiveVariableInfo(_index, 0, GL_NONE, _name);
	}
};

class ActiveSubroutineUniformInfo
{
private:
	GLuint _index;
	GLint _size;
	String _name;
public:
	ActiveSubroutineUniformInfo(
		ProgramInterfaceContext& context,
		GLuint index
	): _index(index)
	 , _size(0)
	{
		OGLPLUS_GLFUNC(GetActiveSubroutineUniformiv)(
			context.Program(),
			context.Stage(),
			index,
			GL_UNIFORM_SIZE,
			&_size
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetActiveSubroutineUniformiv,
			Program,
			nullptr,
			context.Program()
		));

		GLsizei strlen = 0;
		OGLPLUS_GLFUNC(GetActiveSubroutineUniformName)(
			context.Program(),
			context.Stage(),
			index,
			context.Buffer().size(),
			&strlen,
			context.Buffer().data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetActiveSubroutineUniformName,
			Program,
			nullptr,
			context.Program()
		));
		_name = String(context.Buffer().data(), strlen);
	}

	GLuint Index(void) const
	{
		return _index;
	}

	const String& Name(void) const
	{
		return _name;
	}

	GLint Size(void) const
	{
		return _size;
	}

	SLDataType Type(void) const
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
	{
#ifdef None
#pragma push_macro("None")
#undef None
		return SLDataType::None;
#pragma pop_macro("None")
#else
		return SLDataType::None;
#endif // None
	}
#else
;
#endif

	operator ActiveVariableInfo(void) const
	{
		return ActiveVariableInfo(_index, _size, GL_NONE, _name);
	}
};
#endif

class TransformFeedbackVaryingInfo : public ActiveVariableInfo
{
public:
	TransformFeedbackVaryingInfo(
		ProgramInterfaceContext& context,
		GLuint index
	): ActiveVariableInfo(
		context,
		index,
		OGLPLUS_GLFUNC(GetTransformFeedbackVarying)
	)
	{
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetTransformFeedbackVarying,
			Program,
			nullptr,
			context.Program()
		));
	}
};

class ActiveUniformBlockInfo
{
private:
	GLuint _index;
	String _name;
public:
	ActiveUniformBlockInfo(
		ProgramInterfaceContext& context,
		GLuint index
	): _index(0)
	{
		GLint length = 0;
		OGLPLUS_GLFUNC(GetProgramiv)(
			context.Program(),
			GL_UNIFORM_BLOCK_NAME_LENGTH,
			&length
		);
		if(context.Buffer().size() < size_t(length))
			context.Buffer().resize(length);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramiv,
			Program,
			nullptr,
			context.Program()
		));
		GLsizei strlen = 0;
		OGLPLUS_GLFUNC(GetActiveUniformBlockName)(
			context.Program(),
			index,
			context.Buffer().size(),
			&strlen,
			context.Buffer().data()
		);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			GetActiveUniformBlockName,
			Program,
			nullptr,
			context.Program()
		));
		_name = String(context.Buffer().data(), strlen);
	}

	GLuint Index(void) const
	{
		return _index;
	}

	const String& Name(void) const
	{
		return _name;
	}

	GLint Size(void) const
	{
		return 0;
	}

	SLDataType Type(void) const
#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
	{
#ifdef None
#pragma push_macro("None")
#undef None
		return SLDataType::None;
#pragma pop_macro("None")
#else
		return SLDataType::None;
#endif // None
	}
#else
;
#endif

	operator ActiveVariableInfo(void) const
	{
		return ActiveVariableInfo(_index, 0, GL_NONE, _name);
	}

	// TODO: active uniform indices, etc.
};


} // namespace aux
} // namespace oglplus

#endif // include guard
