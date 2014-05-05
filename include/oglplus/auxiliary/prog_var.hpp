/**
 *  .file oglplus/auxiliary/prog_var.hpp
 *  .brief Program variable (uniform / vertex-attribute) helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_PROG_VAR_1107121519_HPP
#define OGLPLUS_AUX_PROG_VAR_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/fwd.hpp>
#include <oglplus/auxiliary/fwd.hpp>
#include <oglplus/auxiliary/varpara_fns.hpp>

#include <type_traits>
#include <cstddef>

namespace oglplus {
namespace aux {

template <>
class ProgVarSetters<tag::ImplicitSel, tag::VertexAttrib, tag::NativeTypes>
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(VertexAttrib, VertexAttrib)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, f, t, GLfloat)
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, d, t, GLdouble)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, s, t, GLshort)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, i, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, ui, t, GLuint)
#endif

	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, fv, v, GLfloat)
#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_3_0
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, dv, v, GLdouble)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttrib, sv, v, GLshort)

	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, i, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS(VertexAttribI, ui, v, GLuint)
#endif
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

// collection of direct state access ProgramUniform
// setter functions for basic types
template <>
class ProgVarSetters<tag::DirectState, tag::Uniform, tag::NativeTypes>
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniform, ProgramUniform)

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, ui, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, i, t, GLint)
#if GL_ARB_bindless_texture
	OGLPLUS_AUX_VARPARA_FNC(ProgramUniform, Handle, ui64ARB, t, GLuint64, 1)
#endif
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, f, t, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, d, t, GLdouble)

	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, iv, v, GLint)
#if GL_ARB_bindless_texture
	OGLPLUS_AUX_VARPARA_FNC(ProgramUniform, Handle, ui64vARB, v, GLuint64, 1)
#endif
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_FNS(ProgramUniform, dv, v, GLdouble)
#elif GL_EXT_direct_state_access
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, ui, EXT, t, GLuint)
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, i, EXT, t, GLint)
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, f, EXT, t, GLfloat)

	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, iv, EXT, v, GLint)
	OGLPLUS_AUX_VARPARA_FNS_EXT(ProgramUniform, fv, EXT, v, GLfloat)
#endif
};

// collection of direct state access ProgramUniform
// setter functions for matrices
template <>
class ProgVarSetters<tag::DirectState, tag::Uniform, tag::MatrixTypes>
{
protected:
	OGLPLUS_ERROR_INFO_CONTEXT(ProgramUniformMatrix, ProgramUniform)

#if GL_VERSION_4_1 || GL_ARB_separate_shader_objects
	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, fv, v, GLfloat)
	OGLPLUS_AUX_VARPARA_MAT_FNS(ProgramUniformMatrix, dv, v, GLdouble)
#elif GL_EXT_direct_state_access
	OGLPLUS_AUX_VARPARA_MAT_FNS_EXT(ProgramUniformMatrix,fv,EXT, v, GLfloat)
#endif
};

template <typename T>
class ProgVarCallers<tag::ImplicitSel, T>
{
protected:
	template <typename UI>
	static void _call_set_v(
		GLuint /*program*/,
		GLuint location,
		void(GLAPIENTRY *_fn)(UI, const T*),
		const T* v
	)
	{
		_fn(location, v);
	}

	template <typename UI, typename SI>
	static void _call_set_v(
		GLuint /*program*/,
		GLuint location,
		void(GLAPIENTRY *_fn)(UI, SI, const T*),
		const T* v
	)
	{
		_fn(location, 1, v);
	}

	template <typename UI, typename SI>
	static void _call_set_vn(
		GLuint /*program*/,
		GLuint location,
		GLsizei n,
		void(GLAPIENTRY *_fn)(UI, SI, const T*),
		const T* v
	)
	{
		_fn(location, n, v);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint location,
		void(GLAPIENTRY *_fn)(UI, P),
		P v0
	)
	{
		_fn(location, v0);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint location,
		void(GLAPIENTRY *_fn)(UI, P, P),
		P v0, P v1
	)
	{
		_fn(location, v0, v1);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint location,
		void(GLAPIENTRY *_fn)(UI, P, P, P),
		P v0, P v1, P v2
	)
	{
		_fn(location, v0, v1, v2);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint location,
		void(GLAPIENTRY *_fn)(UI, P, P, P, P),
		P v0, P v1, P v2, P v3
	)
	{
		_fn(location, v0, v1, v2, v3);
	}

	template <typename ID, typename CT, typename TP>
	static void _call_set_m(
		GLuint /*program*/,
		GLuint location,
		GLsizei count,
		GLboolean transpose,
		void(GLAPIENTRY *_fn)(ID, CT, TP, const T*),
		const T* v
	)
	{
		_fn(location, count, transpose, v);
	}
};

template <typename T>
class ProgVarCallers<tag::DirectState, T>
{
protected:
	template <typename UI>
	static void _call_set_v(
		GLuint program,
		GLuint location,
		void(GLAPIENTRY *_fn)(GLuint, UI, const T*),
		const T* v
	)
	{
		_fn(program, location, v);
	}

	template <typename UI, typename SI>
	static void _call_set_v(
		GLuint program,
		GLuint location,
		void(GLAPIENTRY *_fn)(GLuint, UI, SI, const T*),
		const T* v
	)
	{
		_fn(program, location, 1, v);
	}

	template <typename UI, typename SI>
	static void _call_set_vn(
		GLuint program,
		GLuint location,
		GLsizei n,
		void(GLAPIENTRY *_fn)(GLuint, UI, SI, const T*),
		const T* v
	)
	{
		_fn(program, location, n, v);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint location,
		void(GLAPIENTRY *_fn)(GLuint, UI, P),
		P v0
	)
	{
		_fn(program, location, v0);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint location,
		void(GLAPIENTRY *_fn)(GLuint, UI, P, P),
		P v0, P v1
	)
	{
		_fn(program, location, v0, v1);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint location,
		void(GLAPIENTRY *_fn)(GLuint, UI, P, P, P),
		P v0, P v1, P v2
	)
	{
		_fn(program, location, v0, v1, v2);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint location,
		void(GLAPIENTRY *_fn)(GLuint, UI, P, P, P, P),
		P v0, P v1, P v2, P v3
	)
	{
		_fn(program, location, v0, v1, v2, v3);
	}

	template <typename ID, typename CT, typename TP>
	static void _call_set_m(
		GLuint program,
		GLuint location,
		GLsizei count,
		GLboolean transpose,
		void(GLAPIENTRY *_fn)(GLuint, ID, CT, TP, const T*),
		const T* v
	)
	{
		_fn(program, location, count, transpose, v);
	}
};

class ProgVarSetUtils
{
private:
	static void _handle_error(
		const oglplus::ErrorInfo& error_info,
		GLuint program,
		GLuint location,
		GLenum result
	);
protected:
	static void _do_handle_if_error(
		const oglplus::ErrorInfo& error_info,
		GLuint program,
		GLuint location
	)
	{
		GLenum result = OGLPLUS_GLFUNC(GetError)();
		if(OGLPLUS_IS_ERROR(result != GL_NO_ERROR))
		{
			_handle_error(error_info, program, location, result);
		}
	}
};

template <
	typename OpsTag,
	typename VarTag,
	typename T,
	std::size_t MaxCount
> class ProgVarSetOps<OpsTag, VarTag, tag::NativeTypes, T, MaxCount>
 : public ProgVarSetters<OpsTag, VarTag, tag::NativeTypes>
 , public ProgVarCallers<OpsTag, T>
 , public ProgVarSetUtils
{
private:
	typedef ProgVarSetters<OpsTag, VarTag, tag::NativeTypes> Setters;
	typedef ProgVarCallers<OpsTag, T> Callers;

	OGLPLUS_ERROR_INFO_REUSE_CONTEXT(Setters)

	static void _report_if_error(GLuint program, GLuint base_location)
	{
		ProgVarSetUtils::_do_handle_if_error(
			OGLPLUS_ERROR_INFO_AUTO_CTXT(),
			program,
			base_location
		);
	}

	typedef std::false_type _set_done;
	typedef std::true_type  _set_cont;

	template <std::size_t N>
	static std::integral_constant<bool,  (N > 4)> _set_mode(void)
	{
		return std::integral_constant<bool, (N > 4)>();
	}

	template <std::size_t N, typename V>
	static void _do_set_v(
		_set_cont,
		GLuint program,
		GLuint base_location,
		GLuint location,
		const V* v
	)
	{
		std::integral_constant<std::size_t, 4> nparam;
		Callers::_call_set_v(
			program,
			location,
			Setters::_fns_v(nparam, v),
			v
		);
		_report_if_error(program, base_location);
		_do_set_v<N - 4, V>(
			_set_mode<N - 4>(),
			program,
			base_location,
			location+1,
			v+4
		);
	}

	template <std::size_t N, typename V>
	static void _do_set_v(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		const V* v
	)
	{
		std::integral_constant<std::size_t, N> nparam;
		Callers::_call_set_v(
			program,
			location,
			Setters::_fns_v(nparam, v),
			v
		);
		_report_if_error(program, base_location);
	}

	template <std::size_t N, typename V>
	static void _do_set_n(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		GLsizei n,
		const V* v
	)
	{
		std::integral_constant<std::size_t, N> nparam;
		Callers::_call_set_vn(
			program,
			location,
			n,
			Setters::_fns_v(nparam, v),
			v
		);
		_report_if_error(program, base_location);
	}


#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename S, typename ... V>
	static void _do_set_t(
		_set_cont,
		GLuint program,
		GLuint base_location,
		GLuint location,
		S v0, S v1, S v2, S v3,
		V ... v
	)
	{
		std::integral_constant<std::size_t, 4> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v0),
			v0, v1, v2, v3
		);
		_report_if_error(program, base_location);
		_do_set_t(
			_set_mode<sizeof...(V)>(),
			program,
			base_location,
			location+1,
			v...
		);
	}

	template <typename ... V>
	static void _do_set_t(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		V ... v
	)
	{
		std::integral_constant<std::size_t, sizeof...(V)> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v...),
			v...
		);
		_report_if_error(program, base_location);
	}
#endif //NO_VARIADIC_TEMPLATES

protected:

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename ... V>
	static void _do_set(GLuint program, GLuint location, V ... v)
	{
		static_assert(
			(sizeof...(V) > 0) && (sizeof...(V) <= MaxCount),
			"Set requires 1 to MaxCount arguments"
		);
		_do_set_t(
			_set_mode<sizeof...(V)>(),
			program,
			location,
			location,
			v...
		);
		_report_if_error(program, location);
	}
#else
	template <typename V>
	static void _do_set(GLuint program, GLuint location, V v0)
	{
		std::integral_constant<std::size_t, 1> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v0),
			v0
		);
		_report_if_error(program, location);
	}

	template <typename V>
	static void _do_set(GLuint program, GLuint location, V v0, V v1)
	{
		std::integral_constant<std::size_t, 2> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v0),
			v0, v1
		);
		_report_if_error(program, location);
	}

	template <typename V>
	static void _do_set(GLuint program, GLuint location, V v0, V v1, V v2)
	{
		std::integral_constant<std::size_t, 3> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v0),
			v0, v1, v2
		);
		_report_if_error(program, location);
	}

	template <typename V>
	static void _do_set(GLuint program, GLuint location, V v0, V v1, V v2, V v3)
	{
		std::integral_constant<std::size_t, 4> nparam;
		Callers::_call_set_t(
			program,
			location,
			Setters::_fns_t(nparam, &v0),
			v0, v1, v2, v3
		);
		_report_if_error(program, location);
	}
#endif //NO_VARIADIC_TEMPLATES

	template <std::size_t Cols, typename V>
	static void _do_set(GLuint program, GLuint location, const V* v)
	{
		static_assert(
			(Cols > 0) && (Cols <= MaxCount),
			"The number of elements must be between 1 and MaxCount"
		);
		_do_set_v<Cols, V>(
			_set_mode<Cols>(),
			program,
			location,
			location,
			v
		);
	}

	template <std::size_t Cols, typename V>
	static void _do_set_many(GLuint prog, GLuint location, GLsizei n, const V*v)
	{
		static_assert(
			(Cols > 0) && (Cols <= MaxCount),
			"The number of elements must be between 1 and MaxCount"
		);
		_do_set_n<Cols, V>(
			_set_mode<Cols>(),
			prog,
			location,
			location,
			n,
			v
		);
	}
};

template <
	typename OpsTag,
	typename VarTag,
	typename T,
	std::size_t MaxCount
> class ProgVarSetOps<OpsTag, VarTag, tag::MatrixTypes, T, MaxCount>
 : public ProgVarSetters<OpsTag, VarTag, tag::MatrixTypes>
 , public ProgVarCallers<OpsTag, T>
 , public ProgVarSetUtils
{
private:
	typedef ProgVarSetters<OpsTag, VarTag, tag::MatrixTypes> Setters;
	typedef ProgVarCallers<OpsTag, T> Callers;

	OGLPLUS_ERROR_INFO_REUSE_CONTEXT(Setters)

	static void _report_if_error(GLuint program, GLuint base_location)
	{
		ProgVarSetUtils::_do_handle_if_error(
			OGLPLUS_ERROR_INFO_AUTO_CTXT(),
			program,
			base_location
		);
	}
protected:
	template <std::size_t Cols, std::size_t Rows, typename V>
	static void _do_set_mat(
		GLuint program,
		GLuint location,
		GLsizei count,
		bool transpose,
		V* v
	)
	{
		static_assert(
			(Cols > 0) && (Cols <= 4),
			"The number of columns must be between 1 and 4"
		);
		static_assert(
			(Rows > 0) && (Rows <= 4),
			"The number of rows must be between 1 and 4"
		);
		std::integral_constant<std::size_t, Rows> rows;
		std::integral_constant<std::size_t, Cols> cols;
		Callers::_call_set_m(
			program,
			location,
			count,
			transpose ? GL_TRUE : GL_FALSE,
			Setters::_fns_v(cols, rows, v),
			v
		);
		_report_if_error(program, location);
	}

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <std::size_t Cols, typename V, typename ... P>
	static void _do_set_mat_p(
		GLuint program,
		GLuint location,
		bool transpose,
		V v,
		P ... p
	)
	{
		static_assert(
			(Cols > 0) && (Cols <= 4),
			"The number of columns must be between 1 and 4"
		);
		static_assert(
			(sizeof...(P) + 1) % Cols == 0,
			"Not enough values for the last row"
		);
		V values[] = {v, V(p)...};
		_do_set_mat<Cols, (sizeof...(P) + 1) / Cols, V>(
			program,
			location,
			1,
			transpose,
			values
		);
	}
#endif //NO_VARIADIC_TEMPLATES
};

} // namespace aux
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/auxiliary/shader_data.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
