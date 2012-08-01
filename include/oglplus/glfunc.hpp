/**
 *  @file oglplus/glfunc.hpp
 *  @brief Helper macro for optional checking of availability of GL function
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_GLFUNC_1201020903_HPP
#define OGLPLUS_GLFUNC_1201020903_HPP

#include <oglplus/config.hpp>

#if !OGLPLUS_NO_GLFUNC_CHECKS
#include <oglplus/error.hpp>
#endif

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY
/// Exception class for situations when a pointer to a GL function is invalid.
/** @OGLplus optionally (based on the value of the #OGLPLUS_NO_GLFUNC_CHECKS
 *  compile-time switch) checks, if pointers to OpenGL functions are valid
 *  (i.e. not @c nullptr). OpenGL functions are usually called through pointers,
 *  when using a library such as GLEW, which tries to find and get the addresses
 *  of GL functions from the GL library dynamically at run-time. Sometimes
 *  the pointers to several of the functions remain uninitialized and usually
 *  result in a memory violation and program termination if called.
 *
 *  The MissingFunction exception class indicates that the usage
 *  of such uninitialized function pointer was detected at run-time
 *  and allows the application to terminate more gracefully.
 *
 *  @see #OGLPLUS_NO_GLFUNC_CHECKS
 *
 *  @ingroup error_handling
 */
class MissingFunction
 : public Error
{ };
#elif !OGLPLUS_NO_VARIADIC_TEMPLATES && !OGLPLUS_NO_GLFUNC_CHECKS
class MissingFunction
 : public Error
{
public:
	MissingFunction(GLenum code, const char* msg, const ErrorInfo& info)
	 : Error(code, msg, info, true)
	{ }
};

template <typename RV, typename ... Params>
inline auto _checked_glfunc(
	RV (*pfn)(Params...),
	const ErrorInfo&
) -> decltype(pfn)
{
	return pfn;
}

template <typename RV, typename ... Params>
inline auto _checked_glfunc(
	RV (**ppfn)(Params...),
	const ErrorInfo& error_info
) -> decltype(*ppfn)
{
	if(!ppfn || !*ppfn) HandleMissingFunction<MissingFunction>(error_info);
	return *ppfn;
}

#define OGLPLUS_GLFUNC(FUNCNAME) \
	::oglplus::_checked_glfunc( \
		&::gl##FUNCNAME, \
		OGLPLUS_ERROR_INFO(FUNCNAME) \
	)
#else
#define OGLPLUS_GLFUNC(FUNCNAME) \
	::gl##FUNCNAME
#endif


} // namespace oglplus

#endif // include guard
