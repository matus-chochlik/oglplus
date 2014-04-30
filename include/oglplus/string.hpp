/**
 *  @file oglplus/string.hpp
 *  @brief String-related typedefs
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_1107121519_HPP
#define OGLPLUS_STRING_1107121519_HPP

#include <oglplus/config.hpp>

#include <string>
#include <cassert>

#if OGLPLUS_LAZY_STR_LIT
#include <cstring>
#endif

namespace oglplus {

/** @defgroup oglplus_strings Strings
 *
 *  Classes, types and functions in this group are related to text string
 *  and/or string literal handling.
 */

/// Checks if the range between @p begin and @p end is valid UTF-8 sequence
/**
 *  @ingroup oglplus_strings
 */
bool ValidString(const GLchar* begin, const GLchar* end);

/// String class
/**
 *  @ingroup oglplus_strings
 */
typedef ::std::basic_string<GLchar> String;

const String& EmptyString(void)
OGLPLUS_NOEXCEPT(true);

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

	std::size_t size(void) const
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
/** The literal optionally checks the source c-string literal
 *  for UTF-8 validity (which is required by the OpenGL specification
 *  for input string parameters of GL functions).
 *
 *  @see #OGLPLUS_NO_UTF8_CHECKS
 *
 *  @ingroup oglplus_strings
 */
class StrLit
{
private:
	const GLchar* _lit;
#if !OGLPLUS_LAZY_STR_LIT
	std::size_t _size;
#endif

	void _check(void) const
	{
		assert(ValidString(begin(), end()));
	}
public:
	/// Default constructor
	StrLit(void)
	 : _lit("")
#if !OGLPLUS_LAZY_STR_LIT
	 , _size(0)
#endif
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from nullptr
	StrLit(std::nullptr_t);
#elif !OGLPLUS_NO_NULLPTR
	StrLit(std::nullptr_t)
#else
	StrLit(int)
#endif
	 : _lit("")
#if !OGLPLUS_LAZY_STR_LIT
	 , _size(0)
#endif
	{ }

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Construction from a c-string @p literal
	/** The input @p literal can be optionally checked
	 *  for UTF-8 validity.
	 *
	 *  @see #OGLPLUS_NO_UTF8_CHECKS
	 */
	explicit StrLit(const GLchar* literal);
#elif !OGLPLUS_LAZY_STR_LIT
	template <std::size_t N>
	explicit StrLit(const GLchar (&lit)[N])
	 : _lit(lit)
	 , _size(N-1)
	{ _check(); }
#else
	explicit StrLit(const GLchar* lit)
	 : _lit(lit)
	{ _check(); }
#endif

	/// Construction from a c-string @p and a length
	/** The input @p literal can be optionally checked
	 *  for UTF-8 validity.
	 *
	 *  @see #OGLPLUS_NO_UTF8_CHECKS
	 */
	explicit StrLit(const GLchar* lit, std::size_t lit_size)
	 : _lit(lit)
#if !OGLPLUS_LAZY_STR_LIT
	 , _size(lit_size)
#endif
	{
		OGLPLUS_FAKE_USE(lit_size);
		_check();
	}

	/// Efficient conversion to String
	String str(void) const
	{
#if !OGLPLUS_LAZY_STR_LIT
		return String(_lit, _lit+_size);
#else
		return String(_lit);
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

	/// Returns the c-string literal
	const GLchar* c_str(void) const
	{
		return _lit;
	}

	/// Returns the size (in GLchars) of the literal
	std::size_t size(void) const
	{
#if !OGLPLUS_LAZY_STR_LIT
		return _size;
#else
		return std::strlen(_lit);
#endif
	}

	/// Returns true if the literal is empty
	bool empty(void) const
	{
#if !OGLPLUS_LAZY_STR_LIT
		return _size == 0;
#else
		return _lit[0] == '\0';
#endif
	}

	/// character iterator
	typedef const GLchar* iterator;

	/// character iterator
	typedef const GLchar* const_iterator;

	/// returns a const iterator to the first character in the literal
	const_iterator begin(void) const
	{
		return c_str();
	}

	/// returns a const iterator past the last character in the literal
	const_iterator end(void) const
	{
		return c_str()+size();
	}

	/// returns a const iterator to the first character in the literal
	friend const_iterator begin(const StrLit& strlit)
	{
		return strlit.begin();
	}

	/// returns a const iterator past the last character in the literal
	friend const_iterator end(const StrLit& strlit)
	{
		return strlit.end();
	}

	/// Equivalent to @c !empty()
	operator bool (void) const
	{
		return !empty();
	}

	/// Equivalent to the empty() function
	bool operator ! (void) const
	{
		return empty();
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Literal concatenation operator
	/** Returns an unspecified type explicitly convertible to String
	 */
	friend Unspecified operator + (StrLit a, StrLit b);
#endif

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

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/string.ipp>
#endif

#endif // include guard
