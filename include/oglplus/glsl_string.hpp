/**
 *  @file oglplus/glsl_string.hpp
 *  @brief Helper classes for passing source code in GLSL as parameters
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_GLSL_STRING_1207111232_HPP
#define OGLPLUS_GLSL_STRING_1207111232_HPP

#include <oglplus/config/compiler.hpp>
#include <oglplus/string/ref.hpp>
#include <oglplus/string/literal.hpp>

#include <utility>
#include <vector>
#include <array>
#include <cassert>

namespace oglplus {

/// Class for passing a single string as a Source to a Shader
class GLSLString
{
private:
	const GLchar* _str;
	GLint _len;

	GLSLString(const GLSLString&);
public:
	GLSLString(const GLchar* str)
	OGLPLUS_NOEXCEPT(true)
	 : _str(str)
	 , _len(-1)
	{ }

	template <std::size_t N>
	GLSLString(const GLchar (&str)[N])
	OGLPLUS_NOEXCEPT(true)
	 : _str(str)
	 , _len(N)
	{ }

	GLSLString(const String& str)
	 : _str(str.c_str())
	 , _len(GLint(str.size()))
	{ }

	GLSLString(const StrLit& lit)
	 : _str(lit.c_str())
	 , _len(GLint(lit.size()))
	{ }

	GLSLString(const std::vector<GLchar>& v)
	 : _str(v.data())
	 , _len(GLint(v.size()))
	{ }

	GLsizei Count(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return 1;
	}

	const GLchar** Parts(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return const_cast<const GLchar**>(&_str);
	}

	const GLint* Lengths(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return (_len<0)?(nullptr):(&_len);
	}
};


/// Class for passing a set of strings as a Source to a Shader
class GLSLStrings
{
private:
	GLsizei _count;
	const GLchar** _strs;
	const GLint* _lens;

	GLSLStrings(const GLSLStrings&);
public:
	GLSLStrings(GLsizei count, const GLchar** strs)
	OGLPLUS_NOEXCEPT(true)
	 : _count(count)
	 , _strs(strs)
	 , _lens(nullptr)
	{ }

	template <std::size_t N>
	GLSLStrings(const GLchar* (&strs)[N])
	OGLPLUS_NOEXCEPT(true)
	 : _count(GLsizei(N))
	 , _strs(strs)
	 , _lens(nullptr)
	{ }

	GLSLStrings(const std::vector<const GLchar*>& v)
	 : _count(GLsizei(v.size()))
	 , _strs(const_cast<const GLchar**>(v.data()))
	 , _lens(nullptr)
	{ }

	template <std::size_t N>
	GLSLStrings(const std::array<const GLchar*, N>& a)
	 : _count(GLsizei(a.size()))
	 , _strs(const_cast<const GLchar**>(a.data()))
	 , _lens(nullptr)
	{ }

	GLsizei Count(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _count;
	}

	const GLchar** Parts(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _strs;
	}

	const GLint* Lengths(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _lens;
	}
};

} // namespace oglplus

#endif // include guard
