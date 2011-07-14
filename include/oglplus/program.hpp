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
#include <oglplus/auxiliary/info_log.hpp>

#include <vector>
#include <string>

namespace oglplus {

class LinkError
 : public CompileOrLinkError
{
public:
	LinkError(const std::string& _msg)
	 : CompileOrLinkError("OpenGL shader language linking error", _msg)
	{ }
};

class Program
 : public FriendOf<Shader>
{
protected:
	GLuint _name;
public:

	Program(void)
	 : _name(::glCreateProgram())
	{
		ThrowOnError();
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
		ThrowOnError();
	}

	void DetachShader(const Shader& shader)
	{
		::glDetachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError();
	}

	bool IsLinked(void) const
	{
		int status;
		::glGetProgramiv(_name, GL_LINK_STATUS, &status);
		ThrowOnError();
		return status == GL_TRUE;
	}

	std::string GetInfoLog(void) const
	{
		return aux::GetInfoLog(_name, ::glGetProgramiv, ::glGetProgramInfoLog);
	}

	void Link(void)
	{
		::glLinkProgram(_name);
		ThrowOnError();
		if(!IsLinked()) throw LinkError(GetInfoLog());
	}

	void Use(void)
	{
		::glUseProgram(_name);
		AssertNoError();
	}
};

} // namespace oglplus

#endif // include guard
