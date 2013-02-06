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

#include <oglplus/config.hpp>
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
	bool empty(void) const
	{
		return _storage.empty();
	}

	size_t size(void) const
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

template <typename ObjectOps>
class BaseArray<Object<ObjectOps>, true>
 : public ObjectInitializer<Object<ObjectOps> >
{
private:
	std::vector<GLuint> _names;

	bool _names_ok(void) const
	{
		for(auto i=_names.begin(), e=_names.end(); i!=e; ++i)
		{
			if(*i == 0) return false;
			if(!this->_type_ok(*i)) return false;
		}
		return true;
	}
protected:
	GLuint _get_name(size_t index) const
	{
		return _names[index];
	}

	BaseArray(GLsizei c)
	 : _names(c, 0)
	{
		if(!_names.empty())
		{
			this->_init(_names.size(), _names.data());
			assert(_names_ok());
		}
	}

	BaseArray(BaseArray&& temp)
	 : _names(std::move(temp._names))
	{
		assert(_names_ok());
		assert(temp._names.empty());
	}

	~BaseArray(void)
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

	Managed<ObjectOps> at(GLuint index) const
	{
		assert(index < GLuint(size()));
		return Managed<ObjectOps>(_names[index]);
	}

	Managed<ObjectOps> operator [](GLuint index) const
	{
		return at(index);
	}

	typedef aux::BaseIter<Managed<ObjectOps> > const_iterator;
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
		return aux::ArrayRange<Managed<ObjectOps> >(begin(), end());
	}
};


} // namespace aux
} // namespace oglplus

#endif // include guard
