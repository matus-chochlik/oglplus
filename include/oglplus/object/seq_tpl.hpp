/**
 *  @file oglplus/object/seq_tpl.hpp
 *  @brief Implementation of Sequence of Object names
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_OBJECT_SEQ_TPL_1405011014_HPP
#define OGLPLUS_OBJECT_SEQ_TPL_1405011014_HPP

#include <cstddef>
#include <cassert>

namespace oglplus {
namespace aux {

/// Object sequence iterator template
template <
	typename ObjectT,
	typename NameT,
	typename ObjTag,
	template <class> class NameTpl
> class SeqIterTpl
{
private:
	const NameT* _pos;
public:
	SeqIterTpl(const NameT* pos)
	 : _pos(pos)
	{ }

	/// Equality comparison
	friend bool operator == (SeqIterTpl a, SeqIterTpl b)
	{
		return a._pos == b._pos;
	}

	/// Inequality comparison
	friend bool operator != (SeqIterTpl a, SeqIterTpl b)
	{
		return a._pos != b._pos;
	}

	/// Ordering
	friend bool operator <  (SeqIterTpl a, SeqIterTpl b)
	{
		return a._pos <  b._pos;
	}

	/// Value type
	typedef ObjectT value_type;

	/// Difference type
	typedef std::ptrdiff_t difference_type;

	/// Distance
	friend difference_type operator - (SeqIterTpl a, SeqIterTpl b)
	{
		return a._pos - b._pos;
	}

	/// Dereference
	value_type operator * (void) const
	{
		assert(_pos != nullptr);
		return ObjectT(ObjectName<ObjTag>(*_pos));
	}

	/// Array access
	value_type operator [](std::size_t index) const
	{
		assert(_pos != nullptr);
		return ObjectT(ObjectName<ObjTag>(_pos[index]));
	}

	/// Preincrement
	SeqIterTpl& operator ++ (void)
	{
		++_pos;
		return *this;
	}

	/// Postincrement
	SeqIterTpl operator ++ (int)
	{
		return SeqIterTpl(_pos++);
	}

	/// Predecrement
	SeqIterTpl& operator -- (void)
	{
		--_pos;
		return *this;
	}

	/// Postdecrement
	SeqIterTpl operator -- (int)
	{
		return SeqIterTpl(_pos--);
	}

	/// Positive offset
	friend SeqIterTpl operator + (SeqIterTpl a, difference_type d)
	{
		return SeqIterTpl(a._pos+d);
	}

	/// Positive offset
	SeqIterTpl& operator += (difference_type d)
	{
		_pos += d;
		return *this;
	}

	/// Negative offset
	friend SeqIterTpl operator - (SeqIterTpl a, difference_type d)
	{
		return SeqIterTpl(a._pos-d);
	}

	/// Negative offset
	SeqIterTpl& operator -= (difference_type d)
	{
		_pos -= d;
		return *this;
	}
};

/// Common base class for Object name sequences
template <typename NameT, typename ObjTag, template <class> class NameTpl>
class SeqTpl
{
protected:
	const NameT* _names;
	std::size_t _size;
public:
	SeqTpl(void)
	 : _names(nullptr)
	 , _size(0)
	{ }

	SeqTpl(const NameT* names, std::size_t count)
	 : _names(names)
	 , _size(count)
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
	NameTpl<ObjTag> at(std::size_t index) const
	{
		assert(index < _size);
		return NameTpl<ObjTag>(_names[index]);
	}

	/// Returns the object name at the specified @p index
	NameTpl<ObjTag> operator[](std::size_t index) const
	{
		return at(index);
	}

	/// Returns a subsequence starting at @p start
	SeqTpl slice(std::size_t start) const
	{
		assert(start <= _size);
		return SeqTpl(_names+start, _size-start);
	}

	/// Returns a subsequence with the specified @p count starting at @p start
	SeqTpl slice(std::size_t start, std::size_t count) const
	{
		assert(start + count <= _size);
		return SeqTpl(_names+start, count);
	}

	typedef SeqIterTpl<
		NameTpl<ObjTag>,
		NameT,
		ObjTag,
		NameTpl
	> const_iterator;

	/// Position at the beginning of the sequence
	const_iterator begin(void) const
	{
		return const_iterator(_names);
	}

	/// Position past the end of the sequence
	const_iterator end(void) const
	{
		return const_iterator(_names+_size);
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard
