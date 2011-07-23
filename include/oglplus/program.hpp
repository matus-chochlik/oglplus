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
#include <oglplus/link_error.hpp>
#include <oglplus/auxiliary/info_log.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace oglplus {

class VertexAttribOps;

/// Program operations wrapper helper class
/** This class implements OpenGL shading language program operations.
 *  @note Do not use this class directly, use @c Program instead.
 *
 *  @see Program
 */
class ProgramOps
 : public Named
 , public FriendOf<Shader>
 , public FriendOf<VertexAttribOps>
{
protected:
	static void _init(GLsizei, GLuint& _name)
	{
		_name = ::glCreateProgram();
		ThrowOnError(OGLPLUS_ERROR_INFO(CreateProgram));
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
	/// Attaches the shader to this program
	void AttachShader(const Shader& shader)
	{
		assert(_name != 0);
		::glAttachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO(AttachShader));
	}


	/// Detaches the shader to this program
	void DetachShader(const Shader& shader)
	{
		assert(_name != 0);
		::glDetachShader(_name, FriendOf<Shader>::GetName(shader));
		ThrowOnError(OGLPLUS_ERROR_INFO(DetachShader));
	}

	/// Returns true if the program is already linked,, false otherwise
	/**
	 *  @see Link
	 */
	bool IsLinked(void) const
	{
		int status;
		::glGetProgramiv(_name, GL_LINK_STATUS, &status);
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
		return status == GL_TRUE;
	}

	/// Returns the linker output if the program is linked
	/**
	 *  @see IsLinked
	 *  @see Link
	 */
	std::string GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, ::glGetProgramiv,
			::glGetProgramInfoLog,
			"GetProgramiv",
			"GetProgramInfoLog"
		);
	}

	/// Links this shading language program
	/**
	 *  @throws Error LinkError
	 *  @see Link
	 */
	void Link(void) const
	{
		assert(_name != 0);
		::glLinkProgram(_name);
		ThrowOnError(OGLPLUS_ERROR_INFO(LinkProgram));
		if(!IsLinked())
			throw LinkError(
				GetInfoLog(),
				OGLPLUS_ERROR_INFO(LinkProgram)
			);
	}

	/// Uses this shading language program
	/**
	 *  @note The program must be linked before it is used.
	 *
	 *  @see IsLinked
	 *  @see Link
	 */
	void Use(void) const
	{
		assert(_name != 0);
		assert(IsLinked());
		::glUseProgram(_name);
		AssertNoError(OGLPLUS_ERROR_INFO(UseProgram));
	}

	void MakeSeparable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_SEPARABLE,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ProgramParameteri));
	}

	void MakeRetrievable(bool para = true) const
	{
		assert(_name != 0);
		glProgramParameteri(
			_name,
			GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
			para ? GL_TRUE : GL_FALSE
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(ProgramParameteri));
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
		ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramiv));
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
			ThrowOnError(OGLPLUS_ERROR_INFO(GetProgramBinary));
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
		ThrowOnError(OGLPLUS_ERROR_INFO(ProgramBinary));
	}

	// Implemented in vertex_attrib.hpp
	/// Binds the location of a SL variable to the vertex_attrib
	/** This function binds the location of the vertex attribute
	 *  @c vertex_attrib to the shader variable identified by
	 *  @c identifier.
	 */
	inline void BindLocation(
		const VertexAttribOps& vertex_attrib,
		const GLchar* identifier
	) const;
};

#ifdef OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates OpenGL shading language-related program functionality
class Program
 : public ProgramOps
{ };
#else
typedef Object<ProgramOps, false> Program;
#endif

} // namespace oglplus

#endif // include guard
