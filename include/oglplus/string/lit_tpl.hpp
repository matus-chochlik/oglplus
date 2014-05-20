/**
 *  @file oglplus/string/lit_tpl.hpp
 *  @brief String-literal wrapper template
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_LIT_TPL_1107121519_HPP
#define OGLPLUS_STRING_LIT_TPL_1107121519_HPP

#include <oglplus/string/ref_tpl.hpp>

namespace oglplus {
namespace aux {

// helper class used for implementation of concatenation
template <typename Char, typename Left, typename Right>
class StrLitCatTpl
{
private:
	Left _left;
	Right _right;
public:
	StrLitCatTpl(Left left, Right right)
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

	void append_to(std::basic_string<Char>& dest) const
	{
		_left.append_to(dest);
		_right.append_to(dest);
	}

	std::basic_string<Char> str(void) const
	{
		std::basic_string<Char> result;
		result.reserve(this->size()+1);
		this->append_to(result);
		return result;
	}

	OGLPLUS_EXPLICIT operator std::basic_string<Char>(void) const
	{
		return str();
	}
};

} // namespace aux

/// String literal wrapper template
/** The literal optionally checks the source c-string literal
 *  for UTF-8 validity (which is required by the OpenGL specification
 *  for input string parameters of GL functions).
 *
 *  @see #OGLPLUS_NO_UTF8_CHECKS
 *
 *  @ingroup oglplus_strings
 */
template <typename Char>
class StrLitTpl
{
private:
	const Char* _lit;
	std::size_t _size;

	void _check(void) const
	{
		assert(aux::ValidUTF8(
			(const char*)begin(),
			(const char*)end()
		));
	}
public:
	/// Default constructor
	StrLitTpl(void)
	 : _lit("")
	 , _size(0)
	{ }

	/// Construction from nullptr
	StrLitTpl(std::nullptr_t)
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
	explicit StrLitTpl(const Char (&lit)[N])
	 : _lit(lit)
	 , _size(N-1)
	{ _check(); }

	StrLitTpl(const Char* lit, std::size_t n)
	 : _lit(lit)
	 , _size(n)
	{ _check(); }

	/// Efficient conversion to String
	std::basic_string<Char> str(void) const
	{
		return std::basic_string<Char>(_lit, _lit+_size);
	}

	void append_to(std::basic_string<Char>& dest) const
	{
		dest.append(_lit, _lit+_size);
	}

	/// Returns the c-string literal
	const Char* c_str(void) const
	{
		return _lit;
	}

	/// Returns the size (in Chars) of the literal
	std::size_t size(void) const
	{
		return _size;
	}

	/// Returns true if the literal is empty
	bool empty(void) const
	{
		return _size == 0;
	}

	/// Character iterator
	typedef const Char* iterator;

	/// Character iterator
	typedef const Char* const_iterator;

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
	friend const_iterator begin(const StrLitTpl& strlit)
	{
		return strlit.begin();
	}

	/// returns a const iterator past the last character in the literal
	friend const_iterator end(const StrLitTpl& strlit)
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
	friend Unspecified operator + (StrLitTpl a, StrLitTpl b);
#endif

	friend aux::StrLitCatTpl<Char, StrLitTpl, StrLitTpl>
	operator + (StrLitTpl a, StrLitTpl b)
	{
		return aux::StrLitCatTpl<Char, StrLitTpl, StrLitTpl>(a, b);
	}

	template <typename Left, typename Right>
	friend aux::StrLitCatTpl<Char, aux::StrLitCatTpl<Char, Left, Right>, StrLitTpl>
	operator + (aux::StrLitCatTpl<Char, Left, Right> a, StrLitTpl b)
	{
		return aux::StrLitCatTpl<
			Char,
			aux::StrLitCatTpl<Char, Left, Right>,
			StrLitTpl
		>(a, b);
	}

	/// Conversion to String
	operator ::std::basic_string<Char> (void) const

	{
		return ::std::basic_string<Char>(begin(), size());
	}

	/// Conversion to string const reference
	operator StrCRefTpl<Char> (void) const
	{
		return StrCRef(begin(), size());
	}
};

} // namespace oglplus

#endif // include guard
