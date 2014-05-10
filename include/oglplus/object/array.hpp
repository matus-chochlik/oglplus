/**
 *  @file oglplus/object/array.hpp
 *  @brief Array data structure
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_ARRAY_1107121519_HPP
#define OGLPLUS_OBJECT_ARRAY_1107121519_HPP

#include <oglplus/fwd.hpp>
#include <oglplus/config.hpp>
#include <oglplus/object/tags.hpp>
#include <oglplus/object/name.hpp>
#include <oglplus/object/sequence.hpp>

#include <vector>
#include <cassert>

namespace oglplus {

/// Allows to allocate and manage several instances of Object at the same time
/**
 * This class is non-copyable.
 *
 *  @ingroup modifier_classes
 */
template <typename Object>
class Array
 : public ObjGenDelOps<typename ObjectTag<Object>::Type>
{
private:
	typedef typename ObjectTag<Object>::Type ObjTag;
	typedef ObjGenDelOps<ObjTag> GenDelOps;

	std::vector<GLuint> _names;

	/// Array is not copyable
	Array(const Array&);
public:

	/// Array is moveable
	Array(Array&& temp)
	 : _names(std::move(temp._names))
	{ }

	/// Constructs an an array of @p count instances of Object
	Array(std::size_t count)
	 : _names(count, 0u)
	{
		GenDelOps::Gen(GLsizei(_names.size()), _names.data());
	}

	~Array(void)
	{
		GenDelOps::Delete(GLsizei(_names.size()), _names.data());
	}

	/// Returns true if the array is empty
	bool empty(void) const
	{
		return _names.empty();
	}

	/// Returns the number of instances in the array
	std::size_t size(void) const
	{
		return _names.size();
	}

	/// Reference to elements
	typedef Reference<Object> reference;

	/// Reference to const elements
	typedef const reference const_reference;

	/// Returns a reference to the i-th instance in the array
	reference at(std::size_t index)
	{
		return reference(_names.at(index));
	}

	/// Returns a const reference to the i-th instance in the array
	const_reference at(GLuint index) const
	{
		return const_reference(_names.at(index));
	}

	/// Returns a reference to the i-th instance in the array
	reference operator[](std::size_t index)
	{
		return at(index);
	}

	/// Returns a const reference to the i-th instance in the array
	const_reference operator[](std::size_t index) const
	{
		return at(index);
	}

	/// Iterator type
	typedef SeqIterator<Object> iterator;

	/// Const-iterator type
	typedef iterator const_iterator;

	/// Returns an iterator pointing to the first element
	const_iterator begin(void) const
	{
		return const_iterator(_names.data());
	}

	/// Returns an iterator pointing past the last element
	const_iterator end(void) const
	{
		return const_iterator(_names.data()+_names.size());
	}

/*
	/// Returns a range allowing to traverse the instances in the array
	Range<Object> all(void) const;
*/
	Sequence<ObjectName<ObjTag>> seq(void) const
	{
		return Sequence<ObjectName<ObjTag>>(
			_names.data(),
			_names.size()
		);
	}

	operator Sequence<ObjectName<ObjTag>> (void) const
	{
		return seq();
	}
};

} // namespace oglplus

#endif // include guard
