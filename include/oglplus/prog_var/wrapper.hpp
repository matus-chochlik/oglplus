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
	/// Variable from a ProgVarLoc
	ProgVar(ProgVarLoc<VarTag> pvloc)
	 : BaseGetSetOps(pvloc)
	{ }

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

// TODO: template alias when available
#define OGLPLUS_DECLARE_PROG_VAR(PROG_VAR, OPS_TAG, VAR_TAG, CHK_TAG) \
template <typename T> \
class PROG_VAR \
 : public ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> \
{ \
private:\
	typedef ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> Base;\
public:\
	PROG_VAR(ProgVarLoc<VAR_TAG> pvloc) : Base(pvloc) { } \
	PROG_VAR(GLuint location) : Base(location) { } \
	PROG_VAR(ProgramName program, GLuint location) \
	 : Base(program, location) { } \
	PROG_VAR(ProgramName program, StrCRef identifier) \
	 : Base(program, identifier) { } \
};

} // namespace oglplus

#endif // include guard
