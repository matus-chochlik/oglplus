/**
 *  @file oglplus/prog_var/location.hpp
 *  @brief Program variable location getters
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
#include <oglplus/object/tags.hpp>
#include <oglplus/object/name.hpp>

namespace oglplus {

/// Wrapper encapsulating program variable location/index
template <typename VarTag>
class ProgVarLoc
{
private:
	friend GLint GetGLLocation<VarTag>(ProgVarLoc);
	GLuint _prog;
	GLint _location;
public:
	ProgVarLoc(ProgramName prog, GLint location)
	OGLPLUS_NOEXCEPT(true)
	 : _prog(GetGLName(prog))
	 , _location(location)
	{ }

	/// The program the variable belongs to
	ProgramName Program(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return ProgramName(_prog);
	}

	/// Returns true if the variable is active
	bool IsActive(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _location >= 0;
	}

	/// Equality comparison
	friend bool operator == (ProgVarLoc a, ProgVarLoc b)
	OGLPLUS_NOEXCEPT(true)
	{
		return (a._prog == b._prog) && (a._location == b._location);
	}

	/// Inequality comparison
	friend bool operator != (ProgVarLoc a, ProgVarLoc b)
	OGLPLUS_NOEXCEPT(true)
	{
		return (a._prog != b._prog) || (a._location != b._location);
	}

	/// Ordering
	friend bool operator < (ProgVarLoc a, ProgVarLoc b)
	OGLPLUS_NOEXCEPT(true)
	{
		if(a._prog <  b._prog) return true;
		if(a._prog == b._prog) return (a._location < b._location);
		return false;
	}
};

/// Returns the GL location/index of the specified @p variable
template <typename VarTag>
inline GLint GetGLLocation(ProgVarLoc<VarTag> variable)
{
	return variable._location;
}

} // namespace oglplus

#endif // include guard
