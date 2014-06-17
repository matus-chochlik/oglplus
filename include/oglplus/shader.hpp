/**
 *  @file oglplus/shader.hpp
 *  @brief Shader wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHADER_1107121519_HPP
#define OGLPLUS_SHADER_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/object/wrapper.hpp>
#include <oglplus/object/array.hpp>
#include <oglplus/error/program.hpp>
#include <oglplus/precision_type.hpp>
#include <oglplus/shader_type.hpp>
#include <oglplus/glsl_source.hpp>

#include <array>
#include <vector>
#include <cassert>

namespace oglplus {

/// Class wrapping shader construction/destruction functions
/** @note Do not use this class directly, use Shader instead.
 *
 *  @glsymbols
 *  @glfunref{CreateShader}
 *  @glfunref{DeleteShader}
 *  @glfunref{IsShader}
 */
template <>
class ObjGenDelOps<tag::Shader>
{
protected:
	static void Gen(GLsizei count, GLuint* names, GLenum type)
	{
		assert(names != nullptr);
		for(GLsizei i=0; i<count; ++i)
		{
			names[i] = OGLPLUS_GLFUNC(CreateShader)(type);
			OGLPLUS_CHECK_SIMPLE(CreateShader);
		}
	}

	GLenum _type;

	void Gen(GLsizei count, GLuint* names) const
	{
		Gen(count, names, _type);
	}

	static void Delete(GLsizei count, GLuint* names)
	{
		assert(names != nullptr);
		for(GLsizei i=0; i<count; ++i)
		{
			OGLPLUS_GLFUNC(DeleteShader)(names[i]);
			OGLPLUS_VERIFY_SIMPLE(DeleteShader);
		}
	}

	static GLboolean IsA(GLuint name)
	{
		assert(name != 0);
		GLboolean result = OGLPLUS_GLFUNC(IsShader)(name);
		OGLPLUS_VERIFY_SIMPLE(IsShader);
		return result;
	}
};

/// Common shader operations
/** @note Do not use this class directly, use Shader instead.
 */
template <>
class ObjCommonOps<tag::Shader>
 : public ShaderName
{
protected:
	ObjCommonOps(void) { }

#if OGLPLUS_DOCUMENTATION_ONLY || \
	GL_ES_VERSION_3_0 || \
	GL_VERSION_4_1 || \
	GL_ARB_ES2_compatibility
	/// Get the shader precision format
	/**
	 *  @glvoereq{4,1,ARB,ES2_compatibility}
	 *  @glsymbols
	 *  @glfunref{GetShaderPrecisionFormat}
	 */
	static void PrecisionFormat(
		ShaderType shader_type,
		PrecisionType precision_type,
		GLint* range_log_2,
		GLint* precision_log_2
	)
	{
		OGLPLUS_GLFUNC(GetShaderPrecisionFormat)(
			GLenum(shader_type),
			GLenum(precision_type),
			range_log_2,
			precision_log_2
		);
		OGLPLUS_VERIFY_SIMPLE(GetShaderPrecisionFormat);
	}
#endif
};

/// Class wrapping shader functions (with direct state access)
/** @note Do not use this class directly, use Shader instead.
 */
template <>
class ObjectOps<tag::DirectState, tag::Shader>
 : public ObjCommonOps<tag::Shader>
{
protected:
	ObjectOps(void){ }
public:
	/// Types related to Shader
	struct Property
	{
		/// The type of a Shader
		typedef ShaderType Type;
	};

	/// Get the type of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{GetShader}
	 *  @gldefref{SHADER_TYPE}
	 */
	ShaderType Type(void) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetShaderiv)(
			_name,
			GL_SHADER_TYPE,
			&result
		);
		OGLPLUS_VERIFY(
			GetShaderiv,
			ObjectError,
			Object(*this)
		);
		return ShaderType(result);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(
		const GLchar** srcs,
		const GLint* lens,
		int count
	)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ShaderSource)(_name, count, srcs, lens);
		return *this;
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(const String& source)
	{
		const GLchar* srcs[1] = {source.c_str()};
		GLint lens[1] = {GLint(source.size())};
		return Source(srcs, lens, 1);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(const StrLit& source)
	{
		const GLchar* srcs[1] = {source.c_str()};
		GLint lens[1] = {GLint(source.size())};
		return Source(srcs, lens, 1);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(const GLchar* source)
	{
		return Source(&source, nullptr, 1);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(const GLchar** srcs, int count)
	{
		return Source(srcs, nullptr, count);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(const std::vector<const GLchar*>& srcs)
	{
		return Source(
			const_cast<const GLchar**>(srcs.data()),
			nullptr,
			srcs.size()
		);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	template <std::size_t N>
	ObjectOps& Source(
		const std::array<const GLchar*, N>& srcs
	)
	{
		return Source(
			const_cast<const GLchar**>(srcs.data()),
			nullptr,
			srcs.size()
		);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	ObjectOps& Source(const GLSLSource& glsl_source)
	{
		return Source(
			glsl_source.Parts(),
			glsl_source.Lengths(),
			glsl_source.Count()
		);
	}

	/// Returns true if the shader is already compiled, returns false otherwise
	/**
	 *  @see Compile
	 *
	 *  @glsymbols
	 *  @glfunref{GetShader}
	 *  @gldefref{COMPILE_STATUS}
	 */
	bool IsCompiled(void) const
	{
		assert(_name != 0);
		int status;
		OGLPLUS_GLFUNC(GetShaderiv)(_name, GL_COMPILE_STATUS, &status);
		OGLPLUS_VERIFY(
			GetShaderiv,
			ObjectError,
			Object(*this).
			EnumParam(Type())
		);
		return status == GL_TRUE;
	}

	/// Returns the compiler output if the program is compiled
	/**
	 *  @see IsCompiled
	 *  @see Compile
	 *
	 *  @glsymbols
	 *  @glfunref{GetShader}
	 *  @glfunref{GetShaderInfoLog}
	 */
	String GetInfoLog(void) const;

	/// Compiles the shader
	/**
	 *  @post IsCompiled()
	 *  @throws Error CompileError
	 *  @see IsCompiled
	 *
	 *  @glsymbols
	 *  @glfunref{CompileShader}
	 */
	ObjectOps& Compile(void);

#if OGLPLUS_DOCUMENTATION_ONLY || \
	GL_ES_VERSION_3_0 || \
	GL_VERSION_4_1 || \
	GL_ARB_ES2_compatibility
	/// Indicate that the resources associated with the compiler can be freed
	/**
	 *  @glvoereq{4,1,ARB,ES2_compatibility}
	 *  @glsymbols
	 *  @glfunref{ReleaseShaderCompiler}
	 */
	static void ReleaseCompiler(void)
	{
		OGLPLUS_GLFUNC(ReleaseShaderCompiler)();
		OGLPLUS_VERIFY_SIMPLE(ReleaseShaderCompiler);
	}
#endif
};

/// Shader operations (with direct state access)
typedef ObjectOps<tag::DirectState, tag::Shader>
	ShaderOps;

template <>
struct ObjectSubtype<tag::Shader>
{
	typedef ShaderType Type;
};

/// An object encasulating the shader object functionality
/**
 *  @see Program
 *  @see VertexShader
 *  @see GeometryShader
 *  @see FragmentShader
 *  @see TessControlShader
 *  @see TessEvaluationShader
 *  @see ComputeShader
 */
class Shader
 : public Object<ShaderOps>
{
private:
	Shader(const Shader&); // = delete;
protected:
	using Object<ShaderOps>::Uninitialized_;

	/// Uninitialized construction
	Shader(Uninitialized_ u)
	 : Object<ShaderOps>(u)
	{ }
public:
	/// Construction with shader @p type specifier
	Shader(ShaderType type)
	 : Object<ShaderOps>(type)
	{ }

	/// Construction with type specifier and textual descriptor
	Shader(ShaderType type, ObjectDesc&& description)
	 : Object<ShaderOps>(type, std::move(description))
	{ }

	/// Construction with type and source code wrapper
	Shader(
		ShaderType type,
		const GLSLSource& glsl_source
	): Object<ShaderOps>(type)
	{
		this->Source(glsl_source);
		this->Compile();
	}

	/// Construction with type, description and source code string
	Shader(
		ShaderType type,
		ObjectDesc&& description,
		const GLchar* glsl_source
	): Object<ShaderOps>(type, std::move(description))
	{
		this->Source(glsl_source);
		this->Compile();
	}

	/// Construction with type, description and source code string
	Shader(
		ShaderType type,
		ObjectDesc&& description,
		const StrLit& glsl_source
	): Object<ShaderOps>(type, std::move(description))
	{
		this->Source(glsl_source);
		this->Compile();
	}

	/// Construction with type, description and source code wrapper
	Shader(
		ShaderType type,
		ObjectDesc&& description,
		const GLSLSource& glsl_source
	): Object<ShaderOps>(type, std::move(description))
	{
		this->Source(glsl_source);
		this->Compile();
	}

	/// Shaders are movable
	Shader(Shader&& temp)
	 : Object<ShaderOps>(static_cast<Object<ShaderOps>&&>(temp))
	{ }

	Shader& operator = (Shader&& temp)
	{
		Object<ShaderOps>::operator = (std::move(temp));
		return *this;
	}
};

template <>
struct Classify<Shader>
 : Classify<Object<ShaderOps>>
{ };

template <>
class Array<Shader>
 : public Array<ObjectOps<tag::DirectState, tag::Shader>>
{
public:
	Array(GLsizei n, ShaderType type)
	 : Array<ObjectOps<tag::DirectState, tag::Shader>>(n, type)
	{ }
};

/// Base template for specialized shader types
template <typename enums::EnumValueType<ShaderType>::Type ShType>
class SpecShader
 : public Shader
{
private:
	SpecShader(const SpecShader&); // = delete;
public:
	/// Default construction
	SpecShader(void)
	 : Shader(ShType)
	{ }

	/// Construction with a textual descriptor
	SpecShader(ObjectDesc&& description)
	 : Shader(ShType, std::move(description))
	{ }

	/// Construction with a source code wrapper
	SpecShader(const GLSLSource& glsl_source)
	 : Shader(ShType, glsl_source)
	{ }

	/// Construction with description and source code string
	SpecShader(
		ObjectDesc&& description,
		const GLchar* glsl_source
	): Shader(ShType, std::move(description), glsl_source)
	{ }

	/// Construction with description and source code string
	SpecShader(
		ObjectDesc&& description,
		const StrLit& glsl_source
	): Shader(ShType, std::move(description), glsl_source)
	{ }

	/// Construction with description and source code wrapper
	SpecShader(
		ObjectDesc&& description,
		const GLSLSource& glsl_source
	): Shader(ShType, std::move(description), glsl_source)
	{ }

	SpecShader(SpecShader&& temp)
	 : Shader(static_cast<Shader&&>(temp))
	{ }
};

/// Vertex shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
typedef SpecShader<OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex)>
	VertexShader;

/// Geometry shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
typedef SpecShader<OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry)>
	GeometryShader;

/// Fragment shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
typedef SpecShader<OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment)>
	FragmentShader;

#if OGLPLUS_DOCUMENTATION_ONLY || GL_TESS_CONTROL_SHADER
/// Tesselation control shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
typedef SpecShader<OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl)>
	TessControlShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_TESS_EVALUATION_SHADER
/// Tesselation evaluation shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
typedef SpecShader<OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation)>
	TessEvaluationShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY || GL_COMPUTE_SHADER
/// Compute shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
typedef SpecShader<OGLPLUS_CONST_ENUM_VALUE(ShaderType::Compute)>
	ComputeShader;
#endif

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/shader.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
