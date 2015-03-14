/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_subroutine_loc_ops
namespace oglplus {

template <>
class __ProgVarLocOps<__tag_Subroutine>
{
public:
	static GLint GetLocation(
		__ProgramName program,
		__ShaderType stage,
		__StrCRef identifier,
		bool active_only
	); /*<
	Finds the location of the subroutine specified by [^identifier]
	in the [^stage] of a [^program]. If [^active_only] is [^true] then
	throws __ProgVarError if no such subroutine exists or if it is not active.
	See [glfunc GetSubroutineIndex].
	>*/

	GLint GetLocation(
		__ProgramName program,
		__StrCRef identifier,
		bool active_only
	) const;

	__ShaderType Stage(void) const; /*<
	Returns this subroutine's program stage.
	>*/
};

//]
//[oglplus_subroutine_uniform_loc_ops

template <>
class __ProgVarLocOps<__tag_SubroutineUniform>
{
public:
	static GLint GetLocation(
		__ProgramName program,
		__ShaderType stage,
		__StrCRef identifier,
		bool active_only
	); /*<
	Finds the location of the subroutine uniform specified by [^identifier]
	in the [^stage] of a [^program]. If [^active_only] is [^true] then
	throws __ProgVarError if no such uniform exists or if it is not active.
	See [glfunc GetSubroutineUniformLocation].
	>*/

	GLint GetLocation(
		__ProgramName program,
		__StrCRef identifier,
		bool active_only
	) const;

	__ShaderType Stage(void) const; /*<
	Returns this subroutine uniforms's program stage.
	>*/
};

//]
//[oglplus_subroutine_prog_var

template <>
class __ProgVar<__tag_ImplicitSel, __tag_Subroutine, __tag_NoTypecheck, void>
 : public __ProgVarLoc<__tag_Subroutine>
{
public:
	ProgVar(__ProgVarLoc<__tag_Subroutine> pvloc);

	ProgVar(__ProgramName program, __ShaderType stage, __StrCRef identifier);

	ProgVar(
		__ProgramName program,
		__ShaderType stage,
		__StrCRef identifier,
		bool active_only
	);
};

//]
//[oglplus_subroutine_uniform_prog_var

template <>
class __ProgVar<__tag_ImplicitSel, __tag_SubroutineUniform, __tag_NoTypecheck, void>
 : public __ProgVarLoc<__tag_SubroutineUniform>
{
public:
	ProgVar(__ProgVarLoc<__tag_SubroutineUniform> pvloc);

	ProgVar(__ProgramName program, __ShaderType stage, __StrCRef identifier);

	ProgVar(
		__ProgramName program,
		__ShaderType stage,
		__StrCRef identifier,
		bool active_only
	);
};

//]
//[oglplus_subroutine_def

typedef __ProgVar_Subroutine<
	__tag_ImplicitSel,
	__tag_Subroutine,
	__tag_NoTypecheck,
	void
> Subroutine;

//]
//[oglplus_subroutine_uniform_def

typedef __ProgVar_SubroutineUniform<
	__tag_ImplicitSel,
	__tag_SubroutineUniform,
	__tag_NoTypecheck,
	void
> SubroutineUniform;

//TODO

} // namespace oglplus
//]

