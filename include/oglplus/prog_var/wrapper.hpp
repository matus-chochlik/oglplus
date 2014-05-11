/**
 *  @file oglplus/prog_var/wrapper.hpp
 *  @brief Program variable wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_WRAPPER_1405052234_HPP
#define OGLPLUS_PROG_VAR_WRAPPER_1405052234_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/prog_var/location.hpp>
#include <oglplus/prog_var/typecheck.hpp>

namespace oglplus {

/// Program variable (vertex attrib / uniform ) wrapper
template <typename OpsTag, typename VarTag, typename ChkTag, typename T>
class ProgVar
 : public ProgVarGetSetOps<OpsTag, VarTag, T>
 , public ProgVarTypecheck<ChkTag, VarTag>
{
private:
	typedef ProgVarGetSetOps<OpsTag, VarTag, T> BaseGetSetOps;
public:
	/// Variable with the specified @p location without a specific program
	ProgVar(GLuint location)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(GLint(location)))
	{ }

	/// Variable with the specified @p location in the specified @p program
	ProgVar(ProgramName program, GLuint location)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program, GLint(location)))
	{ }

	/// Variable with the specified @p identifier in the specified @p program
	ProgVar(ProgramName program, StrCRef identifier)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program, identifier))
	{ }

	/// Sets the variable value if it is active
	void TrySet(const T& value)
	{
		if(this->IsActive())
		{
			this->Set(value);
		}
	}
};

} // namespace oglplus

#endif // include guard
