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

namespace oglplus {

/// String class
typedef ::std::basic_string<GLchar> String;

/// String literal wrapper
class StrLit
{
private:
	const GLchar* _lit;
	size_t _size;
public:
	StrLit(void)
	 : _lit("")
	 , _size(0)
	{ }

	StrLit(std::nullptr_t)
	 : _lit("")
	 , _size(0)
	{ }

	template <size_t N>
	explicit StrLit(const GLchar (&lit)[N])
	OGLPLUS_NOEXCEPT(true)
	 : _lit(lit)
	 , _size(N-1)
	{ }

	String&& str(void) const
	{
		return std::move(String(_lit, _lit+_size));
	}

	const GLchar* c_str(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _lit;
	}

	const size_t size(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _size;
	}

	const bool empty(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _size == 0;
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
};

} // namespace oglplus

#endif // include guard
