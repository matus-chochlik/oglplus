/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_vertex_attrib
namespace oglplus {

template <typename T>
class VertexAttrib
 : public __ProgVar<__tag_ImplicitSel, __tag_VertexAttrib, __tag_NoTypecheck, T>
{
public:
	using __ProgVar<
		__tag_ImplicitSel,
		__tag_Uniform,
		__tag_NoTypecheck,
		T
	>::ProgVar; /*<
	[^VertexAttrib] inherits the constructors from __ProgVar.
	>*/

	static void BindLocation(
		__ProgramName program,
		__VertexAttribSlot location,
		__StrCRef identifier
	); /*<
	Binds the vertex attribute location.
	See [glfunc BindAttribLocation].
	>*/

	static GLint GetLocation(
		__ProgramName program,
		__StrCRef identifier,
		bool active_only
	); /*<
	Finds the location of the input vertex attribute specified
	by [^identifier] in a [^program]. If [^active_only] is [^true] then
	throws if no such attribute exists or if it is not active.
	For a non-throwing version see QueryActiveLocation().
	See [glfunc GetAttribLocation].
	>*/
	static VertexAttribSlot GetLocation(
		__ProgramName program,
		__StrCRef identifier
	); /*<
	Equivalent to [^GetLocation(program, identifier, true)].
	>*/

	static bool QueryActiveLocation(
		__ProgramName program,
		__StrCRef identifier,
		__VertexAttribSlot& location
	); /*<
	Queries the vertex attribute location, returns [^false] on failure.
	See [glfunc GetAttribLocation].
	>*/

	static bool QueryCommonLocation(
		const __Sequence<__ProgramName>& programs,
		__StrCRef identifier,
		__VertexAttribSlot& location
	); /*<
	Allows to query the vertex attribute [^location] in multiple [^programs]
	This function returns a temporary object that allows to query
	the [^location] of the specified [^identifier] in several programs.
	The returned object has two functions called [^In] and [^And]
	which are equivalent and take a __Program as the argument. Both
	these functions return in turn a new instance of the temporary
	which allows to check in another program, and so on.
	The temporary is also convertible to [^bool] indicating whether
	a common location was found in all programs in the chain.
	See [glfunc GetAttribLocation].
	[note Never store the resulting object in a named variable
	nor use it after the call to this overload of QueryCommonLocation
	has finished. Doing this causes undefined behavior.]
	>*/

	static __VertexAttribSlot GetCommonLocation(
		const __Sequence<__ProgramName>& programs,
		__StrCRef identifier
	); /*<
	Returns vertex attribute location in multiple programs if it's consistent.
	Finds the location of the input vertex attribute specified
	by [^identifier] in every program in [^programs].
	Throws __Error if no such attribute exists or if it is not active
	in some of the programs or if the attribute has different locations
	in different programs. Otherwise returns the vertex attribute
	position.
	See [glfunc GetAttribLocation].
	>*/

	void Set(T value); /*<
	Sets the vertex attribute to the specified value.
	Throws if the referenced variable is not active.
	>*/

	void TrySet(T value); /*<
	Sets the vertex attribute to the specified value,
	but only if the referenced variable is active.
	>*/
};
// TODO

//]
//[oglplus_vertex_array_attrib

class VertexArrayAttrib
 : public __ProgVarCommonOps<__tag_VertexAttrib>
{
public:
	VertexArrayAttrib(VertexAttribSlot location);

	VertexArrayAttrib(__ProgramName program, __VertexAttribSlot location);

	VertexArrayAttrib(__ProgramName program, __StrCRef identifier);

	const VertexArrayAttrib& Setup(
		GLint values_per_vertex,
		__DataType data_type
	) const;

	const VertexArrayAttrib& Setup(
		GLint values_per_vertex,
		__DataType data_type
	) const; /*<
	Sets up the properties of [^this] vertex attribute array.
	See [glfunc VertexAttribPointer].
	[note Consider using the templated version of Setup(), because
	it is more portable.]
	>*/

	template <typename T>
	const VertexArrayAttrib& Setup(GLuint n = 1) const; /*<
	Sets up the properties of [^this] vertex attribute array.
	See [glfunc VertexAttribPointer].
	>*/

	const VertexArrayAttrib& Pointer(
		GLint values_per_vertex,
		__DataType data_type,
		__Boolean normalized,
		GLsizei stride,
		const void* pointer
	) const; /*<
	See [glfunc VertexAttribPointer].
	>*/

	const VertexArrayAttrib& IPointer(
		GLuint values_per_vertex,
		DataType data_type,
		GLsizei stride,
		const void* pointer
	) const; /*<
	See [glfunc VertexAttribIPointer].
	>*/

#if GL_VERSION_4_2 || GL_ARB_vertex_attrib_64bit
	const VertexArrayAttrib& LPointer(
		GLuint values_per_vertex,
		__DataType data_type,
		GLsizei stride,
		const void* pointer
	) const; /*<
	See [glfunc VertexAttribLPointer].
	>*/
#endif

#if GL_VERSION_4_3 || GL_ARB_vertex_attrib_binding
	const VertexArrayAttrib& Format(
		GLint values_per_vertex,
		__DataType data_type,
		__Boolean normalized,
		GLuint relative_offset
	) const; /*<
	See [glfunc VertexAttribFormat].
	>*/

	const VertexArrayAttrib& IFormat(
		GLint values_per_vertex,
		__DataType data_type,
		GLuint relative_offset
	) const; /*<
	See [glfunc VertexAttribIFormat].
	>*/

	const VertexArrayAttrib& LFormat(
		GLint values_per_vertex,
		__DataType data_type,
		GLuint relative_offset
	) const; /*<
	See [glfunc VertexAttribLFormat].
	>*/
#endif

	const VertexArrayAttrib& Enable(void) const; /*<
	Enables [^this] vertex attribute array.
	See [glfunc EnableVertexArrayAttrib].
	>*/

	const VertexArrayAttrib& Disable(void) const; /*<
	Disables [^this] vertex attribute array.
	See [glfunc DisableVertexArrayAttrib].
	>*/
};

template <std::size_t N>
__VertexArrayAttrib operator | (
	__ProgramName program,
	const GLchar (&identifier)[N]
);

__VertexArrayAttrib operator | (
	ProgramName program,
	GLuint location
);

} // namespace oglplus
//]

