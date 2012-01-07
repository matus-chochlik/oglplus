/**
 *  @file oglplus/shader.hpp
 *  @brief Shader wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHADER_1107121519_HPP
#define OGLPLUS_SHADER_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/object.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/compile_error.hpp>
#include <oglplus/auxiliary/info_log.hpp>
#include <oglplus/string.hpp>

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
{
public:
	/// The kind of the shader
	enum class Kind : GLenum {
#include <oglplus/enums/shader_kind.ipp>
	};
protected:
	static void _init(GLsizei, GLuint& _name, Kind kind)
	{
		_name = OGLPLUS_GLFUNC(CreateShader)(GLenum(kind));
		HandleIfError(OGLPLUS_ERROR_INFO(CreateShader));
	}

	static void _cleanup(GLsizei, GLuint& _name)
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(DeleteShader)(_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsShader)(_name);
	}

	friend class FriendOf<ShaderOps>;
public:
	/// Get the type of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{GetShader}
	 *  @gldefref{SHADER_TYPE}
	 */
	Kind Type(void) const
	{
		GLint result = 0;
		OGLPLUS_GLFUNC(GetShaderiv)(
			_name,
			GL_SHADER_TYPE,
			&result
		);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			CreateShader,
			Shader,
			_name
		));
		return Kind(result);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	void Source(const String& source) const
	{
		assert(_name != 0);
		const GLchar* srcs[1] = {source.c_str()};
		GLint lens[] = {GLint(source.size())};
		OGLPLUS_GLFUNC(ShaderSource)(_name, 1, srcs, lens);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	void Source(const GLchar* source) const
	{
		assert(_name != 0);
		const GLchar* srcs[1] = {source};
		OGLPLUS_GLFUNC(ShaderSource)(_name, 1, srcs, 0);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	void Source(const GLchar* source, int length) const
	{
		assert(_name != 0);
		const GLchar* srcs[1] = {source};
		int lens[] = {length};
		OGLPLUS_GLFUNC(ShaderSource)(_name, 1, srcs, lens);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	void Source(const GLchar** srcs, int count) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ShaderSource)(_name, count, srcs, 0);
	}

	/// Set the source code of the shader
	/**
	 *  @glsymbols
	 *  @glfunref{ShaderSource}
	 */
	void Source(const std::vector<const GLchar*>& srcs) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(ShaderSource)(
			_name,
			srcs.size(),
			const_cast<const GLchar**>(srcs.data()),
			0
		);
	}

	/// Returns true if the shader is already compile, returns false otherwise
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
		AssertNoError(OGLPLUS_OBJECT_ERROR_INFO(
			GetShaderiv,
			Shader,
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
	String GetInfoLog(void) const
	{
		assert(_name != 0);
		return aux::GetInfoLog(
			_name, OGLPLUS_GLFUNC(GetShaderiv),
			OGLPLUS_GLFUNC(GetShaderInfoLog),
			"GetShaderiv",
			"GetShaderInfoLog"
		);
	}

	/// Compiles the shader
	/**
	 *  @throws Error CompileError
	 *  @see IsCompiled
	 *
	 *  @glsymbols
	 *  @glfunref{CompileShader}
	 */
	void Compile(void) const
	{
		assert(_name != 0);
		OGLPLUS_GLFUNC(CompileShader)(_name);
		HandleIfError(OGLPLUS_OBJECT_ERROR_INFO(
			CompileShader,
			Shader,
			_name
		));
		if(!IsCompiled())
			HandleBuildError<CompileError>(
				GetInfoLog(),
				OGLPLUS_OBJECT_ERROR_INFO(
					CompileShader,
					Shader,
					_name
				)
			);
	}
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_4_1 || GL_ARB_ES2_compatibility
	/// Indicate that the resources associated with the compiler can be freed
	/**
	 *  @glsymbols
	 *  @glfunref{ReleaseShaderCompiler}
	 */
	static void ReleaseCompiler(void)
	{
		OGLPLUS_GLFUNC(ReleaseShaderCompiler)();
		HandleIfError(OGLPLUS_ERROR_INFO(ReleaseShaderCompiler));
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
	Shader(ShaderOps::Kind kind);
	Shader(ShaderOps::Kind kind, String description);
};
#else
typedef Object<ShaderOps, false> Shader;
#endif

template <Shader::Kind kind>
class SpecializedShader
 : public Shader
{
private:
	void _initialize(const GLchar* source)
	{
		this->Source(source);
		this->Compile();
	}
public:
	SpecializedShader(void)
	 : Shader(kind)
	{ }

	SpecializedShader(const GLchar* desc)
	 : Shader(kind, desc)
	{ }

	SpecializedShader(const String& desc)
	 : Shader(kind, desc)
	{ }

	SpecializedShader(const GLchar* desc, const GLchar* source)
	 : Shader(kind, desc)
	{
		_initialize(source);
	}

	SpecializedShader(const String& desc, const GLchar* source)
	 : Shader(kind, desc)
	{
		_initialize(source);
	}

	SpecializedShader(const SpecializedShader&) = delete;

	SpecializedShader(SpecializedShader&& tmp)
	 : Shader(std::forward<Shader>(tmp))
	{ }
};

template <Shader::Kind kind>
struct BaseOps<SpecializedShader<kind> >
{
	typedef typename BaseOps<Shader>::Type Type;
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// Vertex shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup objects
 */
class VertexShader
 : public Shader
{ };
#elif defined GL_VERTEX_SHADER
typedef SpecializedShader<Shader::Kind::Vertex> VertexShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Geometry shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup objects
 */
class GeometryShader
 : public Shader
{ };
#elif defined GL_GEOMETRY_SHADER
typedef SpecializedShader<Shader::Kind::Geometry> GeometryShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Fragment shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup objects
 */
class FragmentShader
 : public Shader
{ };
#elif GL_FRAGMENT_SHADER
typedef SpecializedShader<Shader::Kind::Fragment> FragmentShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Tesselation control shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup objects
 */
class TessControlShader
 : public Shader
{ };
#elif GL_TESS_CONTROL_SHADER
typedef SpecializedShader<Shader::Kind::TessControl> TessControlShader;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Tesselation evaluation shader wrapper
/**
 *  @see Shader
 *  @see Program
 *  @ingroup objects
 */
class TessEvaluationShader
 : public Shader
{ };
#elif GL_TESS_EVALUATION_SHADER
typedef SpecializedShader<Shader::Kind::TessEvaluation> TessEvaluationShader;
#endif

} // namespace oglplus

#endif // include guard
