/**
 *  .file oglplus/auxiliary/shader_data.hpp
 *  .brief Shader uniform / vertex-attribute data helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_SHADER_DATA_1107121519_HPP
#define OGLPLUS_AUX_SHADER_DATA_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/string.hpp>
#include <oglplus/auxiliary/varpara_fns.hpp>

#include <type_traits>
#include <cstddef>

namespace oglplus {
namespace aux {

template <typename T>
class ActiveProgramCallOps
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
class SpecificProgramCallOps
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

class ShaderDataSetUtils
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

template <class Setters, class Callers, std::size_t MaxCount>
class ShaderDataSetOps
 : public Setters
 , public Callers
 , public ShaderDataSetUtils
{
private:
	static void _report_if_error(GLuint program, GLuint base_location)
	{
		ShaderDataSetUtils::_do_handle_if_error(
			OGLPLUS_ERROR_INFO_AUTO_CTXT(),
			program,
			base_location
		);
	}

	OGLPLUS_ERROR_INFO_REUSE_CONTEXT(Setters)
	typedef std::false_type _set_done;
	typedef std::true_type  _set_cont;

	template <std::size_t N>
	static std::integral_constant<bool,  (N > 4)> _set_mode(void)
	{
		return std::integral_constant<bool, (N > 4)>();
	}

	template <std::size_t N, typename T>
	static void _do_set_v(
		_set_cont,
		GLuint program,
		GLuint base_location,
		GLuint location,
		const T* v
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
		_do_set_v<N - 4, T>(
			_set_mode<N - 4>(),
			program,
			base_location,
			location+1,
			v+4
		);
	}

	template <std::size_t N, typename T>
	static void _do_set_v(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		const T* v
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

	template <std::size_t N, typename T>
	static void _do_set_n(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		GLsizei n,
		const T* v
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
	template <typename S, typename ... T>
	static void _do_set_t(
		_set_cont,
		GLuint program,
		GLuint base_location,
		GLuint location,
		S v0, S v1, S v2, S v3,
		T ... v
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
			_set_mode<sizeof...(T)>(),
			program,
			base_location,
			location+1,
			v...
		);
	}

	template <typename ... T>
	static void _do_set_t(
		_set_done,
		GLuint program,
		GLuint base_location,
		GLuint location,
		T ... v
	)
	{
		std::integral_constant<std::size_t, sizeof...(T)> nparam;
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
	template <typename ... T>
	static void _do_set(GLuint program, GLuint location, T ... v)
	{
		static_assert(
			(sizeof...(T) > 0) && (sizeof...(T) <= MaxCount),
			"Set requires 1 to MaxCount arguments"
		);
		_do_set_t(
			_set_mode<sizeof...(T)>(),
			program,
			location,
			location,
			v...
		);
		_report_if_error(program, location);
	}
#else
	template <typename T>
	static void _do_set(GLuint program, GLuint location, T v0)
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

	template <typename T>
	static void _do_set(GLuint program, GLuint location, T v0, T v1)
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

	template <typename T>
	static void _do_set(GLuint program, GLuint location, T v0, T v1, T v2)
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

	template <typename T>
	static void _do_set(GLuint program, GLuint location, T v0, T v1, T v2, T v3)
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

	template <std::size_t Cols, typename T>
	static void _do_set(GLuint program, GLuint location, const T* v)
	{
		static_assert(
			(Cols > 0) && (Cols <= MaxCount),
			"The number of elements must be between 1 and MaxCount"
		);
		_do_set_v<Cols, T>(
			_set_mode<Cols>(),
			program,
			location,
			location,
			v
		);
	}

	template <std::size_t Cols, typename T>
	static void _do_set_many(GLuint prog, GLuint location, GLsizei n, const T*v)
	{
		static_assert(
			(Cols > 0) && (Cols <= MaxCount),
			"The number of elements must be between 1 and MaxCount"
		);
		_do_set_n<Cols, T>(
			_set_mode<Cols>(),
			prog,
			location,
			location,
			n,
			v
		);
	}
};

template <typename Setters, typename Callers>
class ShaderMatrixSetOps
 : public Setters
 , public Callers
 , public ShaderDataSetUtils
{
private:
	OGLPLUS_ERROR_INFO_REUSE_CONTEXT(Setters)

	static void _report_if_error(GLuint program, GLuint base_location)
	{
		ShaderDataSetUtils::_do_handle_if_error(
			OGLPLUS_ERROR_INFO_AUTO_CTXT(),
			program,
			base_location
		);
	}
protected:
	template <std::size_t Cols, std::size_t Rows, typename T>
	static void _do_set_mat(
		GLuint program,
		GLuint location,
		GLsizei count,
		bool transpose,
		T* v
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
	template <std::size_t Cols, typename T, typename ... P>
	static void _do_set_mat_p(
		GLuint program,
		GLuint location,
		bool transpose,
		T v,
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
		T values[] = {v, T(p)...};
		_do_set_mat<Cols, (sizeof...(P) + 1) / Cols, T>(
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
