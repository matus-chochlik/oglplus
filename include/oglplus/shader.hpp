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
#include <oglplus/friend_of.hpp>
#include <oglplus/compile_error.hpp>
#include <oglplus/auxiliary/info_log.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace oglplus {

/// Shader operations wrapper helper class
/**
 *  @note Do not use this class directly, use Shader instead.
 *
 *  @see Shader
 */
class ShaderOps
 : public Named
{
public:
	/// The kind of the shader
	enum class Kind : GLenum {
		Vertex = GL_VERTEX_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		TessControl = GL_TESS_CONTROL_SHADER,
		TessEvaluation = GL_TESS_EVALUATION_SHADER
	};
protected:
	static void _init(GLsizei, GLuint& _name, Kind kind)
	{
		_name = ::glCreateShader(GLenum(kind));
		ThrowOnError(OGLPLUS_ERROR_INFO());
	}

	static void _cleanup(GLsizei, GLuint& _name)
	{
		assert(_name != 0);
		::glDeleteShader(_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return ::glIsShader(_name);
	}

	friend class FriendOf<ShaderOps>;
public:
	/// Set the source code of the shader
	void Source(const std::string& source) const
	{
		assert(_name != 0);
		const GLchar* srcs[1] = {source.c_str()};
		GLint lens[] = {GLint(source.size())};
		::glShaderSource(_name, 1, srcs, lens);
	}

	/// Set the source code of the shader
	void Source(const GLchar* source) const
	{
		assert(_name != 0);
		const GLchar* srcs[1] = {source};
		::glShaderSource(_name, 1, srcs, 0);
	}

	/// Set the source code of the shader
	void Source(const GLchar* source, int length) const
	{
		assert(_name != 0);
		const GLchar* srcs[1] = {source};
		int lens[] = {length};
		::glShaderSource(_name, 1, srcs, lens);
	}

	/// Set the source code of the shader
	void Source(const std::vector<const GLchar*>& srcs) const
	{
		assert(_name != 0);
		::glShaderSource(
			_name,
			srcs.size(),
			const_cast<const GLchar**>(srcs.data()),
			0
		);
	}

	/// Returns true if the shader is already compile, returns false otherwise
	/**
	 *  @see Compile
	 */
	bool IsCompiled(void) const
	{
		assert(_name != 0);
		int status;
		::glGetShaderiv(_name, GL_COMPILE_STATUS, &status);
		ThrowOnError(OGLPLUS_ERROR_INFO());
		return status == GL_TRUE;
	}

	/// Returns the compiler output if the program is compiled
	/**
	 *  @see IsCompiled
	 *  @see Compile
	 */
	std::string GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, ::glGetShaderiv,
			::glGetShaderInfoLog
		);
	}

	/// Compiles the shader
	/**
	 *  @throws Error CompileError
	 *  @see IsCompiled
	 */
	void Compile(void) const
	{
		assert(_name != 0);
		::glCompileShader(_name);
		ThrowOnError(OGLPLUS_ERROR_INFO());
		if(!IsCompiled())
			throw CompileError(GetInfoLog(), OGLPLUS_ERROR_INFO());
	}
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Encasulates the shading language shader-related functionality
/**
 *  @see Program
 *  @see VertexShader
 *  @see GeometryShader
 *  @see FragmentShader
 *  @see TessControlShader
 *  @see TessEvaluationShader
 */
class Shader
 : public ShaderOps
{
public:
	Shader(ShaderOps::Kind kind);
};
#else
typedef Object<ShaderOps, false> Shader;
#endif

/// Vertex shader wrapper
/**
 *  @see Shader
 *  @see Program
 */
class VertexShader
 : public Shader
{
public:
	VertexShader(void)
	 : Shader(Shader::Kind::Vertex)
	{ }
};

/// Geometry shader wrapper
/**
 *  @see Shader
 *  @see Program
 */
class GeometryShader
 : public Shader
{
public:
	GeometryShader(void)
	 : Shader(Shader::Kind::Geometry)
	{ }
};

/// Fragment shader wrapper
/**
 *  @see Shader
 *  @see Program
 */
class FragmentShader
 : public Shader
{
public:
	FragmentShader(void)
	 : Shader(Shader::Kind::Fragment)
	{ }
};

/// Tesselation control shader wrapper
/**
 *  @see Shader
 *  @see Program
 */
class TessControlShader
 : public Shader
{
public:
	TessControlShader(void)
	 : Shader(Shader::Kind::TessControl)
	{ }
};

/// Tesselation evaluation shader wrapper
/**
 *  @see Shader
 *  @see Program
 */
class TessEvaluationShader
 : public Shader
{
public:
	TessEvaluationShader(void)
	 : Shader(Shader::Kind::TessEvaluation)
	{ }
};

} // namespace oglplus

#endif // include guard
