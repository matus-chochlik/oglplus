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

namespace oglplus {

class Error
 : public std::runtime_error
{
private:
	GLenum _code;
protected:
	Error(GLenum _c, const char* _desc)
	 : std::runtime_error(_desc)
	 , _code(_c)
	{ }

	Error(GLenum _c, const std::string& _desc)
	 : std::runtime_error(_desc)
	 , _code(_c)
	{ }

	friend void ThrowOnError(void);
public:
	GLenum code(void) const
	{
		return _code;
	}
};

class OutOfMemory
 : public Error
{
public:
	OutOfMemory(GLenum _c, const char* _desc)
	 : Error(_c, _desc)
	{ }
};

inline void ThrowOnError(void)
{
	GLenum code = ::glGetError();
	if(code != GL_NO_ERROR)
	{
		const char* msg = "Unknown error";
		switch(code)
		{
			case GL_OUT_OF_MEMORY:
				msg = "OpenGL out of memory";
				throw OutOfMemory(code, msg);
			case GL_INVALID_ENUM:
				msg = "Invalid OpenGL enum argument";
				break;
			case GL_INVALID_VALUE:
				msg = "OpenGL numeric argument out of range";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				msg = "Invalid OpenGL framebuffer operation";
		}
		throw Error(code, msg);
	}
}

inline void AssertNoError(void)
{
	//TODO make this compile-time configurable
	ThrowOnError();
}

} // namespace oglplus

#endif // include guard
