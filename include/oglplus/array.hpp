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

#include <oglplus/config.hpp>
#include <oglplus/object.hpp>
#include <oglplus/auxiliary/base_iter.hpp>
#include <oglplus/auxiliary/base_range.hpp>

#include <vector>
#include <cassert>

namespace oglplus {

/// Allows to allocate and manage several instances of Object at the same time
/**
 *
 * This class is non-copyable.
 *
 *  @ingroup modifier_classes
 */
template <class Object>
class Array
{
private:
	std::vector<Object> _storage;
public:
	/// Constructor specifying the number of instance in the array
	Array(GLsizei c)
	 : _storage(c)
	{ }

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	Array(const Array&) = delete;
#else
private:
	Array(const Array&);
public:
#endif

	/// Returns true if the array is empty
	bool empty(void) const
	{
		return _storage.empty();
	}

	/// Returns the number of instances in the array
	GLsizei size(void) const
	{
		return _storage.size();
	}

	/// Returns a reference to the i-th instance in the array
	const Object& at(GLuint index) const
	{
		return _storage[index];
	}

	/// Returns a reference to the i-th instance in the array
	const Object& operator[](GLuint index) const
	{
		return _storage[index];
	}

	/// Iterator type
	typedef typename std::vector<Object>::const_iterator iterator;

	/// Returns an iterator pointing to the first element
	iterator begin(void) const
	{
		return _storage.begin();
	}

	/// Returns an iterator pointing after the last element
	iterator end(void) const
	{
		return _storage.end();
	}

#if OGLPLUS_DOCUMENTATION_ONLY
	/// Returns a range allowing to traverse the instances in the array
	Range<Object> all(void) const;
#else
	aux::IterRange<iterator> all(void) const
	{
		return aux::IterRange<iterator>(begin(), end());
	}
#endif
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
protected:
	GLuint _get_name(size_t index) const
	{
		return _names[index];
	}
public:
	inline Array(GLsizei c)
	 : _names(c, 0)
	{
		if(!_names.empty())
		{
			object::_do_init(_names.size(), _names.data());
			assert(_names_ok());
		}
	}

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	Array(const Array&) = delete;
#else
private:
	Array(const Array&);
public:
#endif

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
			object::_do_cleanup(_names.size(), _names.data());
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
		assert(index < GLuint(size()));
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

#if OGLPLUS_DOCUMENTATION_ONLY
	Range<Object> all(void) const;
#else
	aux::ArrayRange<Managed<ObjectOps> > all(void) const
	{
		return aux::ArrayRange<Managed<ObjectOps> >(begin(), end());
	}
#endif
};

} // namespace oglplus

#endif // include guard
