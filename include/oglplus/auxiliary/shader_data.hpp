/**
 *  .file oglplus/auxiliary/shader_data.hpp
 *  .brief Shader uniform / vertex-attribute data helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_SHADER_DATA_1107121519_HPP
#define OGLPLUS_AUX_SHADER_DATA_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/glfunc.hpp>
#include <oglplus/error.hpp>
#include <oglplus/string.hpp>
#include <oglplus/auxiliary/varpara_fns.hpp>
#include <oglplus/auxiliary/strings.hpp>

#include <type_traits>

namespace oglplus {
namespace aux {

template <typename T>
class ActiveProgramCallOps
{
protected:
	template <typename UI>
	static void _call_set_v(
		GLuint /*program*/,
		GLuint index,
		void(*_fn)(UI, const T*),
		const T* v
	)
	{
		_fn(index, v);
	}

	template <typename UI, typename SI>
	static void _call_set_v(
		GLuint /*program*/,
		GLuint index,
		void(*_fn)(UI, SI, const T*),
		const T* v
	)
	{
		_fn(index, 1, v);
	}

	template <typename UI, typename SI>
	static void _call_set_vn(
		GLuint /*program*/,
		GLuint index,
		GLsizei n,
		void(*_fn)(UI, SI, const T*),
		const T* v
	)
	{
		_fn(index, n, v);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint index,
		void(*_fn)(UI, P),
		P v0
	)
	{
		_fn(index, v0);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint index,
		void(*_fn)(UI, P, P),
		P v0, P v1
	)
	{
		_fn(index, v0, v1);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint index,
		void(*_fn)(UI, P, P, P),
		P v0, P v1, P v2
	)
	{
		_fn(index, v0, v1, v2);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint /*program*/,
		GLuint index,
		void(*_fn)(UI, P, P, P, P),
		P v0, P v1, P v2, P v3
	)
	{
		_fn(index, v0, v1, v2, v3);
	}

	template <typename ID, typename CT, typename TP>
	static void _call_set_m(
		GLuint /*program*/,
		GLuint index,
		GLsizei count,
		GLboolean transpose,
		void(*_fn)(ID, CT, TP, const T*),
		const T* v
	)
	{
		_fn(index, count, transpose, v);
	}
};

template <typename T>
class SpecificProgramCallOps
{
protected:
	template <typename UI>
	static void _call_set_v(
		GLuint program,
		GLuint index,
		void(*_fn)(GLuint, UI, const T*),
		const T* v
	)
	{
		_fn(program, index, v);
	}

	template <typename UI, typename SI>
	static void _call_set_v(
		GLuint program,
		GLuint index,
		void(*_fn)(GLuint, UI, SI, const T*),
		const T* v
	)
	{
		_fn(program, index, 1, v);
	}

	template <typename UI, typename SI>
	static void _call_set_vn(
		GLuint program,
		GLuint index,
		GLsizei n,
		void(*_fn)(GLuint, UI, SI, const T*),
		const T* v
	)
	{
		_fn(program, index, n, v);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint index,
		void(*_fn)(GLuint, UI, P),
		P v0
	)
	{
		_fn(program, index, v0);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint index,
		void(*_fn)(GLuint, UI, P, P),
		P v0, P v1
	)
	{
		_fn(program, index, v0, v1);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint index,
		void(*_fn)(GLuint, UI, P, P, P),
		P v0, P v1, P v2
	)
	{
		_fn(program, index, v0, v1, v2);
	}

	template <typename UI, typename P>
	static void _call_set_t(
		GLuint program,
		GLuint index,
		void(*_fn)(GLuint, UI, P, P, P, P),
		P v0, P v1, P v2, P v3
	)
	{
		_fn(program, index, v0, v1, v2, v3);
	}

	template <typename ID, typename CT, typename TP>
	static void _call_set_m(
		GLuint program,
		GLuint index,
		GLsizei count,
		GLboolean transpose,
		void(*_fn)(GLuint, ID, CT, TP, const T*),
		const T* v
	)
	{
		_fn(program, index, count, transpose, v);
	}
};

class ShaderDataSetUtils
{
protected:
	static void _do_handle_if_error(
		const oglplus::ErrorInfo& error_info,
		GLuint program,
		GLuint index,
		String (*_get_name)(GLuint, GLuint)
	)
	{
		GLenum result = OGLPLUS_GLFUNC(GetError)();
		if(OGLPLUS_IS_ERROR(result != GL_NO_ERROR))
		{
			Error::PropertyMap props;
			props["identifier"] = _get_name(program, index);
			props["program"] = ObjectDescRegistry<ProgramOps>::
					_get_desc(program);
			HandleError(
				result,
				"Error setting shading program variable value",
				error_info,
				std::move(props)
			);
		}
	}
};

template <class Queries, class Setters, class Callers, size_t MaxCount>
class ShaderDataSetOps
 : public Queries
 , public Setters
 , public Callers
 , public ShaderDataSetUtils
{
private:
	static void _report_if_error(GLuint program, GLuint base_index)
	{
		ShaderDataSetUtils::_do_handle_if_error(
			OGLPLUS_ERROR_INFO_AUTO_CTXT(),
			program,
			base_index,
			&Queries::_query_name
		);
	}

	OGLPLUS_ERROR_INFO_REUSE_CONTEXT(Setters)
	typedef std::false_type _set_done;
	typedef std::true_type  _set_cont;

	template <size_t N>
	static std::integral_constant<bool,  (N > 4)> _set_mode(void)
	{
		return std::integral_constant<bool, (N > 4)>();
	}

	template <size_t N, typename T>
	static void _do_set_v(
		_set_cont,
		GLuint program,
		GLuint base_index,
		GLuint index,
		const T* v
	)
	{
		Callers::_call_set_v(
			program,
			index,
			::std::get<3>(Setters::_fns_v(v)),
			v
		);
		_report_if_error(program, base_index);
		_do_set_v<N - 4, T>(
			_set_mode<N - 4>(),
			program,
			base_index,
			index+1,
			v+4
		);
	}

	template <size_t N, typename T>
	static void _do_set_v(
		_set_done,
		GLuint program,
		GLuint base_index,
		GLuint index,
		const T* v
	)
	{
		Callers::_call_set_v(
			program,
			index,
			::std::get<N-1>(Setters::_fns_v(v)),
			v
		);
		_report_if_error(program, base_index);
	}

	template <size_t N, typename T>
	static void _do_set_n(
		_set_done,
		GLuint program,
		GLuint base_index,
		GLuint index,
		GLsizei n,
		const T* v
	)
	{
		Callers::_call_set_vn(
			program,
			index,
			n,
			::std::get<N-1>(Setters::_fns_v(v)),
			v
		);
		_report_if_error(program, base_index);
	}


#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename S, typename ... T>
	static void _do_set_t(
		_set_cont,
		GLuint program,
		GLuint base_index,
		GLuint index,
		S v0, S v1, S v2, S v3,
		T ... v
	)
	{
		Callers::_call_set_t(
			program,
			index,
			std::get<3>(Setters::_fns_t(&v0)),
			v0, v1, v2, v3
		);
		_report_if_error(program, base_index);
		_do_set_t(
			_set_mode<sizeof...(T)>(),
			program,
			base_index,
			index+1,
			v...
		);
	}

	template <typename ... T>
	static void _do_set_t(
		_set_done,
		GLuint program,
		GLuint base_index,
		GLuint index,
		T ... v
	)
	{
		Callers::_call_set_t(
			program,
			index,
			std::get<sizeof...(T) - 1>(Setters::_fns_t(&v...)),
			v...
		);
		_report_if_error(program, base_index);
	}
#endif //NO_VARIADIC_TEMPLATES

protected:

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <typename ... T>
	static void _do_set(GLuint program, GLuint index, T ... v)
	{
		static_assert(
			(sizeof...(T) > 0) && (sizeof...(T) <= MaxCount),
			"Set requires 1 to MaxCount arguments"
		);
		_do_set_t(
			_set_mode<sizeof...(T)>(),
			program,
			index,
			index,
			v...
		);
		_report_if_error(program, index);
	}
#endif //NO_VARIADIC_TEMPLATES

	template <size_t Cols, typename T>
	static void _do_set(GLuint program, GLuint index, const T* v)
	{
		static_assert(
			(Cols > 0) && (Cols <= MaxCount),
			"The number of elements must be between 1 and MaxCount"
		);
		_do_set_v<Cols, T>(
			_set_mode<Cols>(),
			program,
			index,
			index,
			v
		);
	}

	template <size_t Cols, typename T>
	static void _do_set_many(GLuint prog, GLuint index, GLsizei n, const T*v)
	{
		static_assert(
			(Cols > 0) && (Cols <= MaxCount),
			"The number of elements must be between 1 and MaxCount"
		);
		_do_set_n<Cols, T>(
			_set_mode<Cols>(),
			prog,
			index,
			index,
			n,
			v
		);
	}
};

template <typename Queries, typename Setters, typename Callers>
class ShaderMatrixSetOps
 : public Queries
 , public Setters
 , public Callers
 , public ShaderDataSetUtils
{
private:
	OGLPLUS_ERROR_INFO_REUSE_CONTEXT(Setters)

	static void _report_if_error(GLuint program, GLuint base_index)
	{
		ShaderDataSetUtils::_do_handle_if_error(
			OGLPLUS_ERROR_INFO_AUTO_CTXT(),
			program,
			base_index,
			&Queries::_query_name
		);
	}
protected:
	template <size_t Cols, size_t Rows, typename T>
	static void _do_set_mat(
		GLuint program,
		GLuint index,
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
		Callers::_call_set_m(
			program,
			index,
			count,
			transpose ? GL_TRUE : GL_FALSE,
			std::get<Cols - 2>(
				std::get<Rows - 2>(
					Setters::_fns_v(v)
				)
			),
			v
		);
		_report_if_error(program, index);
	}

#if !OGLPLUS_NO_VARIADIC_TEMPLATES
	template <size_t Cols, typename T, typename ... P>
	static void _do_set_mat_p(
		GLuint program,
		GLuint index,
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
			index,
			1,
			transpose,
			values
		);
	}
#endif //NO_VARIADIC_TEMPLATES
};


} // namespace aux
} // namespace oglplus

#endif // include guard
