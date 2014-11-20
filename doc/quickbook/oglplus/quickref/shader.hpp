/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_shader_common
namespace oglplus {

template <>
struct __ObjectSubtype<__tag_Shader>
{
	typedef __ShaderType Type;
};

template <>
class __ObjCommonOps<__tag_Shader>
 : public __ShaderName
{
public:
#if GL_ES_VERSION_3_0 || GL_VERSION_4_1 || GL_ARB_ES2_compatibility
	static void PrecisionFormat(
		__ShaderType shader_type,
		__PrecisionType precision_type,
		GLint* range_log_2,
		GLint* precision_log_2
	); /*< Gets the shader precision format.
	See [glfunc GetShaderPrecisionFormat].
	>*/
};
//]
//[oglplus_shader_1
template <>
class __ObjectOps<__tag_DirectState, __tag_Shader>
 : public __ObjZeroOps<__tag_DirectState, __tag_Shader>
{
public:
	struct Property
	{
		typedef __ShaderType Type;
	};

	__ShaderType Type(void) const; /*<
	Returns the type of [^this] shader.
	See [glfunc GetShader], [glconst SHADER_TYPE].
	>*/

	__ObjectOps& Source(
		const GLsizei count,
		const GLchar* const * srcs,
		const GLint* lens
	); /*<
	Set the source code of this shader.
	See [glfunc ShaderSource].
	>*/
	ObjectOps& Source(__GLSLString&& source);
	ObjectOps& Source(__GLSLStrings&& source);
	ObjectOps& Source(const __GLSLSource& glsl_source);

	bool IsCompiled(void) const; /*<
	Returns true if the shader is already compiled, returns false otherwise.
	See [glfunc GetShader], [glconst COMPILE_STATUS].
	>*/
// TODO
};

} // namespace oglplus
//]

