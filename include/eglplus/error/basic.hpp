/**
 *  @file eglplus/error/basic.hpp
 *  @brief Declaration of basic EGLplus' exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef EGLPLUS_ERROR_BASIC_1107121317_HPP
#define EGLPLUS_ERROR_BASIC_1107121317_HPP

#include <cassert>
#include <eglplus/config.hpp>
#include <eglplus/enumerations.hpp>
#include <eglplus/string.hpp>
#include <map>
#include <stdexcept>

namespace eglplus {

/** @defgroup error_handling Error handling
 *
 *  The exception classes listed below provide information about errors
 *  that occur during the excecution of the OpenGL function calls in the
 *  @EGLplus wrappers.
 */

/// Exception class for general OpenGL errors
/** Instances of this exception class are thrown whenever an error is detected
 *  during the execution of OpenGL API calls in the @EGLplus code. There are
 * several other classes derived for more specific error types, like EGL shading
 * language compilation and linking errors, limit errors , etc. This class is
 * derived from the standard runtime_error exception and thus the basic error
 * message can be obtained by calling its @c what() member function.
 *
 *  @ingroup error_handling
 */
class Error : public std::runtime_error {
private:
    EGLenum _code;
#if !EGLPLUS_ERROR_NO_FILE
    const char* _file;
#endif
#if !EGLPLUS_ERROR_NO_FUNC
    const char* _func;
#endif
#if !EGLPLUS_ERROR_NO_LINE
    unsigned _line;
#endif
#if !EGLPLUS_ERROR_NO_EGL_FUNC
    const char* _eglfunc_name;
#endif
#if !EGLPLUS_ERROR_NO_EGL_SYMBOL
    const char* _enumpar_name;
    EGLenum _enumpar;
#endif

public:
    static const char* Message(EGLenum);

    Error(const char* message);

    Error(const Error&) = default;
    Error(Error&&) = default;

    ~Error() noexcept {
    }

    Error& NoInfo() {
        return *this;
    }

    Error& Code(EGLenum code) {
        _code = code;
        return *this;
    }

    /// Returns the EGL error code related to the error
    EGLenum Code() const {
        return _code;
    }

    Error& SourceFile(const char* file) {
#if !EGLPLUS_ERROR_NO_FILE
        _file = file;
#endif
        EGLPLUS_FAKE_USE(file);
        return *this;
    }

    /// Returns the name of the source file where the error occured
    /**
     *  The result of this function is also influenced by the
     *  #EGLPLUS_ERROR_NO_FILE preprocessor configuration option.
     *  If set to zero this function behaves as described above, otherwise it
     *  returns nullptr.
     */
    const char* SourceFile() const;

    Error& SourceFunc(const char* func) {
#if !EGLPLUS_ERROR_NO_FUNC
        _func = func;
#endif
        EGLPLUS_FAKE_USE(func);
        return *this;
    }

    /// Returns the name of the function where the error occured
    /**
     *  The result of this function is also influenced by the
     *  #EGLPLUS_ERROR_NO_FUNC preprocessor configuration option.
     *  If set to zero this function behaves as described above, otherwise it
     *  returns nullptr.
     */
    const char* SourceFunc() const;

    Error& SourceLine(unsigned line) {
#if !EGLPLUS_ERROR_NO_LINE
        _line = line;
#endif
        EGLPLUS_FAKE_USE(line);
        return *this;
    }

    /// Returns the line of the source file where the error occured
    /**
     *  The result of this function is also influenced by the
     *  #EGLPLUS_ERROR_NO_LINE preprocessor configuration option.
     *  If set to zero this function behaves as described above, otherwise it
     *  returns zero.
     */
    unsigned SourceLine() const;

    Error& EGLFunc(const char* func_name) {
#if !EGLPLUS_ERROR_NO_EGL_FUNC
        _eglfunc_name = func_name;
#endif
        EGLPLUS_FAKE_USE(func_name);
        return *this;
    }

    /// Returns the name of the EGL function related to the error
    /** This function returns the name of the failed OpenGL function
     *  (without the @c egl prefix) which is related to the error.
     *
     *  The result of this function is also influenced by the
     *  #EGLPLUS_ERROR_NO_EGL_SYMBOL preprocessor configuration option.
     *  If set to zero this function behaves as described above, otherwise it
     *  returns nullptr.
     */
    const char* EGLFunc() const;

    template <typename Enum_>
    Error& EnumParam(Enum_ param) {
#if !EGLPLUS_ERROR_NO_EGL_SYMBOL
        _enumpar = EGLenum(param);
        _enumpar_name = EnumValueName(param).c_str();
#endif
        EGLPLUS_FAKE_USE(param);
        return *this;
    }

    Error& EnumParam(EGLenum param, const char* param_name) {
#if !EGLPLUS_ERROR_NO_EGL_SYMBOL
        _enumpar = param;
        _enumpar_name = param_name;
#endif
        EGLPLUS_FAKE_USE(param);
        EGLPLUS_FAKE_USE(param_name);
        return *this;
    }

    /// Returns the value of the enumeration parameter related to the error
    /** This function returns the value of the main enumeration
     *  parameter passed to the failed OpenGL function
     *
     *  The result of this function is also influenced by the
     *  #EGLPLUS_ERROR_NO_EGL_SYMBOL preprocessor configuration option.
     *  If set to zero this function behaves as described above, otherwise it
     *  returns zero.
     */
    EGLenum EnumParam() const;

    /// Returns the name of the enumeration parameter related to the error
    /** This function returns the name of the main enumeration
     *  parameter passed to the failed OpenGL function
     *
     *  The result of this function is also influenced by the
     *  #EGLPLUS_ERROR_NO_EGL_SYMBOL preprocessor configuration option.
     *  If set to zero this function behaves as described above, otherwise it
     *  returns nullptr.
     */
    const char* EnumParamName() const;
};

/// Generic error handling function
template <typename ErrorType>
inline void HandleError(ErrorType& error) {
    throw error;
}
// Macro for generic error handling
#define EGLPLUS_HANDLE_ERROR(ERROR_CODE, MESSAGE, ERROR, ERROR_INFO) \
    {                                                                \
        ERROR error(MESSAGE);                                        \
        EGLPLUS_FAKE_USE(error.ERROR_INFO.SourceFile(__FILE__)       \
                           .SourceFunc(__FUNCTION__)                 \
                           .SourceLine(__LINE__)                     \
                           .Code(error_code));                       \
        HandleError(error);                                          \
    }

// Macro for generic error handling
#define EGLPLUS_HANDLE_ERROR_IF(                                         \
  CONDITION, ERROR_CODE, MESSAGE, ERROR, ERROR_INFO)                     \
    {                                                                    \
        EGLenum error_code = ERROR_CODE;                                 \
        if(CONDITION) {                                                  \
            EGLPLUS_HANDLE_ERROR(error_code, MESSAGE, ERROR, ERROR_INFO) \
        }                                                                \
    }

#define EGLPLUS_GLFUNC_CHECK(FUNC_NAME, ERROR, ERROR_INFO) \
    EGLPLUS_HANDLE_ERROR_IF(                               \
      error_code != EGL_SUCCESS,                           \
      eglGetError(),                                       \
      ERROR::Message(error_code),                          \
      ERROR,                                               \
      ERROR_INFO.EGLFunc(FUNC_NAME))

#define EGLPLUS_CHECK(EGLFUNC, ERROR, ERROR_INFO) \
    EGLPLUS_GLFUNC_CHECK(#EGLFUNC, ERROR, ERROR_INFO)

#define EGLPLUS_CHECK_CTXT(ERROR, ERROR_INFO) \
    EGLPLUS_GLFUNC_CHECK(_errinf_glfn(), ERROR, ERROR_INFO)

#define EGLPLUS_CHECK_SIMPLE(EGLFUNC) EGLPLUS_CHECK(EGLFUNC, Error, NoInfo())

#if !OGPLUS_LOW_PROFILE
#define EGLPLUS_VERIFY(EGLFUNC, ERROR, ERROR_INFO) \
    EGLPLUS_CHECK(EGLFUNS, ERROR, ERROR_INFO)
#else
#define EGLPLUS_VERIFY(PARAM)
#endif

#define EGLPLUS_VERIFY_SIMPLE(EGLFUNC) EGLPLUS_CHECK(EGLFUNC, Error, NoInfo())

#define EGLPLUS_IGNORE(PARAM) ::eglGetError();

} // namespace eglplus

#if !EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)
#include <eglplus/error/basic.ipp>
#endif

#endif // include guard
