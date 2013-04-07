/**
 *  .file oglplus/auxiliary/base_iter.hpp
 *  .brief Base class for Array iterators
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_BASE_ITER_1107121519_HPP
#define OGLPLUS_AUX_BASE_ITER_1107121519_HPP

#include <vector>
#include <cassert>

namespace oglplus {
namespace aux {

template <typename Element, typename NameType>
class BaseIter
{
private:
	typedef typename std::vector<NameType>::const_iterator iterator;
	iterator _pos;

	Element _elem;

	static bool equal(const BaseIter& a, const BaseIter& b)
	{
		return a._pos == b._pos;
	}

	static bool less(const BaseIter& a, const BaseIter& b)
	{
		return a._pos < b._pos;
	}
public:
	BaseIter(iterator i)
	 : _pos(i)
	{ }

	BaseIter(iterator i, iterator e)
	 : _pos(i)
	 , _elem(i == e ? 0 : *i)
	{ }

	friend bool operator == (const BaseIter& a, const BaseIter& b)
	{
		return equal(a, b);
	}

	friend bool operator != (const BaseIter& a, const BaseIter& b)
	{
		return !equal(a, b);
	}

	friend bool operator <= (const BaseIter& a, const BaseIter& b)
	{
		return less(a, b) || equal(a, b);
	}

	friend bool operator >= (const BaseIter& a, const BaseIter& b)
	{
		return !less(a, b);
	}

	friend bool operator <  (const BaseIter& a, const BaseIter& b)
	{
		return less(a, b);
	}

	friend bool operator >  (const BaseIter& a, const BaseIter& b)
	{
		return !less(a, b) && !equal(a, b);
	}

	Element& operator * (void)
	{
		return _elem;
	}

	const Element& operator * (void) const
	{
		return _elem;
	}

	Element* operator -> (void)
	{
		return &_elem;
	}

	const Element* operator -> (void) const
	{
		return &_elem;
	}

	BaseIter& operator ++(void)
	{
		_elem = Element(*++_pos);
		return *this;
	}

	BaseIter operator ++(int)
	{
		iterator tmp = _pos;
		_elem = Element(*++_pos);
		return BaseIter(*tmp);
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
