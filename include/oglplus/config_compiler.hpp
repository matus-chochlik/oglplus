/**
 *  @file oglplus/config_compiler.hpp
 *  @brief Configuration options based on compiler capabilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONFIG_COMPILER_1107121519_HPP
#define OGLPLUS_CONFIG_COMPILER_1107121519_HPP

#ifndef OGLPLUS_NO_SITE_CONFIG
#include <oglplus/site_config.hpp>
#endif

#if OGLPLUS_USE_BOOST_CONFIG
#include <boost/config.hpp>
#endif


// ------- C++11 feature availability detection -------

#ifndef OGLPLUS_NO_SCOPED_ENUMS
#ifdef BOOST_NO_SCOPED_ENUMS
#define OGLPLUS_NO_SCOPED_ENUMS 1
#else
#define OGLPLUS_NO_SCOPED_ENUMS 0
#endif
#endif

#ifndef OGLPLUS_NO_VARIADIC_MACROS
#ifdef BOOST_NO_VARIADIC_MACROS
#define OGLPLUS_NO_VARIADIC_MACROS 1
#else
#define OGLPLUS_NO_VARIADIC_MACROS 0
#endif
#endif

#ifndef OGLPLUS_NO_VARIADIC_TEMPLATES
#ifdef BOOST_NO_VARIADIC_TEMPLATES
#define OGLPLUS_NO_VARIADIC_TEMPLATES 1
#else
#define OGLPLUS_NO_VARIADIC_TEMPLATES 0
#endif
#endif

#ifndef OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX
#ifdef BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX
#define OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX 1
#else
#define OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX 0
#endif
#endif

#ifndef OGLPLUS_NO_INITIALIZER_LISTS
#ifdef BOOST_NO_INITIALIZER_LISTS
#define OGLPLUS_NO_INITIALIZER_LISTS 1
#else
#define OGLPLUS_NO_INITIALIZER_LISTS 0
#endif
#endif

#ifndef OGLPLUS_NO_DEFAULTED_FUNCTIONS
#ifdef BOOST_NO_DEFAULTED_FUNCTIONS
#define OGLPLUS_NO_DEFAULTED_FUNCTIONS 1
#else
#define OGLPLUS_NO_DEFAULTED_FUNCTIONS 0
#endif
#endif

#ifndef OGLPLUS_NO_DELETED_FUNCTIONS
#ifdef BOOST_NO_DELETED_FUNCTIONS
#define OGLPLUS_NO_DELETED_FUNCTIONS 1
#else
#define OGLPLUS_NO_DELETED_FUNCTIONS 0
#endif
#endif

#ifndef OGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS
#ifdef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#define OGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS 1
#else
#define OGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS 0
#endif
#endif

#ifndef OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#ifdef BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS 1
#else
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS 0
#endif
#endif

#ifndef OGLPLUS_NO_UNICODE_LITERALS
#ifdef BOOST_NO_UNICODE_LITERALS
#define OGLPLUS_NO_UNICODE_LITERALS 1
#else
#define OGLPLUS_NO_UNICODE_LITERALS 0
#endif
#endif

#ifndef OGLPLUS_NO_USER_DEFINED_LITERALS
/* TODO this macro is not (yet) available in Boost.
 * Update this if/when it is implemented
 */
#ifdef BOOST_NO_USER_DEFINED_LITERALS
#define OGLPLUS_NO_USER_DEFINED_LITERALS 1
#else
#define OGLPLUS_NO_USER_DEFINED_LITERALS 0
#endif
#endif

#ifndef OGLPLUS_NO_CONSTEXPR
#ifdef BOOST_NO_CONSTEXPR
#define OGLPLUS_NO_CONSTEXPR 1
#else
#define OGLPLUS_NO_CONSTEXPR 0
#endif
#endif

#ifndef OGLPLUS_NO_NOEXCEPT
#ifdef BOOST_NO_NOEXCEPT
#define OGLPLUS_NO_NOEXCEPT 1
#else
#define OGLPLUS_NO_NOEXCEPT 0
#endif
#endif

#ifndef OGLPLUS_NO_LAMBDAS
#ifdef BOOST_NO_LAMBDAS
#define OGLPLUS_NO_LAMBDAS 1
#else
#define OGLPLUS_NO_LAMBDAS 0
#endif
#endif

#ifndef OGLPLUS_NO_NULLPTR
#ifdef BOOST_NO_NULLPTR
#define OGLPLUS_NO_NULLPTR 1
#else
#define OGLPLUS_NO_NULLPTR 0
#endif
#endif


#ifndef OGLPLUS_NO_CHRONO
#ifdef BOOST_NO_CXX11_HDR_CHRONO
#define OGLPLUS_NO_CHRONO 1
#else
#define OGLPLUS_NO_CHRONO 0
#endif
#endif

// ------- C++11 feature availability detection -------

#if OGLPLUS_NO_NULLPTR
#define nullptr 0
#endif

#if !OGLPLUS_NO_CONSTEXPR
#define OGLPLUS_CONSTEXPR constexpr
#else
#define OGLPLUS_CONSTEXPR const
#endif

#if !OGLPLUS_NO_NOEXCEPT
#define OGLPLUS_NOEXCEPT(...) noexcept(__VA_ARGS__)
#define OGLPLUS_NOEXCEPT_IF(...) noexcept(noexcept(__VA_ARGS__))
#else
#define OGLPLUS_NOEXCEPT(...)
#define OGLPLUS_NOEXCEPT_IF(...)
#endif

// -------- helper definitions ---------

#ifndef OGLPLUS_DOCUMENTATION_ONLY
#define OGLPLUS_DOCUMENTATION_ONLY 0
#endif

// helper macro that marks unused parameters
// so that the compiler does not complain
#define OGLPLUS_FAKE_USE(X) (void)X

#endif // include guard
