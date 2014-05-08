/**
 *  @file oglplus/error/basic.hpp
 *  @brief Declaration of basic OGLplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_BASIC_1107121317_HPP
#define OGLPLUS_ERROR_BASIC_1107121317_HPP

#include <oglplus/config.hpp>
#include <oglplus/enumerations.hpp>
#include <oglplus/string/def.hpp>
#include <stdexcept>
#include <cassert>
#include <map>

namespace oglplus {

/** @defgroup error_handling Error handling
 *
 *  The exception classes listed below provide information about errors
 *  that occur during the excecution of the OpenGL function calls in the
 *  @OGLplus wrappers.
 */

/// Exception class for general OpenGL errors
/** Instances of this exception class are thrown whenever an error is detected
 *  during the execution of OpenGL API calls in the @OGLplus code. There are several
 *  other classes derived for more specific error types, like GL shading language
 *  compilation and linking errors, limit errors , etc.
 *  This class is derived from the standard runtime_error exception and thus
 *  the basic error message can be obtained by calling its @c what() member function.
 *
 *  @ingroup error_handling
 */
class Error
 : public std::runtime_error
{
public:
	/// A map of properties attached to the exception
	typedef std::map<String, String> PropertyMap;
private:
	GLenum _code;
#if !OGLPLUS_ERROR_INFO_NO_FILE
	const char* _file;
#endif
#if !OGLPLUS_ERROR_INFO_NO_LINE
	unsigned _line;
#endif
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
	const char* _glfunc_name;
	const char* _enumpar_name;
	GLenum _enumpar;
	GLuint _index;
#endif

#if !OGLPLUS_ERROR_NO_PROPERTIES
	PropertyMap _properties;
#endif
public:
	static const char* Message(GLenum);

	Error(const char* message);

	Error& NoInfo(void) { return *this; }

	Error& Code(GLenum code)
	{
		_code = code;
		return *this;
	}

	/// Returns the GL error code related to the error
	GLenum Code(void) const { return _code; }

	Error& SourceFile(const char* file)
	{
#if !OGLPLUS_ERROR_INFO_NO_FILE
		_file = file;
#endif
		(void)file;
		return *this;
	}

	/// Returns the name of the source file where the error occured
	/**
	 *  The result of this function is also influenced by the
	 *  #OGLPLUS_ERROR_INFO_NO_FILE preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns an empty C string.
	 */
	const char* SourceFile(void) const;

	Error& SourceLine(unsigned line)
	{
#if !OGLPLUS_ERROR_INFO_NO_LINE
		_line = line;
#endif
		(void)line;
		return *this;
	}

	/// Returns the line of the source file where the error occured
	/**
	 *  The result of this function is also influenced by the
	 *  #OGLPLUS_ERROR_INFO_NO_LINE preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns zero.
	 */
	unsigned SourceLine(void) const;

	Error& GLFuncName(const char* func_name)
	{
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
		_glfunc_name = func_name;
#endif
		(void)func_name;
		return *this;
	}

	/// Returns the name of the GL function related to the error
	/** This function returns the name of the failed OpenGL function
	 *  (without the @c gl prefix) which is related to the error.
	 *
	 *  The result of this function is also influenced by the
	 *  #OGLPLUS_ERROR_INFO_NO_GL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns an empty C-string.
	 */
	const char* GLFuncName(void) const;

	template <typename Enum_>
	Error& EnumParam(Enum_ param)
	{
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
		_enumpar = GLenum(param);
		_enumpar_name = EnumValueName(param).c_str();
#endif
		(void)param;
		return *this;
	}

	Error& EnumParam(GLenum param, const char* param_name)
	{
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
		_enumpar = param;
		_enumpar_name = param_name;
#endif
		(void)param;
		(void)param_name;
		return *this;
	}

	/// Returns the value of the enumeration parameter related to the error
	/** This function returns the value of the main enumeration
	 *  parameter passed to the failed OpenGL function
	 *
	 *  The result of this function is also influenced by the
	 *  #OGLPLUS_ERROR_INFO_NO_GL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns zero.
	 */
	GLenum EnumParam(void) const;

	/// Returns the name of the enumeration parameter related to the error
	/** This function returns the name of the main enumeration
	 *  parameter passed to the failed OpenGL function
	 *
	 *  The result of this function is also influenced by the
	 *  #OGLPLUS_ERROR_INFO_NO_GL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns an empty C-string.
	 */
	const char* EnumParamName(void) const;

	Error& Index(GLuint index)
	{
#if !OGLPLUS_ERROR_INFO_NO_GL_SYMBOL
		_index = index;
#endif
		(void)index;
		return *this;
	}

	/// Returns the index parameter related to the error
	/** This function returns the value of the index
	 *  parameter passed to the failed OpenGL function
	 *
	 *  The result of this function is also influenced by the
	 *  #OGLPLUS_ERROR_INFO_NO_GL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns zero.
	 */
	GLuint Index(void) const;

#if OGLPLUS_DOCUMENTATION_ONLY || OGLPLUS_ERROR_NO_PROPERTIES
	/// Returns the properties of the exception
	/**
	 *  @see #OGLPLUS_ERROR_NO_PROPERTIES
	 */
	PropertyMap Properties(void) const
	{
		return PropertyMap();
	}

	Error& PropertyValue(const String&, const String&)
	{
		return *this;
	}
#else
	template <typename Key, typename Value>
	Error& PropertyValue(Key&& key, Value&& value)
	{
		_properties[std::forward<Key>(key)] =
			std::forward<Value>(value);
		return *this;
	}

	const PropertyMap& Properties(void) const
	{
		return _properties;
	}
#endif
	void Cleanup(void) const;
};

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
{
public:
	static const char* Message(void);

	MissingFunction(const char* message)
	 : Error(message)
	{ }
};

/// Generic error handling function
template <typename ErrorType>
inline void HandleError(ErrorType& error)
{
	throw error;
}

// Macro for generic error handling
#define OGLPLUS_HANDLE_ERROR_IF(\
	CONDITION,\
	ERROR_CODE,\
	ERROR,\
	MESSAGE,\
	ERROR_INFO\
)\
{\
	GLenum error_code = ERROR_CODE;\
	if(CONDITION)\
	{\
		ERROR error(MESSAGE);\
		(void)error\
			.ERROR_INFO\
			.SourceFile(__FILE__)\
			.SourceLine(__LINE__)\
			.Code(error_code);\
		HandleError(error);\
	}\
}

#define OGLPLUS_CHECK(GLFUNC, ERROR, ERROR_INFO) \
	OGLPLUS_HANDLE_ERROR_IF(\
		error_code != GL_NO_ERROR,\
		glGetError(),\
		ERROR,\
		ERROR::Message(error_code),\
		ERROR_INFO.GLFuncName(#GLFUNC)\
	)

#define OGLPLUS_CHECK_FUNC(GLFUNC) \
	OGLPLUS_CHECK(GLFUNC, Error, NoInfo())

#if !OGPLUS_LOW_PROFILE
#define OGLPLUS_VERIFY(GLFUNC, ERROR, ERROR_INFO) \
	OGLPLUS_CHECK(GLFUNS, ERROR, ERROR_INFO)
#else
#define OGLPLUS_VERIFY(PARAM)
#endif

#define OGLPLUS_VERIFY_FUNC(GLFUNC) \
	OGLPLUS_CHECK(GLFUNC, Error, NoInfo())

#define OGLPLUS_IGNORE(PARAM) ::glGetError();

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/error/basic.ipp>
#endif

#endif // include guard
