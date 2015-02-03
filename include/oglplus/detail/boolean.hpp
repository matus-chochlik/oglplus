/**
 *  .file oglplus/detail/boolean.hpp
 *  .brief Implementation of wrapper for booleans
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DETAIL_BOOLEAN_1501311633_HPP
#define OGLPLUS_DETAIL_BOOLEAN_1501311633_HPP

#include <oglplus/config/compiler.hpp>
#include <stdexcept>
#include <new>

namespace oglplus {

template <typename T, T TrueVal, T FalseVal>
struct BoolImpl
{
private:
	T _v;
public:
	// implementation detail
	inline
	T _get(void) const
	noexcept
	{
		return _v;
	}

	// implementation detail
	inline
	T* _ptr(void)
	noexcept
	{
		return &_v;
	}

	BoolImpl(void)
	noexcept
	 : _v(T(FalseVal))
	{ }

	BoolImpl(bool bv)
	noexcept
	 : _v(bv?TrueVal:FalseVal)
	{ }

	BoolImpl(T v, std::nothrow_t)
	noexcept
	 : _v(v)
	{ }

	explicit
	BoolImpl(T v)
	 : _v(v)
	{
		if((_v != TrueVal) && (_v != FalseVal))
		{
			throw std::domain_error(
				"Invalid value for Boolean"
			);
		}
	}

	operator bool (void) const
	noexcept
	{
		return _v == TrueVal;
	}

	bool operator ! (void) const
	noexcept
	{
		return _v == FalseVal;
	}
};

} // namespace oglplus

#endif // include guard
