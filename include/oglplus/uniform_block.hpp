/**
 *  @file oglplus/uniform_block.hpp
 *  @brief Named uniform block wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_UNIFORM_BLOCK_1107121519_HPP
#define OGLPLUS_UNIFORM_BLOCK_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/error/prog_var.hpp>
#include <oglplus/prog_var/location.hpp>
#include <oglplus/prog_var/varpara_fns.hpp>
#include <oglplus/prog_var/set_ops.hpp>
#include <oglplus/prog_var/wrapper.hpp>
#include <oglplus/shader_type.hpp>
#include <oglplus/buffer_binding.hpp>

#include <cassert>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_1 || GL_ARB_uniform_buffer_object

template <>
class ProgVarLocOps<tag::UniformBlock>
{
private:
	static const char* MsgGettingInactive(void);
protected:
	static const char* MsgUsingInactive(void);
public:
	/// Finds the uniform block location, throws on failure if active_only
	/** Finds the location / index of the uniform block specified
	 *  by @p identifier in a @p program. If active_only is true then
	 *  throws if no such uniform block exists or if it is not active.
	 *
	 *  @glsymbols
	 *  @glfunref{GetUniformLocation}
	 */
	static GLint GetLocation(
		ProgramName program,
		StrCRef identifier,
		bool active_only
	)
	{
		GLint result = OGLPLUS_GLFUNC(GetUniformBlockIndex)(
			GetGLName(program),
			identifier.c_str()
		);
		OGLPLUS_CHECK(
			GetUniformBlockIndex,
			ProgVarError,
			Program(program).
			Identifier(identifier)
		);
		OGLPLUS_HANDLE_ERROR_IF(
			active_only && (result < 0),
			GL_INVALID_OPERATION,
			MsgGettingInactive(),
			ProgVarError,
			Program(program).
			Identifier(identifier)
		);
		return result;
	}
};

template <>
class ProgVarCommonOps<tag::UniformBlock>
 : public ProgVarLoc<tag::UniformBlock>
{
private:
	static GLenum _translate_ref(ShaderType shader_type);
	static GLenum _translate_max(ShaderType shader_type);
protected:
	ProgVarCommonOps(UniformBlockLoc ubloc)
	 : ProgVarLoc<tag::UniformBlock>(ubloc)
	{ }
public:
	/// Return the maximum number of uniform blocks for a @p shader_type
	static GLuint MaxIn(ShaderType shader_type)
	{
		GLint result;
		OGLPLUS_GLFUNC(GetIntegerv)(
			_translate_max(shader_type),
			&result
		);
		OGLPLUS_VERIFY(
			GetIntegerv,
			Error,
			EnumParam(_translate_max(shader_type))
		);
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
			this->_program,
			this->_location,
			_translate_ref(shader_type),
			&result
		);
		OGLPLUS_VERIFY(
			GetActiveUniformBlockiv,
			Error,
			EnumParam(_translate_ref(shader_type))
		);
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
			this->_program,
			this->_location,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&result
		);
		OGLPLUS_VERIFY(
			GetActiveUniformBlockiv,
			Error,
			EnumParam(GLenum(GL_UNIFORM_BLOCK_DATA_SIZE))
		);
		assert(result >= 0);
		return GLuint(result);
	}

	/// Sets up the uniform block binding
	/**
	 *  @glsymbols
	 *  @glfunref{UniformBlockBinding}
	 */
	void Binding(UniformBufferBindingPoint binding)
	{
		OGLPLUS_GLFUNC(UniformBlockBinding)(
			this->_program,
			this->_location,
			GLuint(binding)
		);
		OGLPLUS_VERIFY(
			UniformBlockBinding,
			ProgVarError,
			Program(ProgramName(this->_program)).
			Index(GLuint(binding))
		);
	}
};

template <typename OpsTag>
class ProgVarGetSetOps<OpsTag, tag::UniformBlock, UniformBufferBindingPoint>
 : public ProgVarCommonOps<tag::UniformBlock>
{
protected:
	ProgVarGetSetOps(UniformBlockLoc ubloc)
	 : ProgVarCommonOps<tag::UniformBlock>(ubloc)
	{ }
public:
	void SetValue(UniformBufferBindingPoint value)
	{
		this->Binding(value);
	}
};

/// Encapsulates uniform block operations
/**
 *  @see Uniform
 *
 *  @ingroup shader_variables
 *
 *  @glvoereq{3,1,ARB,uniform_buffer_object}
 */
typedef ProgVar<
	tag::ImplicitSel,
	tag::UniformBlock,
	tag::NoTypecheck,
	UniformBufferBindingPoint
> UniformBlock;

#endif // uniform buffer object

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/uniform_block.ipp>
#endif

#endif // include guard
