/**
 *  @file oglplus/object/sequence.hpp
 *  @brief Sequence of Object names
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_SEQUENCE_1405011014_HPP
#define OGLPLUS_OBJECT_SEQUENCE_1405011014_HPP

#include <oglplus/object/name.hpp>
#include <cstddef>
#include <cassert>

namespace oglplus {

/// Common base class for Object name sequences
template <typename ObjTag>
class Sequence<ObjectName<ObjTag>>
{
protected:
	friend const GLuint*
	GetGLNames<ObjectName<ObjTag>>(const Sequence&);

	const GLuint* _names;
	std::size_t _size;
public:
	Sequence(void)
	 : _names(nullptr)
	 , _size(0)
	{ }

	Sequence(const GLuint* names, std::size_t size)
	 : _names(names)
	 , _size(size)
	{ }

	/// Returns true if the sequence is empty
	bool empty(void) const
	{
		return _size == 0;
	}

	/// Returns the size of the sequence
	std::size_t size(void) const
	{
		return _size;
	}

	/// Returns the object name at the specified @p index
	ObjectName<ObjTag> at(std::size_t index) const
	{
		assert(index < _size);
		return ObjectName<ObjTag>(_names[index]);
	}

	/// Returns the object name at the specified @p index
	ObjectName<ObjTag> operator[](std::size_t index) const
	{
		return at(index);
	}

	/// Returns a subsequence starting at @p begin
	Sequence slice(std::size_t begin) const
	{
		assert(begin <= _size);
		return Sequence(_names+begin, _size-begin);
	}

	/// Returns a subsequence with the specified @p size starting at @p begin
	Sequence slice(std::size_t begin, std::size_t size) const
	{
		assert(begin + size <= _size);
		return Sequence(_names+begin, size);
	}
};

/// Returns a pointer to array of names stored in a @p sequence
template <typename ObjName>
inline const GLuint*
GetGLNames(const Sequence<ObjName>& sequence)
{
	return sequence._names;
}

} // namespace oglplus

#endif // include guard
