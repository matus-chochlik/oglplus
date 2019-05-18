/**
 *  @file oglplus/config/compiler.hpp
 *  @brief Configuration options based on compiler capabilities
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
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

// ------- C++XY feature availability detection -------

#ifndef OGLPLUS_NO_VARIADIC_MACROS
#if defined(BOOST_NO_CXX11_VARIADIC_MACROS) || defined(BOOST_NO_VARIADIC_MACROS)
#define OGLPLUS_NO_VARIADIC_MACROS 1
#else
#define OGLPLUS_NO_VARIADIC_MACROS 0
#endif
#endif

#ifndef OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX
#if defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) || \
  defined(BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX)
#define OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX 1
#else
#define OGLPLUS_NO_UNIFIED_INITIALIZATION_SYNTAX 0
#endif
#endif

#ifndef OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) || \
  defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS 1
#else
#define OGLPLUS_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS 0
#endif
#endif

#ifndef OGLPLUS_NO_UNICODE_LITERALS
#if defined(BOOST_NO_CXX11_UNICODE_LITERALS) || \
  defined(BOOST_NO_UNICODE_LITERALS)
#define OGLPLUS_NO_UNICODE_LITERALS 1
#else
#define OGLPLUS_NO_UNICODE_LITERALS 0
#endif
#endif

#ifndef OGLPLUS_NO_GENERALIZED_ATTRIBUTES
#define OGLPLUS_NO_GENERALIZED_ATTRIBUTES 1
#endif

// ------- C++XY feature availability detection -------

#if !OGLPLUS_NO_GENERALIZED_ATTRIBUTES
#define OGLPLUS_NORETURN [[noreturn]]
#if defined(__GNUC__)
#if __GNUC_PREREQ(7, 0)
#define OGLPLUS_FALLTHROUGH __attribute__((fallthrough));
#endif
#elif defined(__clang__)
#define OGLPLUS_FALLTHROUGH [[clang::fallthrough]];
#endif
#else
#define OGLPLUS_NORETURN
#endif

#ifndef OGLPLUS_FALLTHROUGH
#define OGLPLUS_FALLTHROUGH
#endif

// -------- disable certain warnings ---------

#ifdef _MSC_VER
#pragma warning(disable : 4396)
#endif //_MSC_VER

// -------- helper definitions ---------

#ifndef OGLPLUS_DOCUMENTATION_ONLY
#define OGLPLUS_DOCUMENTATION_ONLY 0
#endif

// helper macro that marks unused parameters
// so that the compiler does not complain
#define OGLPLUS_FAKE_USE(X) (void)X

#endif // include guard
