/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_uniform
namespace oglplus {

template <typename T>
class Uniform
 : public __ProgVar<__tag_ImplicitSel, __tag_Uniform, __tag_NoTypecheck, T>
{
public:
	using __ProgVar<
		__tag_ImplicitSel,
		__tag_Uniform,
		__tag_NoTypecheck,
		T
	>::ProgVar; /*<
	[^Uniform] inherits the constructors from __ProgVar.
	>*/

	static GLint GetLocation(
		__ProgramName program,
		__StrCRef identifier,
		bool active_only
	); /*<
	Finds the location of the uniform variable specified
	by [^identifier] in a [^program]. If [^active_only] is [^true] then
	throws __ProgVarError if no such uniform exists or if it is not active.
	See [glfunc GetUniformLocation].
	>*/

	void Set(T value); /*<
	Sets the uniform variable to the specified value.
	Throws if the referenced variable is not active.
	>*/

	void Set(std::size_t count, const T* values);

	void Set(const std::vector<T>& values);

	void TrySet(T value); /*<
	Sets the uniform variable to the specified value,
	but only if the referenced variable is active.
	>*/
};

//]
//[oglplus_untyped_uniform

typedef __ProgVar<
	__tag_ImplicitSel,
	__tag_Uniform,
	__tag_NoTypecheck,
	void
> UntypedUniform;

UntypedUniform
operator / (__ProgramName program, __StrCRef identifier);

} // namespace oglplus
//]

