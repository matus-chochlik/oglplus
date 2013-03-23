/**
 *  @file oalplus/config.hpp
 *  @brief Compile-time configuration options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_CONFIG_1303201545_HPP
#define OALPLUS_CONFIG_1303201545_HPP

#ifndef OGLPLUS_NO_SITE_CONFIG
#include <oglplus/site_config.hpp>
#endif


#if OGLPLUS_USE_BOOST_CONFIG
#include <boost/config.hpp>
#endif

#include <oglplus/config_compiler.hpp>

#if OGLPLUS_NO_NULLPTR
#define nullptr 0
#endif

#ifdef  OGLPLUS_DOCUMENTATION_ONLY
#define OALPLUS_DOCUMENTATION_ONLY OGLPLUS_DOCUMENTATION_ONLY
#endif

#ifdef OGLPLUS_NO_OBJECT_DESCS
#define OALPLUS_NO_OBJECT_DESCS OGLPLUS_NO_OBJECT_DESCS
#endif

#define OALPLUS_FAKE_USE(EXPR) (void)EXPR

#endif // include guard
