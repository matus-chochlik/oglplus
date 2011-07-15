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

namespace oglplus {

class VertexAttribOps;

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

class Program
 : public FriendOf<Shader>
 , public FriendOf<VertexAttribOps>
{
protected:
	GLuint _name;

	friend class FriendOf<Program>;
public:

	Program(void)
	 : _name(::glCreateProgram())
	{
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	Program(const Program&) = delete;

	Program(Program&& temp)
	 : _name(temp._name)
	{
		temp._name = 0;
	}

	~Program(void)
	{
		::glDeleteProgram(_name);
	}

	void AttachShader(const Shader& shader)
	{
		::glAttachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	void DetachShader(const Shader& shader)
	{
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
		return aux::GetInfoLog(
			_name, ::glGetProgramiv,
			::glGetProgramInfoLog
		);
	}

	void Link(void)
	{
		::glLinkProgram(_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
		if(!IsLinked())
			throw LinkError(GetInfoLog(),OGLPLUS_ERROR_INFO());
	}

	void Use(void)
	{
		assert(IsLinked());
		::glUseProgram(_name);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	// Implemented in vertex_attrib.hpp
	inline void BindLocation(
		const VertexAttribOps& vertex_attrib,
		const GLchar* identifier
	) const;
};

} // namespace oglplus

#endif // include guard
