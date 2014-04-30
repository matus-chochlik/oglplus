/**
 *  @file oglplus/buffer_gpu_addr.hpp
 *  @brief Object representing Buffer's GPU address.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_BUFFER_GPU_ADDR_1310102147_HPP
#define OGLPLUS_BUFFER_GPU_ADDR_1310102147_HPP

#if GL_NV_shader_buffer_load

#include <oglplus/fwd.hpp>
#include <oglplus/error.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/uniform.hpp>

namespace oglplus {

class BufferGPUAddress
{
private:
	GLuint64EXT _addr;

	friend class FriendOf<BufferGPUAddress>;
	friend class BufferOps;
	friend class DSABufferEXTOps;
protected:
	BufferGPUAddress(GLuint64EXT addr)
	 : _addr(addr)
	{ }
};

template <>
class FriendOf<BufferGPUAddress>
{
protected:
	static GLuint64EXT GetValue(const BufferGPUAddress& bga)
	OGLPLUS_NOEXCEPT(true)
	{
		return bga._addr;
	}
};

/// Specialization of uniform operations for BufferGPUAddress
template <
	class LocationInit,
	class Typechecker,
	class SpecOpsWrapper
>
class UniformSpecOps<
	BufferGPUAddress,
	LocationInit,
	Typechecker,
	SpecOpsWrapper
>: public UniformOps<LocationInit, Typechecker>
 , public SpecOpsWrapper::Type
 , public FriendOf<BufferGPUAddress>
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
	void Set(BufferGPUAddress bga)
	{
		this->_do_set(
			this->_get_program(),
			this->_get_location(),
			FriendOf<BufferGPUAddress>::GetValue(bga)
		);
	}
};

} // namespace oglplus

#endif // GL_NV_shader_buffer_load

#endif // include guard
