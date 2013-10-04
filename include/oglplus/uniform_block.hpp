/**
 *  @file oglplus/uniform_block.hpp
 *  @brief Named uniform block wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
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

	GLint _do_init_location(GLuint program, const GLchar* identifier) const
	{
		GLint result = OGLPLUS_GLFUNC(GetUniformBlockIndex)(
			program,
			identifier
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetUniformBlockIndex));
		return result;
	}

	void _handle_error(
		GLuint program,
		const GLchar* identifier,
		GLint location
	) const;

	GLint _init_location(GLuint program, const GLchar* identifier) const
	{
		GLint location = _do_init_location(program, identifier);
		if(OGLPLUS_IS_ERROR(location == GLint(-1)))
		{
			_handle_error(program, identifier, location);
		}
		return location;
	}

	static GLenum _translate_ref(ShaderType shader_type);
	static GLenum _translate_max(ShaderType shader_type);
};

typedef EagerUniformInitTpl<UniformBlockInitOps>
	EagerUniformBlockInit;

typedef LazyUniformInitTpl<UniformBlockInitOps, NoUniformTypecheck>
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
	template <class String_>
	UniformBlockTpl(const Program& program, String_&& identifier)
	 : Initializer(
		program,
		Nothing(),
		std::forward<String_>(identifier),
		NoTypecheck()
	)
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
	bool ReferencedBy(ShaderType shader_type)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetActiveUniformBlockiv)(
			this->_get_program(),
			this->_get_location(),
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
	GLuint DataSize(void)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetActiveUniformBlockiv)(
			this->_get_program(),
			this->_get_location(),
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&result
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(GetActiveUniformBlockiv));
		assert(result >= 0);
		return GLuint(result);
	}

	void Binding(UniformBufferBindingPoint binding)
	{
		OGLPLUS_GLFUNC(UniformBlockBinding)(
			this->_get_program(),
			this->_get_location(),
			GLuint(binding)
		);
		OGLPLUS_VERIFY(OGLPLUS_ERROR_INFO(UniformBlockBinding));
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// Encapsulates uniform block operations
/**
 *  The difference between UniformBlock and LazyUniformBlock is,
 *  that UniformBlock tries to get the location of the GLSL
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
 *  that UniformBlock tries to get the location of the GLSL
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

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/uniform_block.ipp>
#endif

#endif // include guard
