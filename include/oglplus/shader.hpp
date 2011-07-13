/**
 *  @file oglplus/shader.hpp
 *  @brief Shader wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHADER_1107121519_HPP
#define OGLPLUS_SHADER_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/object.hpp>

#include <vector>
#include <string>

namespace oglplus {

class CompileOrLinkError
 : public Error
{
private:
	std::string msg;
public:
	CompileOrLinkError(const char* _what, const std::string& _msg)
	 : Error(0, _what)
	 , msg(_msg)
	{ }

	~CompileOrLinkError(void) throw()
	{ }

	const std::string& Log(void) const
	{
		return msg;
	}
};

class CompileError
 : public CompileOrLinkError
{
public:
	CompileError(const std::string& _msg)
	 : CompileOrLinkError("OpenGL shader language compilation error", _msg)
	{ }
};

class LinkError
 : public CompileOrLinkError
{
public:
	LinkError(const std::string& _msg)
	 : CompileOrLinkError("OpenGL shader language linking error", _msg)
	{ }
};

class Shader
{
protected:
	GLuint _name;
public:
	enum class Kind {
		Vertex = GL_VERTEX_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		TessControl = GL_TESS_CONTROL_SHADER,
		TessEvaluation = GL_TESS_EVALUATION_SHADER
	};

	Shader(Kind kind)
	 : _name(::glCreateShader(GLenum(kind)))
	{
		ThrowOnError();
	}

	~Shader(void)
	{
		::glDeleteShader(_name);
	}

	void Source(const std::string& source) const
	{
		const GLchar* srcs[1] = {source.c_str()};
		GLint lens[] = {source.size()};
		::glShaderSource(_name, 1, srcs, lens);
	}

	void Source(const GLchar* source) const
	{
		const GLchar* srcs[1] = {source};
		::glShaderSource(_name, 1, srcs, 0);
	}

	void Source(const GLchar* source, int length) const
	{
		const GLchar* srcs[1] = {source};
		int lens[] = {length};
		::glShaderSource(_name, 1, srcs, lens);
	}

	void Source(const std::vector<const GLchar*>& srcs) const
	{
		::glShaderSource(
			_name,
			srcs.size(),
			const_cast<const GLchar**>(srcs.data()),
			0
		);
	}

	bool IsCompiled(void) const
	{
		int status;
		::glGetShaderiv(_name, GL_COMPILE_STATUS, &status);
		ThrowOnError();
		return status == GL_TRUE;
	}

	std::string GetInfoLog(void) const
	{
		int length = 0;
		::glGetShaderiv(_name, GL_INFO_LOG_LENGTH, &length);
		ThrowOnError();
		if(length > 0)
		{
			GLsizei real_length = 0;
			std::vector<GLchar> buffer(length);
			::glGetShaderInfoLog(
				_name,
				buffer.size(),
				&real_length,
				buffer.data()
			);
			ThrowOnError();
			return std::string(buffer.data(), buffer.size());
		}
		else return std::string();
	}

	void Compile(void) const
	{
		::glCompileShader(_name);
		ThrowOnError();
		if(!IsCompiled()) throw CompileError(GetInfoLog());
	}
};

} // namespace oglplus

#endif // include guard
