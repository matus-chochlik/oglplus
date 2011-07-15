/**
 *  @file oglplus/error.hpp
 *  @brief Declaration of OpenGL++'s exceptions
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

struct ErrorInfo
{
	const char* file;
	const char* func;
	const unsigned line;
};

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

	friend void ThrowOnError(const ErrorInfo& info);
public:
	GLenum Code(void) const
	{
		return _code;
	}

	const ErrorInfo& ThrowInfo(void) const
	{
		return _info;
	}

	const char* File(void) const
	{
		return _info.file;
	}

	const char* Func(void) const
	{
		return _info.func;
	}

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

class OutOfMemory
 : public Error
{
public:
	OutOfMemory(GLenum code, const char* desc, const ErrorInfo& info)
	 : Error(code, desc, info)
	{ }
};

inline void ThrowOnError(const ErrorInfo& info)
{
	GLenum code = ::glGetError();
	if(code != GL_NO_ERROR)
	{
		const char* msg = "Unknown error";
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
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				msg = "Invalid OpenGL framebuffer operation";
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
