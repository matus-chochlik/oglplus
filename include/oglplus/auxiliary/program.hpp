/**
 *  @file oglplus/auxiliary/program.hpp
 *  @brief Helper classes used in Program
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_PROGRAM_1107121519_HPP
#define OGLPLUS_AUX_PROGRAM_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <vector>
#include <cassert>

namespace oglplus {

class ProgramOps;

namespace aux {

class ProgramPartInfoContext
{
private:
	GLuint _name;
	GLuint _size;
	GLenum _stage;
	std::vector<GLchar> _buffer;
public:
	ProgramPartInfoContext(GLuint name, GLuint size, GLenum stage = GL_NONE)
	 : _name(name)
	 , _size(size)
	 , _stage(stage)
	{ }

	ProgramPartInfoContext(ProgramPartInfoContext&& tmp)
	 : _name(tmp._name)
	 , _size(tmp._size)
	 , _stage(tmp._stage)
	 , _buffer(std::move(tmp._buffer))
	{ }

	GLuint Program(void) const
	{
		return _name;
	}

	GLenum Stage(void) const
	{
		return _stage;
	}

	std::vector<GLchar>& Buffer(void)
	{
		if(_size && _buffer.empty())
			_buffer.resize(_size);
		return _buffer;
	}
};

// Information about a single active vertex attribute or uniform
class ActiveVariableInfo
{
private:
	GLuint _index;
	GLint _size;
	GLenum _type;
	String _name;
protected:
	ActiveVariableInfo(
		ProgramPartInfoContext& context,
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
		ProgramPartInfoContext& context,
		GLuint index,
		void (GLAPIENTRY *GetActiveVariable)(GLuint, GLuint, GLint*)
	): _index(index)
	 , _size(0)
	 , _type(0)
	 , _name(0)
	{
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

	const GLint Size(void) const
	{
		return _size;
	}

	const SLDataType Type(void) const
	{
		return SLDataType(_type);
	}

	/// TODO: convert to Uniform (if possible)
};

struct ActiveAttribInfo : ActiveVariableInfo
{
	ActiveAttribInfo(
		ProgramPartInfoContext& context,
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

struct ActiveUniformInfo : ActiveVariableInfo
{
	ActiveUniformInfo(
		ProgramPartInfoContext& context,
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
struct ActiveSubroutineInfo
{
private:
	GLuint _index;
	String _name;
public:
	ActiveSubroutineInfo(
		ProgramPartInfoContext& context,
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
};

struct ActiveSubroutineUniformInfo
{
private:
	GLuint _index;
	GLint _size;
	String _name;
public:
	ActiveSubroutineUniformInfo(
		ProgramPartInfoContext& context,
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

	const GLint Size(void) const
	{
		return _size;
	}

	const SLDataType Type(void) const
	{
		return SLDataType::None;
	}
};
#endif

struct TransformFeedbackVaryingInfo : ActiveVariableInfo
{
	TransformFeedbackVaryingInfo(
		ProgramPartInfoContext& context,
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
		ProgramPartInfoContext& context,
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

	// TODO: active uniform indices, etc.
};


} // namespace aux
} // namespace oglplus

#endif // include guard
