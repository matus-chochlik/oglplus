/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_prog_var_location
namespace oglplus {

template <typename __VarTag>
class ProgVarLoc
 : public __ProgVarLocOps<__VarTag>
{
public:
	ProgVarLoc(void)
	noexcept;

	ProgVarLoc(__ProgramName program)
	noexcept; /*<
	Creates variable without specific location in the specified [^program].
	The location can be specified later.
	>*/

	explicit
	ProgVarLoc(GLint location)
	noexcept; /*<
	Creates variable with specified [^location] without a reference
	to a specific program. The program can be specified later.
	>*/

	ProgVarLoc(__ProgramName program, GLint location)
	noexcept; /*<
	Creates variable with the specified [^location] in the specified [^program].
	>*/

	ProgVarLoc(__ProgramName program, __CStrRef identifier); /*<
	Creates variable with the specified [^identifier] in the specified [^program].
	>*/

	ProgVarLoc(__ProgramName program, CStrRef identifier, bool active_only); /*<
	Creates variable with the specified [^identifier] in the specified [^program].
	This overload allows to specify whether the constructor should throw
	if no such variable is active in the program. If [^active_only] is [^true]
	then the constructor throws.
	>*/

	ProgVarLoc& BindTo(__CStrRef identifier, bool is_active = true); /*<
	Late initialization of the variable location from its identifier.
	The program name must already be specified.
	>*/

	__ProgramName Program(void) const
	noexcept; /*<
	The [^program] that [^this] variable belongs to.
	>*/

	GLint Location(void) const
	noexcept; /*<
	The location of [^this] variable.
	>*/

	bool IsActive(void) const
	noexcept; /*<
	Returns [^true] if the variable is active, false otherwise.
	>*/

	explicit
	operator bool (void) const
	noexcept; /*<
	Returns [^true] if the variable is active, false otherwise.
	Synonym for [^Active].
	>*/

	friend bool operator == (ProgVarLoc a, ProgVarLoc b)
	noexcept;

	friend bool operator != (ProgVarLoc a, ProgVarLoc b)
	noexcept;

	friend bool operator < (ProgVarLoc a, ProgVarLoc b)
	noexcept;
};

/// Returns the GL location/index of the specified @p variable
template <typename __VarTag>
GLint GetGLLocation(__ProgVarLoc<__VarTag> variable);

} // namespace oglplus
//]

