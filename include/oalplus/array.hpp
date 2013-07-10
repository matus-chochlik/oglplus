/**
 *  @file oalplus/array.hpp
 *  @brief Array of objects.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ARRAY_1303201647_HPP
#define OALPLUS_ARRAY_1303201647_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error.hpp>
#include <oalplus/object.hpp>
#include <oalplus/friend_of.hpp>

#include <oalplus/auxiliary/base_iter.hpp>
#include <oalplus/auxiliary/base_range.hpp>

#include <cassert>
#include <vector>

namespace oalplus {

template <typename Object>
class Array;

template <typename ObjectOps>
class Array<Object<ObjectOps> >
 : public ObjectInitializer<Object<ObjectOps> >
{
private:
	friend class FriendOf<Array<Object<ObjectOps> > >;

	std::vector<ALuint> _names;

	bool _names_ok(void) const
	{
		for(auto i=_names.begin(), e=_names.end(); i!=e; ++i)
		{
			if(*i == 0) return false;
			if(!this->_type_ok(*i)) return false;
		}
		return true;
	}
public:
	Array(ALsizei c)
	 : _names(c, 0)
	{
		if(!_names.empty())
		{
			this->_init(_names.size(), _names.data());
			assert(_names_ok());
		}
	}

	Array(Array&& temp)
	 : _names(std::move(temp._names))
	{
		assert(_names_ok());
		assert(temp._names.empty());
	}

	~Array(void)
	{
		if(!_names.empty())
		{
			assert(_names_ok());
			this->_cleanup(_names.size(), _names.data());
		}
	}

	bool empty(void) const
	{
		return _names.empty();
	}

	size_t size(void) const
	{
		return _names.size();
	}

	Managed<ObjectOps> front(void) const
	{
		return Managed<ObjectOps>(_names.front());
	}

	Managed<ObjectOps> back(void) const
	{
		return Managed<ObjectOps>(_names.back());
	}

	Managed<ObjectOps> at(ALuint index) const
	{
		assert(index < ALuint(size()));
		return Managed<ObjectOps>(_names[index]);
	}

	Managed<ObjectOps> operator [](ALuint index) const
	{
		return at(index);
	}

	typedef aux::BaseIter<Managed<ObjectOps>, ALuint> const_iterator;
	typedef const_iterator iterator;

	iterator begin(void) const
	{
		return iterator(_names.begin(), _names.end());
	}

	iterator end(void) const
	{
		return iterator(_names.end());
	}

	aux::ArrayRange<Managed<ObjectOps> > all(void) const
	{
		return aux::ArrayRange<Managed<ObjectOps> >(
			_names.begin(),
			_names.end()
		);
	}
};

template <typename Object>
class FriendOf<Array<Object> >
{
protected:
	static ALsizei GetSize(const Array<Object>& array)
	{
		return ALsizei(array._names.size());
	}

	const ALuint* GetNames(const Array<Object>& array)
	{
		return array._names.data();
	}

	ALuint* GetNames(Array<Object>& array)
	{
		return array._names.data();
	}
};

} // namespace oalplus

#endif // include guard
