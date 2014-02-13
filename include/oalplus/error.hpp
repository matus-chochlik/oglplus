/**
 *  @file oalplus/error.hpp
 *  @brief Declaration of OALplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ERROR_1303201611_HPP
#define OALPLUS_ERROR_1303201611_HPP

#include <oalplus/config.hpp>
#include <stdexcept>
#include <cassert>
#include <list>
#include <map>

#if OALPLUS_CUSTOM_ERROR_HANDLING
#include <functional>
#endif

// Define a macro that initializes the _alsym member of ErrorInfo
#if OALPLUS_ERROR_INFO_NO_AL_SYMBOL
#define OALPLUS_ERROR_INFO_INIT_ALSYM(SYMBOL)
#else
#define OALPLUS_ERROR_INFO_INIT_ALSYM(SYMBOL) , SYMBOL
#endif

// Define a macro that initializes the _file member of ErrorInfo
#if OALPLUS_ERROR_INFO_NO_FILE
#define OALPLUS_ERROR_INFO_INIT_FILE(FILEPATH)
#else
#define OALPLUS_ERROR_INFO_INIT_FILE(FILEPATH) , FILEPATH
#endif

// Define a macro that initializes the _func member of ErrorInfo
#if OALPLUS_ERROR_INFO_NO_FUNC
#define OALPLUS_ERROR_INFO_INIT_FUNC(FUNC)
#else
#define OALPLUS_ERROR_INFO_INIT_FUNC(FUNC) , FUNC
#endif

// Define a macro that initializes the _line member of ErrorInfo
#if OALPLUS_ERROR_INFO_NO_LINE
#define OALPLUS_ERROR_INFO_INIT_LINE(LINE)
#else
#define OALPLUS_ERROR_INFO_INIT_LINE(LINE) , LINE
#endif

// Define a macro that initializes the _cls_name member of ErrorInfo
#if OALPLUS_ERROR_INFO_NO_CLASS_NAME
#define OALPLUS_ERROR_INFO_INIT_CLS_NAME(NAME)
#else
#define OALPLUS_ERROR_INFO_INIT_CLS_NAME(NAME) , NAME
#endif


#define OALPLUS_ERROR_INFO(LIB, CONTEXT) \
oalplus::ErrorInfo(\
	sizeof(decltype(&LIB ## CONTEXT)) \
	OALPLUS_ERROR_INFO_INIT_ALSYM(#CONTEXT) \
	OALPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OALPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OALPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OALPLUS_ERROR_INFO_INIT_CLS_NAME("") \
)

#define OALPLUS_OBJECT_ERROR_INFO(LIB, CONTEXT, CLASS, NAME) \
oalplus::ErrorInfo(\
	sizeof(decltype(&LIB ## CONTEXT)) \
	OALPLUS_ERROR_INFO_INIT_ALSYM(#CONTEXT) \
	OALPLUS_ERROR_INFO_INIT_FILE(__FILE__) \
	OALPLUS_ERROR_INFO_INIT_FUNC(__FUNCTION__) \
	OALPLUS_ERROR_INFO_INIT_LINE(__LINE__) \
	OALPLUS_ERROR_INFO_INIT_CLS_NAME(#CLASS) \
)

namespace oalplus {

/** @defgroup error_handling Error handling
 *
 *  The exception classes listed below provide information about errors
 *  that occur during the excecution of the OpenAL function calls in the
 *  @OALplus wrappers.
 */

/// Basic information about exception's throw site and propagation trace points
/**
 *  @see ErrorALSymbol
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

#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
	const char* _alsym;
#endif

#if !OALPLUS_ERROR_INFO_NO_FILE
	const char* _file;
#endif

#if !OALPLUS_ERROR_INFO_NO_FUNC
	const char* _func;
#endif

#if !OALPLUS_ERROR_INFO_NO_LINE
	const unsigned _line;
#endif

#if !OALPLUS_ERROR_INFO_NO_CLASS_NAME
	const char* _cls_name;
#endif

	inline ErrorInfo(
		const size_t dummy
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
		, const char* alsym
#endif

#if !OALPLUS_ERROR_INFO_NO_FILE
		, const char* file
#endif

#if !OALPLUS_ERROR_INFO_NO_FUNC
		, const char* func
#endif

#if !OALPLUS_ERROR_INFO_NO_LINE
		, const unsigned line
#endif

#if !OALPLUS_ERROR_INFO_NO_CLASS_NAME
		, const char* cls_name
#endif

	): _dummy(dummy)

#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
	 , _alsym(alsym)
#endif

#if !OALPLUS_ERROR_INFO_NO_FILE
	 , _file(file)
#endif

#if !OALPLUS_ERROR_INFO_NO_FUNC
	 , _func(func)
#endif

#if !OALPLUS_ERROR_INFO_NO_LINE
	 , _line(line)
#endif

#if !OALPLUS_ERROR_INFO_NO_CLASS_NAME
	 , _cls_name(cls_name)
#endif
	{ }
};

/// Returns the name of the symbol or constant related to the error
/** This function returns the name of the failed OpenAL function
 *  without the al prefix in case of a function error or the name
 *  of the OpenAL constant (usually a implementation-dependent) limit
 *  which are related to the error.
 *
 *  The result of this function is also influenced by the
 *  #OALPLUS_ERROR_INFO_NO_AL_SYMBOL preprocessor configuration option.
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
inline const char* ErrorALSymbol(const ErrorInfo& info)
{
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
	return info._alsym;
#else
	return "";
#endif
}

/// Returns the path of the source file where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OALPLUS_ERROR_INFO_NO_FILE preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorALSymbol()
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
#if !OALPLUS_ERROR_INFO_NO_FILE
	return info._file;
#else
	OALPLUS_FAKE_USE(info);
	return "";
#endif
}

/// Returns the name of the function where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OALPLUS_ERROR_INFO_NO_FUNC preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns an empty C string.
 *
 *  @see ErrorInfo
 *  @see ErrorALSymbol()
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
#if !OALPLUS_ERROR_INFO_NO_FUNC
	return info._func;
#else
	OALPLUS_FAKE_USE(info);
	return "";
#endif
}

/// Returns the line in the source file where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OALPLUS_ERROR_INFO_NO_LINE preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns zero.
 *
 *  @see ErrorInfo
 *  @see ErrorALSymbol()
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
#if !OALPLUS_ERROR_INFO_NO_LINE
	return info._line;
#else
	OALPLUS_FAKE_USE(info);
	return 0;
#endif
}

/// Returns the name of the class of the object where the exception originated
/**
 *  The result of this function is also influenced by the
 *  #OALPLUS_ERROR_INFO_NO_CLASS_NAME preprocessor configuration option.
 *  If set to zero this function behaves as described above, otherwise it
 *  returns the string "UnknownClass".
 *
 *  @see ErrorInfo
 *  @see ErrorALSymbol()
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
#if !OALPLUS_ERROR_INFO_NO_CLASS_NAME
	return (info._cls_name && *info._cls_name) ?
		info._cls_name :
		"UnknownClass";
#else
	OALPLUS_FAKE_USE(info);
	return "UnknownClass";
#endif
}


/// Exception class for general OpenAL errors
/** Instances of this exception class are throws whenever an error is detected
 *  during the execution of OpenAL API calls in the @OALplus code. There are several
 *  other classes derived for more specific error types like out-of-memory errors, etc.
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
	ALenum _code;
	ErrorInfo _info;

#if !OALPLUS_ERROR_NO_PROPAGATION_INFO
	PropagationInfoList  _propagation;
#endif
	bool _assertion;
public:
	Error(
		ALenum code,
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

	/// Returns the OpenAL error code
	/** This is basically the value of error code returned by the alGetError
	 *  functions.
	 *
	 *  @see ThrowInfo
	 *  @see File
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	ALenum Code(void) const
	{
		return _code;
	}

	/// Returns information about the throw site of the exception
	/**
	 *  @see ALSymbol
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
	/** This function returns the name of the failed OpenAL function
	 *  without the al prefix which is related to the error.
	 *
	 *  @see ThrowInfo
	 *  @see Code
	 *  @see Func
	 *  @see File
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* ALSymbol(void) const
	{
		return ::oalplus::ErrorALSymbol(_info);
	}

	/// Returns the path of the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see ALSymbol
	 *  @see Code
	 *  @see Func
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* File(void) const
	{
		return ::oalplus::ErrorFile(_info);
	}

	/// Returns the name of the function where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see ALSymbol
	 *  @see Code
	 *  @see File
	 *  @see Line
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	const char* Func(void) const
	{
		return ::oalplus::ErrorFunc(_info);
	}

	/// Returns the line in the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see ALSymbol
	 *  @see Code
	 *  @see File
	 *  @see Func
	 *  @see ClassName
	 *  @see ObjectDescription
	 */
	unsigned Line(void) const
	{
		return ::oalplus::ErrorLine(_info);
	}

	/// Returns the class name of the object that caused the exception
	const char* ClassName(void) const
	{
		return ::oalplus::ErrorClassName(_info);
	}

#if OALPLUS_DOCUMENTATION_ONLY || OALPLUS_ERROR_NO_PROPAGATION_INFO
	/// Returns a list of ErrorInfo objects marking exception trace points
	/**
	 *  @see #OALPLUS_ERROR_NO_PROPAGATION_INFO
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
#if !OALPLUS_ERROR_NO_PROPAGATION_INFO
		_propagation.push_back(info);
#else
		OALPLUS_FAKE_USE(info);
#endif
		throw;
	}

	void Cleanup(void) const
	{
	}
};

/// Exception class for out-of-memory OpenAL errors
/** Out-of-memory is a very serious error and applications generally should not
 *  try to recover from such errors, but terminate gracefully if possible.
 *
 *  @ingroup error_handling
 */
class OutOfMemory
 : public Error
{
public:
	OutOfMemory(ALenum code, const char* desc, const ErrorInfo& info)
	 : Error(code, desc, info, true)
	{ }
};

#if OALPLUS_DOCUMENTATION_ONLY || OALPLUS_CUSTOM_ERROR_HANDLING

/// Structure containing all error-related data; Used in custom error handlers
/**
 *  Available only if the #OALPLUS_CUSTOM_ERROR_HANDLING compile-time switch
 *  is set to a nonzero value.
 *
 *  @ingroup error_handling
 */
struct ErrorData
{
private:
	ALenum _error_code;
	const char* _message;
	ErrorInfo _info;
	bool _assertion;
	bool _fatal_error;
	bool _build_error;
	bool _limit_error;
public:
	/// The OpenAL error code
	inline ALenum ErrorCode(void) const
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
		ALenum error_code,
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
 *  Available only if the #OALPLUS_CUSTOM_ERROR_HANDLING compile-time switch
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
 *  Available only if the #OALPLUS_CUSTOM_ERROR_HANDLING compile-time switch
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

#endif // OALPLUS_CUSTOM_ERROR_HANDLING

void HandleError(
	ALenum code,
	const ALchar* msg,
	const ErrorInfo& info,
	bool assertion
);

inline void HandleALError(ALenum code, const ErrorInfo& info, bool assertion)
{
	HandleError(code, ::alGetString(code), info, assertion);
}

inline void HandleALCError(ALenum code, const ErrorInfo& info, bool assertion)
{
	HandleError(code, ::alcGetString(nullptr, code), info, assertion);
}

void HandleALUTError(ALenum code, const ErrorInfo& info, bool assertion);

#if OALPLUS_DOCUMENTATION_ONLY
/// Macro checking and possibly handling run-time errors in previous call to AL
/** This macro is called immediatelly after calls to AL functions
 *  that may fail due to invalid values of run-time parameters.
 */
#define OALPLUS_CHECK(PARAM)
#endif

#ifndef OALPLUS_CHECK
#define OALPLUS_CHECK(PARAM) { \
	ALenum error_code = ::alGetError(); \
	if(error_code != AL_NO_ERROR) HandleALError(error_code, PARAM, false); \
}
#define OALPLUS_CHECK_ALC(PARAM,DEVICE) { \
	ALenum error_code = ::alcGetError(DEVICE); \
	if(error_code != ALC_NO_ERROR) HandleALCError(error_code, PARAM, false); \
}
#define OALPLUS_CHECK_ALUT(PARAM) { \
	ALenum error_code = ::alutGetError(); \
	if(error_code != AL_NO_ERROR) HandleALUTError(error_code, PARAM, false); \
}
#endif

#if OALPLUS_DOCUMENTATION_ONLY
/// Macro asserting that no errors occured in prevous call to AL
/** This macro is called immediatelly after calls to AL functions
 *  that "should not" fail and if they do fail it indicates
 *  a program logic error that is not dependent on run-time parameters.
 */
#define OALPLUS_VERIFY(PARAM)
#endif

#ifndef OALPLUS_VERIFY
#if !OGPLUS_LOW_PROFILE
#define OALPLUS_VERIFY(PARAM) { \
	ALenum error_code = ::alGetError(); \
	if(error_code != AL_NO_ERROR) HandleALError(error_code, PARAM, true); \
}
#define OALPLUS_VERIFY_ALC(PARAM,DEVICE) { \
	ALenum error_code = ::alcGetError(DEVICE); \
	if(error_code != ALC_NO_ERROR) HandleALCError(error_code, PARAM, true); \
}
#define OALPLUS_VERIFY_ALUT(PARAM) { \
	ALenum error_code = ::alutGetError(); \
	if(error_code != AL_NO_ERROR) HandleALUTError(error_code, PARAM, true); \
}
#else
#define OALPLUS_VERIFY(PARAM)
#define OALPLUS_VERIFY_ALC(PARAM,DEVICE)
#define OALPLUS_VERIFY_ALUT(PARAM)
#endif
#endif

#define OALPLUS_IGNORE(LIB,PARAM) ::alGetError();

} // namespace oalplus

#if !OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)
#include <oalplus/error.ipp>
#endif

#endif // include guard
