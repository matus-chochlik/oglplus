/**
 *  @file oglplus/glfunc.hpp
 *  @brief Helper macro for optional checking of availability of GL function
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_GLFUNC_1201020903_HPP
#define OGLPLUS_GLFUNC_1201020903_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/config/gl.hpp>

#if !OGLPLUS_NO_GLFUNC_CHECKS
#include <oglplus/error/basic.hpp>
#endif

namespace oglplus {

#if !OGLPLUS_NO_VARIADIC_TEMPLATES && !OGLPLUS_NO_GLFUNC_CHECKS
template <typename RV, typename ... Params>
inline auto _checked_glfunc(
	RV (GLAPIENTRY *pfn)(Params...),
	const char*
) -> decltype(pfn)
{
	return pfn;
}

template <typename RV, typename ... Params>
inline auto _checked_glfunc(
	RV (* GLAPIENTRY *ppfn)(Params...),
	const char* func_name
) -> decltype(*ppfn)
{
	OGLPLUS_HANDLE_ERROR_IF(
		(!ppfn || !*ppfn),
		GL_INVALID_OPERATION,
		MissingFunction::Message(),
		MissingFunction,
		GLFuncName(func_name)
	);
	return *ppfn;
}

#ifndef OGLPLUS_GLFUNC
#define OGLPLUS_GLFUNC(FUNCNAME) \
	::oglplus::_checked_glfunc( \
		&::gl##FUNCNAME, \
		#FUNCNAME \
	)
#endif
#else
#ifndef OGLPLUS_GLFUNC
#define OGLPLUS_GLFUNC(FUNCNAME) \
	::gl##FUNCNAME
#endif
#endif


} // namespace oglplus

#endif // include guard
