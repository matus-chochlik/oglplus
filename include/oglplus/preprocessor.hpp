/**
 *  @file oglplus/preprocessor.hpp
 *  @brief Preprocessor utilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_PREPROCESSOR_1202231207_HPP
#define OGLPLUS_PREPROCESSOR_1202231207_HPP

#include <oglplus/config.hpp>

#if !OGLPLUS_NO_VARIADIC_MACROS

#if !OGLPLUS_NO_INITIALIZER_LISTS
#define OGLPLUS_STD_VECTOR_INIT(TYPE, ...) {__VA_ARGS__}
#elif !OGLPLUS_NO_LAMBDAS
#define OGLPLUS_STD_VECTOR_INIT(TYPE, ...) \
([](void) -> std::vector< TYPE > \
{ \
	const TYPE _values[] = {__VA_ARGS__}; \
	return std::vector<TYPE>( \
		_values, \
		_values+ \
		sizeof(_values)/ \
		sizeof(_values[0])\
	); \
})()
#elif !OGLPLUS_NO_VARIADIC_TEMPLATES
namespace oglplus {
namespace aux {

template <typename T>
inline void _init_std_vector_push_back(std::vector<T>& result)
{ }

template <typename T, typename P, typename ... Pi>
inline void _init_std_vector_push_back(std::vector<T>& result, P p, Pi ... pi)
{
	result.push_back(p);
	_init_std_vector_push_back(result, pi...);
}

template <typename T, typename ... Pi>
inline std::vector<T> _init_std_vector(Pi ... pi)
{
	std::vector<T> result;
	result.reserve(sizeof...(Pi));
	_init_std_vector_push_back(result, pi...);
	return result;
}

#define OGLPLUS_STD_VECTOR_INIT(TYPE, ...) \
	oglplus::aux::_init_std_vector<TYPE>(__VA_ARGS__)

} }
#endif

#endif //NO_VARIADIC_MACROS

#endif // include guard
