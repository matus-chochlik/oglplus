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
	typedef None ParamType;

	UniformBlockInitOps(None)
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
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER;
#if GL_VERSION_4_0 || GL_ARB_tessellation_shader
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER;
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER;
#endif // tessellation shader
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER;
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment):
			return GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER;
		}
		return 0;
	}

	static GLenum _translate_max(ShaderType shader_type)
	{
		switch(shader_type)
		{
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Vertex):
			return GL_MAX_VERTEX_UNIFORM_BLOCKS;
#if GL_VERSION_4_0 || GL_ARB_tessellation_shader
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessControl):
			return GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS;
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::TessEvaluation):
			return GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS;
#endif // tessellation shader
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Geometry):
			return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
			case OGLPLUS_CONST_ENUM_VALUE(ShaderType::Fragment):
			return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
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
 *  @ingroup shader_variables
 */
template <class Initializer>
class UniformBlockTpl
 : public Initializer
{
public:
	/// Reference a uniform block @p identifier in the @p program
	/**
	 *  @glsymbols
	 *  @glfunref{GetUniformBlockIndex}
	 */
	template <class String>
	UniformBlockTpl(const Program& program, String&& identifier)
	 : Initializer(program, None(), std::forward<String>(identifier))
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

/// Encapsulates uniform block operations
/**
 *  @ingroup shader_variables
 */
typedef UniformBlockTpl<aux::EagerUniformBlockInit>
	UniformBlock;

typedef UniformBlockTpl<aux::LazyUniformBlockInit>
	LazyUniformBlock;

#endif // uniform buffer object

} // namespace oglplus

#endif // include guard
