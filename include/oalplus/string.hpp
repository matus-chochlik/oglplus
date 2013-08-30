/**
 *  @file oalplus/string.hpp
 *  @brief String-related typedefs
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_STRING_1303291951_HPP
#define OALPLUS_STRING_1303291951_HPP

#include <oalplus/config.hpp>

#include <oglplus/auxiliary/utf8.hpp>

#include <string>
#include <cassert>

namespace oalplus {

/// String class
/**
 *  @ingroup oalplus_strings
 */
typedef ::std::basic_string<ALchar> String;

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
	OALPLUS_NOEXCEPT(true)
	 : _left(left)
	 , _right(right)
	{ }

	bool empty(void) const
	OALPLUS_NOEXCEPT(true)
	{
		return _left.empty() && _right.empty();
	}

	std::size_t size(void) const
	OALPLUS_NOEXCEPT(true)
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
		return result;
	}

#if !OGLPLUS_NO_EXPLICIT_CONVERSION_OPERATORS
	inline explicit operator String(void) const
#else
	inline operator String(void) const
#endif
	{
		return str();
	}
};

} // namespace aux

/// String literal wrapper
/**
 *  @ingroup oalplus_strings
 */
class StrLit
{
private:
	const ALchar* _lit;
	std::size_t _size;

	void _check(void) const
	{
		oglplus::aux::UTF8Validator valid_utf8;
		assert(valid_utf8(begin(), end()));
	}
public:
	/// Default constructor
	StrLit(void)
	 : _lit("")
	 , _size(0)
	{ }

#if OALPLUS_DOCUMENTATION_ONLY
	/// Construction from a c-string @p literal
	explicit StrLit(const ALchar* literal);
#else
	template <std::size_t N>
	explicit StrLit(const ALchar (&lit)[N])
	OALPLUS_NOEXCEPT(true)
	 : _lit(lit)
	 , _size(N-1)
	{ _check(); }
#endif

	/// Construction from a c-string @p and a length
	explicit StrLit(const ALchar* lit, std::size_t lit_size)
	OALPLUS_NOEXCEPT(true)
	 : _lit(lit)
	 , _size(lit_size)
	{
		_check();
	}

	/// Efficient conversion to String
	String str(void) const
	{
		return String(_lit, _lit+_size);
	}

	void append_to(String& dest) const
	{
		dest.append(_lit, _lit+_size);
	}

	/// Returns the c-string literal
	const ALchar* c_str(void) const
	OALPLUS_NOEXCEPT(true)
	{
		return _lit;
	}

	/// Returns the size (in ALchars) of the literal
	std::size_t size(void) const
	OALPLUS_NOEXCEPT(true)
	{
		return _size;
	}

	/// Returns true if the literal is empty
	bool empty(void) const
	OALPLUS_NOEXCEPT(true)
	{
		return _size == 0;
	}

	/// character iterator
	typedef const ALchar* iterator;

	/// character iterator
	typedef const ALchar* const_iterator;

	/// returns a const iterator to the first character in the literal
	const_iterator begin(void) const
	OALPLUS_NOEXCEPT(true)
	{
		return c_str();
	}

	/// returns a const iterator past the last character in the literal
	const_iterator end(void) const
	OALPLUS_NOEXCEPT(true)
	{
		return c_str()+size();
	}

	/// returns a const iterator to the first character in the literal
	friend const_iterator begin(const StrLit& strlit)
	OALPLUS_NOEXCEPT(true)
	{
		return strlit.begin();
	}

	/// returns a const iterator past the last character in the literal
	friend const_iterator end(const StrLit& strlit)
	OALPLUS_NOEXCEPT(true)
	{
		return strlit.end();
	}

	/// Equivalent to @c !empty()
	operator bool (void) const
	OALPLUS_NOEXCEPT(true)
	{
		return !empty();
	}

	/// Equivalent to the empty() function
	bool operator ! (void) const
	OALPLUS_NOEXCEPT(true)
	{
		return empty();
	}

#if OALPLUS_DOCUMENTATION_ONLY
	/// Literal concatenation operator
	/** Returns an unspecified type explicitly convertible to String
	 */
	friend Unspecified operator + (StrLit a, StrLit b);
#endif

	friend aux::StrLitCat<StrLit, StrLit> operator + (StrLit a, StrLit b)
	OALPLUS_NOEXCEPT(true)
	{
		return aux::StrLitCat<StrLit, StrLit>(a, b);
	}

	template <typename Left, typename Right>
	friend aux::StrLitCat<aux::StrLitCat<Left, Right>, StrLit>
	operator + (aux::StrLitCat<Left, Right> a, StrLit b)
	OALPLUS_NOEXCEPT(true)
	{
		return aux::StrLitCat<aux::StrLitCat<Left, Right>,StrLit>(a, b);
	}
};

} // namespace oalplus

#endif // include guard
