/**
 *  @file oglplus/uniform_subroutines.hpp
 *  @brief Wrapper for uniform subroutine operations
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
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

	GLint _do_init_location(GLuint program, const GLchar* identifier) const
	{
		GLint result = OGLPLUS_GLFUNC(GetSubroutineUniformLocation)(
			program,
			GLenum(_stage),
			identifier
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetSubroutineUniformLocation));
		return result;
	}

	void _handle_error(
		GLuint program,
		const GLchar* identifier,
		GLint location
	) const;

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		GLint location = _do_init_location(program, identifier);
		if(OGLPLUS_IS_ERROR(location == GLint(-1)))
		{
			_handle_error(program, identifier, location);
		}
		return location;
	}
public:
	/// Returns this subroutine uniform's program stage
	ShaderType Stage(void) const
	{
		return _stage;
	}
};

typedef EagerUniformInitTpl<SubroutineUniformInitOps>
	EagerSubroutineUniformInit;

typedef LazyUniformInitTpl<SubroutineUniformInitOps, NoUniformTypecheck>
	LazySubroutineUniformInit;


} //namespace aux

/// Template for SubroutineUniform and LazySubroutineUniform
/** @note Do not use directly, use SubroutineUniform or
 *  LazySubroutineUniform instead.
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB,shader_subroutine}
 */
template <class Initializer>
class SubroutineUniformTpl
 : public Initializer
{
private:
	friend class UniformSubroutines;
public:
	template <typename String_>
	SubroutineUniformTpl(
		const Program& program,
		const ShaderType stage,
		String_&& identifier
	): Initializer(
		program,
		stage,
		std::forward<String_>(identifier),
		NoTypecheck()
	)
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
		return this->_try_init_location();
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

#if OGLPLUS_DOCUMENTATION_ONLY
/// Subroutine uniform variable
/**
 *  The difference between SubroutineUniform and LazySubroutineUniform is,
 *  that SubroutineUniform tries to get the location of the GLSL
 *  subroutine uniform variable in a Program during construction
 *  and LazySubroutineUniform postpones this initialization until
 *  the value is actually needed at the cost of having to internally
 *  store the identifer in a String.
 *
 *  @see LazySubroutineUniform
 *  @see Subroutine
 *  @see LazySubroutine
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB,shader_subroutine}
 */
struct SubroutineUniform
 : public SubroutineUniformTpl<Unspecified>
{
	/// Constructionf from a program, stage and identifier
	SubroutineUniform(
		const Program& program,
		const ShaderType stage,
		String identifier
	);
};
#else
typedef SubroutineUniformTpl<aux::EagerSubroutineUniformInit>
	SubroutineUniform;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Lazy subroutine uniform variable
/**
 *  The difference between SubroutineUniform and LazySubroutineUniform is,
 *  that SubroutineUniform tries to get the location of the GLSL
 *  subroutine uniform variable in a Program during construction
 *  and LazySubroutineUniform postpones this initialization until
 *  the value is actually needed at the cost of having to internally
 *  store the identifer in a String.
 *
 *  @see SubroutineUniform
 *  @see Subroutine
 *  @see LazySubroutine
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB,shader_subroutine}
 */
struct LazySubroutineUniform
 : public SubroutineUniformTpl<Unspecified>
{
	/// Constructionf from a program, stage and identifier
	LazySubroutineUniform(
		const Program& program,
		const ShaderType stage,
		String identifier
	);
};
#else
typedef SubroutineUniformTpl<aux::LazySubroutineUniformInit>
	LazySubroutineUniform;
#endif

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

	GLint _do_init_location(GLuint program, const GLchar* identifier) const
	{
		GLint result = OGLPLUS_GLFUNC(GetSubroutineIndex)(
			program,
			GLenum(_stage),
			identifier
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetSubroutineIndex));
		return result;
	}

	void _handle_error(
		GLuint program,
		const GLchar* identifier,
		GLint location
	) const;

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		GLint location = _do_init_location(program, identifier);
		if(OGLPLUS_IS_ERROR(location == GLint(-1)))
		{
			_handle_error(program, identifier, location);
		}
		return location;
	}
public:
	/// Returns this subroutine's program stage
	ShaderType Stage(void) const
	{
		return _stage;
	}
};

typedef EagerUniformInitTpl<SubroutineInitOps>
	EagerSubroutineInit;

typedef LazyUniformInitTpl<SubroutineInitOps, NoUniformTypecheck>
	LazySubroutineInit;

} // namespace aux

/// Template for Subroutine and LazySubroutine
/** @note Do not use directly, use Subroutine or LazySubroutine instead.
 *
 *  @ingroup shader_variables
 */
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
	): Initializer(
		program,
		stage,
		std::forward<String>(identifier),
		NoTypecheck()
	)
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
		return this->_try_init_location();
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


#if OGLPLUS_DOCUMENTATION_ONLY
/// Subroutine variable
/**
 *  The difference between Subroutine and LazySubroutine is,
 *  that Subroutine tries to get the location of the GLSL
 *  function declared as subroutine in a Program during construction
 *  and LazySubroutine postpones this initialization until
 *  the value is actually needed at the cost of having to internally
 *  store the identifer in a String.
 *
 *  @see SubroutineUniform
 *  @see LazySubroutineUniform
 *  @see LazySubroutine
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB,shader_subroutine}
 */
struct Subroutine
 : public SubroutineTpl<Unspecified>
{
	/// Constructionf from a program, stage and identifier
	Subroutine(
		const Program& program,
		const ShaderType stage,
		String identifier
	);
};
#else
typedef SubroutineTpl<aux::EagerSubroutineInit> Subroutine;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Lazy subroutine variable
/**
 *  The difference between Subroutine and LazySubroutine is,
 *  that Subroutine tries to get the location of the GLSL
 *  function declared as subroutine in a Program during construction
 *  and LazySubroutine postpones this initialization until
 *  the value is actually needed at the cost of having to internally
 *  store the identifer in a String.
 *
 *  @see SubroutineUniform
 *  @see LazySubroutineUniform
 *  @see Subroutine
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB,shader_subroutine}
 */
struct LazySubroutine
 : public SubroutineTpl<Unspecified>
{
	/// Constructionf from a program, stage and identifier
	LazySubroutine(
		const Program& program,
		const ShaderType stage,
		String identifier
	);
};
#else
typedef SubroutineTpl<aux::LazySubroutineInit> LazySubroutine;
#endif


/// Encapsulates the uniform subroutine setting operations
/**
 *  @ingroup shader_variables
 *
 *  @glvoereq{4,0,ARB,shader_subroutine}
 */
class UniformSubroutines
 : public FriendOf<Program>
{
private:
	GLuint _program;
	GLenum _stage;
	std::vector<GLuint> _indices;

	static GLsizei _get_location_count(
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

	std::vector<GLuint>& _get_indices(void)
	{
		if(_indices.empty())
			_indices.resize(_get_location_count(_program, _stage), 0);
		return _indices;
	}
public:
	/// Constructs a uniform subroutine setter for a @p stage of a @p program
	UniformSubroutines(
		const Program& program,
		const ShaderType stage
	): _program(FriendOf<Program>::GetName(program))
	 , _stage(GLenum(stage))
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Assigns the @p subroutine to the subroutine @p uniform
	/**
	 *  @note This function does not apply the changes to the actual
	 *  uniform variables in the stage of the program. Use Apply
	 *  function to do this after the subroutines are assigned.
	 *
	 *  @see Apply
	 */
	UniformSubroutines& Assign(
		SubroutineUniform& uniform,
		Subroutine& subroutine
	);
#endif
	template <typename SUInit, typename SInit>
	UniformSubroutines& Assign(
		SubroutineUniformTpl<SUInit>& uniform,
		SubroutineTpl<SInit>& subroutine
	)
	{
		assert(uniform._get_program() == _program);
		assert(subroutine._get_program() == _program);
		assert(uniform.Stage() == ShaderType(_stage));
		assert(subroutine.Stage() == ShaderType(_stage));
		assert(uniform._get_location() <= GLint(_get_indices().size()));

		_get_indices()[uniform._get_location()] = subroutine._get_location();
		return *this;
	}

	/// This type stores a setting of the whole set of subroutine uniforms
	/** Preset stores a whole setting of a set of subroutine uniforms
	 *  which can be later applied or loaded.
	 *
	 *  Applications should treat this type as opaque and use it
	 *  only with the Save, Load and Apply functions.
	 *
	 *  @see Save
	 *  @see Load
	 *  @see Apply
	 */
	class Preset
	{
	private:
		friend class UniformSubroutines;

		const std::vector<GLuint> _indices;
#ifndef NDEBUG
		GLuint _program;
		GLenum _stage;
#endif

		Preset(
#ifndef NDEBUG
			GLuint program,
			GLenum stage,
#endif
			const std::vector<GLuint>& indices
		): _indices(indices)
#ifndef NDEBUG
		 , _program(program)
		 , _stage(stage)
#endif
		{ }
	public:
		Preset(Preset&& tmp)
		 : _indices(std::move(tmp._indices))
#ifndef NDEBUG
		 , _program(tmp._program)
		 , _stage(tmp._stage)
#endif
		{ }
	};

	/// Saves the current setting of subroutine uniforms into a preset
	/**
	 *  @see Preset
	 *  @see Apply
	 *  @see Load
	 */
	Preset Save(void)
	{
		return Preset(
#ifndef NDEBUG
			_program,
			_stage,
#endif
			_get_indices()
		);
	}

	/// Loads the setting of subroutine uniforms from a @p preset
	/** @note Only presets from the same instance of UniformSubroutines
	 *  that saved them can be loaded or applied.
	 *
	 *  @see Preset
	 *  @see Apply
	 *  @see Save
	 */
	void Load(const Preset& preset)
	{
		assert(_program == preset._program);
		assert(_stage == preset._stage);
		assert(_get_indices().size() == preset._indices.size());
		_get_indices() = preset._indices;
	}

	/// Applies the setting from a preset without changing the current setting
	/** @note Only presets from the same instance of UniformSubroutines
	 *  that saved them can be loaded or applied.
	 *
	 *  @see Preset
	 *  @see Save
	 *  @see Load
	 */
	void Apply(const Preset& preset)
	{
		assert(_program == preset._program);
		assert(_stage == preset._stage);
		assert(_get_indices().size() == preset._indices.size());

		OGLPLUS_GLFUNC(UniformSubroutinesuiv)(
			_stage,
			GLsizei(preset._indices.size()),
			preset._indices.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(UniformSubroutinesuiv));
	}

	/// Applies all changes made by Assign
	/**
	 *  @see Assign
	 */
	void Apply(void)
	{
		OGLPLUS_GLFUNC(UniformSubroutinesuiv)(
			_stage,
			GLsizei(_get_indices().size()),
			_get_indices().data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(UniformSubroutinesuiv));
	}
};
#endif

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/uniform_subroutines.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
