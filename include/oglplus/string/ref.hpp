/**
 *  @file oglplus/string/ref.hpp
 *  @brief String reference
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_STRING_REF_1107121519_HPP
#define OGLPLUS_STRING_REF_1107121519_HPP

#include <string>
#include <cstring>
#include <cstddef>
#include <cassert>

namespace oglplus {

/// String const reference wrapper
class StrCRef
{
private:
	const char* _c_str;
	mutable std::size_t _size;

	static const char* _ecs(void) { return ""; }
public:
	/// Default construction (reference to an empty c-string)
	StrCRef(void)
	 : _c_str(nullptr)
	 , _size(0)
	{ }

	/// Construction from a null-terminated string
	StrCRef(const char* cstr)
	 : _c_str(cstr)
	 , _size(0)
	{ }

	/// Construction from a c-string and size
	StrCRef(const char* cstr, std::size_t ssize)
	 : _c_str(cstr)
	 , _size(ssize)
	{ }

	/// Construction from a std::string
	StrCRef(const std::string& str)
	 : _c_str(str.c_str())
	 , _size(str.size())
	{ }

	/// Return the size (length) string
	std::size_t size(void) const
	{
		if((_size == 0) && (_c_str != nullptr))
			_size = std::strlen(_c_str);
		return _size;
	}

	/// Returns true if the string is empty
	bool empty(void) const
	{
		return size() == 0;
	}

	/// Iterator type
	typedef const char* iterator;
	/// Const iterator type
	typedef iterator const_iterator;

	/// Returns iterator to the first character
	const_iterator begin(void) const
	{
		return _c_str?_c_str:_ecs();
	}

	/// Returns iterator past the last character
	const_iterator end(void) const
	{
		return begin()+size();
	}

	/// Returns true if the string is null-terminated
	bool is_nts(void) const
	{
		return *end() == '\0';
	}

	/// Returns the null-terminated c-string
	/**
	 *  @pre is_nts()
	 */
	const char* c_str(void) const
	{
		assert(is_nts());
		return begin();
	}
};

} // namespace oglplus

#endif // include guard
