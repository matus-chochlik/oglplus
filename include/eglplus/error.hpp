/**
 *  @file eglplus/error.hpp
 *  @brief Declaration of EGLplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_ERROR_1305290957_HPP
#define EGLPLUS_ERROR_1305290957_HPP

#include <eglplus/config.hpp>
#include <stdexcept>
#include <cassert>
#include <list>
#include <map>

#if EGLPLUS_CUSTOM_ERROR_HANDLING
#include <functional>
#endif

// Define a macro that initializes the _eglsym member of ErrorInfo
#if EGLPLUS_ERROR_INFO_NO_EGL_SYMBOL
#define EGLPLUS_ERROR_INFO_INIT_EGLSYM(SYMBOL)
#else
#define EGLPLUS_ERROR_INFO_INIT_EGLSYM(SYMBOL) , SYMBOL
#endif

// Define a macro that initializes the _file member of ErrorInfo
#if EGLPLUS_ERROR_INFO_NO_FILE
#define EGLPLUS_ERROR_INFO_INIT_FILE(FILEPATH)
#else
#define EGLPLUS_ERROR_INFO_INIT_FILE(FILEPATH) , FILEPATH
#endif

// Define a macro that initializes the _func member of ErrorInfo
#if EGLPLUS_ERROR_INFO_NO_FUNC
#define EGLPLUS_ERROR_INFO_INIT_FUNC(FUNC)
#else
#define EGLPLUS_ERROR_INFO_INIT_FUNC(FUNC) , FUNC
#endif

// Define a macro that initializes the _line member of ErrorInfo
#if EGLPLUS_ERROR_INFO_NO_LINE
#define EGLPLUS_ERROR_INFO_INIT_LINE(LINE)
#else
#define EGLPLUS_ERROR_INFO_INIT_LINE(LINE) , LINE
#endif

// Define a macro that initializes the _cls_name member of ErrorInfo
#if EGLPLUS_ERROR_INFO_NO_CLASS_NAME
#define EGLPLUS_ERROR_INFO_INIT_CLS_NAME(NAME)
#else
#define EGLPLUS_ERROR_INFO_INIT_CLS_NAME(NAME) , NAME
#endif


#define EGLPLUS_ERROR_INFO(CONTEXT) \
eglplus::ErrorInfo(\
	sizeof(decltype(&egl ## CONTEXT)) \
	EGLPLUS_ERROR_INFO_INIT_EGLSYM(#CONTEXT) \
	EGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	EGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	EGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	EGLPLUS_ERROR_INFO_INIT_CLS_NAME("") \
)

#define EGLPLUS_OBJECT_ERROR_INFO(LIB, CONTEXT, CLASS, NAME) \
eglplus::ErrorInfo(\
	sizeof(decltype(&LIB ## CONTEXT)) \
	EGLPLUS_ERROR_INFO_INIT_EGLSYM(#CONTEXT) \
	EGLPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	EGLPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	EGLPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	EGLPLUS_ERROR_INFO_INIT_CLS_NAME(#CLASS) \
)

namespace eglplus {

/** @defgroup error_handling Error handling
 *
 *  The exception classes listed below provide information about errors
 *  that occur during the excecution of the EGL function calls in the
 *  @EGLplus wrappers.
 */

/// Basic information about exception's throw site and propagation trace points
/**
 *  @see ErrorEGLSymbol
 *  @see ErrorFunc
 *  @see ErrorFile
 *  @see ErrorLine
 *  @see ErrorObjectDescription
 *
 *  @ingroup error_handling
 */
struct ErrorInfo
{
	// the data members of this structure are internal
	// implementation details which are subject to change
	// without any prior notice. Do not use directly.

	const size_t _dummy;

#if !EGLPLUS_ERROR_INFO_NO_EGL_SYMBOL
	const char* _eglsym;
#endif

#if !EGLPLUS_ERROR_INFO_NO_FILE
	const char* _file;
#endif

#if !EGLPLUS_ERROR_INFO_NO_FUNC
	const char* _func;
#endif

#if !EGLPLUS_ERROR_INFO_NO_LINE
	const unsigned _line;
#endif

#if !EGLPLUS_ERROR_INFO_NO_CLASS_NAME
	const char* _cls_name;
#endif

	inline ErrorInfo(
		const size_t dummy
#if !EGLPLUS_ERROR_INFO_NO_EGL_SYMBOL
		, const char* eglsym
#endif

#if !EGLPLUS_ERROR_INFO_NO_FILE
		, const char* file
#endif

#if !EGLPLUS_ERROR_INFO_NO_FUNC
		, const char* func
#endif

#if !EGLPLUS_ERROR_INFO_NO_LINE
		, const unsigned line
#endif

#if !EGLPLUS_ERROR_INFO_NO_CLASS_NAME
		, const char* cls_name
#endif

	): _dummy(dummy)

#if !EGLPLUS_ERROR_INFO_NO_EGL_SYMBOL
	 , _eglsym(eglsym)
#endif

#if !EGLPLUS_ERROR_INFO_NO_FILE
	 , _file(file)
#endif

#if !EGLPLUS_ERROR_INFO_NO_FUNC
	 , _func(func)
#endif

#if !EGLPLUS_ERROR_INFO_NO_LINE
	 , _line(line)
#endif

#if !EGLPLUS_ERROR_INFO_NO_CLASS_NAME
	 , _cls_name(cls_name)
#endif
	{ }
};

/// Returns the name of the symbol or constant related to the error
/** This function returns the name of the failed EGL function
 *  without the egl prefix in case of a function error or the name
 *  of the EGL constant (usually a implementation-dependent) limit
 *  which are related to the error.
 *
 *  The result of this function is also influenced by the
 *  #EGLPLUS_ERROR_INFO_NO_EGL_SYMBOL preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorFunc()
 *  @see ErrorFile()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorEGLSymbol(const ErrorInfo& info)
{
#if !EGLPLUS_ERROR_INFO_NO_EGL_SYMBOL
	return info._eglsym;
#else
	return "";
#endif
}

/// Returns the path of the source file where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #EGLPLUS_ERROR_INFO_NO_FILE preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorEGLSymbol()
 *  @see ErrorFunc()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorFile(const ErrorInfo& info)
{
#if !EGLPLUS_ERROR_INFO_NO_FILE
	return info._file;
#else
	EGLPLUS_FAKE_USE(info);
	return "";
#endif
}

/// Returns the name of the function where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #EGLPLUS_ERROR_INFO_NO_FUNC preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorEGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorLine()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorFunc(const ErrorInfo& info)
{
#if !EGLPLUS_ERROR_INFO_NO_FUNC
	return info._func;
#else
	EGLPLUS_FAKE_USE(info);
	return "";
#endif
}

/// Returns the line in the source file where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #EGLPLUS_ERROR_INFO_NO_LINE preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns zero.
 *
 *  @see ErrorInfo
 *  @see ErrorEGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorFunc()
 *  @see ErrorClassName()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline unsigned ErrorLine(const ErrorInfo& info)
{
#if !EGLPLUS_ERROR_INFO_NO_LINE
	return info._line;
#else
	EGLPLUS_FAKE_USE(info);
	return 0;
#endif
}

/// Returns the name of the class of the object where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #EGLPLUS_ERROR_INFO_NO_CLASS_NAME preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns the string "UnknownClass".
 *
 *  @see ErrorInfo
 *  @see ErrorEGLSymbol()
 *  @see ErrorFile()
 *  @see ErrorFunc()
 *  @see ErrorLine()
 *  @see ErrorBindTarget()
 *  @see ErrorObjectDescription()
 *
 *  @ingroup error_handling
 */
inline const char* ErrorClassName(const ErrorInfo& info)
{
#if !EGLPLUS_ERROR_INFO_NO_CLASS_NAME
	return (info._cls_name && *info._cls_name) ?
		info._cls_name :
		"UnknownClass";
#else
	EGLPLUS_FAKE_USE(info);
	return "UnknownClass";
#endif
}


/// Exception class for general EGL errors
/** Instances of this exception class are throws whenever an error is detected
 *  during the execution of EGL API calls in the @EGLplus code. There are several
 *  other classes derived for more specific error types, like EGL shading language
 *  compilation and linking errors, out-of-memory errors, etc.
 *  This class is derived from the standard runtime_error exception and thus
 *  the basic error message can be obtained by calling its @c what() member function.
 *
 *  @ingroup error_handling
 */
class Error
 : public std::runtime_error
{
public:
	/// List of ErrorInfo objects marking exception trace points
	typedef std::list<ErrorInfo> PropagationInfoList;
private:
	EGLint _code;
	ErrorInfo _info;

#if !EGLPLUS_ERROR_NO_PROPAGATION_INFO
	PropagationInfoList  _propagation;
#endif
	bool _assertion;
public:
	Error(
		EGLint code,
		const char* desc,
		const ErrorInfo& info,
		bool assertion = false
	): std::runtime_error(desc)
	 , _code(code)
	 , _info(info)
	 , _assertion(assertion)
	{ }

	inline ~Error(void) throw()
	{ }

	/// Returns the EGL error code
	/** This is basically the value of error code returned by the eglGetError
	 *  functions.
	 *
	 *  @see ThrowInfo
	 *  @see File
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	EGLint Code(void) const
	{
		return _code;
	}

	/// Returns information about the throw site of the exception
	/**
	 *  @see EGLSymbol
	 *  @see Code
	 *  @see File
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const ErrorInfo& ThrowInfo(void) const
	{
		return _info;
	}

	/// Returns the name of the symbol or constant related to the error
	/** This function returns the name of the failed EGL function
	 *  without the egl prefix which is related to the error.
	 *
	 *  @see ThrowInfo
	 *  @see Code
	 *  @see Func
	 *  @see File
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* EGLSymbol(void) const
	{
		return ::eglplus::ErrorEGLSymbol(_info);
	}

	/// Returns the path of the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see EGLSymbol
	 *  @see Code
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* File(void) const
	{
		return ::eglplus::ErrorFile(_info);
	}

	/// Returns the name of the function where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see EGLSymbol
	 *  @see Code
	 *  @see File
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* Func(void) const
	{
		return ::eglplus::ErrorFunc(_info);
	}

	/// Returns the line in the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see EGLSymbol
	 *  @see Code
	 *  @see File
	 *  @see Func
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	unsigned Line(void) const
	{
		return ::eglplus::ErrorLine(_info);
	}

	/// Returns the class name of the object that caused the exception
	const char* ClassName(void) const
	{
		return ::eglplus::ErrorClassName(_info);
	}

#if EGLPLUS_DOCUMENTATION_ONLY || EGLPLUS_ERROR_NO_PROPAGATION_INFO
	/// Returns a list of ErrorInfo objects marking exception trace points
	/**
	 *  @see #EGLPLUS_ERROR_NO_PROPAGATION_INFO
	 */
	PropagationInfoList PropagationInfo(void) const
	{
		return PropagationInfoList();
	}
#else
	const PropagationInfoList& PropagationInfo(void) const
	{
		return _propagation;
	}
#endif

	void Trace(const ErrorInfo& info)
	{
#if !EGLPLUS_ERROR_NO_PROPAGATION_INFO
		_propagation.push_back(info);
#else
		EGLPLUS_FAKE_USE(info);
#endif
		throw;
	}

	void Cleanup(void) const
	{
	}
};

/// Exception class for out-of-memory EGL errors
/** Out-of-memory is a very serious error and applications generally should not
 *  try to recover from such errors, but terminate gracefully if possible.
 *
 *  @ingroup error_handling
 */
class OutOfMemory
 : public Error
{
public:
	OutOfMemory(EGLint code, const char* desc, const ErrorInfo& info)
	 : Error(code, desc, info, true)
	{ }
};

#if EGLPLUS_DOCUMENTATION_ONLY || EGLPLUS_CUSTOM_ERROR_HANDLING

/// Structure containing all error-related data; Used in custom error handlers
/**
 *  Available only if the #EGLPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
struct ErrorData
{
private:
	EGLint _error_code;
	const char* _message;
	ErrorInfo _info;
	bool _assertion;
	bool _fatal_error;
	bool _build_error;
	bool _limit_error;
public:
	/// The EGL error code
	inline EGLint ErrorCode(void) const
	{
		return _error_code;
	}

	/// The error message
	/** The returned pointer should not be used when its ErrorData instance
	 *  goes out of scope. If this is necessary the string should be copied.
	 */
	inline const char* Message(void) const
	{
		return _message;
	}

	/// Additional error info
	inline const ErrorInfo& Info(void) const
	{
		return _info;
	}

	/// Indicates that an assertion has failed
	inline bool Assertion(void) const
	{
		return _assertion;
	}

	/// Indicates a fatal (very severe) error like (out of memory)
	inline bool FatalError(void) const
	{
		return _fatal_error;
	}

	/// Indicates a build error
	inline bool BuildError(void) const
	{
		return _build_error;
	}

	inline ErrorData(
		EGLint error_code,
		const char* message,
		const ErrorInfo& info,
		bool assertion,
		bool fatal_error,
		bool build_error,
		bool limit_error
	): _error_code(error_code)
	 , _message(message)
	 , _info(info)
	 , _assertion(assertion)
	 , _fatal_error(fatal_error)
	 , _build_error(build_error)
	 , _limit_error(limit_error)
	{ }
};

/// Type of installable custom error handler functor
/**
 *  Available only if the #EGLPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
typedef std::function<bool (const ErrorData&)> ErrorHandlerFunc;

namespace aux {

bool _has_error_handler(void);
ErrorHandlerFunc& _get_error_handler(void);

} // namespace aux

/// A RAII class installing a temporary custom error handler
/**
 *  Available only if the #EGLPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
class LocalErrorHandler
{
private:
	size_t _installed;
public:
	/// Installs the specified error @p handler
	LocalErrorHandler(ErrorHandlerFunc handler);

	/// This class is non-copyable
	LocalErrorHandler(const LocalErrorHandler&) = delete;

	/// Uninstalls the previously installed handler
	~LocalErrorHandler(void);
};

#endif // EGLPLUS_CUSTOM_ERROR_HANDLING

void HandleError(
	EGLint code,
	const char* msg,
	const ErrorInfo& info,
	bool assertion
);

void HandleEGLError(EGLint code, const ErrorInfo& info, bool assertion);

#if EGLPLUS_DOCUMENTATION_ONLY
/// Macro checking and possibly handling run-time errors in previous call to EGL
/** This macro is called immediatelly after calls to EGL functions
 *  that may fail due to invalid values of run-time parameters.
 */
#define EGLPLUS_CHECK(PARAM)
#endif

#ifndef EGLPLUS_CHECK
#define EGLPLUS_CHECK(PARAM) { \
	EGLint error_code = ::eglGetError(); \
	if(error_code != EGL_SUCCESS) HandleEGLError(error_code, PARAM, false); \
}
#endif

#if EGLPLUS_DOCUMENTATION_ONLY
/// Macro asserting that no errors occured in prevous call to EGL
/** This macro is called immediatelly after calls to EGL functions
 *  that "should not" fail and if they do fail it indicates
 *  a program logic error that is not dependent on run-time parameters.
 */
#define EGLPLUS_VERIFY(PARAM)
#endif

#ifndef EGLPLUS_VERIFY
#if !OGPLUS_LOW_PROFILE
#define EGLPLUS_VERIFY(PARAM) { \
	EGLint error_code = ::eglGetError(); \
	if(error_code != EGL_SUCCESS) HandleEGLError(error_code, PARAM, true); \
}
#else
#define EGLPLUS_VERIFY(PARAM)
#endif
#endif

#define EGLPLUS_IGNORE(PARAM) ::eglGetError();

} // namespace eglplus

#if !EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)
#include <eglplus/error.ipp>
#endif

#endif // include guard
