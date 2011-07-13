/**
 *  .file oglplus/auxiliary/base_iter.hpp
 *  .brief Base class for Array iterators
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_BASE_ITER_1107121519_HPP
#define OGLPLUS_AUX_BASE_ITER_1107121519_HPP

#include <cassert>

namespace oglplus {
namespace aux {

template <typename Element>
class BaseIter
{
private:
	GLsizei _index;
	GLuint _base;

	Element _elem;

	void init_elem(void)
	{
	}

	static bool equal(const BaseIter& a, const BaseIter& b)
	{
		assert(a._base == b._base);
		return a._index == b._index;
	}

	static bool less(const BaseIter& a, const BaseIter& b)
	{
		assert(a._base == b._base);
		return a._index < b._index;
	}
public:
	BaseIter(GLsizei _i, GLuint _h)
	 : _index(_i)
	 , _base(_h)
	 , _elem(_index + _base)
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
		++_index;
		_elem = Element(_index + _base);
		return *this;
	}

	BaseIter operator ++(int)
	{
		GLuint tmp = _index++;
		return BaseIter(tmp + _base);
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
