/**
 *  @file oalplus/object/sequence.hpp
 *  @brief Sequence of Object names
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_OBJECT_SEQUENCE_1405011014_HPP
#define OALPLUS_OBJECT_SEQUENCE_1405011014_HPP

#include <oalplus/object/name.hpp>
#include <oalplus/object/seq_tpl.hpp>
#include <cstddef>
#include <cassert>

namespace oalplus {

template <typename ObjName>
const ALuint* GetALNames(const Sequence<ObjName>&);

/// Object sequence iterator template
template <typename ObjectT>
class SeqIterator;

template <typename OpsTag, typename ObjTag>
class SeqIterator<ObjectOps<OpsTag, ObjTag>>
 : public aux::SeqIterTpl<
	Reference<ObjectOps<OpsTag, ObjTag>>,
	ALuint,
	ObjTag,
	ObjectName
>
{
private:
	typedef aux::SeqIterTpl<
		Reference<ObjectOps<OpsTag, ObjTag>>,
		ALuint,
		ObjTag,
		ObjectName
	> Base;
public:
	SeqIterator(const ALuint* pos)
	 : Base(pos)
	{ }
};

template <typename ObjectOps>
class SeqIterator<Object<ObjectOps>>
 : public SeqIterator<ObjectOps>
{
public:
	SeqIterator(const ALuint* pos)
	 : SeqIterator<ObjectOps>(pos)
	{ }
};

/// Common base class for Object name sequences
template <typename ObjTag>
class Sequence<ObjectName<ObjTag>>
 : public aux::SeqTpl<ALuint, ObjTag, ObjectName>
{
protected:
	friend const ALuint*
	GetALNames<ObjectName<ObjTag>>(const Sequence&);

	typedef aux::SeqTpl<ALuint, ObjTag, ObjectName> Base;
public:
	Sequence(void)
	 : Base()
	{ }

	Sequence(const ALuint* names, std::size_t count)
	 : Base(names, count)
	{ }
};

/// Returns a pointer to array of names stored in a @p sequence
template <typename ObjName>
inline const ALuint*
GetALNames(const Sequence<ObjName>& sequence)
{
	return sequence._names;
}

} // namespace oalplus

#endif // include guard
