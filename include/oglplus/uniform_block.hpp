/**
 *  @file oglplus/uniform_block.hpp
 *  @brief Named uniform block wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_UNIFORM_BLOCK_1107121519_HPP
#define OGLPLUS_UNIFORM_BLOCK_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/friend_of.hpp>
#include <oglplus/shader.hpp>
#include <oglplus/program.hpp>
#include <oglplus/buffer.hpp>
#include <oglplus/string.hpp>

#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_uniform_buffer_object
namespace aux {

class UniformBlockInitOps
{
protected:
	typedef Nothing ParamType;

	UniformBlockInitOps(Nothing)
	{ }

	GLint _do_init_index(GLuint program, const GLchar* identifier) const
	{
		return OGLPLUS_GLFUNC(GetUniformBlockIndex)(
			program,
			identifier
		);
	}

	GLint _init_index(GLuint program, const GLchar* identifier) const
	{
		GLint index = _do_init_index(program, identifier);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetUniformBlockIndex));
		if(OGLPLUS_IS_ERROR(index == GLint(-1)))
		{
			Error::PropertyMap props;
			props["identifier"] = identifier;
			props["program"] = aux::ObjectDescRegistry<ProgramOps>::
						_get_desc(program);
			HandleError(
				GL_INVALID_OPERATION,
				"Getting the location of inactive uniform block",
				OGLPLUS_ERROR_INFO(GetUniformBlockIndex),
				std::move(props)
			);
		}
		return index;
	}

	static GLenum _translate_ref(ShaderType shader_type)
	{
		switch(shader_type)
		{
#ifdef GL_VERTEX_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER;
#endif
#ifdef GL_TESS_CONTROL_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER;
#endif
#ifdef GL_TESS_EVALUATION_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER;
#endif
#ifdef GL_GEOMETRY_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER;
#endif
#ifdef GL_FRAGMENT_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER;
#endif
#ifdef GL_COMPUTE_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Compute):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER;
#endif
		}
		return 0;
	}

	static GLenum _translate_max(ShaderType shader_type)
	{
		switch(shader_type)
		{
#ifdef GL_VERTEX_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex):
			return GL_MAX_VERTEX_UNIFORM_BLOCKS;
#endif
#ifdef GL_TESS_CONTROL_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl):
			return GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS;
#endif
#ifdef GL_TESS_EVALUATION_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation):
			return GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS;
#endif
#ifdef GL_GEOMETRY_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry):
			return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
#endif
#ifdef GL_FRAGMENT_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment):
			return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
#endif
#ifdef GL_COMPUTE_SHADER
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Compute):
			return GL_MAX_COMPUTE_UNIFORM_BLOCKS;
#endif
		}
		return 0;
	}
};

typedef EagerUniformInitTpl<UniformBlockInitOps>
	EagerUniformBlockInit;

typedef LazyUniformInitTpl<UniformBlockInitOps>
	LazyUniformBlockInit;

} // namespace aux

/// Base class for shader uniform block operations functionality
/**
 *  @note Do not use this class directly. Use UniformBlock or LazyUniformBlock
 *  instead.
 *
 *  @see UniformBlock
 *  @see LazyUniformBlock
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{3,1,ARB,uniform_buffer_object}
 */
template <class Initializer>
class UniformBlockTpl
 : public Initializer
{
public:
	template <class _String>
	UniformBlockTpl(const Program& program, _String&& identifier)
	 : Initializer(program, Nothing(), std::forward<_String>(identifier))
	{ }

	/// Return the maximum number of uniform blocks for a @p shader_type
	static GLuint MaxIn(ShaderType shader_type)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(
			Initializer::_translate_max(shader_type),
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetIntegerv));
		assert(result >= 0);
		return GLuint(result);
	}

	/// Returns true if this uniform block is referenced by @p shader_type
	/**
	 *  @glsymbols
	 *  @glfunref{GetActiveUniformBlock}
	 */
	bool ReferencedBy(ShaderType shader_type) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetActiveUniformBlockiv)(
			this->_get_program(),
			this->_get_index(),
			Initializer::_translate_ref(shader_type),
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		return result == GL_TRUE;
	}

	/// Returns the size of the uniform block
	/**
	 *  @glsymbols
	 *  @glfunref{GetActiveUniformBlock}
	 */
	GLuint DataSize(void) const
	{
		GLint result;
		OGLPLUS_GLFUNC(GetActiveUniformBlockiv)(
			this->_get_program(),
			this->_get_index(),
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		assert(result >= 0);
		return GLuint(result);
	}

	void Binding(UniformBufferBindingPoint binding) const
	{
		OGLPLUS_GLFUNC(UniformBlockBinding)(
			this->_get_program(),
			this->_get_index(),
			GLuint(binding)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(UniformBlockBinding));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates uniform block operations
/**
 *  The difference between UniformBlock and LazyUniformBlock is,
 *  that UniformBlock tries to get the location (index) of the GLSL
 *  uniform block variable in a Program during construction
 *  and LazyUniformBlock postpones this initialization until the value
 *  is actually needed at the cost of having to internally store
 *  the identifer in a String.
 *
 *  @see LazyUniformBlock
 *  @see Uniform
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{3,1,ARB,uniform_buffer_object}
 */
struct UniformBlock
 : public UniformBlockTpl<Unspecified>
{
	/// Construction from a program and an identifier
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformBlockIndex}
	 */
	UniformBlock(const Program& program, String identifier);
};
#else
typedef UniformBlockTpl<aux::EagerUniformBlockInit> UniformBlock;
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates lazily initialized uniform block operations
/**
 *  The difference between UniformBlock and LazyUniformBlock is,
 *  that UniformBlock tries to get the location (index) of the GLSL
 *  uniform block variable in a Program during construction
 *  and LazyUniformBlock postpones this initialization until the value
 *  is actually needed at the cost of having to internally store
 *  the identifer in a String.
 *
 *  @see UniformBlock
 *  @see LazyUniform
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{3,1,ARB,uniform_buffer_object}
 */
struct LazyUniformBlock
 : public UniformBlockTpl<Unspecified>
{
	/// Construction from a program and an identifier
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformBlockIndex}
	 */
	LazyUniformBlock(const Program& program, String identifier);
};
#else
typedef UniformBlockTpl<aux::LazyUniformBlockInit> LazyUniformBlock;
#endif

#endif // uniform buffer object

} // namespace oglplus

#endif // include guard
