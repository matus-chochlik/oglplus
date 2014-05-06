/**
 *  .file oglplus/prog_var/set_ops.hpp
 *  .brief Program variable (uniform / vertex-attribute) helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_PROG_VAR_SET_OPS_1107121519_HPP
#define OGLPLUS_PROG_VAR_SET_OPS_1107121519_HPP

#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/fwd.hpp>

#include <type_traits>
#include <cstddef>

namespace oglplus {

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
	static void _handle_if_error(
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

template <class OpsTag, class VarTag, class TypTag, class T, std::size_t M>
class ProgVarSetOps;

template <typename OpsTag, typename VarTag, typename T, std::size_t M>
class ProgVarSetOps<OpsTag, VarTag, tag::NativeTypes, T, M>
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
		ProgVarSetUtils::_handle_if_error(
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
			(sizeof...(V) > 0) && (sizeof...(V) <= M),
			"Set requires 1 to M arguments"
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
			(Cols > 0) && (Cols <= M),
			"The number of elements must be between 1 and M"
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
			(Cols > 0) && (Cols <= M),
			"The number of elements must be between 1 and M"
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

template <typename OpsTag, typename VarTag, typename T, std::size_t M>
class ProgVarSetOps<OpsTag, VarTag, tag::MatrixTypes, T, M>
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
		ProgVarSetUtils::_handle_if_error(
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

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/prog_var/set_ops.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
