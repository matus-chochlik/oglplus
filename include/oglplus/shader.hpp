/**
 *  @file oglplus/shader.hpp
 *  @brief Shader wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHADER_1107121519_HPP
#define OGLPLUS_SHADER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/compile_error.hpp>
#include <oglplus/precision_type.hpp>
#include <oglplus/auxiliary/info_log.hpp>
#include <oglplus/string.hpp>
#include <oglplus/shader_type.hpp>
#include <oglplus/glsl_source.hpp>

#include <array>
#include <vector>
#include <cassert>

namespace oglplus {

/// Shader operations wrapper helper class
/**
 *  @note Do not use this class directly, use Shader instead.
 *
 *  @see Shader
 *
 *  @glsymbols
 *  @glfunref{CreateShader}
 *  @glfunref{DeleteShader}
 *  @glfunref{IsShader}
 */
class ShaderOps
 : public Named
 , public BaseObject<false>
{
protected:
	static void _init(GLsizei _count, GLuint* _name, ShaderType type)
	{
		OGLPLUS_FAKE_USE(_count);
		assert(_count == 1);
		assert(_name != nullptr);
		*_name = OGLPLUS_GLFUNC(CreateShader)(GLenum(type));
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CreateShader,
			Shader,
			EnumValueName(type),
			*_name
		));
	}

	static void _cleanup(GLsizei _count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		OGLPLUS_FAKE_USE(_count);
		assert(_count == 1);
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeleteShader)(*_name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != 0);
		try{return OGLPLUS_GLFUNC(IsShader)(_name);}
		catch(...){ }
		return GL_FALSE;
	}

#ifdef GL_SHADER
	static ObjectType _object_type(void)
	OGLPLUS_NOEXCEPT(true)
	{
		return ObjectType::Shader;
	}
#endif

	friend class FriendOf<ShaderOps>;
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
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetShaderiv,
			Shader,
			EnumValueName(ShaderType(result)),
			_name
		));
		return ShaderType(result);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	const ShaderOps& Source(
		const GLchar** srcs,
		const GLint* lens,
		int count
	) const
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
	const ShaderOps& Source(const String& source) const
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
	const ShaderOps& Source(const StrLit& source) const
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
	const ShaderOps& Source(const GLchar* source) const
	{
		return Source(&source, nullptr, 1);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	const ShaderOps& Source(const GLchar** srcs, int count) const
	{
		return Source(srcs, nullptr, count);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	const ShaderOps& Source(const std::vector<const GLchar*>& srcs) const
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
	const ShaderOps& Source(
		const std::array<const GLchar*, N>& srcs
	) const
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
	const ShaderOps& Source(const GLSLSource& glsl_source) const
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
		OGLPLUS_VERIFY(OGLPLUS_OBJECT_ERROR_INFO(
			GetShaderiv,
			Shader,
			EnumValueName(Type()),
			_name
		));
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

	void HandleCompileError(void) const;

	/// Compiles the shader
	/**
	 *  @post IsCompiled()
	 *  @throws Error CompileError
	 *  @see IsCompiled
	 *
	 *  @glsymbols
	 *  @glfunref{CompileShader}
	 */
	const ShaderOps& Compile(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(CompileShader)(_name);
		OGLPLUS_CHECK(OGLPLUS_OBJECT_ERROR_INFO(
			CompileShader,
			Shader,
			EnumValueName(Type()),
			_name
		));
		if(OGLPLUS_IS_ERROR(!IsCompiled()))
		{
			HandleCompileError();
		}
		return *this;
	}

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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(ReleaseShaderCompiler));
	}
#endif

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
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetShaderPrecisionFormat));
	}
#endif
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An object encasulating the shading language shader functionality
/**
 *  @see Program
 *  @see VertexShader
 *  @see GeometryShader
 *  @see FragmentShader
 *  @see TessControlShader
 *  @see TessEvaluationShader
 */
class Shader
 : public ShaderOps
{
public:
	Shader(ShaderType type);
	Shader(ShaderType type, String description);
};
#else
typedef Object<ShaderOps> Shader;
#endif


struct SpecializedShaderInitializer
{
protected:
	typedef const GLSLSource& ParameterType;

	SpecializedShaderInitializer(void){ }

	SpecializedShaderInitializer(
		Shader& shader,
		Shader::Property::Type,
		const GLSLSource& source
	)
	{
		shader.Source(source);
		shader.Compile();
	}
};


template <>
class Group<Shader>
 : public BaseGroup<Shader>
{
public:
	/// Constructs an empty group of Shaders
	Group(void)
	{ }

	/// Constructs an empty group and reserves space for @c n Shaders
	Group(std::size_t n)
	 : BaseGroup<Shader>(n)
	{ }

	/// Constructs a group initially storing references to one Shader
	Group(
		const ShaderOps& shader1,
		std::size_t n = 1
	): BaseGroup<Shader>(n<1?1:n)
	{
		this->push_back(shader1);
	}

	/// Constructs a group initially storing references to two Shaders
	Group(
		const ShaderOps& shader1,
		const ShaderOps& shader2,
		std::size_t n = 2
	): BaseGroup<Shader>(n<2?2:n)
	{
		this->push_back(shader1);
		this->push_back(shader2);
	}

	/// Constructs a group initially storing references to three Shaders
	Group(
		const ShaderOps& shader1,
		const ShaderOps& shader2,
		const ShaderOps& shader3,
		std::size_t n = 3
	): BaseGroup<Shader>(n<3?3:n)
	{
		this->push_back(shader1);
		this->push_back(shader2);
		this->push_back(shader3);
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// Vertex shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
class VertexShader
 : public Shader
{ };
#elif defined GL_VERTEX_SHADER
typedef Specialized<
	Shader,
	OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex),
	SpecializedShaderInitializer
> VertexShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Geometry shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
class GeometryShader
 : public Shader
{ };
#elif defined GL_GEOMETRY_SHADER
typedef Specialized<
	Shader,
	OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry),
	SpecializedShaderInitializer
> GeometryShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Fragment shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
class FragmentShader
 : public Shader
{ };
#elif GL_FRAGMENT_SHADER
typedef Specialized<
	Shader,
	OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment),
	SpecializedShaderInitializer
> FragmentShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Tesselation control shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
class TessControlShader
 : public Shader
{ };
#elif GL_TESS_CONTROL_SHADER
typedef Specialized<
	Shader,
	OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl),
	SpecializedShaderInitializer
> TessControlShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Tesselation evaluation shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
class TessEvaluationShader
 : public Shader
{ };
#elif GL_TESS_EVALUATION_SHADER
typedef Specialized<
	Shader,
	OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation),
	SpecializedShaderInitializer
> TessEvaluationShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compute shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup oglplus_objects
 */
class ComputeShader
 : public Shader
{ };
#elif GL_COMPUTE_SHADER
typedef Specialized<
	Shader,
	OGLPLUS_CONST_ENUM_VALUE(ShaderType::Compute),
	SpecializedShaderInitializer
> ComputeShader;
#endif

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/shader.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
