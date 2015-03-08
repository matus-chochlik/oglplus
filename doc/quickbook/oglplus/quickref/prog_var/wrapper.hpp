/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_prog_var_common_ops
namespace oglplus {

template <typename __VarTag>
class ProgVarCommonOps
 : public __ProgVarLoc<__VarTag>
{
public:
};

//]
//[oglplus_prog_var_get_set_ops

template <typename __OpsTag, typename __VarTag, typename T>
class ProgVarGetSetOps
 : public __ProgVarCommonOps<__VarTag>
{
public:
	void SetValue(T value);
};


//]
//[oglplus_prog_var_typecheck

template <typename __ChkTag, typename __VarTag>
class ProgVarTypecheck
{
public:
	void CheckType(
		__ProgramName program,
		GLint location,
		__StrCRef identifier
	) const;
};

//]
//[oglplus_prog_var_wrapper

template <typename __OpsTag, typename __VarTag, typename __ChkTag, typename T>
class ProgVar
 : public __ProgVarGetSetOps<__OpsTag, __VarTag, T>
 , public __ProgVarTypecheck<__ChkTag, __VarTag>
{
public:
	ProgVar(void);
	ProgVar(const ProgVar&);

	ProgVar(__ProgVarLoc<__VarTag> pvloc);

	ProgVar(__ProgramName program, GLuint location);

	ProgVar(__ProgramName program, __StrCRef identifier);

	ProgVar(__ProgramName program, __StrCRef identifier, bool active_only);

	ProgVar(__ProgramName program, __StrCRef identifier, std::nothrow_t);

	ProgVar& BindTo(__StrCRef identifier);

	ProgVar operator[](std::size_t offset) const;

	ProgVar& operator = (const ProgVar& var);
	ProgVar& operator = (__ProgVarLoc<__VarTag> pvloc);

	void Set(T value);

	void Set(std::size_t count, const T* values);

	void Set(const std::vector<T>& values);

	template <typename ... P>
	void Set(P ... v);

	void TrySet(T value);
};
// TODO

} // namespace oglplus
//]

