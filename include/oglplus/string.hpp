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

class StrLit;

namespace aux {

// helper class used for implementation of concatenation
template <typename Left, typename Right>
class StrLitCat
{
private:
	Left _left;
	Right _right;

public:
	StrLitCat(Left left, Right right)
	 : _left(left)
	 , _right(right)
	{ }

	bool empty(void) const
	{
		return _left.empty() && _right.empty();
	}

	size_t size(void) const
	{
		return _left.size() + _right.size();
	}

	void append_to(String& dest) const
	{
		_left.append_to(dest);
		_right.append_to(dest);
	}

	String str(void) const
	{
		String result;
		result.reserve(this->size()+1);
		this->append_to(result);
		return std::move(result);
	}

	inline explicit operator String(void) const
	{
		return str();
	}
};

} // namespace aux

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

	void append_to(String& dest) const
	{
#if !OGLPLUS_LAZY_STR_LIT
		dest.append(_lit, _lit+_size);
#else
		dest.append(_lit);
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

	friend aux::StrLitCat<StrLit, StrLit> operator + (StrLit a, StrLit b)
	{
		return aux::StrLitCat<StrLit, StrLit>(a, b);
	}

	template <typename Left, typename Right>
	friend aux::StrLitCat<aux::StrLitCat<Left, Right>, StrLit>
	operator + (aux::StrLitCat<Left, Right> a, StrLit b)
	{
		return aux::StrLitCat<aux::StrLitCat<Left, Right>,StrLit>(a, b);
	}
};

} // namespace oglplus

#endif // include guard
