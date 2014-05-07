/**
 *  @file oglplus/string/literal.hpp
 *  @brief String-literal wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_LITERAL_1107121519_HPP
#define OGLPLUS_STRING_LITERAL_1107121519_HPP

#include <oglplus/string/ref.hpp>
#include <oglplus/string/def.hpp>
#include <oglplus/config.hpp>

namespace oglplus {
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

	OGLPLUS_EXPLICIT operator String(void) const
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
	std::size_t _size;

	void _check(void) const
	{
		assert(ValidString(begin(), end()));
	}
public:
	/// Default constructor
	StrLit(void)
	 : _lit("")
	 , _size(0)
	{ }

	/// Construction from nullptr
	StrLit(std::nullptr_t)
	 : _lit("")
	 , _size(0)
	{ }

	/// Construction from a c-string @p literal
	/** The input @p literal can be optionally checked
	 *  for UTF-8 validity.
	 *
	 *  @see #OGLPLUS_NO_UTF8_CHECKS
	 */
	template <std::size_t N>
	explicit StrLit(const GLchar (&lit)[N])
	 : _lit(lit)
	 , _size(N-1)
	{ _check(); }

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
	const GLchar* c_str(void) const
	{
		return _lit;
	}

	/// Returns the size (in GLchars) of the literal
	std::size_t size(void) const
	{
		return _size;
	}

	/// Returns true if the literal is empty
	bool empty(void) const
	{
		return _size == 0;
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

	/// Conversion to String
	operator String (void) const
	{
		return String(begin(), size());
	}

	/// Conversion to string const reference
	operator StrCRef (void) const
	{
		return StrCRef(begin(), size());
	}
};

} // namespace oglplus

#endif // include guard
