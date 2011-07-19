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
class Managed
 : public ObjectOps
 , public FriendOf<ObjectOps>
{
private:
	Managed(void)
	{ }

	Managed(GLuint _name)
	{
		FriendOf<ObjectOps>::SetName(*this, _name);
	}

	friend class Array<Object<ObjectOps, true> >;
	friend class aux::BaseIter<Managed>;
public:
	~Managed(void)
	{
		FriendOf<ObjectOps>::SetName(*this, 0);
	}
};

template <class ObjectOps>
class Array<Object<ObjectOps, true> >
{
private:
	std::vector<GLuint> _names;

	bool _names_ok(void) const
	{
		for(auto i=_names.begin(), e=_names.end(); i!=e; ++i)
		{
			if(*i == 0) return false;
			if(!object::_type_ok(*i)) return false;
		}
		return true;
	}

	typedef Object<ObjectOps, true> object;
public:
	inline Array(GLsizei c)
	 : _names(c, 0)
	{
		if(!_names.empty())
		{
			object::_do_init(_names.size(), *_names.data());
			assert(_names_ok());
		}
	}

	Array(const Array&) = delete;

	inline Array(Array&& temp)
	 : _names(std::move(temp._names))
	{
		assert(_names_ok());
		assert(temp._names.empty());
	}

	inline ~Array(void)
	{
		if(!_names.empty())
		{
			assert(_names_ok());
			object::_do_cleanup(_names.size(), *_names.data());
		}
	}

	bool empty(void) const
	{
		return _names.empty();
	}

	GLsizei size(void) const
	{
		return _names.size();
	}


	Managed<ObjectOps> at(GLuint index) const
	{
		assert(index < size());
		return Managed<ObjectOps>(_names[index]);
	}

	Managed<ObjectOps> operator [](GLuint index) const
	{
		return at(index);
	}

	typedef aux::BaseIter<Managed<ObjectOps> > iterator;

	iterator begin(void) const
	{
		return iterator(_names.begin(), _names.end());
	}

	iterator end(void) const
	{
		return iterator(_names.end());
	}
};

} // namespace oglplus

#endif // include guard
