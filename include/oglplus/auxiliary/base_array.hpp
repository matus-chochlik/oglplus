/**
 *  .file oglplus/auxiliary/base_array.hpp
 *  .brief Base classes for Array
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_AUX_BASE_ARRAY_1206141447_HPP
#define OGLPLUS_AUX_BASE_ARRAY_1206141447_HPP

#include <oglplus/object.hpp>
#include <oglplus/auxiliary/base_iter.hpp>
#include <oglplus/auxiliary/base_range.hpp>

#include <vector>
#include <cassert>

namespace oglplus {
namespace aux {

template <typename Object, bool MultiObject>
class BaseArray;

template <typename Object>
class BaseArray<Object, false>
{
private:
	std::vector<Object> _storage;
protected:
	BaseArray(GLsizei c)
	 : _storage(c)
	{ }

	BaseArray(BaseArray&& tmp)
	 : _storage(std::move(tmp.storage))
	{ }
public:
	typedef Object& reference;
	typedef const Object& const_reference;

	bool empty(void) const
	{
		return _storage.empty();
	}

	size_t size(void) const
	{
		return _storage.size();
	}

	const Object& front(void) const
	{
		return _storage.front();
	}

	const Object& back(void) const
	{
		return _storage.back();
	}

	reference at(GLuint index)
	{
		return _storage[index];
	}

	const_reference at(GLuint index) const
	{
		return _storage[index];
	}

	reference operator[](GLuint index)
	{
		return _storage[index];
	}

	const_reference operator[](GLuint index) const
	{
		return _storage[index];
	}

	typedef typename std::vector<Object>::const_iterator const_iterator;
	typedef const_iterator iterator;

	iterator begin(void) const
	{
		return _storage.begin();
	}

	iterator end(void) const
	{
		return _storage.end();
	}

	IterRange<iterator> all(void) const
	{
		return IterRange<iterator>(begin(), end());
	}
};

template <typename Object>
class MultiObjectBaseArray
 : public ObjectInitializer<Object>
{
protected:
	std::vector<GLuint> _names;
private:
	bool _names_ok(void) const
	{
		for(auto i=_names.begin(), e=_names.end(); i!=e; ++i)
		{
			if(*i == 0) return false;
			if(!this->_type_ok(*i)) return false;
		}
		return true;
	}

	void _init_names(void)
	{
		if(!_names.empty())
		{
			this->_init(_names.size(), _names.data());
			assert(_names_ok());
		}
	}
protected:
	MultiObjectBaseArray(GLsizei c)
	 : _names(c, 0)
	{
		_init_names();
	}

	MultiObjectBaseArray(MultiObjectBaseArray&& temp)
	 : _names(std::move(temp._names))
	{
		assert(_names_ok());
		assert(temp._names.empty());
	}

	~MultiObjectBaseArray(void)
	{
		if(!_names.empty())
		{
			assert(_names_ok());
			this->_cleanup(_names.size(), _names.data());
		}
	}
public:
	bool empty(void) const
	{
		return _names.empty();
	}

	size_t size(void) const
	{
		return _names.size();
	}
};

template <typename Object>
class BaseArray<Object, true>
 : public MultiObjectBaseArray<Object>
{
private:
	typedef MultiObjectBaseArray<Object> _base;
protected:
	BaseArray(GLsizei c)
	 : _base(c)
	{ }

	BaseArray(BaseArray&& temp)
	 : _base(static_cast<_base&&>(temp))
	{ }
public:
	typedef Managed<Object> reference;
	typedef Managed<Object> const_reference;

	const_reference front(void) const
	{
		return const_reference(this->_names.front());
	}

	const_reference back(void) const
	{
		return const_reference(this->_names.back());
	}

	const_reference at(GLuint index) const
	{
		assert(index < GLuint(this->size()));
		return const_reference(this->_names[index]);
	}

	const_reference operator [](GLuint index) const
	{
		return at(index);
	}

	typedef aux::BaseIter<const_reference, GLuint> const_iterator;
	typedef const_iterator iterator;

	iterator begin(void) const
	{
		return iterator(this->_names.begin(), this->_names.end());
	}

	iterator end(void) const
	{
		return iterator(this->_names.end());
	}

	aux::ArrayRange<const_reference> all(void) const
	{
		return aux::ArrayRange<const_reference>(begin(), end());
	}
};


} // namespace aux
} // namespace oglplus

#endif // include guard
