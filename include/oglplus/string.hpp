/**
 *  @file oglplus/string.hpp
 *  @brief String-related typedefs
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_STRING_1107121519_HPP
#define OGLPLUS_STRING_1107121519_HPP

#include <oglplus/config.hpp>
#include <string>

#if OGLPLUS_LAZY_STR_LIT
#include <cstring>
#endif

namespace oglplus {

/// String class
typedef ::std::basic_string<GLchar> String;

/// String literal wrapper
class StrLit
{
private:
	const GLchar* _lit;
#if !OGLPLUS_LAZY_STR_LIT
	size_t _size;
#endif
public:
	StrLit(void)
	 : _lit("")
#if !OGLPLUS_LAZY_STR_LIT
	 , _size(0)
#endif
	{ }

#if !OGLPLUS_NO_NULLPTR
	StrLit(std::nullptr_t)
#else
	StrLit(int)
#endif
	 : _lit("")
#if !OGLPLUS_LAZY_STR_LIT
	 , _size(0)
#endif
	{ }

#if !OGLPLUS_LAZY_STR_LIT
	template <size_t N>
	explicit StrLit(const GLchar (&lit)[N])
	OGLPLUS_NOEXCEPT(true)
	 : _lit(lit)
	 , _size(N-1)
	{ }
#else
	explicit StrLit(const GLchar* lit)
	OGLPLUS_NOEXCEPT(true)
	 : _lit(lit)
	{ }
#endif

	String str(void) const
	{
#if !OGLPLUS_LAZY_STR_LIT
		return std::move(String(_lit, _lit+_size));
#else
		return std::move(String(_lit));
#endif
	}

	const GLchar* c_str(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _lit;
	}

	size_t size(void) const
	OGLPLUS_NOEXCEPT(true)
	{
#if !OGLPLUS_LAZY_STR_LIT
		return _size;
#else
		return std::strlen(_lit);
#endif
	}

	bool empty(void) const
	OGLPLUS_NOEXCEPT(true)
	{
#if !OGLPLUS_LAZY_STR_LIT
		return _size == 0;
#else
		return _lit[0] == '\0';
#endif
	}

	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return empty();
	}

	bool operator ! (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return !empty();
	}

	friend String operator + (StrLit a, StrLit b)
	{
		String result;
		result.reserve(a.size()+b.size()+1);
		result.append(a.c_str(), a.size());
		result.append(b.c_str(), b.size());
		return std::move(result);
	}

	friend String operator + (String a, StrLit b)
	{
		a.append(b.c_str(), b.size());
		return a;
	}
};

} // namespace oglplus

#endif // include guard
