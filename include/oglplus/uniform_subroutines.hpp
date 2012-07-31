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
#include <oglplus/auxiliary/uniform_init.hpp>

#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_0 || GL_ARB_shader_subroutine
class UniformSubroutines;

namespace aux {

class SubroutineUniformInitOps
{
private:
	ShaderType _stage;
protected:
	typedef ShaderType ParamType;

	SubroutineUniformInitOps(ShaderType stage)
	 : _stage(stage)
	{ }

	GLint _do_init_index(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetSubroutineUniformLocation)(
			program,
			GLenum(_stage),
			identifier
		);
	}

	GLint _init_index(GLuint program, const GLchar* identifier) const
	{
		GLint index = _do_init_index(program, identifier);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetSubroutineUniformLocation));
		if(OGLPLUS_IS_ERROR(index == GLint(-1)))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["stage"] = EnumValueName(_stage);
			props["program"] = aux::ObjectDescRegistry<ProgramOps>::
						_get_desc(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform",
				OGLPLUS_ERROR_INFO(GetSubroutineUniformLocation),
				std::move(props)
			);
		}
		return index;
	}
};

typedef EagerUniformInitTpl<SubroutineUniformInitOps>
	EagerSubroutineUniformInit;

typedef LazyUniformInitTpl<SubroutineUniformInitOps>
	LazySubroutineUniformInit;


} //namespace aux

template <class Initializer>
class SubroutineUniformTpl
 : public Initializer
{
private:
	friend class UniformSubroutines;
public:
	template <typename String>
	SubroutineUniformTpl(
		const Program& program,
		const ShaderType stage,
		String&& identifier
	): Initializer(program, stage, std::forward<String>(identifier))
	{ }

	/// Tests if this SubroutineUniform is active and can be used
	/**
	 *  For SubroutineUniform this function always
	 *  returns true as it cannot be in uninitialized state.
	 *  For LazySubroutineUniform this function
	 *  returns true if the uniform is active and can be referenced
	 *  and used for subsequent operations.
	 *  If this function returns false then trying to use the
	 *  uniform throws an exception.
	 */
	bool IsActive(void)
	{
		return this->_try_init_index();
	}

	/// Equivalent to IsActive()
	/**
	 *  @see IsActive
	 */
	operator bool (void)
	{
		return IsActive();
	}

	/// Equivalent to !IsActive()
	/**
	 *  @see IsActive
	 */
	bool operator ! (void)
	{
		return !IsActive();
	}
};

typedef SubroutineUniformTpl<aux::EagerSubroutineUniformInit>
	SubroutineUniform;

typedef SubroutineUniformTpl<aux::LazySubroutineUniformInit>
	LazySubroutineUniform;

namespace aux {

class SubroutineInitOps
{
private:
	ShaderType _stage;
protected:
	typedef ShaderType ParamType;

	SubroutineInitOps(ShaderType stage)
	 : _stage(stage)
	{ }

	GLint _do_init_index(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetSubroutineIndex)(
			program,
			GLenum(_stage),
			identifier
		);
	}

	GLint _init_index(GLuint program, const GLchar* identifier) const
	{
		GLint index = _do_init_index(program, identifier);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetSubroutineIndex));
		if(OGLPLUS_IS_ERROR(index == GLint(-1)))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = aux::ObjectDescRegistry<ProgramOps>::
						_get_desc(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive subroutine",
				OGLPLUS_ERROR_INFO(GetSubroutineIndex),
				std::move(props)
			);
		}
		return index;
	}
};

typedef EagerUniformInitTpl<SubroutineInitOps>
	EagerSubroutineInit;

typedef LazyUniformInitTpl<SubroutineInitOps>
	LazySubroutineInit;

} // namespace aux

template <class Initializer>
class SubroutineTpl
 : public Initializer
{
private:
	friend class UniformSubroutines;
public:
	template <class String>
	SubroutineTpl(
		const Program& program,
		const ShaderType stage,
		String&& identifier
	): Initializer(program, stage, std::forward<String>(identifier))
	{ }

	/// Tests if this Subroutine is active and can be used
	/**
	 *  For Subroutine this function always
	 *  returns true as it cannot be in uninitialized state.
	 *  For LazySubroutine this function
	 *  returns true if the subroutine is active and can be referenced
	 *  and used for subsequent assignment operations.
	 *  If this function returns false then trying to use the
	 *  subroutine throws an exception.
	 */
	bool IsActive(void)
	{
		return this->_try_init_index();
	}

	/// Equivalent to IsActive()
	/**
	 *  @see IsActive
	 */
	operator bool (void)
	{
		return IsActive();
	}

	/// Equivalent to !IsActive()
	/**
	 *  @see IsActive
	 */
	bool operator ! (void)
	{
		return !IsActive();
	}
};

typedef SubroutineTpl<aux::EagerSubroutineInit> Subroutine;

typedef SubroutineTpl<aux::LazySubroutineInit> LazySubroutine;


/// Encapsulates the uniform subroutine setting operations
/**
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB_shader_subroutine}
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
		assert(uniform._get_program() == _program);
		assert(subroutine._get_program() == _program);
		assert(uniform._get_index() <= GLint(_indices.size()));

		_indices[uniform._get_index()] = subroutine._get_index();
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
