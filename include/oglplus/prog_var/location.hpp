/**
 *  @file oglplus/prog_var/location.hpp
 *  @brief Program variable location wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_LOCATION_1405052234_HPP
#define OGLPLUS_PROG_VAR_LOCATION_1405052234_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/name.hpp>
#include <oglplus/error/prog_var.hpp>

namespace oglplus {

template <typename VarTag>
GLint GetGLLocation(ProgVarLoc<VarTag>)
noexcept;

/// Wrapper encapsulating program variable location/index
template <typename VarTag>
class ProgVarLoc
 : public ProgVarLocOps<VarTag>
{
protected:
	friend
	GLint GetGLLocation<VarTag>(ProgVarLoc)
	noexcept;

	GLuint _program;
	GLint _location;

	void RequireActive(const GLCStrRef& identifier) const
	{
		OGLPLUS_HANDLE_ERROR_IF(
			!IsActive(),
			GL_INVALID_OPERATION,
			ProgVarLocOps<VarTag>::MsgUsingInactive(),
			ProgVarError,
			Program(ProgramName(_program)).
			Identifier(identifier)
		);
	}

	void RequireActive(void) const
	{
		RequireActive(GLCStrRef());
	}
public:
	/// Default construction
	ProgVarLoc(void)
	noexcept
	 : _program(0u)
	 , _location(-1)
	{ }

	/// Creates variable without specific @p location in specified @p program
	ProgVarLoc(ProgramName program)
	noexcept
	 : _program(GetGLName(program))
	 , _location(-1)
	{ }

	/// Creates variable with specified @p location without specific program
	explicit
	ProgVarLoc(GLint location)
	noexcept
	 : _program(0)
	 , _location(location)
	{ }

	/// Creates variable with specified @p location in specified @p program
	ProgVarLoc(ProgramName program, GLint location)
	noexcept
	 : _program(GetGLName(program))
	 , _location(location)
	{ }

	/// Creates variable with specified @p identifier in specified @p program
	ProgVarLoc(ProgramName program, const GLCStrRef& identifier)
	 : _program(GetGLName(program))
	 , _location(ProgVarLocOps<VarTag>::GetLocation(
		program,
		identifier,
		true
	)){ }

	template <typename LocOpsParam>
	ProgVarLoc(
		LocOpsParam param,
		ProgramName program,
		const GLCStrRef& identifier
	): ProgVarLocOps<VarTag>(param)
	 , _program(GetGLName(program))
	 , _location(ProgVarLocOps<VarTag>::GetLocation(
		program,
		identifier,
		true
	)){ }

	/// Creates variable with specified @p identifier in specified @p program
	ProgVarLoc(
		ProgramName program,
		const GLCStrRef& identifier,
		bool active_only
	): _program(GetGLName(program))
	 , _location(ProgVarLocOps<VarTag>::GetLocation(
		program,
		identifier,
		active_only
	)){ }

	template <typename LocOpsParam>
	ProgVarLoc(
		LocOpsParam param,
		ProgramName program,
		const GLCStrRef& identifier,
		bool active_only
	): ProgVarLocOps<VarTag>(param)
	 , _program(GetGLName(program))
	 , _location(ProgVarLocOps<VarTag>::GetLocation(
		program,
		identifier,
		active_only
	)){ }

	/// Copy assignment
	ProgVarLoc& Assign(ProgVarLoc that)
	noexcept
	{
		this->_program = that._program;
		this->_location= that._location;
		return *this;
	}

	/// Late initialization of the variable location from its identifier
	ProgVarLoc& BindTo(const GLCStrRef& identifier, bool is_active = true)
	{
		_location = ProgVarLocOps<VarTag>::GetLocation(
			ProgramName(_program),
			identifier,
			is_active
		);
		return *this;
	}

	/// The program the variable belongs to
	ProgramName Program(void) const
	noexcept
	{
		return ProgramName(_program);
	}

	/// Returns the location of the variable
	GLint Location(void) const
	noexcept
	{
		return _location;
	}

	/// Returns true if the variable is active
	bool IsActive(void) const
	noexcept
	{
		return _location >= 0;
	}

	/// Returns true if the variable is active
	explicit
	operator bool (void) const
	noexcept
	{
		return IsActive();
	}

	/// Equality comparison
	friend
	bool operator == (ProgVarLoc a, ProgVarLoc b)
	noexcept
	{
		return	(a._program == b._program) &&
			(a._location == b._location);
	}

	/// Inequality comparison
	friend
	bool operator != (ProgVarLoc a, ProgVarLoc b)
	noexcept
	{
		return	(a._program != b._program) ||
			(a._location != b._location);
	}

	/// Ordering
	friend
	bool operator < (ProgVarLoc a, ProgVarLoc b)
	noexcept
	{
		if(a._program <  b._program) return true;
		if(a._program == b._program)
		{
			return (a._location < b._location);
		}
		return false;
	}
};

/// Returns the GL location/index of the specified @p variable
template <typename VarTag>
inline
GLint GetGLLocation(ProgVarLoc<VarTag> variable)
noexcept
{
	return variable._location;
}

} // namespace oglplus

#endif // include guard
