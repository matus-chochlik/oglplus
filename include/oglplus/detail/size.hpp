/**
 *  .file oglplus/detail/size.hpp
 *  .brief Implementation of wrapper for sizei
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DETAIL_SIZE_1501311633_HPP
#define OGLPLUS_DETAIL_SIZE_1501311633_HPP

#include <oglplus/config/compiler.hpp>
#include <type_traits>
#include <stdexcept>
#include <cstddef>
#include <limits>
#include <new>

namespace oglplus {

template <typename T>
struct SizeImpl
{
private:
	T _v;

	template <typename X>
	static
	typename std::enable_if<(sizeof(T) <= sizeof(X)), T>::type
	_chkin2(X v)
	{
		if(v > X(std::numeric_limits<T>::max()))
		{
			throw std::domain_error("Size value too big");
		}
		return T(v);
	}

	template <typename X>
	static
	typename std::enable_if<(sizeof(T) > sizeof(X)), T>::type
	_chkin2(X v)
	{
		if(std::numeric_limits<X>::max()>std::numeric_limits<T>::max())
		{
			if(T(v) > std::numeric_limits<T>::max())
			{
				throw std::domain_error("Size value too big");
			}
		}
		return T(v);
	}

	template <typename X>
	static inline
	typename std::enable_if<std::is_signed<X>::value, T>::type
	_chkin1(X v)
	{
		if(v < X(0))
		{
			throw std::domain_error("Negative size value");
		}
		return _chkin2(v);
	}

	template <typename X>
	static inline
	typename std::enable_if<!std::is_signed<X>(), T>::type
	_chkin1(X v)
	{
		return _chkin2(v);
	}

	template <typename X>
	static inline
	T _checkin(X v)
	{
		return _chkin1(v);
	}
public:
	SizeImpl(void)
	OGLPLUS_NOEXCEPT(true)
	 : _v(T(0))
	{ }

	SizeImpl(T v, std::nothrow_t)
	OGLPLUS_NOEXCEPT(true)
	 : _v(v)
	{ }

	SizeImpl(T v)
	 : _v(_checkin(v))
	{ }

	template <typename X>
	explicit
	SizeImpl(X v)
	 : _v(_checkin(v))
	{ }

	OGLPLUS_EXPLICIT
	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v >= T(0);
	}

	bool operator ! (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v < T(0);
	}

	operator T (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v;
	}
};

} // namespace oglplus

#endif // include guard
