/**
 *  @file oglplus/config/compiler.hpp
 *  @brief Configuration options based on compiler capabilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONFIG_COMPILER_1107121519_HPP
#define OGLPLUS_CONFIG_COMPILER_1107121519_HPP

#ifndef OGLPLUS_NO_SITE_CONFIG
#include <oglplus/config/site.hpp>
#endif

#ifndef OGLPLUS_USE_BOOST_CONFIG
#define OGLPLUS_USE_BOOST_CONFIG 0
#endif

#if OGLPLUS_USE_BOOST_CONFIG
#include <boost/config.hpp>
#endif

// ------- C++11 feature availability detection -------

#ifndef OGLPLUS_NO_INITIALIZER_LISTS
#if	defined(BOOST_NO_CXX11_INITIALIZER_LISTS) ||\
	defined(BOOST_NO_INITIALIZER_LISTS)
#define OGLPLUS_NO_INITIALIZER_LISTS 1
#else
#define OGLPLUS_NO_INITIALIZER_LISTS 0
#endif
#endif

#ifndef OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#if	defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) ||\
	defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS 1
#else
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS 0
#endif
#endif

#ifndef OGLPLUS_NO_UNICODE_LITERALS
#if	defined(BOOST_NO_CXX11_UNICODE_LITERALS) ||\
	defined(BOOST_NO_UNICODE_LITERALS)
#define OGLPLUS_NO_UNICODE_LITERALS 1
#else
#define OGLPLUS_NO_UNICODE_LITERALS 0
#endif
#endif

#ifndef OGLPLUS_NO_USER_DEFINED_LITERALS
/* TODO this macro is not (yet) available in Boost.
 * Update this if/when it is implemented
 */
#if	defined(BOOST_NO_CXX11_USER_DEFINED_LITERALS) ||\
	defined(BOOST_NO_USER_DEFINED_LITERALS)
#define OGLPLUS_NO_USER_DEFINED_LITERALS 1
#else
#define OGLPLUS_NO_USER_DEFINED_LITERALS 0
#endif
#endif

#ifndef OGLPLUS_NO_TEMPLATE_ALIASES
#if	defined(BOOST_NO_CXX11_TEMPLATE_ALIASES) ||\
	defined(BOOST_NO_TEMPLATE_ALIASES)
#define OGLPLUS_NO_TEMPLATE_ALIASES 1
#else
#define OGLPLUS_NO_TEMPLATE_ALIASES 0
#endif
#endif

#ifndef OGLPLUS_NO_INHERITED_CONSTRUCTORS
/* TODO this macro is not (yet) available in Boost.
 * Update this if/when it is implemented
 */
#if	defined(BOOST_NO_CXX11_INHERITED_CONSTRUCTORS) ||\
	defined(BOOST_NO_INHERITED_CONSTRUCTORS)
#define OGLPLUS_NO_INHERITED_CONSTRUCTORS 1
#else
#define OGLPLUS_NO_INHERITED_CONSTRUCTORS 0
#endif
#endif

#ifndef OGLPLUS_NO_LAMBDAS
#if	defined(BOOST_NO_CXX11_LAMBDAS) ||\
	defined(BOOST_NO_LAMBDAS)
#define OGLPLUS_NO_LAMBDAS 1
#else
#define OGLPLUS_NO_LAMBDAS 0
#endif
#endif

#ifndef OGLPLUS_NO_CHRONO
#if	defined(BOOST_NO_CXX11_HDR_CHRONO) ||\
	defined(BOOST_NO_HDR_CHRONO)
#define OGLPLUS_NO_CHRONO 1
#else
#define OGLPLUS_NO_CHRONO 0
#endif
#endif

// -------- disable certain warnings ---------

#ifdef _MSC_VER
#pragma warning( disable : 4396 )
#endif //_MSC_VER

// -------- helper definitions ---------

#ifndef OGLPLUS_DOCUMENTATION_ONLY
#define OGLPLUS_DOCUMENTATION_ONLY 0
#endif

// helper macro that marks unused parameters
// so that the compiler does not complain
#define OGLPLUS_FAKE_USE(X) (void)X

#endif // include guard
