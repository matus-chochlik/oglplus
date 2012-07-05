/**
 *  @file oglplus/uniform_subroutines.hpp
 *  @brief Wrapper for uniform subroutine operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_UNIFORM_SUBROUTINE_1107121519_HPP
#define OGLPLUS_UNIFORM_SUBROUTINE_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/program.hpp>
#include <oglplus/string.hpp>

#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine
class UniformSubroutines;

class SubroutineUniform
 : public FriendOf<Program>
{
private:
	GLuint _program;
	GLint _index;

	friend class UniformSubroutines;

	static GLint _get_index(
		const Program& program,
		const ShaderType stage,
		const GLchar* identifier
	)
	{
		GLint result = OGLPLUS_GLFUNC(GetSubroutineUniformLocation)(
			FriendOf<Program>::GetName(program),
			GLenum(stage),
			identifier
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetSubroutineUniformLocation));
		if(OGLPLUS_IS_ERROR(result == GLint(-1)))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = DescriptionOf(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform",
				OGLPLUS_ERROR_INFO(GetSubroutineUniformLocation),
				std::move(props)
			);
		}
		return result;
	}
public:
	SubroutineUniform(
		const Program& program,
		const ShaderType stage,
		const GLchar* identifier
	): _program(FriendOf<Program>::GetName(program))
	 , _index(_get_index(program, stage, identifier))
	{ }

	SubroutineUniform(
		const Program& program,
		const ShaderType stage,
		const String& identifier
	): _program(FriendOf<Program>::GetName(program))
	 , _index(_get_index(program, stage, identifier.c_str()))
	{ }
};

class Subroutine
 : public FriendOf<Program>
{
private:
	GLuint _program;
	GLint _index;

	friend class UniformSubroutines;

	static GLint _get_index(
		const Program& program,
		const ShaderType stage,
		const GLchar* identifier
	)
	{
		GLint result = OGLPLUS_GLFUNC(GetSubroutineIndex)(
			FriendOf<Program>::GetName(program),
			GLenum(stage),
			identifier
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetSubroutineIndex));
		if(OGLPLUS_IS_ERROR(result == GLint(-1)))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = DescriptionOf(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive subroutine",
				OGLPLUS_ERROR_INFO(GetSubroutineIndex),
				std::move(props)
			);
		}
		return result;
	}
public:
	Subroutine(
		const Program& program,
		const ShaderType stage,
		const GLchar* identifier
	): _program(FriendOf<Program>::GetName(program))
	 , _index(_get_index(program, stage, identifier))
	{ }

	Subroutine(
		const Program& program,
		const ShaderType stage,
		const String& identifier
	): _program(FriendOf<Program>::GetName(program))
	 , _index(_get_index(program, stage, identifier.c_str()))
	{ }
};

/// Encapsulates the uniform subroutine setting operations
/**
 *  @ingroup shader_variables
 */
class UniformSubroutines
 : public FriendOf<Program>
{
private:
	GLuint _program;
	GLenum _stage;
	std::vector<GLuint> _indices;

	static GLsizei _get_index_count(
		GLuint program,
		GLenum stage
	)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetProgramStageiv)(
			program,
			stage,
			GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetProgramStageiv,
			Program,
			nullptr,
			program
		));
		return result;
	}
public:
	/// Constructs a uniform subroutine setter for a @p stage of a @p program
	UniformSubroutines(
		const Program& program,
		const ShaderType stage
	): _program(FriendOf<Program>::GetName(program))
	 , _stage(GLenum(stage))
	 , _indices(_get_index_count(_program, _stage), 0)
	{ }

	/// Assigns the @p subroutine to the subroutine @p uniform
	/**
	 *  @note This function does not apply the changes to the actual
	 *  uniform variables in the stage of the program. Use Apply
	 *  function to do this after the subroutines are assigned.
	 *
	 *  @see Apply
	 */
	UniformSubroutines& Assign(
		const SubroutineUniform& uniform,
		const Subroutine& subroutine
	)
	{
		assert(uniform._program == _program);
		assert(subroutine._program == _program);
		assert(uniform._index <= GLint(_indices.size()));

		_indices[uniform._index] = subroutine._index;
		return *this;
	}

	/// Applies all changes made by Assign
	/**
	 *  @see Assign
	 */
	void Apply(void)
	{
		OGLPLUS_GLFUNC(UniformSubroutinesuiv)(
			_stage,
			GLsizei(_indices.size()),
			_indices.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(UniformSubroutinesuiv));
	}
};
#endif

} // namespace oglplus

#endif // include guard
