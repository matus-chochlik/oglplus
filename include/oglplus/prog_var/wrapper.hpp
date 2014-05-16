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

template <typename VarTag>
class ProgVarCommonOps
 : public ProgVarLoc<VarTag>
{
protected:
	ProgVarCommonOps(ProgVarLoc<VarTag> pvloc)
	 : ProgVarLoc<VarTag>(pvloc)
	{ }
public:
};

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
	 , Typecheck((BaseType*)0)
	{ }

	/// Creates variable without specific @p location in specified @p program
	ProgVar(ProgramName program)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program))
	 , Typecheck((BaseType*)0)
	{ }

	/// Variable with the specified @p location without a specific program
	ProgVar(GLuint location)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(GLint(location)))
	 , Typecheck((BaseType*)0)
	{ }

	/// Variable with the specified @p location in the specified @p program
	ProgVar(ProgramName program, GLuint location)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program, GLint(location)))
	 , Typecheck((BaseType*)0)
	{ }

	/// Variable with the specified @p identifier in the specified @p program
	ProgVar(ProgramName program, StrCRef identifier)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program, identifier))
	 , Typecheck((BaseType*)0)
	{
		this->CheckType(program, this->_location, identifier);
	}

	/// Variable with the specified @p identifier in the specified @p program
	ProgVar(ProgramName program, StrCRef identifier, bool active_only)
	 : BaseGetSetOps(ProgVarLoc<VarTag>(program, identifier, active_only))
	 , Typecheck((BaseType*)0)
	{
		this->CheckType(program, this->_location, identifier);
	}

	/// Parameter value type
	typedef typename AdjustProgVar<T>::ValueType ParamType;

	/// Set the variable value
	void Set(ParamType value)
	{
		BaseGetSetOps::SetValue(AdjustProgVar<T>::Adjust(value));
	}

	template <typename T0, typename T1>
	void Set(T0 v0, T1 v1)
	{
		Set(ParamType(v0, v1));
	}

	template <typename T0, typename T1, typename T2>
	void Set(T0 v0, T1 v1, T2 v2)
	{
		Set(ParamType(v0, v1, v2));
	}

	template <typename T0, typename T1, typename T2, typename T3>
	void Set(T0 v0, T1 v1, T2 v2, T3 v3)
	{
		Set(ParamType(v0, v1, v2, v3));
	}

	/// Sets the variable value if it is active
	void TrySet(ParamType value)
	{
		if(this->IsActive())
		{
			BaseGetSetOps::SetValue(AdjustProgVar<T>::Adjust(value));
		}
	}

	/// Sets the variable value
	ProgVar& operator = (ParamType value)
	{
		this->Set(value);
		return *this;
	}
};

template <typename ProgVar>
struct BaseProgVar;

template <typename OpsTag, typename VarTag, typename ChkTag, typename T>
struct BaseProgVar<ProgVar<OpsTag, VarTag, ChkTag, T>>
{
	typedef ProgVar<OpsTag, VarTag, ChkTag, T> Type;
};

#if !OGLPLUS_NO_INHERITED_CONSTRUCTORS
#define OGLPLUS_IMPLEMENT_PROG_VAR_CTRS(VAR_TAG, PROG_VAR, BASE) \
	using Base::Base;

#else
#define OGLPLUS_IMPLEMENT_PROG_VAR_CTRS(VAR_TAG, PROG_VAR, BASE) \
	PROG_VAR(ProgVarLoc<VAR_TAG> pvloc) : BASE(pvloc) { } \
	PROG_VAR(ProgramName program) : BASE(program) { } \
	PROG_VAR(GLuint location) : BASE(location) { } \
	PROG_VAR(ProgramName program, GLuint location) \
	 : BASE(program, location) { } \
	PROG_VAR(ProgramName program, StrCRef identifier) \
	 : BASE(program, identifier) { } \
	PROG_VAR(ProgramName program, StrCRef identifier, bool active_only) \
	 : BASE(program, identifier, active_only) { }
#endif

#if !OGLPLUS_NO_TEMPLATE_ALIASES

// OGLPLUS_DECLARE_PROG_VAR
#define OGLPLUS_DECLARE_PROG_VAR(PROG_VAR, OPS_TAG, VAR_TAG, CHK_TAG) \
template <typename T> \
using PROG_VAR = ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T>;

#else

// OGLPLUS_DECLARE_PROG_VAR
#define OGLPLUS_DECLARE_PROG_VAR(PROG_VAR, OPS_TAG, VAR_TAG, CHK_TAG) \
template <typename T> \
class PROG_VAR \
 : public ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> \
{ \
private:\
	typedef ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> Base;\
public:\
	OGLPLUS_IMPLEMENT_VAR_TAG_CTRS(VAR_TAG, PROG_VAR, Base) \
	PROG_VAR& operator = (ParamType value) \
	{ \
		this->Set(value); \
		return *this; \
	} \
}; \
template <typename T> \
struct BaseProgVar<PROG_VAR> \
{ \
	typedef ProgVar<OPS_TAG, VAR_TAG, CHK_TAG, T> Type;\
};
#endif

} // namespace oglplus

#endif // include guard
