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

#include <vector>
#include <cassert>

namespace oglplus {

template <class Object>
class Array
{
private:
	std::vector<Object> _storage;
public:
	Array(GLsizei c)
	 : _storage(c)
	{ }

	Array(const Array&) = delete;

	bool empty(void) const
	{
		return _storage.empty();
	}

	GLsizei size(void) const
	{
		return _storage.size();
	}

	const Object& at(GLuint index) const
	{
		return _storage[index];
	}

	const Object& operator[](GLuint index) const
	{
		return _storage[index];
	}

	typedef typename std::vector<Object>::const_iterator iterator;

	iterator begin(void) const
	{
		return _storage.begin();
	}

	iterator end(void) const
	{
		return _storage.end();
	}
};

template <class ObjectOps>
class Array<Object<ObjectOps, true> >
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
	typedef Object<ObjectOps, true> object;
public:
	inline Array(GLsizei c)
	 : _count(c)
	 , _base(0)
	{
		assert(_count != 0);
		object::_do_init_m(_count, _base);
		assert(_base != 0);
		assert(object::_type_ok(_base));
	}

	Array(const Array&) = delete;

	inline Array(Array&& temp)
	 : _count(temp._count)
	 , _base(temp._release())
	{
		assert(_base != 0);
		assert(object::_type_ok(_base));
	}

	inline ~Array(void)
	{
		if(_count && _base)
		{
			assert(object::_type_ok());
			object::_do_cleanup(_count, _base);
		}
	}

	bool empty(void) const
	{
		return _count == 0;
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
