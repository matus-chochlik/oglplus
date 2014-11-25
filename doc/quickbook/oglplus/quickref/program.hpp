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
	See [glfunc LinkProgram].
	>*/

	ObjectOps& Build(void); /*<
	Checks if all attached shaders are compiled
	and if they are not the it compiles them and then links
	this __Program.
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
// TODO
};

} // namespace oglplus
//]

