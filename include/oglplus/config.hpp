/**
 *  @file oglplus/config.hpp
 *  @brief Compile-time configuration options
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CONFIG_1107121519_HPP
#define OGLPLUS_CONFIG_1107121519_HPP

#ifndef OGLPLUS_NO_SITE_CONFIG
#include <oglplus/site_config.hpp>
#endif

#ifndef OGLPLUS_USE_GLEW
#define OGLPLUS_USE_GLEW 0
#endif

#ifndef OGLPLUS_USE_FREEGLUT
#define OGLPLUS_USE_FREEGLUT 0
#endif

#ifndef OGLPLUS_USE_BOOST_CONFIG
#define OGLPLUS_USE_BOOST_CONFIG 0
#endif

#if OGLPLUS_USE_BOOST_CONFIG
#include <boost/config.hpp>
#endif

#include <oglplus/config_compiler.hpp>

// define GLAPIENTRY
#ifdef GLAPIENTRY
#undef GLAPIENTRY
#endif
// borrowed from glew.h which does define GLAPIENTRY properly
// at the beginning but undefs it at the end of the header
#if defined(__MINGW32__) || defined(__CYGWIN__)
#  define GLAPIENTRY __stdcall
#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#  define GLAPIENTRY __stdcall
#else
#  define GLAPIENTRY
#endif

// -------------------- Compile-time configuration ----------------------------

/** @defgroup compile_time_config Compile-time configuration
 *
 *  @section oglplus_configuration_options Configuration options
 *
 *  This section describes compile-time preprocessor symbols that
 *  can be used to configure several aspects of @OGLplus.
 *
 *  Most of the options are set either to a zero or a non-zero
 *  integer value to disable or enable the behavior controlled
 *  by the option.
 *
 *  All options have a default value which can be overriden by
 *  setting the option before @c oglplus/config.hpp is processed
 *  either by editing the @c oglplus/site_config.hpp file or by
 *  using the @c -D compiler option (or its equivalent for defining
 *  preprocessor symbols on the command-line).
 */

#include <oglplus/config_basic.hpp>

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the testing of object type on construction
/** Setting this preprocessor option to a non-zero integer value
 *  disables the additional checking of the type of object
 *  returned by OpenGL's @c glGen*(...) functions during the construction
 *  of an Object. Setting it to zero enables the check.
 *
 *  By default this option is set to 1, i.e. object type tests are disabled.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_DONT_TEST_OBJECT_TYPE
#else
# ifndef OGLPLUS_DONT_TEST_OBJECT_TYPE
#  define OGLPLUS_DONT_TEST_OBJECT_TYPE 1
# endif
#endif


#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling textual object descriptions
/** Setting this preprocessor option to a non-zero integer value
 *  disables the @ref oglplus_object_description attached to
 *  various specializations of @c Object (like Program, Shader,
 *  Texture, etc.) during construction by the means of the ObjectDesc
 *  parameter in constructor of Object.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. objects descriptions are enabled, when not in low-profile mode
 *  and disabled otherwise.
 *
 *  @note Object descriptions use statically initialized data which
 *  may cause problems if the final executable is built together from
 *  several different object files. Because of this, if object descriptions
 *  are enabled it is recommended that OGLplus applications are built with
 *  #OGLPLUS_LINK_LIBRARY set to non-zero or are built as a single translation
 *  unit.
 *
 *  @see OGLPLUS_LINK_LIBRARY
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_NO_OBJECT_DESCS
#else
# ifndef OGLPLUS_NO_OBJECT_DESCS
#  define OGLPLUS_NO_OBJECT_DESCS OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch enabling lazy implementation of StrLit
/** The StrLit class has two implementations, one referred to as 'Lazy'
 *  which only stores the pointer to the C-string literal where the size
 *  is obtained lazily only when required. The other implementation lets
 *  the compiler to determine and store the size of the literal during
 *  compilation.
 *
 *  The advantage of the lazy implementation is smaller code size and slightly
 *  better compilation times, while the calculation of the size of the literal
 *  adds run-time overhead. The other implementation results in slightly
 *  larger binaries but has the advantage that the size of the literal is
 *  pre-calculated.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. lazy string literals are enabled, when in low-profile mode
 *  and disabled otherwise.
 *
 *  @see StrLit
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_LAZY_STR_LIT
#else
# ifndef OGLPLUS_LAZY_STR_LIT
#  define OGLPLUS_LAZY_STR_LIT OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the functions returning enumerated value names
/** Setting this preprocessor symbol to a nonzero value causes that
 *  the @c EnumValueName(Enum) functions always return an empty string.
 *  When set to zero these functions return a textual name of an enumerated
 *  value passed as argument.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. enumeration value names are enabled, when not in low-profile mode
 *  and disabled otherwise.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_NO_ENUM_VALUE_NAMES
#else
# ifndef OGLPLUS_NO_ENUM_VALUE_NAMES
#  define OGLPLUS_NO_ENUM_VALUE_NAMES OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the functions returning enumerated value ranges
/** Setting this preprocessor symbol to a nonzero value causes that
 *  the @c EnumValueRange<Enum>() functions always return an empty range.
 *  When set to zero these functions return a range of all values in the
 *  enumeration passed as template argument.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. enumeration value ranges are enabled, when not in low-profile mode
 *  and disabled otherwise.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_NO_ENUM_VALUE_RANGES
#else
# ifndef OGLPLUS_NO_ENUM_VALUE_RANGES
#  define OGLPLUS_NO_ENUM_VALUE_RANGES OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling UTF-8 validity checks in various functions
/** Setting this preprocessor symbol to a nonzero value causes that
 *  the @c StrLit and @c String constructors skip the UTF-8 validity checks.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. the UTF-8 validity checks are enabled, when not in low-profile mode
 *  and disabled otherwise.
 *
 *  @see String
 *  @see StrLit
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_NO_UTF8_CHECKS
#else
# ifndef OGLPLUS_NO_UTF8_CHECKS
#  define OGLPLUS_NO_UTF8_CHECKS OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling checks of validity of pointers to functions
/** Setting this preprocessor symbol to a nonzero value causes that
 *  if the OpenGL functions are called through a pointer then the pointer
 *  is checked before it is used to call the function. If enabled and a pointer
 *  to GL function is nullptr then the MissingFunction exception is thrown.
 *
 *  This check can safely be disabled if functions from the GL API are
 *  not called through pointers.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. the function pointer checks are enabled, when not in low-profile mode,
 *  and disabled otherwise. The check however requires variadic templates.
 *  If variadic templates are not available then the checks are disabled.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_NO_GLFUNC_CHECKS
#else
# ifndef OGLPLUS_NO_GLFUNC_CHECKS
#  define OGLPLUS_NO_GLFUNC_CHECKS OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch entirely disabling typechecking of uniforms.
/** Setting this preprocessor symbol to a nonzero value causes that
 *  even the Uniform variables that are declared with UniformTypecheckingLevel
 *  other than None, are not typechecked.
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. typechecking of uniforms is enabled when not in low-profile mode,
 *  and disabled otherwise.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_NO_UNIFORM_TYPECHECK
#else
# ifndef OGLPLUS_NO_UNIFORM_TYPECHECK
#  define OGLPLUS_NO_UNIFORM_TYPECHECK OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch enabling customized @ref error_handling
/**
 *  By default this option is set to 0, i.e. customized error handling
 *  is is disabled.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_CUSTOM_ERROR_HANDLING
#else
# ifndef OGLPLUS_CUSTOM_ERROR_HANDLING
#  define OGLPLUS_CUSTOM_ERROR_HANDLING 0
# endif
#endif


// Configuration options related to ErrorInfo


#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorGLSymbol attribute of ErrorInfo
/**
 *  @see ErrorGLSymbol()
 *
 *  By default this option is set to 0, i.e. ErrorGLSymbol is enabled.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
#else
# ifndef OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
#  define OGLPLUS_ERROR_INFO_NO_GL_SYMBOL 0
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorFile attribute of ErrorInfo
/**
 *  @see ErrorFile()
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. ErrorFile is enabled, when not in low-profile and disabled otherwise.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_FILE
#else
# ifndef OGLPLUS_ERROR_INFO_NO_FILE
#  define OGLPLUS_ERROR_INFO_NO_FILE OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorLine attribute of ErrorInfo
/**
 *  @see ErrorLine()
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. ErrorLine is enabled, when not in low-profile and disabled otherwise.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_LINE OGLPLUS_LOW_PROFILE
#else
# ifndef OGLPLUS_ERROR_INFO_NO_LINE
#  define OGLPLUS_ERROR_INFO_NO_LINE OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorFunc attribute of ErrorInfo
/**
 *  @see ErrorFunc()
 *
 *  By default this option is set to 0, i.e. ErrorFunc is enabled.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_FUNC
#else
# ifndef OGLPLUS_ERROR_INFO_NO_FUNC
#  define OGLPLUS_ERROR_INFO_NO_FUNC 0
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorClassName attribute of ErrorInfo
/**
 *  @see ErrorClassName()
 *
 *  By default this option is set to 0, i.e. ErrorClassName is enabled.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_CLASS_NAME
#else
# ifndef OGLPLUS_ERROR_INFO_NO_CLASS_NAME
#  define OGLPLUS_ERROR_INFO_NO_CLASS_NAME 0
# endif
#endif

#if OGLPLUS_NO_ENUM_VALUE_NAMES
#ifdef OGLPLUS_ERROR_INFO_NO_BIND_TARGET
#undef OGLPLUS_ERROR_INFO_NO_BIND_TARGET
#endif
#define OGLPLUS_ERROR_INFO_NO_BIND_TARGET 1
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorBindTarget attribute of ErrorInfo
/**
 *  @see ErrorBindTarget()
 *
 *  By default this option is set to 0, i.e. ErrorBindTarget is enabled,
 *  unless #OGLPLUS_NO_ENUM_VALUE_NAMES is set to a non-zero value,
 *  in which case ErrorBindTarget is disabled and returns an empty string.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_BIND_TARGET
#else
# ifndef OGLPLUS_ERROR_INFO_NO_BIND_TARGET
#  define OGLPLUS_ERROR_INFO_NO_BIND_TARGET 0
# endif
#endif

#if OGLPLUS_NO_OBJECT_DESCS
#ifdef OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
#undef OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
#endif
#define OGLPLUS_ERROR_INFO_NO_OBJECT_DESC 1
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the ErrorObjectDescription attribute of ErrorInfo
/**
 *  @see ErrorObjectDescription()
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. ErrorObjectDescription is enabled, when not in low-profile and disabled
 *  otherwise and returns an empty string.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
#else
# ifndef OGLPLUS_ERROR_INFO_NO_OBJECT_DESC
#  define OGLPLUS_ERROR_INFO_NO_OBJECT_DESC OGLPLUS_LOW_PROFILE
# endif
#endif


#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the PropagationInfo function in Error
/**
 *  @see Error::PropagationInfo()
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. Error::PropagationInfo() is enabled, when not in low-profile
 *   and disabled otherwise and returns an empty list.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_NO_PROPAGATION_INFO
#else
# ifndef OGLPLUS_ERROR_NO_PROPAGATION_INFO
#  define OGLPLUS_ERROR_NO_PROPAGATION_INFO OGLPLUS_LOW_PROFILE
# endif
#endif

#if OGLPLUS_DOCUMENTATION_ONLY
/// Compile-time switch disabling the Properties in Error
/**
 *  @see Error::Properties()
 *
 *  By default this option is set to the same value as #OGLPLUS_LOW_PROFILE,
 *  i.e. Error::Properties() is enabled, when not in low-profile
 *   and disabled otherwise and returns an empty map.
 *
 *  @ingroup compile_time_config
 */
#define OGLPLUS_ERROR_NO_PROPERTIES
#else
# ifndef OGLPLUS_ERROR_NO_PROPERTIES
#  define OGLPLUS_ERROR_NO_PROPERTIES OGLPLUS_LOW_PROFILE
# endif
#endif


#include <oglplus/auxiliary/enum_class.hpp>

#endif // include guard
