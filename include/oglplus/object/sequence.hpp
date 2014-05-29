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
#include <oglplus/object/seq_tpl.hpp>
#include <cstddef>
#include <cassert>

namespace oglplus {

template <typename ObjName>
const GLuint* GetGLNames(const Sequence<ObjName>&);

/// Object sequence iterator template
template <typename ObjectT>
class SeqIterator;

template <typename OpsTag, typename ObjTag>
class SeqIterator<ObjectOps<OpsTag, ObjTag>>
 : public aux::SeqIterTpl<
	Reference<ObjectOps<OpsTag, ObjTag>>,
	GLuint,
	ObjTag,
	ObjectName
>
{
private:
	typedef aux::SeqIterTpl<
		Reference<ObjectOps<OpsTag, ObjTag>>,
		GLuint,
		ObjTag,
		ObjectName
	> Base;
public:
	SeqIterator(const GLuint* pos)
	 : Base(pos)
	{ }
};

template <typename ObjectOps>
class SeqIterator<Object<ObjectOps>>
 : public SeqIterator<ObjectOps>
{
public:
	SeqIterator(const GLuint* pos)
	 : SeqIterator<ObjectOps>(pos)
	{ }
};

/// Common base class for Object name sequences
template <typename ObjTag>
class Sequence<ObjectName<ObjTag>>
 : public aux::SeqTpl<GLuint, ObjTag, ObjectName>
{
protected:
	friend const GLuint*
	GetGLNames<ObjectName<ObjTag>>(const Sequence&);

	typedef aux::SeqTpl<GLuint, ObjTag, ObjectName> Base;
public:
	Sequence(void)
	 : Base()
	{ }

	Sequence(const GLuint* names, std::size_t count)
	 : Base(names, count)
	{ }
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
