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
 : public ProgVarGetSetOps<OpsTag, VarTag, typename AdjustProgVar<T>::BaseType>
 , public ProgVarTypecheck<ChkTag, VarTag>
{
private:
	typedef typename AdjustProgVar<T>::BaseType BaseType;
	typedef ProgVarGetSetOps<OpsTag, VarTag, BaseType> BaseGetSetOps;
	typedef ProgVarTypecheck<ChkTag, VarTag> Typecheck;
public:
	/// Variable from a ProgVarLoc
	ProgVar(ProgVarLoc<VarTag> pvloc)
	 : BaseGetSetOps(pvloc)
	{ }

	/// Creates variable without specific @p location in specified @p program
	ProgVar(ProgramName program)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program))
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
	 , Typecheck((BaseType*)0, program, this->_location, identifier)
	{ }

	/// Variable with the specified @p identifier in the specified @p program
	ProgVar(ProgramName program, StrCRef identifier, bool active_only)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program, identifier, active_only))
	 , Typecheck((BaseType*)0, program, this->_location, identifier)
	{ }

	/// Parameter value type
	typedef typename AdjustProgVar<T>::ValueType ParamType;

	/// Set the variable value
	void Set(ParamType value)
	{
		BaseGetSetOps::SetValue(AdjustProgVar<T>::Adjust(value));
	}

	/// Sets the variable value if it is active
	void TrySet(ParamType value)
	{
		if(this->IsActive())
		{
			BaseGetSetOps::SetValue(AdjustProgVar<T>::Adjust(value));
		}
	}
};

// TODO: use template alias when available
#if !OGLPLUS_NO_INHERITED_CONSTRUCTORS
#define OGLPLUS_DECLARE_PROG_VAR(PROG_VAR, OPS_TAG, VAR_TAG, CHK_TAG) \
template <typename T> \
class PROG_VAR \
 : public ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> \
{ \
public: \
	using ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T>::ProgVar; \
};
#else
#define OGLPLUS_DECLARE_PROG_VAR(PROG_VAR, OPS_TAG, VAR_TAG, CHK_TAG) \
template <typename T> \
class PROG_VAR \
 : public ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> \
{ \
private:\
	typedef ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> Base;\
public:\
	PROG_VAR(ProgVarLoc<VAR_TAG> pvloc) : Base(pvloc) { } \
	PROG_VAR(ProgramName program) : Base(program) { } \
	PROG_VAR(GLuint location) : Base(location) { } \
	PROG_VAR(ProgramName program, GLuint location) \
	 : Base(program, location) { } \
	PROG_VAR(ProgramName program, StrCRef identifier) \
	 : Base(program, identifier) { } \
	PROG_VAR(ProgramName program, StrCRef identifier, bool active_only) \
	 : Base(program, identifier, active_only) { } \
};
#endif

} // namespace oglplus

#endif // include guard
