/**
 *  @file oglplus/array.hpp
 *  @brief Array data structure
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_ARRAY_1107121519_HPP
#define OGLPLUS_ARRAY_1107121519_HPP

#include <oglplus/object.hpp>
#include <oglplus/auxiliary/base_iter.hpp>

namespace oglplus {

template <class Object>
class Array;

template <class ObjectOps>
class Array<Object<ObjectOps> >
{
private:
	GLsizei _count;
	GLuint _base;

	GLuint _release(void)
	{
		GLuint res = _base;
		_count = 0;
		_base = 0;
		return res;
	}
	typedef Object<ObjectOps> object;
public:
	inline Array(GLsizei c)
	 : _count(c)
	{
		object::_do_init(_count, _base);
	}

	Array(const Array&) = delete;

	inline Array(Array&& temp)
	 : _count(temp._count)
	 , _base(temp._release())
	{ }

	inline ~Array(void)
	{
		if(_count && _base)
			object::_do_cleanup(_count, _base);
	}

	GLsizei size(void) const
	{
		return _count;
	}


	ObjectOps at(GLuint index) const
	{
		assert(index < size());
		return ObjectOps(index + _base);
	}

	ObjectOps operator [](GLuint index) const
	{
		return at(index);
	}

	typedef aux::BaseIter<ObjectOps> iterator;

	iterator begin(void) const
	{
		return iterator(0, _base);
	}

	iterator end(void) const
	{
		return iterator(_count, _base);
	}
};

} // namespace oglplus

#endif // include guard
