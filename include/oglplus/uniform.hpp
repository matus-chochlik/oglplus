/**
 *  @file oglplus/uniform.hpp
 *  @brief Uniform wrappers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_UNIFORM_1107121519_HPP
#define OGLPLUS_UNIFORM_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/error/prog_var.hpp>
#include <oglplus/prog_var/location.hpp>
#include <oglplus/prog_var/varpara_fns.hpp>
#include <oglplus/prog_var/set_ops.hpp>
#include <oglplus/prog_var/wrapper.hpp>

namespace oglplus {

template <>
class ProgVarLocOps<tag::Uniform>
{
private:
	static const char* InactiveMessage(void);
public:
	/// Finds the uniform location, throws on failure if active_only
	/** Finds the location of the uniform variable specified
	 *  by @p identifier in a @p program. If active_only is true then
	 *  throws if no such uniform exists or if it is not active.
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
		GLint result = OGLPLUS_GLFUNC(GetUniformLocation)(
			GetGLName(program),
			identifier.c_str()
		);
		OGLPLUS_CHECK(
			GetUniformLocation,
			ProgVarError,
			Program(program).
			Identifier(identifier)
		);
		OGLPLUS_HANDLE_ERROR_IF(
			active_only && (result < 0),
			GL_INVALID_OPERATION,
			InactiveMessage(),
			ProgVarError,
			Program(program).
			Identifier(identifier)
		);
		return result;
	}
};

// collection of Uniform setter functions for basic types
template <>
class ProgVarSetters<tag::ImplicitSel, tag::Uniform, tag::NativeTypes>
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(Uniform, Uniform)

	OGLPLUS_AUX_VARPARA_FNS(Uniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(Uniform, i, t, GLint)
#if GL_ARB_bindless_texture
	OGLPLUS_AUX_VARPARA_FNC(Uniform, Handle, ui64ARB, t, GLuint64, 1)
#endif
	OGLPLUS_AUX_VARPARA_FNS(Uniform, f, t, GLfloat)
#if GL_VERSION_3_3 || GL_ARB_gpu_shader_fp64
	OGLPLUS_AUX_VARPARA_FNS(Uniform, d, t, GLdouble)
#endif

	OGLPLUS_AUX_VARPARA_FNS(Uniform, iv, v, GLint)
#if GL_ARB_bindless_texture
	OGLPLUS_AUX_VARPARA_FNC(Uniform, Handle, ui64vARB, v, GLuint64, 1)
#endif
	OGLPLUS_AUX_VARPARA_FNS(Uniform, fv, v, GLfloat)
#if GL_VERSION_3_3 || GL_ARB_gpu_shader_fp64
	OGLPLUS_AUX_VARPARA_FNS(Uniform, dv, v, GLdouble)
#endif
};

// collection of Uniform setter function for matrices
template <>
class ProgVarSetters<tag::ImplicitSel, tag::Uniform, tag::MatrixTypes>
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(UniformMatrix, Uniform)

	OGLPLUS_AUX_VARPARA_MAT_FNS(UniformMatrix, fv, v, GLfloat)
#if GL_VERSION_3_3 || GL_ARB_gpu_shader_fp64
	OGLPLUS_AUX_VARPARA_MAT_FNS(UniformMatrix, dv, v, GLdouble)
#endif
};

template <>
class ProgVarCommonOps<tag::Uniform>
 : public ProgVarLoc<tag::Uniform>
 , public ProgVarLocOps<tag::Uniform>
{
protected:
	ProgVarCommonOps(UniformLoc uloc)
	 : ProgVarLoc<tag::Uniform>(uloc)
	{ }
public:
};

/// Encapsulates uniform value seting functionality
/**
 *  @ingroup shader_variables
 */
template <typename OpsTag, typename T>
class ProgVarGetSetOps<OpsTag, tag::Uniform, T>
 : public ProgVarCommonOps<tag::Uniform>
 , public ProgVarBaseSetOps<OpsTag, tag::Uniform, tag::NativeTypes, T, 16>
{
protected:
	ProgVarGetSetOps(UniformLoc uloc)
	 : ProgVarCommonOps<tag::Uniform>(uloc)
	{ }
public:
	/// Set the value of the uniform
	/**
	 *  @glsymbols
	 *  @glfunref{Uniform}
	 *  @glfunref{ProgramUniform}
	 */
	void SetValue(T value)
	{
		this->_do_set(_program, _location, value);
	}
};

template <typename OpsTag, typename T, std::size_t N>
class ProgVarGetSetOps<OpsTag, tag::Uniform, Vector<T, N>>
 : public ProgVarCommonOps<tag::Uniform>
 , public ProgVarBaseSetOps<OpsTag, tag::Uniform, tag::NativeTypes, T, 4>
{
protected:
	ProgVarGetSetOps(UniformLoc uloc)
	 : ProgVarCommonOps<tag::Uniform>(uloc)
	{ }
public:
	void SetValue(const Vector<T, N>& value)
	{
		this->template _do_set<N>(_program, _location, Data(value));
	}
};

template <typename OpsTag, typename T, std::size_t R, std::size_t C>
class ProgVarGetSetOps<OpsTag, tag::Uniform, Matrix<T, R, C>>
 : public ProgVarCommonOps<tag::Uniform>
 , public ProgVarBaseSetOps<OpsTag, tag::Uniform, tag::MatrixTypes, T, 16>
{
protected:
	ProgVarGetSetOps(UniformLoc uloc)
	 : ProgVarCommonOps<tag::Uniform>(uloc)
	{ }
public:
	void SetValue(const Matrix<T, R, C>& value)
	{
		this->template _do_set_mat<C, R>(
			_program,
			_location,
			1,
			true,
			Data(value)
		);
	}
};

OGLPLUS_DECLARE_PROG_VAR(
	Uniform,
	tag::ImplicitSel,
	tag::Uniform,
	tag::NoTypecheck
)

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/uniform.ipp>
#endif

#endif // include guard
