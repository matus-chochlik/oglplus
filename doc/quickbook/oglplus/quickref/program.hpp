/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_program_common
namespace oglplus {

template <>
class __ObjCommonOps<__tag_Program>
 : public __ProgramName
{
public:
	static __ProgramName Binding(void); /*<
	Returns the currently bound program.
	See [glfunc Get], [glconst PROGRAM_BINDING].
	>*/

	static void Bind(__ProgramName program); /*<
	Binds the specified [^program] object.
	See [glfunc BindProgram].
	>*/
	void Bind(void) const; /*<
	Binds [^this] program object.
	See [glfunc BindProgram].
	>*/

	void Use(void); /*<
	Makes [^this] program current.
	See [glfunc UseProgram].
	>*/
};
//]

//[oglplus_program_1
template <>
class __ObjectOps<__tag_DirectState, __tag_Program>
 : public __ObjZeroOps<__tag_DirectState, __tag_Program>
{
public:
	ObjectOps& AttachShader(__ShaderName shader); /*<
	Attaches a shader to [^this] program.
	See [glfunc AttachShader].
	>*/

	ObjectOps& AttachShaders(const __Sequence<__ShaderName>& shaders); /*<
	Attaches a set of shaders to [^this] program.
	See [glfunc AttachShader].
	>*/

	ObjectOps& DetachShader(__ShaderName shader); /*<
	Detaches a shader from [^this] program.
	See [glfunc DetachShader].
	>*/

	bool IsLinked(void) const; /*<
	Returns true if [^this] program is already linked, false otherwise.
	See [glfunc GetProgram], [glconst LINK_STATUS].
	>*/

	__String GetInfoLog(void) const; /*<
	Returns the linker output if the program is linked.
	See [glfunc GetProgramInfoLog].
	>*/

	ObjectOps& Link(void); /*<
	Links this shading language program.
	Throws __LinkError if the program cannot be linked.
	See [glfunc LinkProgram].
	>*/

	ObjectOps& Build(void); /*<
	Checks if all attached shaders are compiled
	and if they are not the it compiles them and then links
	this __Program.
	Throws __CompileError if any of the shaders cannot be compiled,
	throws __LinkError if the program cannot be linked.
	See [glfunc CompileShader], [glfunc LinkProgram].
	>*/

#if GL_ARB_shading_language_include
	ObjectOps& BuildInclude(
		GLsizei count,
		const GLchar* const* paths,
		const GLint* lengths
	); /*<
	Checks if all attached shaders are compiled
	and if they are not the it compiles them and using the specified
	include paths and then links [^this] __Program.
	See [glfunc CompileShader], [glfunc LinkProgram].
	>*/
	ObjectOps& BuildInclude(__GLSLString&& incl);
	ObjectOps& BuildInclude(__GLSLStrings&& incl);
	ObjectOps& BuildInclude(const __GLSLSource&& incl);
#endif

	bool IsValid(void) const; /*<
	Returns true if [^this] program is validated, false otherwise.
	See [glfunc GetProgram], [glconst VALIDATE_STATUS].
	>*/

	ObjectOps& Validate(void); /*<
	Validates [^this] shading language program.
	Throws __ValidationError if the program is not valid.
	See [glfunc ValidateProgram].
	>*/
//]
//[oglplus_program_2

	void TransformFeedbackVarying(const GLchar* varying); /*<
	Sets the variables that will be captured during transform feedback
	See [glfunc TransformFeedbackVaryings].
	>*/

	void TransformFeedbackVaryings(
		GLsizei count,
		const GLchar** varyings,
		__TransformFeedbackMode mode
	); /*<
	Sets the variables that will be captured during transform feedback
	See [glfunc TransformFeedbackVaryings].
	>*/

	template <typename std::size_t N>
	void TransformFeedbackVaryings(
		const GLchar* (&varyings)[N],
		__TransformFeedbackMode mode
	);

	void TransformFeedbackVaryings(
		const std::vector<__String>& varyings,
		__TransformFeedbackMode mode
	) const;


#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	ObjectOps& MakeSeparable(bool para = true); /*<
	Makes this program separable (or non-separable).
	See [glfunc ProgramParameter].
	>*/
#endif

#if GL_VERSION_4_1 || GL_ARB_get_program_binary
	ObjectOps& MakeRetrievable(bool para = true); /*<
	Makes this program retrievable (or non-retrievable) in binary form.
	See [glfunc ProgramParameter].
	>*/

	void GetBinary(std::vector<GLubyte>& binary, GLenum& format) const; /*<
	Gets the program code in binary form.
	See [glfunc GetProgramBinary].
	>*/

	void Binary(const std::vector<GLubyte>& binary, GLenum format); /*<
	Specifies the program code in binary form.
	See [glfunc ProgramBinary].
	>*/
#endif

	typedef __Unspecified InterfaceContext; /*<
	Helper class for efficient iteration of [^Program] interface items.
	Instances of this class are created by a program for its specific
	interfaces (uniform, vertex attributes, subroutines, etc.) or
	stages (vertex, geometry, fragment, etc.). Instances of an interface
	context can be used (mostly internally) for efficient iteration
	of individual items of a particular interface (uniforms, subroutines,
	etc.). Contexts for various programs and various interfaces are not
	interchangeable.
	The InterfaceContext type should be treated as opaque and only used
	with appropriate functions.
	>*/

#if GL_VERSION_4_3
	typedef __Range<__ProgramResource> ActiveResourceRange; /*<
	The type of the range for traversing program resource information.
	>*/

	InterfaceContext ActiveResourceContext(__ProgramInterface intf) const; /*<
	Returns the context for traversal of Program's active resources.
	>*/

	ActiveResourceRange ActiveResources(__ProgramInterface intf) const; /*<
	Returns a range allowing to do the traversal of interface's resources.
	This instance of [^Program] must be kept alive during the whole
	lifetime of the returned range, i.e. the returned range must not
	be used after the [^Program] goes out of scope and is destroyed.
	>*/
#endif

//]
//[oglplus_program_3
	class ActiveVariableInfo /*<
	Class providing information about a single active vertex attribute
	or uniform.
	Note that the [^Program]'s functions documented as returning instances
	of [^ActiveVariableInfo] actually return types convertible to
	[^ActiveVariableInfo].
	>*/
	{
	public:
		GLuint Index(void) const; /*<
		Returns the index of the attribute or uniform.
		>*/

		const __String& Name(void) const; /*<
		Returns the name (identifier) of the attribute or uniform.
		>*/

		const GLint Size(void) const; /*<
		Returns the size in units of [^Type].
		>*/

		const __SLDataType Type(void) const; /*<
		Returns the data type of the variable.
		>*/
	};

	typedef __Range<ActiveVariableInfo> ActiveAttribRange; /*<
	The type of the range for traversing active vertex attributes.
	>*/
	typedef __Range<ActiveVariableInfo> ActiveUniformRange; /*<
	The type of the range for traversing active uniforms.
	>*/
	typedef __Range<ActiveVariableInfo> ActiveSubroutineUniformRange; /*<
	The type of the range for traversing active subroutine uniforms.
	>*/
	typedef __Range<ActiveVariableInfo> TransformFeedbackVaryingRange; /*<
	The type of the range for traversing transform feedback varyings.
	>*/
// TODO
};

typedef __ObjectOps<__tag_DirectState, __tag_Program> ProgramOps;

typedef __ObjectZero<__ObjZeroOps<__tag_DirectState, __tag_Program>> NoProgram;

typedef __Object<ProgramOps> Program;

} // namespace oglplus
//]

