/**
 *  @file oglplus/program.hpp
 *  @brief Program wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PROGRAM_1107121519_HPP
#define OGLPLUS_PROGRAM_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/auxiliary/info_log.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace oglplus {

class VertexAttribOps;

/// Exception class for OpenGL shading language program link error
class LinkError
 : public CompileOrLinkError
{
public:
	LinkError(const std::string& log, const ErrorInfo& info)
	 : CompileOrLinkError(
		"OpenGL shading language link error",
		log,
		info
	)
	{ }
};

class ProgramOps
 : public Named
 , public FriendOf<Shader>
 , public FriendOf<VertexAttribOps>
{
protected:
	static void _init(GLsizei, GLuint& _name)
	{
		_name = ::glCreateProgram();
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteProgram(_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsProgram(_name);
	}

	friend class FriendOf<ProgramOps>;
public:
	void AttachShader(const Shader& shader)
	{
		assert(_name != 0);
		::glAttachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void DetachShader(const Shader& shader)
	{
		assert(_name != 0);
		::glDetachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	bool IsLinked(void) const
	{
		int status;
		::glGetProgramiv(_name, GL_LINK_STATUS, &status);
		ThrowOnError(OGLPLUS_ERROR_INFO());
		return status == GL_TRUE;
	}

	std::string GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, ::glGetProgramiv,
			::glGetProgramInfoLog
		);
	}

	void Link(void) const
	{
		assert(_name != 0);
		::glLinkProgram(_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
		if(!IsLinked())
			throw LinkError(GetInfoLog(),OGLPLUS_ERROR_INFO());
	}

	void Use(void) const
	{
		assert(_name != 0);
		assert(IsLinked());
		::glUseProgram(_name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	void MakeSeparable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_SEPARABLE,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void MakeRetrievable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void GetBinary(std::vector<GLubyte>& binary, GLenum& format) const
	{
		assert(_name != 0);
		GLint size = 0;
		::glGetProgramiv(
			_name,
			GL_PROGRAM_BINARY_LENGTH,
			&size
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
		if(size > 0)
		{
			GLsizei len = 0;
			binary.resize(size);
			::glGetProgramBinary(
				_name,
				size,
				&len,
				&format,
				binary.data()
			);
			ThrowOnError(OGLPLUS_ERROR_INFO());
		}
	}

	void Binary(const std::vector<GLubyte>& binary, GLenum format) const
	{
		assert(_name != 0);
		::glProgramBinary(
			_name,
			format,
			binary.data(),
			binary.size()
		);
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	// Implemented in vertex_attrib.hpp
	inline void BindLocation(
		const VertexAttribOps& vertex_attrib,
		const GLchar* identifier
	) const;
};

typedef Object<ProgramOps, false> Program;

} // namespace oglplus

#endif // include guard
