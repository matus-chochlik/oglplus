/**
 *  @file oglplus/ext/ARB_bindless_texture/uniform.hpp
 *  @brief Texture handle uniform operations.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXTURE_HANDLE_UNIFORM_1309262134_HPP
#define OGLPLUS_TEXTURE_HANDLE_UNIFORM_1309262134_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/error.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/uniform.hpp>
#include <oglplus/ext/ARB_bindless_texture/texture_handle.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_ARB_bindless_texture

/// Specialization of uniform operations for TextureHandle types
template <
	class LocationInit,
	class Typechecker,
	class SpecOpsWrapper
>
class UniformSpecOps<
	TextureHandleARB,
	LocationInit,
	Typechecker,
	SpecOpsWrapper
>: public UniformOps<LocationInit, Typechecker>
 , public SpecOpsWrapper::Type
 , public FriendOf<TextureHandleARB>
{
private:
	typedef UniformOps<LocationInit, Typechecker> _base_ops;
protected:
	template <typename TypeSel, class StrOrInt>
	UniformSpecOps(
		TypeSel* type_sel,
		const ProgramOps& program,
		StrOrInt&& name_or_loc
	): _base_ops(type_sel, program, std::forward<StrOrInt>(name_or_loc))
	{ }

	template <typename TypeSel>
	UniformSpecOps(TypeSel* type_sel, GLuint program, GLint location)
	 : _base_ops(type_sel, program, location)
	{ }
public:
	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(TextureHandleARB th)
	{
		this->_do_set(
			this->_get_program(),
			this->_get_location(),
			FriendOf<TextureHandleARB>::GetHandle(th)
		);
	}
};

/// Specialization of uniform operations for ImageHandle types
template <
	class LocationInit,
	class Typechecker,
	class SpecOpsWrapper
>
class UniformSpecOps<
	ImageHandleARB,
	LocationInit,
	Typechecker,
	SpecOpsWrapper
>: public UniformOps<LocationInit, Typechecker>
 , public SpecOpsWrapper::Type
 , public FriendOf<ImageHandleARB>
{
private:
	typedef UniformOps<LocationInit, Typechecker> _base_ops;
protected:
	template <typename TypeSel, class StrOrInt>
	UniformSpecOps(
		TypeSel* type_sel,
		const ProgramOps& program,
		StrOrInt&& name_or_loc
	): _base_ops(type_sel, program, std::forward<StrOrInt>(name_or_loc))
	{ }

	template <typename TypeSel>
	UniformSpecOps(TypeSel* type_sel, GLuint program, GLint location)
	 : _base_ops(type_sel, program, location)
	{ }
public:
	/// Set the value of the uniform variable
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void Set(ImageHandleARB ih)
	{
		this->_do_set(
			this->_get_program(),
			this->_get_location(),
			FriendOf<ImageHandleARB>::GetHandle(ih)
		);
	}
};

#endif // GL_ARB_bindless_texture

} // namespace oglplus

#endif // include guard
