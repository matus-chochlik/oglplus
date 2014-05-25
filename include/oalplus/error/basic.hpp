/**
 *  @file oalplus/error/basic.hpp
 *  @brief Declaration of basic OALplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ERROR_BASIC_1107121317_HPP
#define OALPLUS_ERROR_BASIC_1107121317_HPP

#include <oalplus/config.hpp>
#include <oalplus/enumerations.hpp>
#include <oalplus/string/def.hpp>
#include <oalplus/string/ref.hpp>
#include <stdexcept>
#include <cassert>

namespace oalplus {

/** @defgroup error_handling Error handling
 *
 *  The exception classes listed below provide information about errors
 *  that occur during the excecution of the OpenAL function calls in the
 *  @OALplus wrappers.
 */

/// Exception class for general OpenAL errors
/** Instances of this exception class are thrown whenever an error is detected
 *  during the execution of OpenAL API calls in the @OALplus code. There are several
 *  other classes derived for more specific error types, like AL shading language
 *  compilation and linking errors, limit errors , etc.
 *  This class is derived from the standard runtime_error exception and thus
 *  the basic error message can be obtained by calling its @c what() member function.
 *
 *  @ingroup error_handling
 */
class Error
 : public std::runtime_error
{
private:
	ALenum _code;
#if !OALPLUS_ERROR_INFO_NO_FILE
	const char* _file;
#endif
#if !OALPLUS_ERROR_INFO_NO_FUNC
	const char* _func;
#endif
#if !OALPLUS_ERROR_INFO_NO_LINE
	unsigned _line;
#endif
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
	const char* _allib_name;
	const char* _alfunc_name;
	const char* _enumpar_name;
	ALenum _enumpar;
	ALint _index;
#endif

public:
	static const char* Message(ALenum);

	Error(const char* message);

	~Error(void) throw() { }

	Error& NoInfo(void) { return *this; }

	Error& Code(ALenum code)
	{
		_code = code;
		return *this;
	}

	/// Returns the AL error code related to the error
	ALenum Code(void) const { return _code; }

	Error& SourceFile(const char* file)
	{
#if !OALPLUS_ERROR_INFO_NO_FILE
		_file = file;
#endif
		(void)file;
		return *this;
	}

	/// Returns the name of the source file where the error occured
	/**
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_FILE preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns nullptr.
	 */
	const char* SourceFile(void) const;

	Error& SourceFunc(const char* func)
	{
#if !OALPLUS_ERROR_INFO_NO_FUNC
		_func = func;
#endif
		(void)func;
		return *this;
	}

	/// Returns the name of the function where the error occured
	/**
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_FUNC preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns nullptr.
	 */
	const char* SourceFunc(void) const;

	Error& SourceLine(unsigned line)
	{
#if !OALPLUS_ERROR_INFO_NO_LINE
		_line = line;
#endif
		(void)line;
		return *this;
	}

	/// Returns the line of the source file where the error occured
	/**
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_LINE preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns zero.
	 */
	unsigned SourceLine(void) const;

	Error& ALLibName(const char* lib_name)
	{
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
		_allib_name = lib_name;
#endif
		(void)lib_name;
		return *this;
	}

	/// Returns the name of the AL function related to the error
	/** This function returns the name of the library 'al', 'alc', 'alur'
	 *  of the failed OpenAL function which is related to the error.
	 *
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_AL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns nullptr.
	 */
	const char* ALLibName(void) const;

	Error& ALFuncName(const char* func_name)
	{
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
		_alfunc_name = func_name;
#endif
		(void)func_name;
		return *this;
	}

	/// Returns the name of the AL function related to the error
	/** This function returns the name of the failed OpenAL function
	 *  (without the @c al prefix) which is related to the error.
	 *
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_AL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns nullptr.
	 */
	const char* ALFuncName(void) const;

	template <typename Enum_>
	Error& EnumParam(Enum_ param)
	{
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
		_enumpar = ALenum(param);
		_enumpar_name = EnumValueName(param).c_str();
#endif
		(void)param;
		return *this;
	}

	Error& EnumParam(ALenum param, const char* param_name)
	{
#if !OALPLUS_ERROR_INFO_NO_AL_SYMBOL
		_enumpar = param;
		_enumpar_name = param_name;
#endif
		(void)param;
		(void)param_name;
		return *this;
	}

	/// Returns the value of the enumeration parameter related to the error
	/** This function returns the value of the main enumeration
	 *  parameter passed to the failed OpenAL function
	 *
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_AL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns zero.
	 */
	ALenum EnumParam(void) const;

	/// Returns the name of the enumeration parameter related to the error
	/** This function returns the name of the main enumeration
	 *  parameter passed to the failed OpenAL function
	 *
	 *  The result of this function is also influenced by the
	 *  #OALPLUS_ERROR_INFO_NO_AL_SYMBOL preprocessor configuration option.
	 *  If set to zero this function behaves as described above, otherwise it
	 *  returns nullptr.
	 */
	const char* EnumParamName(void) const;

	/// Returns the bind target
	virtual ALenum BindTarget(void) const { return ALenum(0); }

	/// Returns the bind target name
	virtual const char* TargetName(void) const { return nullptr; }

	/// Returns the object type
	/** If the error is related to a AL object, then an object
	 *  type enumeration value is returned. Otherwise the result is zero.
	 */
	virtual ALenum ObjectType(void) const { return ALenum(0); }

	/// Returns the object type name
	/** If the error is related to a AL object, then a C string
	 *  storing object type name is returned. Otherwise the result
	 *  is nullptr.
	 */
	virtual const char* ObjectTypeName(void) const { return nullptr; }

	/// Returns the object instance AL name
	/** If the error is related to a AL object, then the numeric
	 *  AL name of the object is returned. Otherwise the result
	 *  is a negative integer.
	 */
	virtual ALint ObjectName(void) const { return -1; }

	/// Returns the subject type
	/** If the error is related to a pair of AL objects, then
	 *  an object type enumeration value is returned. Otherwise
	 *  the result is zero.
	 */
	virtual ALenum SubjectType(void) const { return ALenum(0); }

	/// Returns the subject class name
	/** If the error is related a pair of AL objects, then a C string
	 *  storing secondary object type name is returned. Otherwise the result
	 *  is nullptr.
	 */
	virtual const char* SubjectTypeName(void) const { return nullptr; }

	/// Returns the subject AL name
	/** If the error is related to a pair of AL objects, then
	 *  the numeric AL name of the secondary object is returned.
	 *  Otherwise the result is a negative integer.
	 */
	virtual ALint SubjectName(void) const { return -1; }
};

/// Generic error handling function
template <typename ErrorType>
inline void HandleError(ErrorType& error)
{
	throw error;
}

// Macro for generic error handling
#define OALPLUS_HANDLE_ERROR_IF(\
	CONDITION,\
	ERROR_CODE,\
	MESSAGE,\
	ERROR,\
	ERROR_INFO\
)\
{\
	ALenum error_code = ERROR_CODE;\
	if(CONDITION)\
	{\
		ERROR error(MESSAGE);\
		(void)error\
			.ERROR_INFO\
			.SourceFile(__FILE__)\
			.SourceFunc(__FUNCTION__)\
			.SourceLine(__LINE__)\
			.Code(error_code);\
		HandleError(error);\
	}\
}

#define OALPLUS_ALFUNC_CHECK(ALLIB, FUNC_NAME, ERROR, ERROR_INFO)\
	OALPLUS_HANDLE_ERROR_IF(\
		error_code != AL_NO_ERROR,\
		ALLIB ## GetError(),\
		ERROR::Message(error_code),\
		ERROR,\
		ERROR_INFO.\
		ALLibName(#ALLIB).\
		ALFuncName(FUNC_NAME)\
	)

#define OALPLUS_CHECK(ALLIB, ALFUNC, ERROR, ERROR_INFO) \
	OALPLUS_ALFUNC_CHECK(ALLIB, #ALFUNC, ERROR, ERROR_INFO)

#define OALPLUS_CHECK_SIMPLE(ALLIB, ALFUNC) \
	OALPLUS_CHECK(ALLIB, ALFUNC, Error, NoInfo())

#if !OGPLUS_LOW_PROFILE
#define OALPLUS_VERIFY(ALLIB, ALFUNC, ERROR, ERROR_INFO) \
	OALPLUS_CHECK(ALLIB, ALFUNS, ERROR, ERROR_INFO)
#else
#define OALPLUS_VERIFY(ALLIB, ALFUNC, ERROR, ERROR_INFO)
#endif

#define OALPLUS_VERIFY_SIMPLE(ALLIB, ALFUNC) \
	OALPLUS_CHECK(ALLIB, ALFUNC, Error, NoInfo())

#define OALPLUS_IGNORE(ALLIB, PARAM) ::ALLIB ## GetError();

} // namespace oalplus

#if !OALPLUS_LINK_LIBRARY || defined(OALPLUS_IMPLEMENTING_LIBRARY)
#include <oalplus/error/basic.ipp>
#endif

#endif // include guard
