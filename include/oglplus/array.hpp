/**
 *  @file oglplus/array.hpp
 *  @brief Array data structure
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ARRAY_1107121519_HPP
#define OGLPLUS_ARRAY_1107121519_HPP

#include <oglplus/config.hpp>
#include <oglplus/object.hpp>
#include <oglplus/auxiliary/base_array.hpp>

#include <vector>
#include <cassert>

namespace oglplus {

template <class Object>
class Array;

#if OGLPLUS_DOCUMENTATION_ONLY
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
public
	/// Unspecified type usable as reference to Object
	typedef Unspecified reference;

	/// Unspecified type usable as const reference to Object
	typedef Unspecified const_reference;

	/// Constructor specifying the number of instance in the array
	Array(GLsizei c);

	/// Returns true if the array is empty
	bool empty(void) const;

	/// Returns the number of instances in the array
	size_t size(void) const;

	/// Returns a reference to the i-th instance in the array
	reference at(GLuint index);

	/// Returns a const reference to the i-th instance in the array
	const_reference at(GLuint index) const;

	/// Returns a reference to the i-th instance in the array
	reference operator[](GLuint index);

	/// Returns a const reference to the i-th instance in the array
	const_reference operator[](GLuint index) const;

	/// Iterator type
	typedef ForwardIterator iterator;

	/// Const-iterator type
	typedef ForwardIterator const_iterator;

	/// Returns an iterator pointing to the first element
	const_iterator begin(void) const;

	/// Returns an iterator pointing after the last element
	const_iterator end(void) const;

	/// Returns a range allowing to traverse the instances in the array
	Range<Object> all(void) const;
};
#else

template <typename ObjectOps>
class Array<Object<ObjectOps> >
 : public aux::BaseArray<
	Object<ObjectOps>,
	ObjectOps::IsMultiObject::value
>
{
private:
	typedef aux::BaseArray<
		Object<ObjectOps>,
		ObjectOps::IsMultiObject::value
	> BaseArray;
public:
	Array(GLsizei c)
	 : BaseArray(c)
	{ }

	Array(Array&& tmp)
	 : BaseArray(std::move(tmp))
	{ }

#if !OGLPLUS_NO_DELETED_FUNCTIONS
	Array(const Array&) = delete;
#else
private:
	Array(const Array&);
public:
#endif
};

#endif

} // namespace oglplus

#endif // include guard
