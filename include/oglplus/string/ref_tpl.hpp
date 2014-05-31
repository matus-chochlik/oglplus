/**
 *  @file oglplus/string/ref_tpl.hpp
 *  @brief String reference
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_REF_TPL_1107121519_HPP
#define OGLPLUS_STRING_REF_TPL_1107121519_HPP

#include <oglplus/string/utf8.hpp>
#include <oglplus/config/compiler.hpp>
#include <string>
#include <cstring>
#include <cstddef>
#include <cassert>

namespace oglplus {

/// String const reference wrapper template
template <typename Char>
class StrCRefTpl
{
private:
	static_assert(
		sizeof(Char) == sizeof(char),
		"Characters with different size that sizeof(char) "
		"are not supported by StrCRefTpl"
	);

	const Char* _c_str;
	mutable std::size_t _size;

	static const Char* _ecs(void)
	OGLPLUS_NOEXCEPT(true)
	{ return ""; }

	void _validate(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(aux::ValidUTF8(
			(const char*)begin(),
			(const char*)end()
		));
	}
public:
	/// Default construction (reference to an empty c-string)
	StrCRefTpl(void)
	OGLPLUS_NOEXCEPT(true)
	 : _c_str(nullptr)
	 , _size(0)
	{ }

	/// Construction from a null-terminated string
	StrCRefTpl(const Char* cstr)
	OGLPLUS_NOEXCEPT(true)
	 : _c_str(cstr)
	 , _size(0)
	{ _validate(); }

	/// Construction from a c-string and size
	StrCRefTpl(const Char* cstr, std::size_t ssize)
	OGLPLUS_NOEXCEPT(true)
	 : _c_str(cstr)
	 , _size(ssize)
	{ _validate(); }

	/// Construction from a std::string
	StrCRefTpl(const std::string& sstr)
	OGLPLUS_NOEXCEPT(true)
	 : _c_str(sstr.c_str())
	 , _size(sstr.size())
	{ _validate(); }

	/// Return the size (length) string
	std::size_t size(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		if((_size == 0) && (_c_str != nullptr))
			_size = std::strlen(_c_str);
		return _size;
	}

	/// Returns true if the string is empty
	bool empty(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return size() == 0;
	}

	/// Iterator type
	typedef const Char* iterator;
	/// Const iterator type
	typedef iterator const_iterator;

	/// Returns iterator to the first character
	const_iterator begin(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _c_str?_c_str:_ecs();
	}

	/// Returns iterator past the last character
	const_iterator end(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return begin()+size();
	}

	/// Returns true if the string is null-terminated
	bool is_nts(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return *end() == '\0';
	}

	/// Returns a String
	std::basic_string<Char> str(void) const
	{
		return std::basic_string<Char>(begin(), end());
	}

	/// Returns the null-terminated c-string
	/**
	 *  @pre is_nts()
	 */
	const Char* c_str(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		assert(is_nts());
		return begin();
	}
};

} // namespace oglplus

#endif // include guard
