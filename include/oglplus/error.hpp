/**
 *  @file oglplus/error.hpp
 *  @brief Declaration of OpenGL+'s exceptions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ERROR_1107121317_HPP
#define OGLPLUS_ERROR_1107121317_HPP

#include <stdexcept>
#include <list>

#define OGLPLUS_ERROR_INFO() {__FILE__, __FUNCTION__, __LINE__}

namespace oglplus {

/// Basic information about exception's throw site and propagation trace points
struct ErrorInfo
{
	/// The source file name
	const char* file;
	/// The function pretty name
	const char* func;
	/// The source file line
	const unsigned line;
};

/// Exception class for general OpenGL errors
/** Instances of this exception class are throws whenever an error is detected
 *  during the execution of OpenGL API calls in the OGL+ code. There are several
 *  other classes derived for more specific error types, like GL shading language
 *  compilation and linking errors, out-of-memory errors, etc.
 *  This class is derived from the standard runtime_error exception and thus
 *  the basic error message can be obtained by calling its @c what() member function.
 */
class Error
 : public std::runtime_error
{
private:
	GLenum _code;
	ErrorInfo _info;
	std::list<ErrorInfo> _prop_info;
protected:
	Error(GLenum code, const char* desc, const ErrorInfo& info)
	 : std::runtime_error(desc)
	 , _code(code)
	 , _info(info)
	{ }

	friend void ThrowOnError(
		GLenum code,
		const GLchar* msg,
		const ErrorInfo& info
	);
	friend void ThrowOnError(const ErrorInfo& info);
public:
	/// Returns the OpenGL error code
	/** This is basically the value of error code returned by the glGetError
	 *  functions.
	 *
	 *  @see ThrowInfo
	 *  @see File
	 *  @see Func
	 *  @see Line
	 */
	GLenum Code(void) const
	{
		return _code;
	}

	/// Returns information about the throw site of the exception
	/**
	 *  @see Code
	 *  @see File
	 *  @see Func
	 *  @see Line
	 */
	const ErrorInfo& ThrowInfo(void) const
	{
		return _info;
	}

	/// Returns the path of the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see Code
	 *  @see Func
	 *  @see Line
	 */
	const char* File(void) const
	{
		return _info.file;
	}

	/// Returns the name of the function where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see Code
	 *  @see Name
	 *  @see Line
	 */
	const char* Func(void) const
	{
		return _info.func;
	}

	/// Returns the line in the source file where the exception originated
	/**
	 *  @see ThrowInfo
	 *  @see Code
	 *  @see Name
	 *  @see Func
	 */
	unsigned Line(void) const
	{
		return _info.line;
	}

	typedef std::list<ErrorInfo> propagation_info_list;

	const propagation_info_list& PropagationInfo(void) const
	{
		return _prop_info;
	}

	Error& Trace(const ErrorInfo& info)
	{
		_prop_info.push_back(info);
		throw;
	}
};

/// Exception class for out-of-memory OpenGL errors
/** Out-of-memory is a very serious error and applications generally should not
 *  try to recover from such errors, but terminate gracefully if possible.
 */
class OutOfMemory
 : public Error
{
public:
	OutOfMemory(GLenum code, const char* desc, const ErrorInfo& info)
	 : Error(code, desc, info)
	{ }
};

inline void ThrowOnError(GLenum code, const GLchar* msg, const ErrorInfo& info)
{
	throw Error(code, msg, info);
}

inline void ThrowOnError(const ErrorInfo& info)
{
	GLenum code = ::glGetError();
	if(code != GL_NO_ERROR)
	{
		const GLchar* msg = "Unknown error";
		switch(code)
		{
			case GL_OUT_OF_MEMORY:
				msg = "OpenGL out of memory";
				throw OutOfMemory(code, msg, info);
			case GL_INVALID_ENUM:
				msg = "Invalid OpenGL enum argument";
				break;
			case GL_INVALID_VALUE:
				msg = "OpenGL numeric argument out of range";
				break;
			case GL_INVALID_OPERATION:
				msg = "Invalid OpenGL operation";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				msg = "Invalid OpenGL framebuffer operation";
				break;
		}
		throw Error(code, msg, info);
	}
}

inline void AssertNoError(const ErrorInfo& info)
{
	//TODO make this compile-time configurable
	ThrowOnError(info);
}

} // namespace oglplus

#endif // include guard
