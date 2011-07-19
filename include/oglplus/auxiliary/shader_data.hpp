/**
 *  .file oglplus/auxiliary/shader_data.hpp
 *  .brief Shader uniform / vertex-attribute data helpers
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_SHADER_DATA_1107121519_HPP
#define OGLPLUS_AUX_SHADER_DATA_1107121519_HPP

#include <oglplus/auxiliary/varpara_fns.hpp>

#include <type_traits>

namespace oglplus {
namespace aux {

template <class Setters, size_t SetMax>
class ShaderDataSetOps
 : public Setters
{
private:
	typedef std::false_type _set_done;
	typedef std::true_type  _set_cont;

	template <size_t N>
	static std::integral_constant<bool,  (N > 4)> _set_mode(void)
	{
		return std::integral_constant<bool, (N > 4)>();
	}

	template <size_t N, typename T>
	static void _call_set_v(
		GLuint index,
		const T* v,
		void(&_fn)(GLuint, const T*)
	)
	{
		_fn(index, v);
	}

	template <size_t N, typename T>
	static void _call_set_v(
		GLuint index,
		const T* v,
		void(&_fn)(GLuint, GLsizei, const T*)
	)
	{
		_fn(index, 1, v);
	}

	template <size_t N, typename T>
	static void _do_set_v(_set_cont, GLuint index, const T* v)
	{
		_call_set_v(index, v, ::std::get<3>(Setters::_fns_v(v)));
		AssertNoError(OGLPLUS_ERROR_INFO());
		_do_set_v<N - 4, T>(_set_mode<N - 4>(), index+1, v+4);
	}

	template <size_t N, typename T>
	static void _do_set_v(_set_done, GLuint index, const T* v)
	{
		_call_set_v(index, v, ::std::get<N-1>(Setters::_fns_v(v)));
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	template <typename S, typename ... T>
	static void _do_set_t(
		_set_cont,
		GLuint index,
		 S v0, S v1, S v2, S v3,
		T ... v
	)
	{
		std::get<3>(Setters::_fns_t(&v0))(index, v0, v1, v2, v3);
		AssertNoError(OGLPLUS_ERROR_INFO());
		_do_set_t(_set_mode<sizeof...(T)>(), index+1, v...);
	}

	template <typename ... T>
	static void _do_set_t(
		_set_done,
		GLuint index,
		T ... v
	)
	{
		std::get<sizeof...(T) - 1>(Setters::_fns_t(&v...))(index, v...);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}
protected:
	template <typename ... T>
	static void _do_set(GLuint index, T ... v)
	{
		static_assert(
			(sizeof...(T) > 0) && (sizeof...(T) <= SetMax),
			"Set requires 1 to SetMax arguments"
		);
		_do_set_t(
			_set_mode<sizeof...(T)>(),
			index,
			v...
		);
		AssertNoError(OGLPLUS_ERROR_INFO());
	}

	template <size_t N, typename T>
	static void _do_set(GLuint index, const T* v)
	{
		static_assert(
			(N > 0) && (N <= SetMax),
			"The number of elements must be between 1 and SetMax"
		);
		_do_set_v<N, T>(_set_mode<N>(), index, v);
	}
};

template <typename Setters>
class ShaderMatrixSetOps
 : public Setters
{
protected:
	template <size_t Cols, size_t Rows, typename T>
	static void _do_set_mat(
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
		std::get<Cols - 2>(
			std::get<Rows - 2>(
				Setters::_fns_v(v)
			)
		)(index, count, transpose ? GL_TRUE : GL_FALSE, v);
	}

	template <size_t Cols, typename T, typename ... P>
	static void _do_set_mat(GLuint index, bool transpose, T v, P ... p)
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
			index,
			1,
			transpose,
			values
		);
	}
};


} // namespace aux
} // namespace oglplus

#endif // include guard
