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
#define OGLPLUS_STD_VECTOR_INIT(TYPE, ...) __VA_ARGS__
#elif !OGLPLUS_NO_LAMBDAS
#define OGLPLUS_STD_VECTOR_INIT(TYPE, ...) \
([](void) -> std::vector< TYPE > \
{ \
	const TYPE _values[] = __VA_ARGS__; \
	return std::vector<TYPE>( \
		_values, \
		_values+ \
		sizeof(_values)/ \
		sizeof(_values[0])\
	); \
})()
#endif

#endif //NO_VARIADIC_MACROS

#endif // include guard
