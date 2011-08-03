/**
 *  @file oglplus/uniform_block.hpp
 *  @brief Named uniform block wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_UNIFORM_BLOCK_1107121519_HPP
#define OGLPLUS_UNIFORM_BLOCK_1107121519_HPP

#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/program.hpp>

#include <string>
#include <cassert>

namespace oglplus {

class UniformBlock
 : public FriendOf<Program>
{
protected:
	GLuint _program;
	GLint _index;

	friend class FriendOf<UniformOps>;

	static GLenum _translate_ref(Shader::Kind shader_kind)
	{
		switch(shader_kind)
		{
			case Shader::Kind::Vertex:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER;
			case Shader::Kind::TessControl:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER;
			case Shader::Kind::TessEvaluation:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER;
			case Shader::Kind::Geometry:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER;
			case Shader::Kind::Fragment:
			return GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER;
		}
		return 0;
	}

	static GLenum _translate_max(Shader::Kind shader_kind)
	{
		switch(shader_kind)
		{
			case Shader::Kind::Vertex:
			return GL_MAX_VERTEX_UNIFORM_BLOCKS;
			case Shader::Kind::TessControl:
			return GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS;
			case Shader::Kind::TessEvaluation:
			return GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS;
			case Shader::Kind::Geometry:
			return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
			case Shader::Kind::Fragment:
			return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
		}
		return 0;
	}
public:
	UniformBlock(const Program& program, GLint index)
	 : _program(FriendOf<Program>::GetName(program))
	 , _index(index)
	{ }

	UniformBlock(const Program& program, const GLchar* identifier)
	 : _program(FriendOf<Program>::GetName(program))
	 , _index(::glGetUniformBlockIndex(_program, identifier))
	{
		ThrowOnError(OGLPLUS_ERROR_INFO(GetUniformBlockIndex));
		if(_index == GLint(-1))
		{
			ThrowOnError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform block",
				OGLPLUS_ERROR_INFO(GetUniformBlockIndex),
				Error::PropertyMap({
					{"identifier", identifier}
				})
			);
		}
	}

	static GLuint MaxIn(Shader::Kind shader_kind)
	{
		GLint result;
		::glGetIntegerv(_translate_max(shader_kind), &result);
		AssertNoError(OGLPLUS_ERROR_INFO(GetIntegerv));
		assert(result >= 0);
		return GLuint(result);
	}

	bool ReferencedBy(Shader::Kind shader_kind) const
	{
		GLint result;
		::glGetActiveUniformBlockiv(
			_program,
			_index,
			_translate_ref(shader_kind),
			&result
		);
		AssertNoError(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		return result == GL_TRUE;
	}

	GLuint DataSize(void) const
	{
		GLint result;
		::glGetActiveUniformBlockiv(
			_program,
			_index,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&result
		);
		AssertNoError(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		assert(result >= 0);
		return GLuint(result);
	}

	void Binding(GLuint binding) const
	{
		::glUniformBlockBinding(
			_program,
			_index,
			binding
		);
		ThrowOnError(OGLPLUS_ERROR_INFO(UniformBlockBinding));
	}
};

} // namespace oglplus

#endif // include guard
